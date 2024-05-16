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
 * @file comparisonReport.hpp
 * @brief This file contains the declarations of the functions reportComparisonAtInteger, reportComparisonByPolarity and
 * reportComparisonByDigit, which reports the result of the comparision from the integer part, polarity and digit
 * respectively.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 */

#pragma once

#include <cstddef>
#include <string>
#include <string_view>

/**
 * @brief Reports the comparison based on the integer. If the integer parts are of different length, the one with longer
 * length is larger than that with shorter length.
 *
 * @param[in] a Number a.
 * @param[in] b Number b.
 * @param[in] bigger Whether a is longer than b.
 * @param[in] steps The steps to show while comparing.
 *
 * @returns The comparison result.
 */
std::string reportComparisonAtInteger(const std::string_view& a, const std::string_view& b, bool bigger, int steps = 2);

/**
 * @brief Reports the comparison based on the polarity. If they are of different polarity, the one that is positive is
 * larger than the negative one.
 *
 * @param[in] a Number a.
 * @param[in] b Number b.
 * @param[in] bigger Whether a is larger than b.
 * @param[in] steps The steps to show while comparing.
 *
 * @returns The comparison result.
 */
std::string reportComparisonByPolarity(const std::string_view& a,
                                       const std::string_view& b,
                                       bool greater,
                                       int steps = 2);

/**
 * @brief Compares each digit and see if one is larger.
 *
 * @param[in] a Number a.
 * @param[in] b Number b.
 * @param[in] _digit The digit where a is bigger than b.
 * @param[in] bigger Whether a is longer than b.
 * @param[in] bothNegative Whether both a and b are negative. If they are both negative, the result needs to be
 * inverted.
 * @param[in] steps The steps to show while comparing.
 *
 * @returns The comparison result.
 */
std::string reportComparisonByDigit(const std::string_view& a,
                                    const std::string_view& b,
                                    size_t digit,
                                    bool greater,
                                    bool bothNegative,
                                    int steps = 2);
