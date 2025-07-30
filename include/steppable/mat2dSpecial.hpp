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
#include "steppable/mat2dConstexpr.hpp"

namespace steppable
{
    /**
     * @class SpecialMatrix
     * @brief Represents special types of matrices and provides static methods to create them.
     */
    class SpecialMatrix
    {
        /**
         * @brief Returns a known form of Hadamard matrix with order 12.
         * @return A known form of Hadamard matrix with order 12.
         */
        static consteval ConstexprMatrix<12, 12> hadamardKnown12()
        {
            // https://www.cs.miami.edu/home/burt/learning/Csc670.034/hadamard (Francois)
            return { {
                { 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
                { 1, 1, -1, 1, -1, -1, -1, 1, 1, 1, -1, 1 },
                { 1, 1, 1, -1, 1, -1, -1, -1, 1, 1, 1, -1 },
                { 1, -1, 1, 1, -1, 1, -1, -1, -1, 1, 1, 1 },
                { 1, 1, -1, 1, 1, -1, 1, -1, -1, -1, 1, 1 },
                { 1, 1, 1, -1, 1, 1, -1, 1, -1, -1, -1, 1 },
                { 1, 1, 1, 1, -1, 1, 1, -1, 1, -1, -1, -1 },
                { 1, -1, 1, 1, 1, -1, 1, 1, -1, 1, -1, -1 },
                { 1, -1, -1, 1, 1, 1, -1, 1, 1, -1, 1, -1 },
                { 1, -1, -1, -1, 1, 1, 1, -1, 1, 1, -1, 1 },
                { 1, 1, -1, -1, -1, 1, 1, 1, -1, 1, 1, -1 },
                { 1, -1, 1, -1, -1, -1, 1, 1, 1, -1, 1, 1 },
            } };
        }

        /**
         * @brief Returns a known form of Hadamard matrix with order 20.
         * @return A known form of Hadamard matrix with order 20.
         */
        static consteval ConstexprMatrix<20, 20> hadamardKnown20()
        {
            // Translated from http://neilsloane.com/hadamard/had.20.pal.txt
            return { {
                { 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
                { 1, 1, -1, 1, 1, -1, -1, -1, -1, 1, -1, 1, -1, 1, 1, 1, 1, -1, -1, 1 },
                { 1, 1, 1, -1, 1, 1, -1, -1, -1, -1, 1, -1, 1, -1, 1, 1, 1, 1, -1, -1 },
                { 1, -1, 1, 1, -1, 1, 1, -1, -1, -1, -1, 1, -1, 1, -1, 1, 1, 1, 1, -1 },
                { 1, -1, -1, 1, 1, -1, 1, 1, -1, -1, -1, -1, 1, -1, 1, -1, 1, 1, 1, 1 },
                { 1, 1, -1, -1, 1, 1, -1, 1, 1, -1, -1, -1, -1, 1, -1, 1, -1, 1, 1, 1 },
                { 1, 1, 1, -1, -1, 1, 1, -1, 1, 1, -1, -1, -1, -1, 1, -1, 1, -1, 1, 1 },
                { 1, 1, 1, 1, -1, -1, 1, 1, -1, 1, 1, -1, -1, -1, -1, 1, -1, 1, -1, 1 },
                { 1, 1, 1, 1, 1, -1, -1, 1, 1, -1, 1, 1, -1, -1, -1, -1, 1, -1, 1, -1 },
                { 1, -1, 1, 1, 1, 1, -1, -1, 1, 1, -1, 1, 1, -1, -1, -1, -1, 1, -1, 1 },
                { 1, 1, -1, 1, 1, 1, 1, -1, -1, 1, 1, -1, 1, 1, -1, -1, -1, -1, 1, -1 },
                { 1, -1, 1, -1, 1, 1, 1, 1, -1, -1, 1, 1, -1, 1, 1, -1, -1, -1, -1, 1 },
                { 1, 1, -1, 1, -1, 1, 1, 1, 1, -1, -1, 1, 1, -1, 1, 1, -1, -1, -1, -1 },
                { 1, -1, 1, -1, 1, -1, 1, 1, 1, 1, -1, -1, 1, 1, -1, 1, 1, -1, -1, -1 },
                { 1, -1, -1, 1, -1, 1, -1, 1, 1, 1, 1, -1, -1, 1, 1, -1, 1, 1, -1, -1 },
                { 1, -1, -1, -1, 1, -1, 1, -1, 1, 1, 1, 1, -1, -1, 1, 1, -1, 1, 1, -1 },
                { 1, -1, -1, -1, -1, 1, -1, 1, -1, 1, 1, 1, 1, -1, -1, 1, 1, -1, 1, 1 },
                { 1, 1, -1, -1, -1, -1, 1, -1, 1, -1, 1, 1, 1, 1, -1, -1, 1, 1, -1, 1 },
                { 1, 1, 1, -1, -1, -1, -1, 1, -1, 1, -1, 1, 1, 1, 1, -1, -1, 1, 1, -1 },
                { 1, -1, 1, 1, -1, -1, -1, -1, 1, -1, 1, -1, 1, 1, 1, 1, -1, -1, 1, 1 },
            } };
        }

    public:
        /**
         * @brief Creates a matrix filled with ones.
         * @param rows The number of rows.
         * @param cols The number of columns.
         * @return A Matrix filled with ones.
         */
        static MatrixBase ones(const size_t& rows, const size_t& cols);

        /**
         * @brief Creates a matrix filled with zeros.
         * @param rows The number of rows.
         * @param cols The number of columns.
         * @return A Matrix filled with zeros.
         */
        static MatrixBase zeros(const size_t& rows, const size_t& cols);

        /**
         * @brief Creates a diagonal matrix
         *
         * @param cols Number of columns and rows.
         * @param fill Number to fill into the matrix.
         * @param rows Number of rows in the matrix. If unspecified or left 0, it will create a square matrix.
         * @param offset Amount to offset from the main diagonal.
         * @return A diagonal matrix filled with the specified values.
         */
        static MatrixBase diag(const size_t& cols,
                               const Number& fill = 1,
                               const size_t& rows = 0,
                               const long long& offset = 0);

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
        static MatrixBase diag(const size_t& cols,
                               const NumberT& fill = 0,
                               const size_t& rows = 0,
                               const long long& offset = 0)
        {
            return diag(cols, Number(fill), rows);
        }

        /**
         * @brief Creates a Hankel matrix.
         *
         * @param firstCol The first column of the matrix.
         * @param lastRow The last row of the matrix. If not provided, uses a duplicate of the first column and creates
         * a symmetrix Hankel matrix.
         * @return A Hankel matrix.
         */
        static MatrixBase hankel(const MatrixBase& firstCol, const MatrixBase& lastRow = MatrixBase{ 0, 0 });

        /**
         * @brief Creates a Toeplitz matrix.
         *
         * @param firstCol The first column of the matrix.
         * @param lastRow The first row of the matrix. If not provided, uses a duplicate of the first column and creates
         * a symmetrix Toeplitz matrix.
         * @return A Toeplitz matrix.
         */
        static MatrixBase toeplitz(const MatrixBase& firstColRow, const MatrixBase& firstRow = MatrixBase{ 0, 0 });

        static MatrixBase magic(const size_t& colsRows);

        /**
         * @brief Creates a Hilbert matrix of given order.
         *
         * @param colsRows The order of the matrix.
         * @return A Hilbert matrix of given order.
         */
        static MatrixBase hilbert(const size_t& colsRows);

        /**
         * @brief Creates a Vandermonde matrix from a given vector.
         *
         * @param vec The input vector.
         * @return A Vandermonde matrix from the given vector.
         */
        static MatrixBase vandermonde(const MatrixBase& vec);

        /**
         * @brief Creates a Hadamard matrix of given order.
         *
         * @param order The order of the Hadamard matrix. Let the order be n, one of `n`, `n/12`, or `n/20` must be an
         * exponent of 2.
         * @return A Hadamard matrix of given order.
         */
        static MatrixBase hadamard(const size_t& order);
    };
} // namespace steppable
