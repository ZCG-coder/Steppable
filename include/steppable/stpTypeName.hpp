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

#include <map>
#include <string>

enum STP_TypeID
{
    STP_TypeID_NULL = 0,
    STP_TypeID_NUMBER = 1,
    STP_TypeID_MATRIX_2D = 2,
    STP_TypeID_STRING = 3,
    STP_TypeID_FUNC = 4,
    STP_TypeID_SYMBOL = 5,
};

inline const std::map<STP_TypeID, std::string> STP_typeNames = {
    { STP_TypeID_NUMBER, "Number" }, { STP_TypeID_MATRIX_2D, "Mat2D" }, { STP_TypeID_STRING, "Str" },
    { STP_TypeID_FUNC, "Func" },     { STP_TypeID_NULL, "Null" },       { STP_TypeID_SYMBOL, "Symbol" },
};
