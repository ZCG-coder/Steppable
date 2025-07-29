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
#include "steppable/mat2d.hpp"
#include "steppable/mat2dBase.hpp"
#include "steppable/number.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <math.h>
#include <memory>
#include <string>

namespace steppable
{
    using namespace __internals;
    using namespace __internals::numUtils;

    MatrixBase SpecialMatrix::ones(const size_t& rows, const size_t& cols)
    {
        return MatrixBase(rows, cols, Number("1"));
    }

    MatrixBase SpecialMatrix::zeros(const size_t& rows, const size_t& cols) { return MatrixBase(rows, cols); }

    MatrixBase SpecialMatrix::diag(const size_t& cols, const Number& fill, const size_t& _rows, const long long& offset)
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

    MatrixBase SpecialMatrix::magic(const size_t& colsRows)
    {
        MatrixBase res = zeros(colsRows, colsRows);
        return res;
    }

    MatrixBase SpecialMatrix::hilbert(const size_t& colsRows)
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
        size_t cols = vec.getCols();
        MatrixBase res = zeros(cols, cols);

        for (size_t j = 0; j < cols; j++)
            for (size_t i = 0; i < cols; i++)
                res[{ .y = i, .x = j }] = vec[{ .y = 0, .x = i }] ^ (cols - j - 1);

        return res;
    }

    MatrixBase SpecialMatrix::toeplitz(const MatrixBase& _firstColRow, const MatrixBase& _firstRow)
    {
        MatrixBase firstRow;
        MatrixBase firstCol;
        // Called with toeplitz(r)
        if (_firstRow.empty())
            firstRow = _firstColRow;

        // Called with toeplitz(c, r)
        else
        {
            firstCol = _firstColRow;
            firstRow = _firstRow;
        }

        if (firstCol.getRows() != 1)
        {
            output::error("SpecialMatrix::toeplitz"s, "Expect vector for first column."s);
            utils::programSafeExit(1);
        }
        if (firstRow.getRows() != 1)
        {
            output::error("SpecialMatrix::toeplitz"s, "Expect vector for first row."s);
            utils::programSafeExit(1);
        }

        if (firstCol[{ .y = 0, .x = 0 }] != firstRow[{ .y = 0, .x = 0 }])
        {
            output::warning("SpecialMatrix::toeplitz"s,
                            "First element of the first column does not match first element of the first row."s);
            output::info("SpecialMatrix::toeplitz"s, "Using column value."s);
        }

        MatrixBase res(0, 0);
        size_t matrixCols = firstRow.getCols();
        size_t matrixRows = firstCol.getCols();
        firstRow = firstRow[{ .y1 = 0, .x1 = 1, .y2 = 0, .x2 = matrixCols - 1 }];

        for (size_t i = 0; i < matrixCols; i++)
        {
            MatrixBase col = firstCol;
            if (i != 0)
            {
                const auto& firstRowElem = firstRow[{ .y1 = 0, .x1 = 0, .y2 = 0, .x2 = i - 1 }];
                col >>= firstRowElem.reverse(MatReverseMode::REVERSE_COLS);
            }
            col = col.transpose();
            col = col[{ .y1 = 0, .x1 = 0, .y2 = matrixRows - 1, .x2 = 0 }];

            res <<= col;
        }

        return res;
    }

    MatrixBase SpecialMatrix::hadamard(const size_t& order)
    {
        if (order == 1)
            return ones(1, 1);

        const long double logN = log2(order); // log2(n)
        const long double logN12 = log2(static_cast<long double>(order) / 12); // log2(n/12)
        const long double logN20 = log2(static_cast<long double>(order) / 20); // log2(n/20)

        auto discardable = std::make_unique<long double>();
        long double logNRemainder = modfl(logN, discardable.get());
        long double logNRemainder12 = modfl(logN12, discardable.get());
        long double logNRemainder20 = modfl(logN20, discardable.get());
        discardable.reset();

        if (logNRemainder * logNRemainder12 * logNRemainder20 != 0.0)
        {
            output::error("SpecialMatrix::hadamard"s, "n, n/12 or n/20 must be an exponent of 2."s);
            utils::programSafeExit(1);
        }
        long double e = NAN;
        MatrixBase res;

        if (logNRemainder == 0.0)
        {
            e = logN - 1;
            res = ones(1, 1);
        }
        else if (logNRemainder12 == 0.0)
        {
            e = logN12 - 1;
            res = MatrixBase(hadamardKnown12());
        }
        else if (logNRemainder20 == 0.0)
        {
            e = logN20 - 1;
            res = MatrixBase(hadamardKnown20());
        }
        assert(e != NAN);

        for (size_t i = 0; i <= static_cast<size_t>(e); i++)
        {
            // Sylvester's construction
            // If H is a known Hadamard matrix of order n,
            // [ H  H ]
            // [ H -H ]
            // will be a Hadamard matrix of order 2n.
            res = MatrixBase({
                { res, res },
                { res, -res },
            });
        }

        return res;
    }
} // namespace steppable
