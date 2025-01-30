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

#include <output.hpp>
#include <platform.hpp>
#include <string>
#include <util.hpp>
#include <utility>
#include <vector>

using namespace std::literals;
using namespace steppable::__internals::utils;

/**
 * @namespace steppable::types
 * @brief The namespace containing types used in the steppable calculator.
 */
namespace steppable::types
{
    /**
     * @brief The status of the calculation.
     */
    enum class Status : std::uint8_t
    {
        CALCULATED_SIMPLIFIED,
        CALCULATED_UNSIMPLIFIED,
        MATH_ERROR
    };

    /**
     * @brief The status of a boolean calculation.
     */
    enum class StatusBool : std::uint8_t
    {
        CALCULATED_SIMPLIFIED_YES,
        CALCULATED_SIMPLIFIED_NO,
        CALCULATED_UNSIMPLIFIED_YES,
        CALCULATED_UNSIMPLIFIED_NO,
        MATH_ERROR
    };

    /**
     * @brief A base class for a result of a calculation. You should use the `Result` and `ResultBool` aliases instead
     * of this class, which has the `Status` and `StatusBool` enums as the status type respectively.
     *
     * @tparam StatusType The type of the status of the calculation.
     */
    template<typename StatusType, typename ResultT, StringLiteral ResultTName>
    class ResultBase
    {
        /// @brief Whether the calculation is done.
        StatusType done;

        /// @brief The inputs to the calculation.
        std::vector<std::string> inputs;

        /// @brief The output of the calculation.
        std::vector<std::string> outputs;

        /// @brief The result of the calculation
        /// @attention This is different from `inputs`, as it stores only the result of the operation.
        ResultT result;

    public:
        ResultBase() = delete;

        /**
         * @brief Constructs a new result object.
         *
         * @param[in] _inputs The inputs to the calculation.
         * @param[in] _out The output of the calculation.
         * @param result The result of the calculation.
         * @param[in] _done A flag indicating how the calculation is done.
         */
        ResultBase(const std::vector<std::string>& _inputs,
                   std::vector<std::string> _out,
                   ResultT result,
                   StatusType _done) :
            done(_done), inputs(_inputs), outputs(std::move(_out)), result(result)
        {
        }

        /// @brief Gets how the calculation is done.
        StatusType getStatus() const { return done; }

        ResultT getResult() const { return result; }

        /// @brief Gets the output of the calculation.
        [[nodiscard("Output should be used")]] std::string getOutput(size_t idx = 0) const
        {
            if (idx >= outputs.size())
            {
                output::error("getOutput"s, "Output index out of range"s);
                programSafeExit(1);
            }
            return outputs[idx];
        }

        /// @brief Gets the inputs to the calculation.
        [[nodiscard("Inputs should be used")]] std::vector<std::string> getInputs() const { return inputs; }
    };

    /// @brief An alias for a result of a calculation. This represents a calculation with a `Status` status.
    template<typename ResultT>
    using Result = ResultBase<Status, ResultT, StringLiteral{ "str" }>;

    /// @brief An alias for a result of a boolean calculation.
    template<typename ResultT>
    using ResultBool = ResultBase<StatusBool, ResultT, StringLiteral{ "bool" }>;
} // namespace steppable::types
