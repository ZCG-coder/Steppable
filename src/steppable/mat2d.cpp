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

#include "output.hpp"
#include "rounding.hpp"
#include "steppable/number.hpp"
#include "symbols.hpp"
#include "util.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
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
        data = roundOffValues(data, prec);
    }

    Matrix::Matrix(const MatVec2D<Number>& data) : data(data), _cols(data.front().size()), _rows(data.size())
    {
        for (auto& row : this->data)
            for (auto& value : row)
                value.setPrec(prec + 3, RoundingMode::USE_MAXIMUM_PREC);
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

    Matrix Matrix::ref()
    {
        // Adapted from https://stackoverflow.com/a/31761026/14868780
        auto matrix = data;
        matrix = roundOffValues(matrix, prec);
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

        matrix = roundOffValues(matrix, prec);
        return matrix;
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

} // namespace steppable
