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
 * @file mat2dBase.hpp
 * @brief Defines a base for 2D matrices.
 * @author Andy Zhang
 * @date 26 Jul 2025
 */

#pragma once

#include "steppable/mat2dConstexpr.hpp"
#include "steppable/number.hpp"
#include "types/point.hpp"

#include <cstddef>
#include <cstdint>
#include <functional>
#include <utility>
#include <vector>

namespace steppable
{
    /**
     * @brief Alias for a 2D matrix represented as a vector of vectors.
     * @tparam NumberT The type of the numbers in the matrix.
     */
    template<typename NumberT>
    using MatVec2D = std::vector<std::vector<NumberT>>;

    enum class MatReverseMode : std::uint8_t
    {
        ALL = 0,
        REVERSE_ROWS = 1,
        REVERSE_COLS = 2
    };

    enum class MatDims : std::uint8_t
    {
        ROWS,
        COLS
    };

    constexpr size_t IDX_START = -1;

    /**
     * @class MatrixBase
     * @brief Represents a mathematical matrix.
     */
    class MatrixBase
    {
        size_t _cols; ///< The number of columns in the matrix.
        size_t _rows; ///< The number of rows in the matrix.
        size_t prec = 10; ///< Precision of numbers in the matrix.
        MatVec2D<Number> data; ///< The data of the matrix.

        /**
         * @brief Checks whether a point is inside the matrix. Errors and exits the program if not.
         * @param point The point to check.
         */
        void _checkIdxSanity(const YXPoint* point) const;

        void _checkSelfSanity() const;

        /**
         * @brief Checks whether the matrix data is correct in format.
         * @details This method checks for non-uniform rows inside the matrix.
         *
         * @param data The matrix data vector.
         */
        static void _checkDataSanity(const MatVec2D<Number>& data);

        /**
         * @brief Rounds off all data inside a vector to a specified precision.
         * @param data A double `std::vector` object containing matrix data.
         * @param prec Precision of the matrix.
         */
        static MatVec2D<Number> roundOffValues(const MatVec2D<Number>& data, size_t prec);

    public:
        using MatFn = std::function<Number(const Number& elem, const YXPoint& loc)>;

        using MatFn2 = std::function<Number(const Number& lhs, const Number& rhs, const YXPoint& loc)>;

        using MatFnUserData =
            std::function<Number(const Number& lhs, const Number& rhs, const void* userData, const YXPoint& loc)>;

        /**
         * @brief Round off all values to a specified precision.
         * @param prec Precision of the new matrix.
         * @return A new instance of the current matrix, with values rounded to the desired precision.
         */
        [[nodiscard]] MatrixBase roundOffValues(size_t prec) const;

        /**
         * @brief Default constructor for the Matrix class.
         */
        constexpr MatrixBase() noexcept : _cols(0), _rows(0) {}

        /**
         * @brief Constructs a matrix with specified dimensions and an optional fill value.
         * @param rows The number of rows.
         * @param cols The number of columns.
         * @param fill The value to fill the matrix with (default is "0").
         */
        explicit MatrixBase(size_t rows, size_t cols, const Number& fill = Number("0"));

        /**
         * @brief Constructs a matrix with specified dimensions and an optional fill value.
         * @param size The size of the matrix to be created.
         * @param fill The value to fill the matrix with (default is "0").
         */
        explicit MatrixBase(const std::pair<size_t, size_t>& size, const Number& fill = Number("0")) :
            _rows(size.first), _cols(size.second)
        {
            *this = MatrixBase(size.first, size.second, fill);
        }

        /**
         * @brief Constructs a matrix from a 2D vector of data.
         * @param data The 2D vector representing the matrix data.
         * @param prec Precision of the numbers.
         */
        explicit MatrixBase(const MatVec2D<Number>& data, size_t prec = 5);

        /**
         * @brief Constructs a matrix from a 2D vector of matrices.
         * @param data The 2D vector representing the submatrices that make up the final matrix.
         * @param prec Precision of the numbers.
         */
        explicit MatrixBase(const MatVec2D<MatrixBase>& data);

