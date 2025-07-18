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

#include "util.hpp"

#include <cstdint>
#include <string>

using namespace std::literals;
using namespace steppable::__internals::utils;

namespace steppable
{
    /**
     * @class Data
     * @brief Represents data that is being passed through Steppable.
     * @details This class contains a data value, and a name of the data.
     *
     * @tparam BaseT The type of the data.
     * @tparam BaseTName A StringLiteral describing the type of the data.
     */
    template<typename BaseT, StringLiteral BaseTName>
    class Data
    {
        BaseT value;

    public:
        std::string getDataType() { return BaseTName.value; }

        Data(const BaseT object) : value(object) {} // NOLINT(*-explicit-constructor)
        Data() : value() {}

        Data& operator=(const BaseT& object)
        {
            value = object;
            return *this;
        }
    };

    enum class _Weekday : std::uint8_t
    {
        Sunday = 0, ///< Sunday
        Monday = 1, ///< Monday
        Tuesday = 2, ///< Tuesday
        Wednesday = 3, ///< Wednesday
        Thursday = 4, ///< Thursday
        Friday = 5, ///< Friday
        Saturday = 6, ///< Saturday
    };

    using Weekday = Data<_Weekday, StringLiteral{ "Weekday" }>;
} // namespace steppable
