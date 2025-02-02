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

#include "types/result.hpp"

#include <string>
#include <vector>

using namespace steppable::types;

namespace steppable::__internals::numUtils
{
    /**
     * @brief Get the factors of a number.
     *
     * @param[in] _number The number to get the factors of.
     * @return The factors of the number.
     */
    std::vector<std::string> getFactors(const std::string& _number);

    /**
     * @brief Get the largest factor of a number, that is a root number.
     *
     * @param[in] _number The number to get the largest root factor of.
     * @param[in] base The base of the root.
     * @return A result object containing the largest root factor of the number.
     */
    ResultBool<std::string> getRootFactor(const std::string& _number, const std::string& base = "2");

    /**
     * @brief Get the greatest root number less than or equal to the given number.
     *
     * @param[in] _number The number to get the greatest root number of.
     * @param[in] base The base of the root.
     * @return The greatest root number less than or equal to the given number.
     */
    std::string getGreatestRootNum(const std::string& _number, const std::string& base = "2");

    /**
     * @brief Check if a number is prime.
     *
     * @param[in] _number The number to check.
     * @return True if the number is prime, false otherwise.
     */
    bool isPrime(const std::string& _number);

    /**
     * @brief Check if a number is a root number.
     *
     * @param[in] _number The number to check.
     * @param[in] base The base of the root.
     * @return StatusBool::CALCULATED_SIMPLIFIED_YES if the number is a root number,
     * StatusBool::CALCULATED_SIMPLIFIED_NO otherwise.
     */
    ResultBool<std::string> isRoot(const std::string& _number, const std::string& base);
} // namespace steppable::__internals::numUtils
