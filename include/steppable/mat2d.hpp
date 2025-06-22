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

#include <cstddef>
#include <string_view>
#include <vector>

namespace steppable
{
    /**
     * @brief Alias for a 2D matrix represented as a vector of vectors.
     * @tparam NumberT The type of the numbers in the matrix.
     */
    template<typename NumberT>
    using MatVec2D = std::vector<std::vector<NumberT>>;

    namespace prettyPrint::printers
    {
        /**
         * @brief Pretty prints a matrix.
         * @param matrix The matrix to be pretty printed.
         * @return A string representation of the matrix.
         */
        std::string ppMatrix(const MatVec2D<Number>& matrix, int endRows = 0);
    } // namespace prettyPrint::printers

    namespace __internals::symbols
    {
        constexpr std::string_view MATRIX_LEFT_TOP = "\u23A1";
        constexpr std::string_view MATRIX_LEFT_MIDDLE = "\u23A2";
        constexpr std::string_view MATRIX_LEFT_BOTTOM = "\u23A3";
        constexpr std::string_view MATRIX_RIGHT_TOP = "\u23A4";
        constexpr std::string_view MATRIX_RIGHT_MIDDLE = "\u23A5";
        constexpr std::string_view MATRIX_RIGHT_BOTTOM = "\u23A6";
    } // namespace __internals::symbols

    /**
     * @class Matrix
     * @brief Represents a mathematical matrix.
     */
    class Matrix
    {
        size_t _cols; ///< The number of columns in the matrix.
        size_t _rows; ///< The number of rows in the matrix.
        size_t prec = 10; ///< Precision of numbers in the matrix.

    public:
        MatVec2D<Number> data; ///< The data of the matrix.

        /**
         * @brief Default constructor for the Matrix class.
         */
        Matrix();

        /**
         * @brief Constructs a matrix with specified dimensions and an optional fill value.
         * @param cols The number of columns.
         * @param rows The number of rows.
         * @param fill The value to fill the matrix with (default is "0").
         */
        Matrix(size_t cols, size_t rows, const Number& fill = Number("0"));

        /**
         * @brief Constructs a matrix from a 2D vector of data.
         * @param data The 2D vector representing the matrix data.
         */
        Matrix(const MatVec2D<Number>& data);

        static MatVec2D<Number> roundOffValues(const MatVec2D<Number>& data, int prec);

        /**
         * @brief Converts the matrix to its row echelon form.
         * @return A new Matrix in row echelon form.
         */
        [[nodiscard]] Matrix ref();

        /**
         * @brief Presents the matrix as a string.
         * @return A string representation of the matrix.
         */
        [[nodiscard]] std::string present(int endRows = 0) const;

        /**
         * @brief Creates a matrix filled with ones.
         * @param cols The number of columns.
         * @param rows The number of rows.
         * @return A Matrix filled with ones.
         */
        static Matrix ones(size_t cols, size_t rows);

        /**
         * @brief Creates a matrix filled with zeros.
         * @param cols The number of columns.
         * @param rows The number of rows.
         * @return A Matrix filled with zeros.
         */
        static Matrix zeros(size_t cols, size_t rows);
    };
} // namespace steppable
