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
 * @file baseConvertReport.hpp
 * @brief This file contains the declaration of the reportBaseConvert function, which reports the converted number to
 * the user.
 * @warning Still work-in-progress.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 */

#pragma once

#include <string>
#include <vector>

/**
 * @brief Reports the base conversion step to the user.
 *
 * @param[in] _number The number to convert.
 * @param[in] _base The base to convert to.
 * @param[in] _quotient The quotient of the division.
 * @param[in] _remainder The remainder of the division.
 *
 * @return The report of the base conversion step.
 */
std::string reportBaseConvertStep(const std::string& _number,
                                  const std::string& _base,
                                  const std::string& _quotient,
                                  const std::string& _remainder);

/**
 * @brief Reports the base conversion to the user.
 *
 * @param[in] _number The number to convert.
 * @param[in] _base The base to convert to.
 * @param[in] _result The result of the base conversion.
 *
 * @return The report of the base conversion.
 */
std::string reportBaseConvert(const std::string& _number,
                              const std::string& _base,
                              const std::vector<std::string>& _result,
                              int steps);
