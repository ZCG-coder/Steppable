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
 * @file powerReport.hpp
 * @brief This file contains the declaration for the function reportPower, which reports the result of raising a
 * number to a power to the user.
 */
#pragma once

#include "fraction.hpp"

#include <string>

/**
 * @brief Reports a power operation for a root.
 *
 * @param _number The number to raise.
 * @param raiseTo The exponent to raise to.
 * @param fraction The exponent as a fraction.
 * @param result The root result.
 * @param steps The steps to show.
 *
 * @return The forrmatted power report.
 */
std::string reportPowerRoot(const std::string& _number,
                            const std::string& raiseTo,
                            const steppable::Fraction& fraction,
                            const std::string& result,
                            int steps);

/**
 * @brief Reports a power operation.
 *
 * @param[in] _number The number to raise to.
 * @param[in] raiseTo The power of the number.
 * @param[in] negativePower Whether the result should be divided by 1.
 * @param[in] steps The steps to show.
 *
 * @return The formatted power report.
 */
std::string reportPower(const std::string& _number,
                        const std::string& raiseTo,
                        size_t numberTrailingZeros,
                        bool negativePower,
                        int steps);
