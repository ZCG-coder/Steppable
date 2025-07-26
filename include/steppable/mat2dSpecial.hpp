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

/**
 * @file mat2dSpecial.hpp
 * @brief Defines functions to generate special 2D matrices.
 * @author Andy Zhang
 * @date 26 Jul 2025
 */

#pragma once

#include "steppable/mat2dBase.hpp"

namespace steppable
{

    /**
     * @class SpecialMatrix
     * @brief Represents special types of matrices and provides static methods to create them.
     */
    class SpecialMatrix
    {
    public:
        /**
         * @brief Creates a matrix filled with ones.
         * @param rows The number of rows.
         * @param cols The number of columns.
         * @return A Matrix filled with ones.
         */
        static MatrixBase ones(size_t rows, size_t cols);

        /**
         * @brief Creates a matrix filled with zeros.
         * @param rows The number of rows.
         * @param cols The number of columns.
         * @return A Matrix filled with zeros.
         */
        static MatrixBase zeros(size_t rows, size_t cols);

        /**
         * @brief Creates a diagonal matrix
         *
         * @param cols Number of columns and rows.
         * @param fill Number to fill into the matrix.
         * @param rows Number of rows in the matrix. If unspecified or left 0, it will create a square matrix.
         * @param offset Amount to offset from the main diagonal.
         * @return A diagonal matrix filled with the specified values.
         */
        static MatrixBase diag(size_t cols, const Number& fill = 1, size_t rows = 0, long long offset = 0);

        /**
         * @brief Creates a diagonal matrix
         *
         * @param cols Number of columns and rows.
         * @param fill Number to fill into the matrix.
         * @param rows Number of rows in the matrix. If unspecified or left 0, it will create a square matrix.
         * @param offset Amount to offset from the main diagonal.
         * @tparam NumberT Type of the number.
         * @return A diagonal matrix filled with the specified values.
         */
        template<concepts::Numeric NumberT>
        static MatrixBase diag(const size_t cols,
                               const NumberT& fill = 0,
                               const size_t rows = 0,
                               const long long offset = 0)
        {
            return diag(cols, Number(fill), rows);
        }

        static MatrixBase hankel(const MatrixBase& firstCol, const MatrixBase& lastRow = MatrixBase{ 0, 0 });

        static MatrixBase magic(size_t colsRows);

        static MatrixBase hilbert(size_t colsRows);

        static MatrixBase vandermonde(const MatrixBase& vec);
    };
} // namespace steppable
