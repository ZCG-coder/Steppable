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

#pragma once

#include "steppable/number.hpp"

#include <array>
#include <initializer_list>

namespace steppable
{

    /**
     * @brief Alias for a 2D matrix represented as a `std::initializer_list` of vectors.
     * @tparam NumberT The type of the numbers in the matrix.
     */
    template<typename NumberT>
    using MatInitializerList2D = std::initializer_list<std::initializer_list<NumberT>>;

    /**
     * @brief Compile-time fixed-size matrix with Number elements.
     * @tparam Rows Number of rows.
     * @tparam Cols Number of columns.
     */
    template<size_t Rows, size_t Cols>
    struct ConstexprMatrix
    {
        std::array<std::array<ConstexprNumber, Cols>, Rows> data;

        /**
         * @brief Construct from a nested std::array.
         */
        constexpr ConstexprMatrix(const std::array<std::array<ConstexprNumber, Cols>, Rows>& arr) noexcept : data(arr)
        {
        }

        /**
         * @brief Construct from initializer_list of initializer_list of ConstexprNumber.
         */
        constexpr ConstexprMatrix(const MatInitializerList2D<ConstexprNumber>& init) noexcept
        {
            size_t i = 0;
            for (const auto& row : init)
            {
                size_t j = 0;
                for (const auto& val : row)
                    data[i][j++] = val;
                ++i;
            }
        }
    };

} // namespace steppable