        /**
         * @brief Constructs a matrix from a 2D vector of C++ numbers.
         * @param data The 2D vector representing the matrix data.
         * @param prec Precision of the numbers.
         * @tparam ValueT Type of value in the `data` parameter.
         */
        template<concepts::Numeric ValueT>
        MatrixBase(const MatVec2D<ValueT>& data, const size_t prec) :
            _cols(data.front().size()), _rows(data.size()), prec(prec)
        {
            this->data = std::vector(_rows, std::vector(_cols, Number("0")));
            for (size_t i = 0; i < _rows; i++)
                for (size_t j = 0; j < _cols; j++)
                    this->data[i][j] = Number(data[i][j], prec);
        }

        /**
         * @brief Construct from a compile-time fixed-size matrix.
         * @tparam Rows Number of rows.
         * @tparam Cols Number of columns.
         * @param m The constexpr matrix to copy from.
         */
        template<size_t Rows, size_t Cols>
        explicit MatrixBase(const ConstexprMatrix<Rows, Cols>& m) :
            _rows(Rows), _cols(Cols), prec(8), data(Rows, std::vector<Number>(Cols))
        {
            for (size_t i = 0; i < Rows; ++i)
                for (size_t j = 0; j < Cols; ++j)
                    data[i][j] = m.data[i][j];
        }

        /**
         * @brief Converts the matrix to its reduced row echelon form.
         * @return A new Matrix in reduced row echelon form.
         */
        [[nodiscard]] MatrixBase rref() const;

        /**
         * @brief Converts a matrix to row echelon form.
         * @details Converts a matrix to row echelon form, with row elimation and swapping.
         * @return A new Matrix in row echelon form.
         */
        [[nodiscard]] MatrixBase ref() const;

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
         * @brief Calculates the trace of a matrix.
         * @details For a given matrix M, the trace tr(M) is defined as tr(M) = M(1, 1) + M(2, 2) + ... + M(n, n). In
         * other words, the sum of values along the diagonal.
         * @return The trace of the matrix.
         */
        [[nodiscard]] Number trace() const;

        /**
         * @brief Transposes a matrix.
         * @details Flips the rows and columns of the matrix and returns a new instance of the transposed matrix.
         * @return An instance of the transposed matrix.
         */
        [[nodiscard]] MatrixBase transpose() const;

        /**
         * @brief Determines if the matrix is symmetric.
         * @details By definition, if M is equal to its transpose, then it is symmetric.
         * @return True if the matrix is symmetric. False otherwise.
         */
        [[nodiscard]] bool isSymmetric() const { return *this == transpose(); }

        /**
         * @brief Add a matrix to another matrix.
         * @details Performs matrix addition, where corresponding elements in both matrices are added.
         *
         * @param rhs The other matrix.
         * @return A new matrix with the addition result.
         */
        MatrixBase operator+(const MatrixBase& rhs) const;

        /**
         * @brief Adds the other matrix to current matrix and assigns result to this matrix.
         *
         * @details This operator performs in-place matrix addition, updating each element of the matrix by
         * addition.
         *
         * @param rhs The other matrix.
         * @return Instance of a new matrix after addition.
         */
        MatrixBase operator+=(const MatrixBase& rhs);

        /**
         * @brief Unary plus operator.
         * @details Does nothing. Simply returns a new instance of the current matrix.
         * @return A new instance of the current matrix.
         */
        MatrixBase operator+() const;

        /**
         * @brief Subtract a matrix from another matrix.
         * @details Performs matrix subtraction, where corresponding elements in both matrices are subtracted.
         *
         * @param rhs The other matrix.
         * @return A new matrix with the subtraction result.
         */
        MatrixBase operator-(const MatrixBase& rhs) const;

