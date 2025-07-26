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

#include "steppable/mat2dSpecial.hpp"

#include "output.hpp"
#include "platform.hpp"
#include "steppable/number.hpp"

#include <algorithm>
#include <string>

namespace steppable
{
    using namespace __internals;
    using namespace __internals::numUtils;

    MatrixBase SpecialMatrix::ones(const size_t rows, const size_t cols) { return MatrixBase(rows, cols, Number("1")); }

    MatrixBase SpecialMatrix::zeros(const size_t rows, const size_t cols) { return MatrixBase(rows, cols); }

    MatrixBase SpecialMatrix::diag(const size_t cols, const Number& fill, const size_t _rows, const long long offset)
    {
        size_t rows = _rows == 0 ? cols : _rows;
        MatrixBase matrix(cols, rows);
        for (size_t i = 0; i < cols; i++)
        {
            size_t j = i;
            if (j >= rows || j >= cols)
                break;
            matrix[{ .y = j, .x = j }] = fill;
        }
        return matrix;
    }

    MatrixBase SpecialMatrix::hankel(const MatrixBase& _firstCol, const MatrixBase& _lastRow)
    {
        auto lastRow = _lastRow;
        auto firstCol = _firstCol;
        if (firstCol.getRows() != 1)
        {
            output::error("SpecialMatrix::hankel"s, "Expect vector for first column."s);
            utils::programSafeExit(1);
        }
        if (lastRow.getRows() != 1)
        {
            output::error("SpecialMatrix::hankel"s, "Expect vector for last row."s);
            utils::programSafeExit(1);
        }
        firstCol = firstCol.transpose();

        // Column wins anti-diagonal conflict.
        Number firstColLast = firstCol[{ .y = firstCol.getRows() - 1, .x = 0 }];
        if (firstColLast != lastRow[{ .y = 0, .x = 0 }])
        {
            output::warning("SpecialMatrix::hankel"s,
                            "Last element of the first column does not match first element of the last row."s);
            output::info("SpecialMatrix::hankel"s, "Using column value."s);
            lastRow[{ .y = 0, .x = 0 }] = firstColLast;
        }
        size_t resRows = firstCol.getRows();
        size_t resCols = lastRow.getCols();
        MatrixBase res = zeros(resRows, resCols);

        std::vector row = _firstCol.getData().front();
        const auto lastRowVec = lastRow.getData().front();
        std::for_each(lastRowVec.begin() + 1, lastRowVec.end(), [&](const auto& val) { row.emplace_back(val); });
        // Fill in the rest
        for (size_t j = 0; j < resRows; j++)
        {
            for (size_t i = 0; i < resCols; i++)
                res[{ .y = j, .x = i }] = row[i];
            row.erase(row.cbegin());
        }
        return res;
    }

    MatrixBase SpecialMatrix::magic(size_t colsRows)
    {
        MatrixBase res = zeros(colsRows, colsRows);
        return res;
    }

    MatrixBase SpecialMatrix::hilbert(const size_t colsRows)
    {
        MatrixBase res = zeros(colsRows, colsRows);
        res = res.roundOffValues(8);

        for (size_t i = 0; i < colsRows; i++)
            for (size_t j = 0; j < colsRows; j++)
                res[{ .y = i, .x = j }] = Number(1) / (i + j + 1);
        return res;
    }

    MatrixBase SpecialMatrix::vandermonde(const MatrixBase& vec)
    {
        if (vec.getRows() != 1)
        {
            output::error("SpecialMatrix::vandermonde"s, "Input is not a vector."s);
            utils::programSafeExit(1);
        }
        MatrixBase res;

        return res;
    }
} // namespace steppable
