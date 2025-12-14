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

#include "steppable/stpTypeName.hpp"
#include "tree_sitter/api.h"

#include <any>
#include <memory>

namespace steppable::parser
{
    /**
     * @brief Determine if a binary operation can be done.
     *
     * @param node The entire binary expression node.
     * @param lhsType The `STP_TypeID` value for the LHS node.
     * @param operatorStr The operator between LHS and RHS.
     * @param rhsType The `STP_TypeID` value for the RHS node.
     * @return std::unique_ptr<STP_TypeID> If the operation can be done, returns a `unique_ptr` to the `STP_TypeID` of
     * the returning value. Otherwise, a `nullptr` is returned.
     */
    std::unique_ptr<STP_TypeID> determineBinaryOperationFeasibility(const TSNode* node,
                                                                    STP_TypeID lhsType,
                                                                    const std::string& operatorStr,
                                                                    STP_TypeID rhsType);

    /**
     * @brief Performs a binary operation.
     *
     * @note This function does not check for the operation feasibility. Check with
     * `determineBinaryOperationFeasibility()` first.
     *
     * @param node The entire binary expression node.
     * @param lhsType The `STP_TypeID` value for the LHS node.
     * @param value The `std::any` value for the LHS node.
     * @param operatorStr The operator between LHS and RHS.
     * @param rhsType The `STP_TypeID` value for the RHS node.
     * @param rhsValue The `std::any` value for the RHS node.
     * @return std::any The value of LHS after the operation is done.
     */
    std::any performBinaryOperation(const TSNode* node,
                                    STP_TypeID lhsType,
                                    std::any value,
                                    std::string operatorStr,
                                    STP_TypeID rhsType,
                                    std::any rhsValue);

    /**
     * @brief Performs a unary operation.
     *
     * @param node The entire unary expression node.
     * @param type The `STP_TypeID` value for the expression node.
     * @param operatorString The unary operator to apply.
     * @param value The value of the expression node.
     * @return std::any The result of the operation done.
     */
    std::any performUnaryOperation(const TSNode* node,
                                   STP_TypeID type,
                                   const std::string& operatorString,
                                   const std::any& value);
} // namespace steppable::parser