        /**
         * @brief Subtracts the other matrix from current matrix and assigns result to this matrix.
         *
         * @details This operator performs in-place matrix subtraction, updating each element of the matrix by
         * subtraction.
         *
         * @param rhs The other matrix.
         * @return Instance of a new matrix after subtraction.
         */
        MatrixBase operator-=(const MatrixBase& rhs);

        /**
         * @brief Unary minus operator.
         * @details Converts the matrix to itself with all values being converted to the opposite sign. Returns a new
         * instance of the matrix.
         * @return A matrix with equal values in the opposite sign.
         */
        MatrixBase operator-() const;

        /**
         * @brief Scalar multiplication.
         * @details Multiplies each element of the matrix by a scalar.
         *
         * @param rhs The scalar to multiply.
         * @return A new matrix after the scalar multiplication
         */
        MatrixBase operator*(const Number& rhs) const;

        /**
         * @brief Multiplies the current matrix by a scalar value and assigns the result to this matrix.
         *
         * @details This operator performs in-place scalar multiplication, updating each element of the matrix
         * by multiplying it with the provided scalar value.
         *
         * @param rhs The scalar value to multiply each element of the matrix by.
         * @return Instance of a modified matrix after multiplication.
         */
        MatrixBase operator*=(const Number& rhs);

        /**
         * @brief Matrix multiplication.
         * @details Multiplies a matrix by another matrix, returning the resulting matrix.
         *
         * @param rhs The other matrix to multiply.
         * @return The new matrix after multiplying.
         */
        MatrixBase operator*(const MatrixBase& rhs) const;

        /**
         * @brief Multiplies this matrix by another matrix and assigns the result to this matrix.
         *
         * @details Performs in-place matrix multiplication with the given right-hand side (rhs) matrix.
         * The current matrix is updated to be the product of itself and rhs.
         *
         * @param rhs The matrix to multiply with this matrix.
         * @return The updated matrix after multiplication.
         */
        MatrixBase operator*=(const MatrixBase& rhs);

        /**
         * @brief Performs element-wise multiplication.
         * @details Automatically performs implicit expansion, then multiplies element-wise to produce a new matrix.
         *
         * @param rhs The other matrix.
         * @returns The element-wise multiplication result.
         */
        [[nodiscard]] MatrixBase elemWiseMultiply(const MatrixBase& rhs) const;

        /**
         * @brief Applies a single-argument function to all elements in the matrix.
         * @param fn The function to be applied to all elements. It takes a `steppable::Number` and a `YXPoint` point,
         * returning a `steppable::Number`.
         * @return The resulting matrix after the function has been applied.
         */
        [[nodiscard]] MatrixBase apply(const MatFn& fn) const;

        /**
         * @brief Applies a two-argument function to all elements in the matrix.
         * @param fn The function to be applied to all elements. It takes two `steppable::Number` objects (one from the
         * current matrix and another from the other matrix) and a `YXPoint` point, returning a `steppable::Number`
         * object.
         * @return The resulting matrix after the function has been applied.
         */
        [[nodiscard]] MatrixBase apply(const MatFn2& fn, const MatrixBase& rhs) const;

        /**
         * @brief Applies a single-argument function to all elements in the matrix.
         * @param fn The function to be applied to all elements. It takes two `steppable::Number` objects (one from the
         * current matrix and another from the other matrix), a user-defined `void*` user data objects, and a `YXPoint`
         * point, returning a `steppable::Number`.
         * @return The resulting matrix after the function has been applied.
         */
        [[nodiscard]] MatrixBase apply(const MatFnUserData& fn, const MatrixBase& rhs, const void* userData) const;

        /**
         * @brief Calculates the sum of the matrix.
         * @return The sum of all elements in the matrix.
         */
        [[nodiscard]] Number sum() const;

        /**
         * @brief Calculates the sum of the matrix along a dimension.
         * @param dims The dimension to calculate on.
         * @return The sum of elements along a dimension in the matrix.
         */
        [[nodiscard]] MatrixBase sumDims(const MatDims& dims = MatDims::COLS) const;

