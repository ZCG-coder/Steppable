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

#include <cstdint>

namespace steppable
{
    /**
     * @enum RoundingMode
     * @brief Specifies how Steppable should round the number in operations.
     */
    enum class RoundingMode : std::uint8_t
    {
        /// @brief Use the higher precision whenever possible.
        USE_MAXIMUM_PREC = 0xFF,

        /// @brief Use the lower precision whenever possible.
        USE_MINIMUM_PREC = 0x01,

        /// @brief Use the current precision.
        USE_CURRENT_PREC = 0x02,

        /// @brief Use the other number's precision.
        USE_OTHER_PREC = 0x03,

        /// @brief Do not append any decimal places.
        DISCARD_ALL_DECIMALS = 0x00
    };

    enum class Rounding : std::uint8_t
    {
        ROUND_DOWN = 0x00, ///< Rounds the number down.
        ROUND_UP = 0x01, ///< Rounds the number up.
        ROUND_OFF = 0x02, ///< Rounds the number off.
    };
} // namespace steppable
