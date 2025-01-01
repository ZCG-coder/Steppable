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

#include <functional>
#include <string>

/**
 * @namespace steppable::__internals::calculus
 * @brief Contains calculus functions.
 */
namespace steppable::__internals::calculus
{
    /**
     * @brief Calculates the Romberg integration of f.
     *
     * @param f The function to integrate. It takes in one argument and returns a string.
     * @param a Lower bound of integral.
     * @param b Upper bound of integral.
     * @param max_steps Maximum steps of integral. More steps can produce higher accuracy, but takes a longer time.
     * @param decimals The decimals to output.
     * @return The result of the integral.
     *
     * @note The function must take in exactly ONE argument, in the form of std::string. The output must be a
     * std::string object. Wrap your function in a lambda expression if it takes more arguments, or outputs in a
     * different type.
     */
    std::string romberg(const std::function<std::string(std::string)>& f,
                        const std::string& a,
                        const std::string& b,
                        int max_steps,
                        int decimals);
} // namespace steppable::__internals::calculus