        /**
         * @brief Calculates the dot-product between the current matrix and another given matrix.\
         *
         * @param rhs The other matrix.
         * @param dims The dimension to operate on.
         * @return The result of the dot-product.
         */
        [[nodiscard]] MatrixBase dot(const MatrixBase& rhs, const MatDims& dims = MatDims::COLS) const;

        /**
         * @brief Raises the current matrix to a certain power.
         * @details Only positive integers (including zero) and the negative number -1 are allowed. Only square matrices
         * are supported. The matrix is multiplied by itself for a specified number of times.
         *
         * @param times Times to raise the matrix to.
         * @return A new matrix of the power result.
         */
        MatrixBase operator^(const Number& times) const;

        /**
         * @brief Raises the current matrix to a certain power, and assigns result to the current matrix.
         * @details Only positive integers (including zero) and the negative number -1 are allowed. Only square matrices
         * are supported.
         *
         * @param times Times to raise the matrix to.
         * @return The current matrix.
         */
        MatrixBase operator^=(const Number& times);

        /**
         * @brief Join a matrix to the right of the current matrix.
         * @details Joins a matrix to the right of the current matrix.
         *
         * @note Requires two matrices to have the same amount of rows.
         *
         * @param rhs The other matrix to join.
         * @return A new matrix where the two matrices are joined.
         */
        MatrixBase operator<<(const MatrixBase& rhs) const;

        /**
         * @brief Join a matrix to the right of the current matrix, then assign the result to the current one.
         * @details Joins a matrix to the right of the current matrix. The result is assigned to the current matrix.
         *
         * @note Requires two matrices to have the same amount of rows.
         *
         * @param rhs The other matrix to join.
         * @return A new matrix where the two matrices are joined.
         */
        MatrixBase operator<<=(const MatrixBase& rhs);

        /**
         * @brief Join a matrix to the left of the current matrix.
         * @details Joins a matrix to the left of the current matrix.
         *
         * @note Requires two matrices to have the same amount of rows.
         *
         * @param rhs The other matrix to join.
         * @return A new matrix where the two matrices are joined.
         */
        MatrixBase operator>>(const MatrixBase& rhs) const;

        /**
         * @brief Join a matrix to the left of the current matrix, then assign the result to the current one.
         * @details Joins a matrix to the left of the current matrix. The result is assigned to the current matrix.
         *
         * @note Requires two matrices to have the same amount of rows.
         *
         * @param rhs The other matrix to join.
         * @return A new matrix where the two matrices are joined.
         */
        MatrixBase operator>>=(const MatrixBase& rhs);

        /**
         * @brief Joins a matrix at the top of the current matrix.
         *
         * @param rhs The matrix to join to the current matrix.
         * @return The resulting matrix after joining.
         */
        MatrixBase joinTop(const MatrixBase& rhs);

        /**
         * @brief Joins a matrix at the bottom of the current matrix.
         *
         * @param rhs The matrix to join to the current matrix.
         * @return The resulting matrix after joining.
         */
        MatrixBase joinBottom(const MatrixBase& rhs);

        /**
         * @brief Test for equal matrices.
         * @details If the current matrix is equal to the other matrix, i.e., equal in dimensions and equal in all of
         * its values, returns True. Returns False otherwise.
         *
         * @param rhs The other matrix.
         * @return Whether the current matrix is equal to the other one.
         */
        bool operator==(const MatrixBase& rhs) const;

        /**
         * @brief Test for unequal matrices.
         * @details If the current matrix is not equal to the other matrix, i.e., not equal in dimensions or not equal
         * in all of its values, returns True. Returns False otherwise.
         *
         * @param rhs The other matrix.
         * @return Whether the current matrix is not equal to the other one.
         */
        bool operator!=(const MatrixBase& rhs) const;

