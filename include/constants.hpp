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

#pragma once

#include <string_view>

/**
 * @namespace steppable::constants
 * @brief Numerical constants used in Steppable.
 */
namespace steppable::constants
{
    /// @brief 100 digits of pi.
    extern const std::string_view& PI;

    /// @brief Pi multiplied by 2.
    // Generated using Python:
    // -------------------------------------------------------
    // 1 | from decimal import Decimal, getcontext
    // 2 | # Set precision to 100 decimal places.
    // 3 | getcontext().prec = 100
    // 4 | Decimal(
    // 5 |     3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
    // 6 | ) * Decimal(2)
    // -------------------------------------------------------
    extern const std::string_view& TWO_PI;

    /// @brief Pi divided by 2.
    // Generated using Python:
    // -------------------------------------------------------
    // 1 | from decimal import Decimal, getcontext
    // 2 | # Set precision to 100 decimal places.
    // 3 | getcontext().prec = 100
    // 4 | Decimal(
    // 5 |     3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
    // 6 | ) / Decimal(2)
    // -------------------------------------------------------
    extern const std::string_view& PI_OVER_2;

    /// @brief Pi divided by 180 (to convert degrees to radians), correct to 100 decimal places.
    // Generated using Python:
    // -------------------------------------------------------
    // 1 | from decimal import Decimal, getcontext
    // 2 | # Set precision to 100 decimal places.
    // 3 | getcontext().prec = 100
    // 4 | Decimal(
    // 5 |     3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
    // 6 | ) / Decimal(180)
    // -------------------------------------------------------
    extern const std::string_view& PI_OVER_180;

    /// @brief Pi divided by 200 (to convert grads to radians), correct to 100 decimal places.
    // Generated using Python:
    // -------------------------------------------------------
    // 1 | from decimal import Decimal, getcontext
    // 2 | # Set precision to 100 decimal places.
    // 3 | getcontext().prec = 100
    // 4 | Decimal(
    // 5 |     3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
    // 6 | ) / Decimal(200)
    // -------------------------------------------------------
    extern const std::string_view& PI_OVER_200;

    extern const std::string_view& E;
} // namespace steppable::constants
