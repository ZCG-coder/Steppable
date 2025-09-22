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

#include "fn/_calc.hpp"

#define STP_EXPORT_FUNC(name) extern "C" void*(name)(void* argSpace)

// #define STP_RETURN(value, type) return STP_Value

using STP_ExportFuncPtr = void*(void* in);
using STP_ExportFuncT = std::function<STP_ExportFuncPtr>;

STP_EXPORT_FUNC(STP_cos);

STP_EXPORT_FUNC(STP_sin);

STP_EXPORT_FUNC(STP_tan);

STP_EXPORT_FUNC(STP_asin);

STP_EXPORT_FUNC(STP_acos);

STP_EXPORT_FUNC(STP_atan);

STP_EXPORT_FUNC(STP_cosh);

STP_EXPORT_FUNC(STP_sinh);

STP_EXPORT_FUNC(STP_tanh);

STP_EXPORT_FUNC(STP_asinh);

STP_EXPORT_FUNC(STP_acosh);

STP_EXPORT_FUNC(STP_atanh);
