/**************************************************************************************************
 * Copyright (c) 2023-2026 NWSOFT                                                                 *
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

#include "steppable/number.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace steppable
{
    using namespace numUtils;

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
} // namespace steppable
