/**************************************************************************************************
 * Copyright (c) 2023-2025 NWSOFT                                                                 *
 *                                                                                                *
 * Permission is hereby granted, free of charge, to any person obtaining a copy                   *
 * of this software and associated documentation files (the "Software"), to deal                  *
 * in the Software without restriction, including without limitation the rights                   *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                      *
 * copies of the Software, and to permit persons to whom the Software is                          *
 * furnished to do so, subject to the following conditions:                                       *
 *                                                                                                *
 * The above copyright notice and this permission notice shall be included in all                 *
 * copies or substantial portions of the Software.                                                *
 *                                                                                                *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                     *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                       *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE                    *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                         *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,                  *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE                  *
 * SOFTWARE.                                                                                      *
 **************************************************************************************************/

#include "stpInterp/stpExprHandler.hpp"

#include "steppable/number.hpp"
#include "steppable/stpArgSpace.hpp"
#include "steppable/stpTypeName.hpp"
#include "stpInterp/stpBetterTS.hpp"
#include "stpInterp/stpInit.hpp"
#include "stpInterp/stpStore.hpp"

#include <cassert>
#include <cstdint>

using namespace std::literals;

namespace steppable::parser
{
    STP_Value STP_handleExpr(const TSNode* exprNode,
                             const STP_InterpState& state,
                             const bool printResult,
                             const std::string& exprName)
    {
        if (state->getExecState() == STP_ExecState::REQUEST_STOP)
            return STP_Value(STP_TypeID::NONE);

        assert(exprNode != nullptr);
        std::string exprType = ts_node_type(*exprNode);

        STP_Value retVal(STP_TypeID::NONE);

        if (exprType == "number")
        {
            // Number
            std::string data = state->getChunk(exprNode);
            retVal = STP_Value(STP_TypeID::NUMBER, Number(data));
        }
        if (exprType == "percentage")
        {
            // percentage := number "%"
            TSNode numberNode = ts_node_child(*exprNode, 0);
            std::string number = state->getChunk(&numberNode);
            Number value(number);
            value /= 100; // NOLINT(*-avoid-magic-numbers)

            retVal = STP_Value(STP_TypeID::NUMBER, value);
        }
        if (exprType == "matrix")
            retVal = STP_handleMatrixExpr(exprNode, state);
        if (exprType == "string")
            retVal = STP_handleStringExpr(exprNode, state);
        if (exprType == "identifier_or_member_access")
        {
            TSNode nameNode = ts_node_child(*exprNode, 0);
            std::string childNodeType = ts_node_type(nameNode);

            // Get the variable
            if (childNodeType == "identifier")
            {
                std::string identifierName = state->getChunk(&nameNode);
                retVal = state->getCurrentScope()->getVariable(&nameNode, identifierName);
            }
        }
        if (exprType == "function_call")
            retVal = STP_processFnCall(exprNode, state);
        if (exprType == "binary_expression")
        {
            // binary_expression := lhs 'operator' rhs
            TSNode binExprNode = ts_node_child(*exprNode, 0);
            TSNode lhsNode = ts_node_child(binExprNode, 0);
            TSNode operatorNode = ts_node_child(ts_node_child(binExprNode, 1), 0);
            TSNode rhsNode = ts_node_child(binExprNode, 2);

            std::string operatorType = ts_node_type(operatorNode);
            STP_Value lhs = STP_handleExpr(&lhsNode, state);

            if (lhs.typeID == STP_TypeID::NONE)
            {
                retVal = STP_Value(STP_TypeID::NONE, nullptr);
                goto end;
            }

            STP_Value rhs = STP_handleExpr(&rhsNode, state);

            if (rhs.typeID == STP_TypeID::NONE)
            {
                retVal = STP_Value(STP_TypeID::NONE, nullptr);
                goto end;
            }

            retVal = lhs.applyBinaryOperator(exprNode, operatorType, rhs);
        }
        if (exprType == "unary_expression")
        {
            TSNode operandNode = ts_node_child(*exprNode, 0);
            TSNode child = ts_node_child(*exprNode, 1);
            std::string operandType = ts_node_type(operandNode);

            STP_Value childVal = STP_handleExpr(&child, state);
            retVal = childVal.applyUnaryOperator(exprNode, operandType);
        }
        if (exprType == "bracketed_expr")
        {
            TSNode innerExpr = ts_node_child(*exprNode, 1);
            retVal = STP_handleExpr(&innerExpr, state);
        }
        if (exprType == "range_expr")
            retVal = STP_handleRangeExpr(exprNode, state);
        if (exprType == "suffix_expression")
            retVal = STP_handleSuffixExpr(exprNode, state);

    end:
        if (printResult and retVal.typeID != STP_TypeID::NONE)
            std::cout << retVal.present(exprName) << '\n';

        return retVal;
    }

    std::vector<STP_Argument> STP_extractArgVector(const TSNode* exprNode, const STP_InterpState& state)
    {
        std::vector<STP_Argument> fnArgsVec;
        TSNode posArgumentsNode = ts_node_named_child(*exprNode, 1);
        if (not ts_node_is_null(posArgumentsNode))
        {
            uint32_t posArgumentsCount = ts_node_named_child_count(posArgumentsNode);

            for (uint32_t i = 0; i < posArgumentsCount; i++)
            {
                TSNode argNode = ts_node_named_child(posArgumentsNode, i);
                STP_Value res = STP_handleExpr(&argNode, state);
                STP_Argument argument("", res.data, res.typeID);
                fnArgsVec.emplace_back(argument);
            }

            TSNode kwArgumentsNode = ts_node_named_child(*exprNode, 2);
            if (not ts_node_is_null(kwArgumentsNode))
            {
                uint32_t keywordArgumentCount = ts_node_named_child_count(kwArgumentsNode);
                for (uint32_t i = 0; i < keywordArgumentCount; i++)
                {
                    TSNode argNode = ts_node_named_child(kwArgumentsNode, i);
                    TSNode argNameNode = ts_node_child_by_field_name(argNode, "argument_name"s);
                    TSNode argExprNode = ts_node_next_named_sibling(argNameNode);

                    std::string argName = state->getChunk(&argNameNode);

                    STP_Value res = STP_handleExpr(&argExprNode, state);
                    STP_Argument argument(argName, res.data, res.typeID);
                    fnArgsVec.emplace_back(argument);
                }
            }
        }

        return fnArgsVec;
    }

} // namespace steppable::parser
