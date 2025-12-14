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

#include "steppable/mat2d.hpp"
#include "stpInterp/stpBetterTS.hpp"
#include "stpInterp/stpErrors.hpp"
#include "stpInterp/stpExprHandler.hpp"
#include "stpInterp/stpInit.hpp"
#include "stpInterp/stpStore.hpp"

using namespace std::literals;
using namespace steppable::utils;

namespace steppable::parser
{
    STP_Value STP_handleSuffixExpr(const TSNode* exprNode, const STP_InterpState& state)
    {
        TSNode opNode = ts_node_child_by_field_name(*exprNode, "operator"s);
        TSNode valueNode = ts_node_prev_sibling(opNode);
        STP_Value value = STP_handleExpr(&valueNode, state);

        STP_Value retValue(value.typeID, value.data);

        char op = *ts_node_type(opNode);

        switch (op)
        {
        case '\'':
        {
            // Matrix transpose
            if (value.typeID != STP_TypeID::MATRIX_2D)
            {
                STP_throwError(*exprNode, state, "Cannot perform transpose on a non-matrix object"s);
                programSafeExit(1);
            }

            auto mat = std::any_cast<Matrix>(value.data);
            mat = mat.transpose();
            retValue = STP_Value(STP_TypeID::MATRIX_2D, mat);
            break;
        }
        case '!':
        {
            // Factorial
            if (value.typeID == STP_TypeID::NUMBER)
            {
                auto num = std::any_cast<Number>(value.data);
                num = calc::factorial(num.present(), 0);
                retValue = STP_Value(STP_TypeID::NUMBER, num);
            }
            else if (value.typeID == STP_TypeID::MATRIX_2D)
            {
                auto mat = std::any_cast<Matrix>(value.data);
                mat = mat.apply([&](const Number& item, const YXPoint& /*unused*/) -> Number {
                    return calc::factorial(item.present(), 0);
                });
                retValue = STP_Value(STP_TypeID::MATRIX_2D, mat);
            }
            else
            {
                STP_throwError(*exprNode, state, "Factorial can only be applied to matrices and numbers"s);
                programSafeExit(1);
            }
            break;
        }
        default:
        {
            // Should not reach here
        }
        }
        return retValue;
    }
} // namespace steppable::parser
