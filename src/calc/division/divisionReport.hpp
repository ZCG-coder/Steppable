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
 * @file divisionReport.cpp
 * @brief This file contains the declaration for function reportDivision, which reports the result of a division
 * operation to the user.
 *
 * @author Andy Zhang
 * @date 23rd November 2023
 */

#pragma once

#include <sstream>
#include <string>

/**
 * @brief Reports a division operation to the user.
 *
 * @param tempFormattedAns The temporary formatted answer object.
 * @param[in] temp The remainder.
 * @param[in] ans The quotient.
 * @param[in] divisor The modified divisor.
 * @param[in] _divisor The original divisor.
 * @param[in] _number The original number.
 * @param[in] steps The steps to show.
 * @param[in] width The width for the output.
 * @param[in] resultIsNegative Whether the result is negative.
 *
 * @return The formatted report.
 */
std::string reportDivision(std::stringstream& tempFormattedAns,
                           const std::string& temp,
                           const std::string& ans,
                           const std::string& divisor,
                           const std::string& _divisor,
                           const std::string& _number,
                           int steps,
                           int width,
                           bool resultIsNegative);

/**
 * @brief Reports a division step.
 *
 * @param[in] temp The remainder.
 * @param[in] quotient The quptient.
 * @param[in] divisor The divisor.
 * @param[in] width The width for the output.
 * @param[in] index The index of the step.
 * @param[in] lastRemainder The previous remainder. Used to determine the width.
 *
 * @return The formatted division step report.
 */
std::string reportDivisionStep(const std::string& temp,
                               const std::string& quotient,
                               const std::string& divisor,
                               size_t width,
                               size_t index,
                               const std::string& lastRemainder);
