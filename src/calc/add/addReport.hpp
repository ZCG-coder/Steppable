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

/**
 * @file addReport.hpp
 * @brief This file contains the declaration of the reportAdd function, which reports the sum of two number strings
 * together.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 */

#pragma once

#include <string>
#include <vector>

/**
 * @brief Reports the sum of two number strings.
 *
 * @param[in] aInteger The integer part of the first number.
 * @param[in] aDecimal The decimal part of the first number.
 * @param[in] bInteger The integer part of the second number.
 * @param[in] bDecimal The decimal part of the second number.
 * @param[in] sumDigits The digits of the sum.
 * @param[in] carries The carries of the sum.
 * @param[in] resultIsNegative Whether the result is negative.
 * @param[in] steps The number of steps to show.
 * @param[in] properlyFormat Whether to properly format the output.
 *
 * @return The reported string.
 */
std::string reportAdd(const std::string& aInteger,
                      const std::string& aDecimal,
                      const std::string& bInteger,
                      const std::string& bDecimal,
                      const std::vector<int>& sumDigits,
                      const std::vector<bool>& carries,
                      bool resultIsNegative,
                      int steps,
                      bool properlyFormat);