        /**
         * @brief Performs element-wise less-than comparison.
         * @details For every element in each matrix, checks whether the element is less than the corresponding one in
         * the other matrix. In the resulting matrix, 1 represents the corresponding element in the matrix is indeed
         * less than the one in the other. 0 otherwise.
         *
         * @note This method requires two matrices to have the same dimensions.
         *
         * @param rhs The other matrix.
         * @return A matrix equal in dimension to the two matrices.
         */
        MatrixBase operator<(const MatrixBase& rhs) const;

        /**
         * @brief Performs element-wise less-than-or-equal-to comparison.
         * @details For every element in each matrix, checks whether the element is less than or equal to the
         * corresponding one in the other matrix. In the resulting matrix, 1 represents the corresponding element in the
         * matrix is indeed less than or equal to the one in the other. 0 otherwise.
         *
         * @note This method requires two matrices to have the same dimensions.
         *
         * @param rhs The other matrix.
         * @return A matrix equal in dimension to the two matrices.
         */
        MatrixBase operator<=(const MatrixBase& rhs) const;

        /**
         * @brief Performs element-wise greater-than comparison.
         * @details For every element in each matrix, checks whether the element is greater than the corresponding one
         * in the other matrix. In the resulting matrix, 1 represents the corresponding element in the matrix is indeed
         * greater than the one in the other. 0 otherwise.
         *
         * @note This method requires two matrices to have the same dimensions.
         *
         * @param rhs The other matrix.
         * @return A matrix equal in dimension to the two matrices.
         */
        MatrixBase operator>(const MatrixBase& rhs) const;

        /**
         * @brief Performs element-wise greater-than-or-equal-to comparison.
         * @details For every element in each matrix, checks whether the element is greater than or equal to the
         * corresponding one in the other matrix. In the resulting matrix, 1 represents the corresponding element in the
         * matrix is indeed greater than or equal to the one in the other. 0 otherwise.
         *
         * @note This method requires two matrices to have the same dimensions.
         *
         * @param rhs The other matrix.
         * @return A matrix equal in dimension to the two matrices.
         */
        MatrixBase operator>=(const MatrixBase& rhs) const;

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
        MatrixBase operator[](const YX2Points& point) const;

        /**
         * @brief Reverses the matrix.
         * @param axis The axis to flip. Defaults to flip in both the row and column axes.
         * @return The reversed copy of the current matrix.
         */
        [[nodiscard]] MatrixBase reverse(const MatReverseMode& axis = MatReverseMode::ALL) const;

        /**
         * @brief Repeats a matrix by a specified amount of times.
         * @param rowCopies The copies to make across rows.
         * @param colCopies The copies to make across columns.
         * @return A repeated copy of the matrix.
         */
        [[nodiscard]] MatrixBase repeat(const size_t& rowCopies, const size_t& colCopies) const;

        /**
         * @brief Get the number of rows in the matrix.
         * @return The number of rows in the matrix.
         */
        [[nodiscard]] constexpr size_t getRows() const noexcept { return _rows; }

        /**
         * @brief Get the number of columns in the matrix.
         * @return The number of columns in the matrix.
         */
        [[nodiscard]] constexpr size_t getCols() const noexcept { return _cols; }

        /**
         * @brief Get the size of the matrix.
         * @return A `std::pair` containing the rows and columns.
         */
        [[nodiscard]] constexpr std::pair<size_t, size_t> size() const noexcept { return { _rows, _cols }; }

        /**
         * @brief Get the data `std::vector` object from the matrix.
         * @return A `std::vector` object containing all the matrix data.
         */
        [[nodiscard]] MatVec2D<Number> getData() const { return data; }

        /**
         * @brief Checks whether the current matrix is empty.
         * @return True if the matrix does not contain any rows or columns, False otherwise.
         */
        [[nodiscard]] constexpr bool empty() const noexcept { return _rows * _cols == 0; }

        /**
         * @brief Get the reference to the `std::vector` data object from the matrix.
         * @return A reference to `std::vector` object containing all the matrix data.
         */
        [[nodiscard]] MatVec2D<Number>& getDataRef() { return data; }
    };
} // namespace steppable
