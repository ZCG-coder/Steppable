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
 * @file mat2d.hpp
 * @brief Defines methods and classes for 2D matrix manipulation.
 * @author Andy Zhang
 * @date 31 May 2025
 */

#pragma once

#include "steppable/number.hpp"
#include "testing.hpp"
#include "types/point.hpp"

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
        MatVec2D<Number> data; ///< The data of the matrix.

        void _checkIdxSanity(const YXPoint* point) const;

        static MatVec2D<Number> roundOffValues(const MatVec2D<Number>& data, size_t prec);

    public:
        /**
         * @brief Round off all values to a specified precision.
         * @param prec Precision of the new matrix.
         * @return A new instance of the current matrix, with values rounded to the desired precision.
         */
        [[nodiscard]] Matrix roundOffValues(size_t prec) const;

        /**
         * @brief Default constructor for the Matrix class.
         */
        Matrix();

        /**
         * @brief Constructs a matrix with specified dimensions and an optional fill value.
         * @param rows The number of rows.
         * @param cols The number of columns.
         * @param fill The value to fill the matrix with (default is "0").
         */
        Matrix(size_t rows, size_t cols, const Number& fill = Number("0"));

        /**
         * @brief Constructs a matrix from a 2D vector of data.
         * @param data The 2D vector representing the matrix data.
         * @param prec Precision of the numbers.
         */
        Matrix(const MatVec2D<Number>& data, size_t prec = 5);

        template<concepts::Numeric ValueT>
        Matrix(const MatVec2D<ValueT>& data, const size_t prec) :
            _cols(data.front().size()), _rows(data.size()), prec(prec)
        {
            this->data = std::vector(_rows, std::vector(_cols, Number("0")));
            for (size_t i = 0; i < _rows; i++)
                for (size_t j = 0; j < _cols; j++)
                    this->data[i][j] = Number(data[i][j], prec);
        }

        /**
         * @brief Converts the matrix to its reduced row echelon form.
         * @return A new Matrix in reduced row echelon form.
         */
        [[nodiscard]] Matrix rref() const;

        /**
         * @brief Converts a matrix to row echelon form.
         * @details Converts a matrix to row echelon form, with row elimation and swapping.
         * @return A new Matrix in row echelon form.
         */
        [[nodiscard]] Matrix ref() const;

        /**
         * @brief Find the determinant of a matrix.
         * @details Calculates the reduced echelon form of the matrix.
         * @return A Number object representing the determinant.
         */
        [[nodiscard]] Number det() const;

        /**
         * @brief Presents the matrix as a string.
         * @return A string representation of the matrix.
         */
        [[nodiscard]] std::string present(int endRows = 0) const;

        /**
         * @brief Creates a matrix filled with ones.
         * @param rows The number of rows.
         * @param cols The number of columns.
         * @return A Matrix filled with ones.
         */
        static Matrix ones(size_t rows, size_t cols);

        /**
         * @brief Creates a matrix filled with zeros.
         * @param rows The number of rows.
         * @param cols The number of columns.
         * @return A Matrix filled with zeros.
         */
        static Matrix zeros(size_t rows, size_t cols);

        /**
         * @brief Creates a diagnal matrix
         *
         * @param colsRows Number of columns and rows.
         * @param fill Number to fill into the matrix.
         * @return A diagnal matrix filled with the specified values.
         */
        static Matrix diag(size_t colsRows, const Number& fill = 1);

        /**
         * @brief Creates a diagnal matrix
         *
         * @param colsRows Number of columns and rows.
         * @param fill Number to fill into the matrix.
         * @tparam NumberT Type of the number.
         * @return A diagnal matrix filled with the specified values.
         */
        template<concepts::Numeric NumberT>
        static Matrix diag(const size_t colsRows, const NumberT& fill = 0)
        {
            return diag(colsRows, Number(fill));
        }

        /**
         * @brief Alias for the data `begin()` method to allow iterating over the matrix rows,
         * @return The beginning of the matrix rows.
         */
        auto begin() { return data.begin(); }

        /**
         * @brief Alias for the data `end()` method to allow iterating over the matrix rows,
         * @return The end of the matrix rows.
         */
        auto end() { return data.end(); }

        /**
         * @brief Calculates the rank of a matrix.
         * @details Calculates the number of non-zero rows when the matrix is converted to row-echelon form.
         * @return The rank of the matrix.
         */
        [[nodiscard]] Number rank() const;

        /**
         * @brief Transposes a matrix.
         * @details Flips the rows and columns of the matrix and returns a new instance of the transposed matrix.
         * @return An instance of the transposed matrix.
         */
        [[nodiscard]] Matrix transpose() const;

        /**
         * @brief Add a matrix to another matrix.
         * @details Performs matrix addition, where corresponding elements in both matrices are added.
         *
         * @param rhs The other matrix.
         * @return A new matrix with the addition result.
         */
        Matrix operator+(const Matrix& rhs) const;

        /**
         * @brief Adds the other matrix to current matrix and assigns result to this matrix.
         *
         * @details This operator performs in-place matrix addition, updating each element of the matrix by
         * addition.
         *
         * @param rhs The other matrix.
         * @return Instance of a new matrix after addition.
         */
        Matrix operator+=(const Matrix& rhs);

        /**
         * @brief Unary plus operator.
         * @details Does nothing. Simply returns a new instance of the current matrix.
         * @return A new instance of the current matrix.
         */
        Matrix operator+() const;

        /**
         * @brief Subtract a matrix from another matrix.
         * @details Performs matrix subtraction, where corresponding elements in both matrices are subtracted.
         *
         * @param rhs The other matrix.
         * @return A new matrix with the subtraction result.
         */
        Matrix operator-(const Matrix& rhs) const;

        /**
         * @brief Subtracts the other matrix from current matrix and assigns result to this matrix.
         *
         * @details This operator performs in-place matrix subtraction, updating each element of the matrix by
         * subtraction.
         *
         * @param rhs The other matrix.
         * @return Instance of a new matrix after subtraction.
         */
        Matrix operator-=(const Matrix& rhs);

        /**
         * @brief Unary minus operator.
         * @details Converts the matrix to itself with all values being converted to the opposite sign. Returns a new
         * instance of the matrix.
         * @return A matrix with equal values in the opposite sign.
         */
        Matrix operator-() const;

        /**
         * @brief Scalar multiplication.
         * @details Multiplies each element of the matrix by a scalar.
         *
         * @param rhs The scalar to multiply.
         * @return A new matrix after the scalar multiplication
         */
        Matrix operator*(const Number& rhs) const;

        /**
         * @brief Multiplies the current matrix by a scalar value and assigns the result to this matrix.
         *
         * @details This operator performs in-place scalar multiplication, updating each element of the matrix
         * by multiplying it with the provided scalar value.
         *
         * @param rhs The scalar value to multiply each element of the matrix by.
         * @return Instance of a modified matrix after multiplication.
         */
        Matrix operator*=(const Number& rhs);

        /**
         * @brief Matrix multiplication.
         * @details Multiplies a matrix by another matrix, returning the resulting matrix.
         *
         * @param rhs The other matrix to multiply.
         * @return The new matrix after multiplying.
         */
        Matrix operator*(const Matrix& rhs) const;

        /**
         * @brief Multiplies this matrix by another matrix and assigns the result to this matrix.
         *
         * @details Performs in-place matrix multiplication with the given right-hand side (rhs) matrix.
         * The current matrix is updated to be the product of itself and rhs.
         *
         * @param rhs The matrix to multiply with this matrix.
         * @return The updated matrix after multiplication.
         */
        Matrix operator*=(const Matrix& rhs);

        /**
         * @brief Raises the current matrix to a certain power.
         * @details Only positive integers (including zero) and the negative number -1 are allowed. Only square matrices
         * are supported. The matrix is multiplied by itself for a specified number of times.
         *
         * @param times Times to raise the matrix to.
         * @return A new matrix of the power result.
         */
        Matrix operator^(const Number& times) const;

        /**
         * @brief Raises the current matrix to a certain power, and assigns result to the current matrix.
         * @details Only positive integers (including zero) and the negative number -1 are allowed. Only square matrices
         * are supported.
         *
         * @param times Times to raise the matrix to.
         * @return The current matrix.
         */
        Matrix operator^=(const Number& times);

        /**
         * @brief Join a matrix to the right of the current matrix.
         * @details Joins a matrix to the right of the current matrix. Requires two matrices to have to same number of
         * rows.
         *
         * @param rhs The other matrix to join.
         * @return A new matrix where the two matrices are joined.
         */
        Matrix operator<<(const Matrix& rhs) const;

        /**
         * @brief Join a matrix to the right of the current matrix, then assign the result to the current one.
         * @details Joins a matrix to the right of the current matrix. Requires two matrices to have to same number of
         * rows. The result is assigned to the current matrix.
         *
         * @param rhs The other matrix to join.
         * @return A new matrix where the two matrices are joined.
         */
        Matrix operator<<=(const Matrix& rhs);

        /**
         * @brief Join a matrix to the left of the current matrix.
         * @details Joins a matrix to the left of the current matrix. Requires two matrices to have to same number of
         * rows.
         *
         * @param rhs The other matrix to join.
         * @return A new matrix where the two matrices are joined.
         */
        Matrix operator>>(const Matrix& rhs) const;

        /**
         * @brief Join a matrix to the left of the current matrix, then assign the result to the current one.
         * @details Joins a matrix to the left of the current matrix. Requires two matrices to have to same number of
         * rows. The result is assigned to the current matrix.
         *
         * @param rhs The other matrix to join.
         * @return A new matrix where the two matrices are joined.
         */
        Matrix operator>>=(const Matrix& rhs);

        /**
         * @brief Test for equal matrices.
         * @details If the current matrix is equal to the other matrix, i.e., equal in all of its values, returns True.
         *
         * @param rhs The other matrix.
         * @return Whether the current matrix is equal to the other one.
         */
        bool operator==(const Matrix& rhs) const;

        /**
         * @brief Test for unequal matrices.
         * @details If the current matrix is not equal to the other matrix, i.e., equal in all of its values, returns
         * True.
         *
         * @param rhs The other matrix.
         * @return Whether the current matrix is not equal to the other one.
         */
        bool operator!=(const Matrix& rhs) const;

        /**
         * @brief Gets the element at a point in the matrix.
         * @details Tries to find an element at the index specified by the point. Prints out error and exits when the
         * index does not exist.
         *
         * @param point The position of the element to find.
         * @return A reference to the element at that position.
         */
        Number& operator[](const YXPoint& point);

        /**
         * @brief Accesses the matrix element at the specified YXPoint.
         *
         * This operator allows read-only access to the matrix element located at the given
         * YXPoint coordinates.
         *
         * @param point The YXPoint specifying the (y, x) coordinates of the element.
         * @return The value of the matrix element at the specified coordinates.
         */
        Number operator[](const YXPoint& point) const;

        /**
         * @brief Accesses the matrix element at the specified YXPoint.
         *
         * This operator allows read-only access to the matrix element located at the given
         * YXPoint coordinates.
         *
         * @param point The YXPoint specifying the (y, x) coordinates of the element.
         * @return The value of the matrix element at the specified coordinates.
         */
        Matrix operator[](const YX2Points& point) const;

        /**
         * @brief Get the number of rows in the matrix.
         * @return The number of rows in the matrix.
         */
        [[nodiscard]] size_t getRows() const { return _rows; }

        /**
         * @brief Get the number of columns in the matrix.
         * @return The number of columns in the matrix.
         */
        [[nodiscard]] size_t getCols() const { return _cols; }

        [[nodiscard]] MatVec2D<Number> getData() const { return data; }
    };
} // namespace steppable
