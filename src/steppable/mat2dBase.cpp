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

#include "steppable/mat2dBase.hpp"

#include "getString.hpp"
#include "output.hpp"
#include "platform.hpp"
#include "rounding.hpp"
#include "steppable/mat2d.hpp"
#include "steppable/mat2dSpecial.hpp"
#include "steppable/number.hpp"
#include "util.hpp"

#include <algorithm>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace steppable
{
    using namespace __internals;
    using namespace __internals::numUtils;
    using namespace localization;

    void MatrixBase::_checkDataSanity(const MatVec2D<Number>& data)
    {
        if (data.empty())
            return;

        size_t size = data.front().size();
        for (const auto& row : data)
        {
            const size_t rowSize = row.size();
            if (rowSize != size)
            {
                output::error("Matrix::_checkDataSanity"s,
                              $("steppable::mat2d", "75953952-0eea-4716-a006-d0f2e7a8f6c9"));
                utils::programSafeExit(1);
            }
            size = rowSize;
        }
    }

    void MatrixBase::_checkSelfSanity() const
    {
        if (_rows * _cols == 0)
        {
            output::error("Matrix::_checkDataSanity"s, "Attempting to opearte an empty matrix."s);
            utils::programSafeExit(1);
        }
    }

    MatrixBase::MatrixBase(const size_t rows, const size_t cols, const Number& fill) :
        data(std::vector(rows, std::vector(cols, fill))), _cols(cols), _rows(rows)
    {
        data = roundOffValues(data, static_cast<int>(prec));
        _checkDataSanity(data);
    }

    MatrixBase::MatrixBase(const MatVec2D<Number>& data, const size_t prec) :
        data(data), _cols(data.front().size()), _rows(data.size()), prec(prec)
    {
        for (auto& row : this->data)
            for (auto& value : row)
                value.setPrec(prec + 3, RoundingMode::USE_MAXIMUM_PREC);
    }

    MatrixBase::MatrixBase(const MatVec2D<MatrixBase>& data) : _cols(0), _rows(0)
    {
        // Size check
        //    [ [ 1 2 3 4 5 ] | [ 1 2 3 4 ] ]
        //    [ [ 2 3 4 5 6 ] | [ 2 3 4 5 ] ]
        //    [ [ 3 4 5 6 7 ] | [ 3 4 5 6 ] ]
        //    [ ------------+-+-------------]
        //    [ [ 1 2 3 4 ] | [ 1 2 3 4 5 ] ]
        //
        // - For each row
        //   => Check if total cols are identical across rows
        // - For each matrix in a row
        //   => Check if row numbers are matching

        auto firstMatrix = data.front().front();
        auto prevRowCols = std::unique_ptr<size_t>();
        prevRowCols.reset();
        MatrixBase res(0, 0);

        for (const auto& row : data)
        {
            const auto& firstMatrix = row.front();
            size_t prevMatRows = firstMatrix.getRows();
            size_t currentRowCols = 0;

            MatrixBase currentRowMatrix(0, 0);

            for (const auto& matrix : row)
            {
                if (matrix.getRows() != prevMatRows)
                {
                    output::error("MatrixBase::MatrixBase"s, "Inconsistent matrix size."s);
                    utils::programSafeExit(1);
                }
                prevMatRows = matrix.getRows();
                currentRowCols += matrix.getCols();

                _cols += matrix.getCols();

                currentRowMatrix <<= matrix;
            }
            _rows += firstMatrix.getRows();

            if (not prevRowCols)
                prevRowCols = std::make_unique<size_t>(currentRowCols);
            else if (currentRowCols != *prevRowCols)
            {
                output::error("MatrixBase::MatrixBase"s, "Inconsistent matrix size."s);
                utils::programSafeExit(1);
            }

            res = res.joinBottom(currentRowMatrix);
        }

        *this = res;
    }

    void MatrixBase::_checkIdxSanity(const YXPoint* point) const
    {
        const auto x = point->x;
        const auto y = point->y;

        if (x > _cols)
        {
            output::error("Matrix::operator[]"s,
                          $("steppable::mat2d",
                            "8d4e4757-415b-4aed-8f5e-26b3503a95dd"s,
                            { std::to_string(x), std::to_string(_cols) }));
            utils::programSafeExit(1);
        }
        if (y > _rows)
        {
            output::error("Matrix::operator[]"s,
                          $("steppable::mat2d",
                            "e7cb3f0b-11d8-4e12-8c93-4a1021b15e10"s,
                            { std::to_string(y), std::to_string(_rows) }));
            utils::programSafeExit(1);
        }
    }

    MatVec2D<Number> MatrixBase::roundOffValues(const MatVec2D<Number>& _data, const size_t prec)
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

    MatrixBase MatrixBase::roundOffValues(const size_t prec) const
    {
        _checkSelfSanity();

        return MatrixBase(roundOffValues(data, prec));
    }

    MatrixBase MatrixBase::rref() const
    {
        _checkSelfSanity();

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
        return MatrixBase{ matrix, prec };
    }

    MatrixBase MatrixBase::ref() const
    {
        _checkSelfSanity();

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
        return MatrixBase{ mat, prec };
    }

    Number MatrixBase::det() const
    {
        _checkSelfSanity();

        if (_rows != _cols)
        {
            output::error("Matrix::det"s, $("steppable::mat2d", "fe78bdc2-b409-4078-8e0e-313c46977f25"));
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

    MatrixBase MatrixBase::operator+(const MatrixBase& rhs) const
    {
        _checkSelfSanity();

        if (rhs._cols != _cols)
        {
            output::error("Matrix::operator+"s,
                          $("steppable::mat2d",
                            "88331f88-3a4c-4b7e-9b43-b51a1d1020e2",
                            { std::to_string(_cols), std::to_string(rhs._cols) }));
            utils::programSafeExit(1);
        }
        if (rhs._rows != _rows)
        {
            output::error("Matrix::operator+"s,
                          $("steppable::mat2d",
                            "34e92306-a4d8-4ff0-8441-bfcd29771e94",
                            { std::to_string(_rows), std::to_string(rhs._rows) }));
            utils::programSafeExit(1);
        }

        MatrixBase output = SpecialMatrix::zeros(_cols, _rows);

        for (size_t i = 0; i < _rows; i++)
            for (size_t j = 0; j < _cols; j++)
                output.data[i][j] += rhs.data[i][j];
        return output;
    }

    MatrixBase MatrixBase::operator+() const
    {
        _checkSelfSanity();

        return *this;
    }

    MatrixBase MatrixBase::operator+=(const MatrixBase& rhs)
    {
        _checkSelfSanity();

        *this = *this + rhs;
        return *this;
    }

    MatrixBase MatrixBase::operator-(const MatrixBase& rhs) const
    {
        _checkSelfSanity();

        return *this + -rhs;
    }

    MatrixBase MatrixBase::operator-() const
    {
        _checkSelfSanity();

        MatrixBase newMatrix = *this;
        for (auto& row : newMatrix.data)
            for (auto& value : row)
                value = -value;
        return newMatrix;
    }

    MatrixBase MatrixBase::operator-=(const MatrixBase& rhs)
    {
        _checkSelfSanity();

        *this = *this - rhs;
        return *this;
    }

    MatrixBase MatrixBase::operator*(const Number& rhs) const
    {
        _checkSelfSanity();

        MatrixBase newMatrix = *this;
        for (auto& row : newMatrix.data)
            for (auto& value : row)
                value *= rhs;
        return newMatrix;
    }

    MatrixBase MatrixBase::operator*(const MatrixBase& rhs) const
    {
        _checkSelfSanity();

        if (_cols != rhs._rows)
        {
            output::error("Matrix::operator*"s, $("steppable::mat2d", "17b6aadd-bce1-4558-a7cc-7a099f00e57c"));
            // https://en.wikipedia.org/wiki/Matrix_multiplication
            output::info("Matrix::operator*"s, $("steppable::mat2d", "8966ce13-8ae9-4f14-ba4e-837b98a4c9fa"));
            utils::programSafeExit(1);
        }
        MatrixBase matrix = SpecialMatrix::zeros(_rows, rhs._cols);
        for (size_t j = 0; j < rhs._rows; j++)
            for (size_t k = 0; k < _cols; k++)
                for (size_t i = 0; i < _rows; i++)
                    matrix.data[i][j] += data[i][k] * rhs.data[k][j];
        return matrix;
    }

    MatrixBase MatrixBase::operator<<(const MatrixBase& rhs) const
    {
        // Concatenating a matrix to nothing gives the matrix.
        if (_rows * _cols == 0)
            return rhs;

        if (rhs._rows != _rows)
        {
            output::error("Matrix::operator<<"s,
                          $("steppable::mat2d",
                            "f255d307-9482-442b-a523-61a1c7465f9c",
                            { std::to_string(rhs._rows), std::to_string(_rows) }));
            utils::programSafeExit(1);
        }

        auto matrix = MatrixBase(_rows, _cols + rhs._cols);

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

    MatrixBase MatrixBase::operator>>(const MatrixBase& rhs) const
    {
        // Concatenating a matrix to nothing gives the matrix.
        if (_rows * _cols == 0)
            return rhs;

        if (rhs._rows != _rows)
        {
            output::error("Matrix::operator<<"s,
                          $("steppable::mat2d",
                            "f255d307-9482-442b-a523-61a1c7465f9c",
                            { std::to_string(rhs._rows), std::to_string(_rows) }));
            utils::programSafeExit(1);
        }

        auto matrix = MatrixBase(_rows, _cols + rhs._cols);

        // Copy other matrix.
        for (size_t i = 0; i < _rows; i++)
            for (size_t j = 0; j < rhs._cols; j++)
                matrix[{ .y = i, .x = j }] = rhs.data[i][j];

        // Copy current matrix.
        for (size_t i = 0; i < _rows; i++)
            for (size_t j = 0; j < _cols; j++)
                matrix[{ .y = i, .x = j + rhs._cols }] = data[i][j];

        return matrix;
    }

    MatrixBase MatrixBase::operator<<=(const MatrixBase& rhs)
    {
        *this = *this << rhs;
        return *this;
    }

    MatrixBase MatrixBase::operator>>=(const MatrixBase& rhs)
    {
        *this = *this >> rhs;
        return *this;
    }

    MatrixBase MatrixBase::joinTop(const MatrixBase& rhs)
    {
        // Concatenating a matrix to nothing gives the matrix.
        if (_rows * _cols == 0)
            return rhs;

        if (rhs._cols != _cols)
        {
            output::error("MatrixBase::joinTop"s,
                          $("steppable::mat2d",
                            "88331f88-3a4c-4b7e-9b43-b51a1d1020e2",
                            { std::to_string(_cols), std::to_string(rhs._cols) }));
            utils::programSafeExit(1);
        }

        MatVec2D<Number> resData = rhs.data;
        std::ranges::for_each(data, [&](const auto& row) { resData.emplace_back(row); });
        return MatrixBase{ resData };
    }

    MatrixBase MatrixBase::joinBottom(const MatrixBase& rhs)
    {
        // Concatenating a matrix to nothing gives the matrix.
        if (_rows * _cols == 0)
            return rhs;

        if (rhs._cols != _cols)
        {
            output::error("MatrixBase::joinBottom"s,
                          $("steppable::mat2d",
                            "88331f88-3a4c-4b7e-9b43-b51a1d1020e2",
                            { std::to_string(_cols), std::to_string(rhs._cols) }));
            utils::programSafeExit(1);
        }

        MatVec2D<Number> resData = data;
        std::ranges::for_each(rhs.data, [&](const auto& row) { resData.emplace_back(row); });
        return MatrixBase{ resData };
    }

    MatrixBase MatrixBase::operator*=(const Number& rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    MatrixBase MatrixBase::operator*=(const MatrixBase& rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    MatrixBase MatrixBase::operator^(const Number& times) const
    {
        _checkSelfSanity();

        if (_rows != _cols)
        {
            output::error("Matrix::operator^"s, $("steppable::mat2d"s, "fe78bdc2-b409-4078-8e0e-313c46977f25"s));
            utils::programSafeExit(1);
        }

        auto matrix = *this;

        // Take inverse of matrix
        if (times == -1)
        {
            matrix <<= SpecialMatrix::diag(_rows);
            matrix = matrix.rref();
            matrix = matrix[{ .y1 = 0, .x1 = _rows, .y2 = _rows - 1, .x2 = _cols * 2 - 1 }];
            return matrix;
        }
        // Matrix to power 0 yields the identity matrix
        if (times == 0)
            return SpecialMatrix::diag(_rows, _cols);

        for (Number i = 0; i < times; ++i)
            matrix *= matrix;
        return matrix;
    }

    std::string MatrixBase::present(const int endRows) const
    {
        _checkSelfSanity();

        return prettyPrint::printers::ppMatrix(data, endRows);
    }

    Number MatrixBase::rank() const
    {
        _checkSelfSanity();

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

    MatrixBase MatrixBase::transpose() const
    {
        _checkSelfSanity();

        MatrixBase matrix(_cols, _rows);
        for (size_t i = 0; i < _rows; i++)
            for (size_t j = 0; j < _cols; j++)
                matrix[{ .y = j, .x = i }] = data[i][j];
        return matrix;
    }

    bool MatrixBase::operator==(const MatrixBase& rhs) const
    {
        _checkSelfSanity();

        return data == rhs.data;
    }

    bool MatrixBase::operator!=(const MatrixBase& rhs) const
    {
        _checkSelfSanity();

        return not(*this == rhs);
    }

    MatrixBase MatrixBase::operator<(const MatrixBase& rhs) const
    {
        _checkSelfSanity();

        if (rhs._cols != _cols)
        {
            output::error("Matrix::operator<"s,
                          $("steppable::mat2d"s,
                            "88331f88-3a4c-4b7e-9b43-b51a1d1020e2"s,
                            { std::to_string(_cols), std::to_string(rhs._cols) }));
            utils::programSafeExit(1);
        }

        if (rhs._rows != _rows)
        {
            output::error("Matrix::operator<"s,
                          $("steppable::mat2d"s,
                            "34e92306-a4d8-4ff0-8441-bfcd29771e94"s,
                            { std::to_string(_cols), std::to_string(rhs._cols) }));
            utils::programSafeExit(1);
        }

        MatrixBase res = SpecialMatrix::zeros(_rows, _cols);
        for (size_t j = 0; j < _rows; j++)
        {
            for (size_t i = 0; i < _cols; i++)
                if (not(data[j][i] < rhs.data[j][i]))
                    res[{ .y = j, .x = i }] = 1;
        }
        return res;
    }

    MatrixBase MatrixBase::operator<=(const MatrixBase& rhs) const
    {
        _checkSelfSanity();

        if (rhs._cols != _cols)
        {
            output::error("Matrix::operator<="s,
                          $("steppable::mat2d"s,
                            "88331f88-3a4c-4b7e-9b43-b51a1d1020e2"s,
                            { std::to_string(_cols), std::to_string(rhs._cols) }));
            utils::programSafeExit(1);
        }

        if (rhs._rows != _rows)
        {
            output::error("Matrix::operator<="s,
                          $("steppable::mat2d"s,
                            "34e92306-a4d8-4ff0-8441-bfcd29771e94"s,
                            { std::to_string(_cols), std::to_string(rhs._cols) }));
            utils::programSafeExit(1);
        }

        MatrixBase res = SpecialMatrix::zeros(_rows, _cols);
        for (size_t j = 0; j < _rows; j++)
        {
            for (size_t i = 0; i < _cols; i++)
                if (not(data[j][i] <= rhs.data[j][i]))
                    res[{ .y = j, .x = i }] = 1;
        }
        return res;
    }

    MatrixBase MatrixBase::operator>(const MatrixBase& rhs) const
    {
        _checkSelfSanity();

        if (rhs._cols != _cols)
        {
            output::error("Matrix::operator>"s,
                          $("steppable::mat2d"s,
                            "88331f88-3a4c-4b7e-9b43-b51a1d1020e2"s,
                            { std::to_string(_cols), std::to_string(rhs._cols) }));
            utils::programSafeExit(1);
        }

        if (rhs._rows != _rows)
        {
            output::error("Matrix::operator>"s,
                          $("steppable::mat2d"s,
                            "34e92306-a4d8-4ff0-8441-bfcd29771e94"s,
                            { std::to_string(_cols), std::to_string(rhs._cols) }));
            utils::programSafeExit(1);
        }

        MatrixBase res = SpecialMatrix::zeros(_rows, _cols);
        for (size_t j = 0; j < _rows; j++)
        {
            for (size_t i = 0; i < _cols; i++)
                if (not(data[j][i] > rhs.data[j][i]))
                    res[{ .y = j, .x = i }] = 1;
        }
        return res;
    }

    MatrixBase MatrixBase::operator>=(const MatrixBase& rhs) const
    {
        _checkSelfSanity();

        if (rhs._cols != _cols)
        {
            output::error("Matrix::operator>="s,
                          $("steppable::mat2d"s,
                            "88331f88-3a4c-4b7e-9b43-b51a1d1020e2"s,
                            { std::to_string(_cols), std::to_string(rhs._cols) }));
            utils::programSafeExit(1);
        }

        if (rhs._rows != _rows)
        {
            output::error("Matrix::operator>="s,
                          $("steppable::mat2d"s,
                            "34e92306-a4d8-4ff0-8441-bfcd29771e94"s,
                            { std::to_string(_cols), std::to_string(rhs._cols) }));
            utils::programSafeExit(1);
        }

        MatrixBase res = SpecialMatrix::zeros(_rows, _cols);
        for (size_t j = 0; j < _rows; j++)
        {
            for (size_t i = 0; i < _cols; i++)
                if (not(data[j][i] >= rhs.data[j][i]))
                    res[{ .y = j, .x = i }] = 1;
        }
        return res;
    }

    Number& MatrixBase::operator[](const YXPoint& point)
    {
        _checkSelfSanity();

        const auto x = point.x;
        const auto y = point.y;

        _checkIdxSanity(&point);
        return data[y][x];
    }

    Number MatrixBase::operator[](const YXPoint& point) const
    {
        _checkSelfSanity();

        const auto x = point.x;
        const auto y = point.y;

        _checkIdxSanity(&point);
        return data[y][x];
    }

    MatrixBase MatrixBase::operator[](const YX2Points& point) const
    {
        _checkSelfSanity();

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

        auto matrix = MatrixBase(y2 - y1 + 1, x2 - x1 + 1);

        for (size_t i = y1; i <= y2; i++)
            for (size_t j = x1; j <= x2; j++)
                matrix[{ .y = i - y1, .x = j - x1 }] = data[i][j];
        return matrix;
    }

    MatrixBase MatrixBase::reverse(const MatReverseMode& axis) const
    {
        MatrixBase res = *this;
        auto reverseRows = [&]() -> void { std::ranges::reverse(res.data); };
        auto reverseCols = [&]() -> void {
            for (auto& row : res.data)
                std::ranges::reverse(row);
        };

        switch (axis)
        {
        case MatReverseMode::REVERSE_ROWS:
        {
            // Reverse rows
            reverseRows();
        }
        case MatReverseMode::REVERSE_COLS:
        {
            // Reverse columns
            reverseCols();
            break;
        }
        default:
        {
            // Reverse both rows and columns
            reverseRows();
            reverseCols();
            break;
        }
        }
        return res;
    }
} // namespace steppable
