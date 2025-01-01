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
 * @file exceptions.hpp
 * @brief This file contains the definition of exceptions.
 *
 * @author Andy Zhang
 * @date 13th March 2024
 */

#pragma once

#include <exception>

/**
 * @namespace steppable::exceptions
 * @brief Contains Steppable exceptions.
 */
namespace steppable::exceptions
{
    /**
     * @class ZeroDenominatorException
     * @brief Thrown when initializing a fraction with zero as denominator.
     */
    class ZeroDenominatorException final : public std::exception
    {
    public:
        [[nodiscard]] const char* what() const noexcept override
        {
            return "The denominator is zero, which is not allowed.";
        }
    };

    /**
     * @class MultiLengthLetterException
     * @brief Thrown when initializing a Key object with two or more letters.
     */
    class MultiLengthLetterException final : public std::exception
    {
    public:
        [[nodiscard]] const char* what() const noexcept override { return "The length of letter exceeds the 1 limit."; }
    };
} // namespace steppable::exceptions
