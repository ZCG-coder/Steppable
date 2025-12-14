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

#pragma once
#include "stpInit.hpp"
#include "stpStore.hpp"

namespace steppable::parser
{
    /**
     * @brief Handle a string expression.
     *
     * @param exprNode Expression node.
     * @param state State of the interpreter.
     *
     * @return A `std::string` wrapped in `STP_Value`.
     */
    STP_Value STP_handleStringExpr(const TSNode* exprNode, const STP_InterpState& state);

    /**
     * @brief Handle a matrix expression.
     *
     * @param exprNode Expression node.
     * @param state State of the interpreter.
     *
     * @return A `steppable::Matrix` wrapped in `STP_Value`.
     */
    STP_Value STP_handleMatrixExpr(const TSNode* exprNode, const STP_InterpState& state);

    /**
     * @brief Handle a range expression.
     * @details A range expression is a matrix shorthand for writing `[start start+step start+2*step ... end]`
     *
     * @param exprNode Expression node.
     * @param state State of the interpreter.
     *
     * @return A `steppable::Matrix` wrapped in `STP_Value`.
     */
    STP_Value STP_handleRangeExpr(const TSNode* exprNode, const STP_InterpState& state);

    /**
     * @brief Handle a suffix expression.
     *
     * @param exprNode Expression node.
     * @param state State of the interpreter.
     *
     * @return A `STP_Value` object for the result of the suffix expression.
     */
    STP_Value STP_handleSuffixExpr(const TSNode* exprNode, const STP_InterpState& state);

    /**
     * @brief Process a function call node to extract all arguments it is called with.
     *
     * @param exprNode The function call expression node.
     * @param state Current state of the interpreter.
     *
     * @return The arguments passed to the function as a vector.
     */
    std::vector<STP_Argument> STP_extractArgVector(const TSNode* exprNode, const STP_InterpState& state);

    /**
     * @brief Handle a function call expression.
     *
     * @param exprNode Expression node.
     * @param state State of the interpreter.
     *
     * @return A `STP_Value` object for the return value of the function.
     */
    STP_Value STP_processFnCall(const TSNode* exprNode, const STP_InterpState& state);

    /**
     * @brief Handle any Steppable expressions.
     *
     * @param exprNode Expression node.
     * @param state State of the interpreter.
     * @param printResult Whether to print out the result of the operation.
     * @param exprName The name of the variable to which the expression is assigned to.
     */
    STP_Value STP_handleExpr(const TSNode* exprNode,
                             const STP_InterpState& state,
                             bool printResult = false,
                             const std::string& exprName = "");
} // namespace steppable::parser
