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

#include "getString.hpp"
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
    using namespace localization;

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

            size_t matrixRows = matrix.size();
            for (size_t rowIdx = 0; rowIdx < matrixRows; rowIdx++)
            {
                const auto& row = matrix[rowIdx];
                if (matrixRows == 1)
                    ss << "[";
                else if (rowIdx == 0)
                    ss << symbols::MATRIX_LEFT_TOP;
                else if (rowIdx == matrixRows - 1)
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

                if (matrixRows == 1)
                    ss << "]";
                else if (rowIdx == 0)
                    ss << symbols::MATRIX_RIGHT_TOP;
                else if (rowIdx == matrixRows - 1)
                    ss << symbols::MATRIX_RIGHT_BOTTOM;
                else
                    ss << symbols::MATRIX_RIGHT_MIDDLE;
                ss << "\n";
            }
            return ss.str();
        }
    } // namespace prettyPrint::printers

    void Matrix::_checkDataSanity(const MatVec2D<Number>& data)
    {
        size_t size = data.front().size();
        for (const auto& row : data)
        {
            const size_t rowSize = row.size();
            if (rowSize != size)
            {
                output::error("Matrix::_checkDataSanity"s, $("mat2d", "75953952-0eea-4716-a006-d0f2e7a8f6c9"));
                utils::programSafeExit(1);
            }
            size = rowSize;
        }
    }

    Matrix::Matrix() : data({ {} }) { _cols = _rows = 0; }

    Matrix::Matrix(const size_t rows, const size_t cols, const Number& fill) :
        data(std::vector(rows, std::vector(cols, fill))), _cols(cols), _rows(rows)
    {
        data = roundOffValues(data, static_cast<int>(prec));
        _checkDataSanity(data);
    }

    Matrix::Matrix(const MatVec2D<Number>& data, const size_t prec) :
        data(data), _cols(data.front().size()), _rows(data.size()), prec(prec)
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
            output::error(
                "Matrix::operator[]"s,
                $("mat2d", "8d4e4757-415b-4aed-8f5e-26b3503a95dd"s, { std::to_string(x), std::to_string(_cols) }));
            utils::programSafeExit(1);
        }
        if (y > _rows)
        {
            output::error(
                "Matrix::operator[]"s,
                $("mat2d", "e7cb3f0b-11d8-4e12-8c93-4a1021b15e10"s, { std::to_string(y), std::to_string(_rows) }));
            utils::programSafeExit(1);
        }
    }

    MatVec2D<Number> Matrix::roundOffValues(const MatVec2D<Number>& _data, const size_t prec)
    {
        auto data = _data;
        for (auto& row : data)
            for (auto& val : row)
            {
                auto valueString = val.present();

                if (valueString == "Indeterminate")
                    valueString = "0";
                else
                {
                    valueString = roundOff(val.present(), prec);
                    valueString = standardizeNumber(valueString);
                }
                val.set(valueString);
            }
        return data;
    }

    Matrix Matrix::roundOffValues(const size_t prec) const { return roundOffValues(data, prec); }

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
                        output::info("Matrix::rref"s,
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
                        output::info("Matrix::rref"s,
                                     oldMatrixRC.present() + " - " + oldMatrixLeadC.present() + " " +
                                         std::string(__internals::symbols::MULTIPLY) + " " + multiplier.present());
                        output::info("Matrix::rref"s,
                                     "    = " + oldMatrixRC.present() + " - " + multiplyResult.present());
                        output::info("Matrix::rref"s, "    = " + matrix[r][c].present());
#endif
                    }

                matrix = roundOffValues(matrix, static_cast<int>(prec) + 3);
            }
#if defined(STP_DEB_MATRIX_REF_RESULT_INSPECT) && DEBUG
            std::cout << prettyPrint::printers::ppMatrix(matrix, 1) << "\n";
