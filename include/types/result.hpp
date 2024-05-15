/**************************************************************************************************
 * Copyright (c) 2023-2024 NWSOFT                                                                 *
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

#include <string>
#include <utility>
#include <vector>

/**
 * @namespace steppable::types
 * @brief The namespace containing types used in the steppable calculator.
 */
namespace steppable::types
{
    /**
     * @brief The status of the calculation.
     */
    enum Status
    {
        CALCULATED_SIMPLIFIED,
        CALCULATED_UNSIMPLIFIED,
        MATH_ERROR
    };

    /**
     * @brief The result of a calculation.
     */
    class Result
    {
    private:
        /// @brief Whether the calculation is done.
        Status done;

        /// @brief The inputs to the calculation.
        std::vector<std::string> inputs;

        /// @brief The output of the calculation.
        std::string out;

    public:
        Result() = delete;

        /**
         * @brief Constructs a new result object.
         *
         * @param[in] _inputs The inputs to the calculation.
         * @param[in] _out The output of the calculation.
         * @param[in] _done A flag indicating how the calculation is done.
         */
        Result(const std::vector<std::string>& _inputs, std::string _out, Status _done) :
            done(_done), inputs(_inputs), out(std::move(_out))
        {
        }

        /// @brief Gets how the calculation is done.
        Status getStatus() { return done; }
    };
} // namespace steppable::types
