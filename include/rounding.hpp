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

#include "types/rounding.hpp"

#include <string>

namespace steppable::__internals::numUtils
{
    /**
     * @brief Round down a number to the nearest integer.
     *
     * @param[in] _number The number to round down.
     * @return The rounded number.
     */
    std::string roundDown(const std::string& _number);

    /**
     * @brief Round up a number to the nearest integer.
     *
     * @param[in] _number The number to round up.
     * @return The rounded number.
     */
    std::string roundUp(const std::string& _number);

    /**
     * @brief Round off a number to the nearest integer.
     *
     * @param[in] _number The number to round.
     * @param[in] digits The number of decimal places to round to.
     * @param[in] mode The mode of rounding. Defaults to rounding off.
     * @return The rounded number.
     */
    std::string roundOff(const std::string& _number, size_t digits = 0, Rounding mode = Rounding::ROUND_OFF);

    /**
     * @brief Move the decimal places of a number.
     *
     * @param _number The number to process.
     * @param places The desired decimal places to move. A negative amount indicates moving to the left, while a
     * positive amount indicates moving to the right.
     *
     * @return The processed number.
     */
    std::string moveDecimalPlaces(const std::string& _number, long places);
} // namespace steppable::__internals::numUtils
