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
 * @file subtractReport.hpp
 * @brief This file contains the declaration of the reportSubtract function, which reports the result of a
 * subtraction to the user.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 */

#pragma once

#include <string>
#include <vector>

/**
 * @brief Reports a subtraction operation to the user.
 *
 * @param[in] aInteger The integer part of the first number.
 * @param[in] aDecimal The decimal part of the first number.
 * @param[in] bInteger The integer part of the second number.
 * @param[in] bDecimal The decimal part of the second number.
 * @param[in] aIsDecimal Whether the first number has a decimal part.
 * @param[in] bIsDecimal Whether the second number has a decimal part.
 * @param[in] _diffDigits The digits of their difference.
 * @param[in] borrows The borrowed digits.
 * @param[in] steps The steps to show while reporting.
 * @param[in] resultIsNegative Whether the result should be negative.
 * @param[in] noMinus Whether to show the minus sign.
 *
 * @return The formatted subtraction report.
 */
std::string reportSubtract(const std::string& aInteger,
                           const std::string& aDecimal,
                           const std::string& bInteger,
                           const std::string& bDecimal,
                           bool aIsDecimal,
                           bool bIsDecimal,
                           const std::vector<int>& _diffDigits,
                           const std::vector<int>& borrows,
                           int steps,
                           bool resultIsNegative,
                           bool noMinus = false);