#endif
        }

        matrix = roundOffValues(matrix, static_cast<int>(prec));
        return { matrix, prec };
    }

    Matrix Matrix::ref() const
    {
        MatVec2D<Number> mat = data;
        mat = roundOffValues(mat, static_cast<int>(prec) + 3);

        for (long long signed col = 0, row = 0; col < _cols && row < _rows; ++col)
        {
            // Find first non-zero in column col, at or below row
            long long signed sel = -1;
            for (long long signed i = row; i < _rows; ++i)
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
            for (long long signed i = row + 1; i < _rows; ++i)
            {
                Number factor = mat[i][col] / mat[row][col];
                for (long long signed j = col; j < _cols; ++j)
                    mat[i][j] -= factor * mat[row][j];
            }
            ++row;
        }
        mat = roundOffValues(mat, static_cast<int>(prec));
        return { mat, prec };
    }

    Number Matrix::det() const
    {
        if (_rows != _cols)
        {
            output::error("Matrix::det"s, $("mat2d", "fe78bdc2-b409-4078-8e0e-313c46977f25"));
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
                          $("mat2d",
                            "88331f88-3a4c-4b7e-9b43-b51a1d1020e2",
                            { std::to_string(_cols), std::to_string(rhs._cols) }));
            utils::programSafeExit(1);
        }
        if (rhs._rows != _rows)
        {
            output::error("Matrix::operator+"s,
                          $("mat2d",
                            "34e92306-a4d8-4ff0-8441-bfcd29771e94",
                            { std::to_string(_rows), std::to_string(rhs._rows) }));
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
            output::error("Matrix::operator*"s, $("mat2d", "17b6aadd-bce1-4558-a7cc-7a099f00e57c"));
            // https://en.wikipedia.org/wiki/Matrix_multiplication
            output::info("Matrix::operator*"s, $("mat2d", "8966ce13-8ae9-4f14-ba4e-837b98a4c9fa"));
            utils::programSafeExit(1);
        }
        Matrix matrix = Matrix::zeros(_rows, rhs._cols);
        for (size_t j = 0; j < rhs._rows; j++)
            for (size_t k = 0; k < _cols; k++)
                for (size_t i = 0; i < _rows; i++)
                    matrix.data[i][j] += data[i][k] * rhs.data[k][j];
        return matrix;
    }

    Matrix Matrix::operator<<(const Matrix& rhs) const
    {
        if (rhs._rows != _rows)
        {
            output::error("Matrix::operator<<"s,
                          $("mat2d",
                            "f255d307-9482-442b-a523-61a1c7465f9c",
                            { std::to_string(rhs._rows), std::to_string(rhs._rows) }));
            utils::programSafeExit(1);
        }

        auto matrix = Matrix(_rows, _cols + rhs._cols);

        // Copy current matrix.
        for (size_t i = 0; i < _rows; i++)
            for (size_t j = 0; j < _cols; j++)
                matrix[{ .y = i, .x = j }] = data[i][j];

        // Copy other matrix.
        for (size_t i = 0; i < _rows; i++)
            for (size_t j = 0; j < rhs._cols; j++)
                matrix[{ .y = i, .x = j + _cols }] = rhs.data[i][j];

        return matrix;
    }

    Matrix Matrix::operator>>(const Matrix& rhs) const
    {
        if (rhs._rows != _rows)
        {
            output::error("Matrix::operator<<"s,
                          $("mat2d",
                            "f255d307-9482-442b-a523-61a1c7465f9c",
                            { std::to_string(rhs._rows), std::to_string(rhs._rows) }));
            utils::programSafeExit(1);
        }

        auto matrix = Matrix(_rows, _cols + rhs._cols);

        // Copy other matrix.
        for (size_t i = 0; i < _rows; i++)
            for (size_t j = 0; j < rhs._cols; j++)
                matrix[{ .y = i, .x = j }] = rhs.data[i][j];

        // Copy current matrix.
        for (size_t i = 0; i < _rows; i++)
            for (size_t j = 0; j < _cols; j++)
                matrix[{ .y = i, .x = j + _cols }] = data[i][j];

        return matrix;
    }

    Matrix Matrix::operator<<=(const Matrix& rhs)
    {
        *this = *this << rhs;
        return *this;
    }

    Matrix Matrix::operator>>=(const Matrix& rhs)
    {
        *this = *this >> rhs;
        return *this;
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

    Matrix Matrix::operator^(const Number& times) const
    {
        if (_rows != _cols)
        {
            output::error("Matrix::operator^"s, "Matrix is not square."s);
            utils::programSafeExit(1);
        }

        auto matrix = *this;

        // Take inverse of matrix
        if (times == -1)
        {
            matrix <<= diag(_rows);
            matrix = matrix.rref();
            matrix = matrix[{ .y1 = 0, .x1 = _rows, .y2 = _rows - 1, .x2 = _cols * 2 - 1 }];
            return matrix;
        }
        for (Number i = 0; i < times; ++i)
            matrix *= matrix;
        return matrix;
    }

    std::string Matrix::present(const int endRows) const { return prettyPrint::printers::ppMatrix(data, endRows); }

    Matrix Matrix::ones(const size_t rows, const size_t cols)
    {
        auto matrix = Matrix(rows, cols, Number("1"));
        return matrix;
    }

    Matrix Matrix::zeros(const size_t rows, const size_t cols)
    {
        auto matrix = Matrix(rows, cols);
        return matrix;
    }

    Matrix Matrix::diag(const size_t colsRows, const Number& fill)
    {
        auto matrix = Matrix(colsRows, colsRows);
        for (size_t i = 0; i < colsRows; i++)
            matrix[{ .y = i, .x = i }] = fill;
        return matrix;
    }

    Number Matrix::rank() const
    {
        auto matrix = *this;
        matrix = matrix.rref();

#if defined(STP_DEB_MATRIX_REF_RESULT_INSPECT) && DEBUG
        std::cout << prettyPrint::printers::ppMatrix(matrix.data) << "\n";
#endif
        size_t rank = 0;

        for (const auto& row : matrix)
        {
            size_t count = 0;
            for (const auto& val : row)
                if (val != 0)
                    count++;

            if (count != 0)
                rank++;
        }
        return { rank };
    }

    Matrix Matrix::transpose() const
    {
        Matrix matrix(_cols, _rows);
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

    Matrix Matrix::operator[](const YX2Points& point) const
    {
        auto [y1, x1, y2, x2] = point;
        const auto startPoint = YXPoint{ .y = y1, .x = x1 };
        _checkIdxSanity(&startPoint);

        const auto endPoint = YXPoint{ .y = y2, .x = x2 };
        _checkIdxSanity(&endPoint);

        // Make sure the end dimensions are always greater
        if (y2 < y1 or x2 < x1)
        {
            std::swap(y2, y1);
            std::swap(x2, x1);
        }

        auto matrix = Matrix(y2 - y1 + 1, x2 - x1 + 1);

        for (size_t i = y1; i <= y2; i++)
            for (size_t j = x1; j <= x2; j++)
                matrix[{ .y = i - y1, .x = j - x1 }] = data[i][j];
        return matrix;
    }
} // namespace steppable
