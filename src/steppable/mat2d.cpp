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

#include "steppable/mat2d.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

namespace steppable
{
    namespace prettyPrint::printers
    {
        std::string ppMatrix(const MatVec2D<Number>& matrix)
        {
            int maxLen = 0;
            std::stringstream ss;
            for (const auto& row : matrix)
            {
                for (const auto& val : row)
                {
                    auto length = static_cast<int>(val.present().length());
                    maxLen = std::max(length, maxLen);
                }
            }
            for (const auto& row : matrix)
            {
                ss << "[";
                for (const auto& val : row)
                    ss << std::right << std::setw(maxLen + 1) << val.present();
                ss << " ]\n";
            }
            return ss.str();
        }
    } // namespace prettyPrint::printers

    Matrix::Matrix() : _data({ {} }) { _cols = _rows = 0; }

    Matrix::Matrix(const size_t cols, const size_t rows, const Number& fill) :
        _data(std::vector(rows, std::vector(cols, fill))), _cols(cols), _rows(rows)
    {
    }

    Matrix::Matrix(const MatVec2D<Number>& data) : _data(data), _cols(data.front().size()), _rows(data.size()) {}

    Matrix Matrix::ref()
    {
        // Adapted from https://stackoverflow.com/a/31761026/14868780
        auto matrix = _data;
        size_t lead = 0;
        while (lead < _rows)
        {
            Number divisor(0);
            Number multiplier(0);
            for (size_t r = 0; r < _rows; r++)
            {
                divisor = matrix[lead][lead];
                multiplier = matrix[r][lead] / matrix[lead][lead];
                for (size_t c = 0; c < _cols; c++)
                    if (r == lead)
                        matrix[r][c] /= divisor;
                    else
                        matrix[r][c] -= matrix[lead][c] * multiplier;
            }
            lead++;
        }
        return matrix;
    }

    std::string Matrix::present() { return prettyPrint::printers::ppMatrix(_data); }

    Matrix Matrix::ones(size_t cols, size_t rows)
    {
        auto matrix = Matrix(cols, rows, Number("1"));
        return matrix;
    }

    Matrix Matrix::zeros(size_t cols, size_t rows)
    {
        auto matrix = Matrix(cols, rows);
        return matrix;
    }

} // namespace steppable
