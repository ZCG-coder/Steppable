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
 * @file mat2d.cpp
 * @brief Implements methods for matrix manipulation.
 * @author Andy Zhang
 * @date 31 May 2025
 */

#include "steppable/mat2d.hpp"

#include "output.hpp"
#include "platform.hpp"
#include "rounding.hpp"
#include "steppable/number.hpp"
#include "symbols.hpp"
#include "util.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace steppable
{
    using namespace __internals;
    using namespace __internals::numUtils;

    namespace prettyPrint::printers
    {
        std::string ppMatrix(const MatVec2D<Number>& matrix, const int endRows)
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
            for (size_t rowIdx = 0; rowIdx < matrix.size(); rowIdx++)
            {
                const auto& row = matrix[rowIdx];
                if (rowIdx == 0)
                    ss << symbols::MATRIX_LEFT_TOP;
                else if (rowIdx == matrix.size() - 1)
                    ss << symbols::MATRIX_LEFT_BOTTOM;
                else
                    ss << symbols::MATRIX_LEFT_MIDDLE;
                for (size_t valIdx = 0; valIdx < row.size(); valIdx++)
                {
                    const auto& val = row[valIdx];
                    if (valIdx + endRows == row.size())
                        ss << symbols::MATRIX_LEFT_MIDDLE;
                    ss << std::right << std::setw(maxLen + 1) << val.present();
                    ss << " ";
                }

                if (rowIdx == 0)
                    ss << symbols::MATRIX_RIGHT_TOP;
                else if (rowIdx == matrix.size() - 1)
                    ss << symbols::MATRIX_RIGHT_BOTTOM;
                else
                    ss << symbols::MATRIX_RIGHT_MIDDLE;
                ss << "\n";
            }
            return ss.str();
        }
    } // namespace prettyPrint::printers

    Matrix::Matrix() : data({ {} }) { _cols = _rows = 0; }

    Matrix::Matrix(const size_t cols, const size_t rows, const Number& fill) :
        data(std::vector(rows, std::vector(cols, fill))), _cols(cols), _rows(rows)
    {
        data = roundOffValues(data, static_cast<int>(prec));
    }

    Matrix::Matrix(const MatVec2D<Number>& data) : data(data), _cols(data.front().size()), _rows(data.size())
    {
        for (auto& row : this->data)
            for (auto& value : row)
                value.setPrec(prec + 3, RoundingMode::USE_MAXIMUM_PREC);
    }

    void Matrix::_checkIdxSanity(const YXPoint* point) const
    {
        const auto x = point->x;
        const auto y = point->y;

        if (x > _cols)
        {
            output::error("Matrix::operator[]"s,
                          "Incorrect x parameter. x exceeds the number of columns in this matrix."s);
            utils::programSafeExit(1);
        }
        if (y > _rows)
        {
            output::error("Matrix::operator[]"s,
                          "Incorrect y parameter. y exceeds the number of rows in this matrix."s);
            utils::programSafeExit(1);
        }
    }

    MatVec2D<Number> Matrix::roundOffValues(const MatVec2D<Number>& _data, const int prec)
    {
        auto data = _data;
        for (auto& row : data)
            for (auto& val : row)
            {
                auto valueString = val.present();
                valueString = roundOff(val.present(), prec);
                valueString = standardizeNumber(valueString);
                val.set(valueString);
            }
        return data;
    }

    Matrix Matrix::rref() const
    {
        // Adapted from https://stackoverflow.com/a/31761026/14868780
        auto matrix = data;
        matrix = roundOffValues(matrix, static_cast<int>(prec));
#if defined(STP_DEB_MATRIX_REF_RESULT_INSPECT) && DEBUG
        std::cout << prettyPrint::printers::ppMatrix(matrix, 1) << "\n";
#endif

        for (size_t lead = 0; lead < _rows; lead++)
        {
            Number divisor("0", 30, RoundingMode::USE_MAXIMUM_PREC);
            Number multiplier("0", 30, RoundingMode::USE_MAXIMUM_PREC);
            for (size_t r = 0; r < _rows; r++)
            {
                divisor = matrix[lead][lead];
                multiplier = matrix[r][lead] / matrix[lead][lead];
                for (size_t c = 0; c < _cols; c++)
                    if (r == lead)
                    {
#if defined(STP_DEB_CALC_DIVISION_RESULT_INSPECT) && DEBUG
                        auto oldMatrixRC = matrix[r][c];
#endif

                        matrix[r][c] /= divisor;

#if defined(STP_DEB_CALC_DIVISION_RESULT_INSPECT) && DEBUG
                        output::info("Matrix::ref"s,
                                     oldMatrixRC.present() + " " + std::string(__internals::symbols::DIVIDED_BY) + " " +
                                         divisor.present() + " = " + matrix[r][c].present());
#endif
                    }
                    else
                    {
#if defined(STP_DEB_MATRIX_REF_RESULT_INSPECT) && DEBUG
                        auto oldMatrixRC = matrix[r][c];
                        auto oldMatrixLeadC = matrix[lead][c];
#endif

                        auto multiplyResult = matrix[lead][c] * multiplier;
                        matrix[r][c] -= multiplyResult;

#if defined(STP_DEB_MATRIX_REF_RESULT_INSPECT) && DEBUG
                        output::info("Matrix::ref"s,
                                     oldMatrixRC.present() + " - " + oldMatrixLeadC.present() + " " +
                                         std::string(__internals::symbols::MULTIPLY) + " " + multiplier.present());
                        output::info("Matrix::ref"s,
                                     "    = " + oldMatrixRC.present() + " - " + multiplyResult.present());
                        output::info("Matrix::ref"s, "    = " + matrix[r][c].present());
#endif
                    }
            }
#if defined(STP_DEB_MATRIX_REF_RESULT_INSPECT) && DEBUG
            std::cout << prettyPrint::printers::ppMatrix(matrix, 1) << "\n";
#endif
        }

        matrix = roundOffValues(matrix, static_cast<int>(prec));
        return matrix;
    }

    Matrix Matrix::ref() const
    {
        MatVec2D<Number> mat = data;
        mat = roundOffValues(mat, static_cast<int>(prec) + 3);

        for (int col = 0, row = 0; col < _cols && row < _rows; ++col)
        {
            // Find first non-zero in column col, at or below row
            int sel = -1;
            for (int i = row; i < _rows; ++i)
                if (mat[i][col] != 0.0)
                {
                    sel = i;
                    break;
                }
            if (sel == -1)
                continue; // All zeros in this column

            if (sel != row)
                std::swap(mat[row], mat[sel]); // Swap if needed

            // Eliminate below
            for (int i = row + 1; i < _rows; ++i)
            {
                Number factor = mat[i][col] / mat[row][col];
                for (int j = col; j < _cols; ++j)
                    mat[i][j] -= factor * mat[row][j];
            }
            ++row;
        }
        mat = roundOffValues(mat, static_cast<int>(prec));
        return mat;
    }

    Number Matrix::det() const
    {
        if (_rows != _cols)
        {
            output::error("Matrix::det"s, "Matrix is not a square."s);
            utils::programSafeExit(1);
        }
        int sign = 1;
        Number determinant = 1;
        MatVec2D<Number> mat = data;
        mat = roundOffValues(mat, static_cast<int>(prec) + 3);

        for (size_t col = 0, row = 0; col < _cols && row < _rows; ++col)
        {
            // Find first non-zero in column col, at or below row
            size_t sel = -1;
            for (size_t i = row; i < _rows; ++i)
                if (mat[i][col] != 0.0)
                {
                    sel = i;
                    break;
                }
            if (sel == -1)
                continue; // All zeros in this column

            if (sel != row)
            {
                // Swap rows - determinant becomes negative
                sign = -sign;
                std::swap(mat[row], mat[sel]);
            }

            // Eliminate below
            for (size_t i = row + 1; i < _rows; ++i)
            {
                Number factor = mat[i][col] / mat[row][col];
                for (size_t j = col; j < _cols; ++j)
                    mat[i][j] -= factor * mat[row][j];
            }
            ++row;
        }
        determinant *= sign;
        mat = roundOffValues(mat, static_cast<int>(prec));
        for (size_t i = 0; i < _cols; i++)
            determinant *= mat[i][i];
        return determinant;
    }

    Matrix Matrix::operator+(const Matrix& rhs) const
    {
        if (rhs._cols != _cols)
        {
            output::error("Matrix::operator+"s,
                          "Matrix dimensions mismatch. Expect {0} columns. Got {1} columns."s,
                          { std::to_string(_cols), std::to_string(rhs._cols) });
            utils::programSafeExit(1);
        }
        if (rhs._rows != _rows)
        {
            output::error("Matrix::operator+"s,
                          "Matrix dimensions mismatch. Expect {0} rows. Got {1} rows."s,
                          { std::to_string(_rows), std::to_string(rhs._rows) });
            utils::programSafeExit(1);
        }

        Matrix output = Matrix::zeros(_cols, _rows);

        for (size_t i = 0; i < _rows; i++)
            for (size_t j = 0; j < _cols; j++)
                output.data[i][j] += rhs.data[i][j];
        return output;
    }

    Matrix Matrix::operator+() const { return *this; }

    Matrix Matrix::operator+=(const Matrix& rhs)
    {
        *this = *this + rhs;
        return *this;
    }

    Matrix Matrix::operator-(const Matrix& rhs) const { return *this + -rhs; }

    Matrix Matrix::operator-() const
    {
        Matrix newMatrix = *this;
        for (auto& row : newMatrix.data)
            for (auto& value : row)
                value = -value;
        return newMatrix;
    }

    Matrix Matrix::operator-=(const Matrix& rhs)
    {
        *this = *this - rhs;
        return *this;
    }

    Matrix Matrix::operator*(const Number& rhs) const
    {
        Matrix newMatrix = *this;
        for (auto& row : newMatrix.data)
            for (auto& value : row)
                value *= rhs;
        return newMatrix;
    }

    Matrix Matrix::operator*(const Matrix& rhs) const
    {
        if (_cols != rhs._rows)
        {
            output::error("Matrix::operator*"s, "Incorrect matrix dimensions for multiplication."s);
            // https://en.wikipedia.org/wiki/Matrix_multiplication
            output::info("Matrix::operator*"s,
                         "For matrix multiplication, the number of columns in the first matrix must be equal to the "
                         "number of rows in the second matrix"s);
            utils::programSafeExit(1);
        }
        Matrix matrix = Matrix::zeros(rhs._cols, _rows);
        for (size_t j = 0; j < rhs._rows; j++)
            for (size_t k = 0; k < _cols; k++)
                for (size_t i = 0; i < _rows; i++)
                    matrix.data[i][j] += data[i][k] * rhs.data[k][j];
        return matrix;
    }

    Matrix Matrix::operator*=(const Number& rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    Matrix Matrix::operator*=(const Matrix& rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    std::string Matrix::present(const int endRows) const { return prettyPrint::printers::ppMatrix(data, endRows); }

    Matrix Matrix::ones(const size_t cols, const size_t rows)
    {
        auto matrix = Matrix(cols, rows, Number("1"));
        return matrix;
    }

    Matrix Matrix::zeros(size_t cols, size_t rows)
    {
        auto matrix = Matrix(cols, rows);
        return matrix;
    }

    Matrix Matrix::transpose() const
    {
        Matrix matrix(_rows, _cols);
        for (size_t i = 0; i < _cols; i++)
            for (size_t j = 0; j < _rows; j++)
                matrix[{ .y = j, .x = i }] = data[i][j];
        return matrix;
    }

    bool Matrix::operator==(const Matrix& rhs) const { return data == rhs.data; }

    bool Matrix::operator!=(const Matrix& rhs) const { return not(*this == rhs); }

    Number& Matrix::operator[](const YXPoint& point)
    {
        const auto x = point.x;
        const auto y = point.y;

        _checkIdxSanity(&point);
        return data[y][x];
    }

    Number Matrix::operator[](const YXPoint& point) const
    {
        const auto x = point.x;
        const auto y = point.y;

        _checkIdxSanity(&point);
        return data[y][x];
    }
} // namespace steppable
