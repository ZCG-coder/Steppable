/**************************************************************************************************
 * Copyright (c) 2023-2024 NWSOFT                                                                 *
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

/**
 * @file multiplyReport.hpp
 * @brief This file contains the declaration for function reportMultiply, which reports the result of a multiplication
 * operation to the user.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 */
#pragma once

#include <string>
#include <vector>

/**
 * @brief Reports a multiplication operation to the user.
 *
 * @param[in] a Number 1.
 * @param[in] b Number 2.
 * @param[in] aStr Modified number 1.
 * @param[in] bStr Modified number 2.
 * @param[in] aStr Decimal part of number 1.
 * @param[in] bStr Decimal part of number 2.
 * @param[in] finalProdDigits The final product digits.
 * @param[in] finalProdCarries The final product's carries.
 * @param[in] prodDigitsOut The product digits for each step.
 * @param[in] carries The carries for each step.
 * @param[in] resultIsNegative Whether the result should be negative.
 * @param[in] scale The scale of the result.
 * @param[in] steps The steps to show while reporting.
 *
 * @return The formatted multiplication report.
 */
std::string reportMultiply(const std::string& a,
                           const std::string& b,
                           const std::string& aStr,
                           const std::string& bStr,
                           const std::string& aDecimal,
                           const std::string& bDecimal,
                           const std::vector<int>& finalProdDigits,
                           const std::vector<int>& finalProdCarries,
                           const std::vector<std::vector<int>>& prodDigitsOut,
                           const std::vector<std::vector<int>>& carries,
                           bool resultIsNegative = false,
                           int steps = 2);
