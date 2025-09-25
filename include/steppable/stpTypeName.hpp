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
#include <map>
#include <string>

enum class STP_TypeID : std::uint8_t
{
    NONE,
    NUMBER,
    MATRIX_2D,
    STRING,
    FUNC,
    SYMBOL,
};

enum class STP_ExecState : std::uint8_t
{
    NORMAL,
    RETURNED,
    CONT,
    BREAK,
};

inline const std::map<STP_TypeID, std::string> STP_typeNames = {
    { STP_TypeID::NUMBER, "Number" }, { STP_TypeID::MATRIX_2D, "Mat2D" },
    { STP_TypeID::STRING, "Str" },    { STP_TypeID::FUNC, "Func" },
    { STP_TypeID::NONE, "Nothing" },     { STP_TypeID::SYMBOL, "Symbol" },
};
