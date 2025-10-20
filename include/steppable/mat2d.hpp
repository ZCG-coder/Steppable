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

#include "steppable/mat2dBase.hpp"
#include "steppable/mat2dSpecial.hpp"

#include <cstddef>
#include <string_view>

namespace steppable
{
    namespace prettyPrint::printers
    {
        /**
         * @brief Pretty prints a matrix.
         * @param matrix The matrix to be pretty printed.
         * @return A string representation of the matrix.
         */
        std::string ppMatrix(const MatVec2D<Number>& matrix, int endRows = 0);
    } // namespace prettyPrint::printers

    namespace symbols
    {
        constexpr std::string_view MATRIX_LEFT_TOP = "\u23A1";
        constexpr std::string_view MATRIX_LEFT_MIDDLE = "\u23A2";
        constexpr std::string_view MATRIX_LEFT_BOTTOM = "\u23A3";
        constexpr std::string_view MATRIX_RIGHT_TOP = "\u23A4";
        constexpr std::string_view MATRIX_RIGHT_MIDDLE = "\u23A5";
        constexpr std::string_view MATRIX_RIGHT_BOTTOM = "\u23A6";
    } // namespace symbols

    class Matrix : public MatrixBase, public SpecialMatrix
    {
    public:
        using MatrixBase::MatrixBase;

        Matrix(const MatrixBase& rhs) : MatrixBase(rhs) {}

        Matrix& operator=(const MatrixBase& rhs)
        {
            MatrixBase::operator=(rhs);
            return *this;
        }
    };
} // namespace steppable
