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

namespace steppable::graphing
{
    /**
     * @brief Fill in integral values with linear interpolation.
     *
     * @param data An x-y corresponding table of values. Must have at least 2 items.
     * @param xMin Minimum `x` value.
     * @param xMax Maximum `x` value.
     */
    void linearInterpolateFill(std::map<long long, long long>* data, long long xMin, long long xMax);

    /**
     * @brief Fill in integral values with cubic interpolation.
     *
     * @param data An x-y corresponding table of values. Must have at least 4 items.
     * @param xMin Minimum `x` value.
     * @param xMax Maximum `x` value.
     */
    void cubicInterpolateFill(std::map<long long, long long>* data, long long xMin, long long xMax);
} // namespace steppable::graphing
