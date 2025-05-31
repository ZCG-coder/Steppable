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

#include "steppable/number.hpp"
#include "util.hpp"

#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

namespace steppable
{
    template<typename NumberT>
    using MatVec2D = std::vector<std::vector<NumberT>>;

    namespace prettyPrint::printers
    {
        std::string ppMatrix(const MatVec2D<Number>& matrix);
    } // namespace prettyPrint::printers

    class Matrix
    {
    private:
        MatVec2D<Number> _data;
        size_t _cols;
        size_t _rows;

    public:
        Matrix();
        Matrix(const size_t cols, const size_t rows, const Number& fill = Number("0"));
        Matrix(const MatVec2D<Number>& data);

        Matrix ref();
        std::string present();

        static Matrix ones(size_t cols, size_t rows);
        static Matrix zeros(size_t cols, size_t rows);
    };
} // namespace steppable
