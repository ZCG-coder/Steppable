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

/**
 * @file basicArithm.hpp
 * @brief This file contains functions for basic arithmetic operations on strings.
 *
 * The functions in this file perform various arithmetic operations on strings, such as absolute value,
 * addition, comparison, decimal conversion, division, multiplication, power, and subtraction.
 * Additionally, there is a template function for looping a specified number of times.
 *
 * @author Andy Zhang
 *
 * @date 8th November 2023
 */

#pragma once

#include "fn/root.hpp"
#include "output.hpp"

#include <string>
#include <string_view>

using namespace std::literals;

/**
 * @namespace steppable::__internals
 * @brief The namespace containing internal functions for the Steppable library.
 */
namespace steppable::__internals::arithmetic
{
    /**
     * @brief Represents the quotient and remainder of a division operation.
     */
    struct QuotientRemainder
    {
        std::string quotient;
        std::string remainder;
    };

    /**
     * @brief Calculates the absolute value of a string representation of a number.
     *
     * @param[in] _number The string representation of the number.
     * @param[in] steps The number of steps to perform the calculation.
     * @return The absolute value of the number as a string.
     */
    std::string abs(const std::string_view& _number, int steps);

    /**
     * @brief Adds two string representations of numbers, and performs with the column method.
     *
     * @param[in] a The first string representation of the number.
     * @param[in] b The second string representation of the number.
     * @param[in] steps The number of steps to perform the addition. 2 = column method, 1 = normal addition, 0 = result
     * only. Default is 2.
     * @param[in] negative Flag indicating whether the result should be negative.
     * @param[in] properlyFormat Flag indicating whether to properly format the output. Default true.
     * @return The sum of the two numbers as a string.
     */
    std::string add(const std::string_view& a,
                    const std::string_view& b,
                    int steps = 2,
                    bool negative = false,
                    bool properlyFormat = true);

    /**
     * @brief Compares two string representations of numbers.
     *
     * @param[in] _a The first string representation of the number.
     * @param[in] _b The second string representation of the number.
     * @param[in] steps The number of steps to perform the comparison.
     * @return A string indicating the result of the comparison:
     *         "2" if a and b are equal,
     *         "1" if a is greater than b,
     *         "0" if a is less than b.
     */
    std::string compare(const std::string_view& _a, const std::string_view& _b, int steps = 2);

    /**
     * @brief Converts a string representation of a number from any base to decimal.
     *
     * @param[in] _inputString The string representation of the number.
     * @param[in] baseString The base of the input number.
     * @param[in] steps The number of steps to perform the conversion.
     * @return The converted number as a string.
     */
    std::string decimalConvert(const std::string_view& _inputString, const std::string_view& baseString, int steps = 2);

    /**
     * @brief Converts a string representation of a number from decimal to another one.
     *
     * @param[in] _number The string representation of the number.
     * @param[in] baseString The desired base.
     * @param[in] steps The number of steps to perform the conversion.
     * @return The converted number as a string.
     */
    std::string baseConvert(const std::string_view& _number, const std::string_view& baseStr, int steps = 2);

    /**
     * @brief Divides a string representation of a number by another string representation of a number.
     *
     * @param[in] number The string representation of the dividend.
     * @param[in] divisor The string representation of the divisor.
     * @param[in] steps The number of steps to perform the division.
     * @param[in] decimals The number of decimal places in the result.
     * @return The quotient of the division as a string.
     */
    std::string divide(const std::string_view& number,
                       const std::string_view& divisor,
                       int steps = 2,
                       int decimals = 5);

    /**
     * Calculates the quotient and remainder of dividing the current remainder by the divisor.
     *
     * @param[in] number The number.
     * @param[in] divisor The divisor.
     * @return A QuotientRemainder object containing the quotient and remainder.
     */
    QuotientRemainder divideWithQuotient(const std::string& number, const std::string& divisor);

    /**
     * @brief Gets the greatest common divisor of two string representations of numbers.
     *
     * @param _a Number 1.
     * @param _b Number 2.
     *
     * @return The greatest common divisor of the two numbers.
     */
    std::string getGCD(const std::string_view& _a, const std::string_view& _b);

    /**
     * @brief Multiplies two string representations of numbers.
     *
     * @param[in] a The first string representation of the number.
     * @param[in] b The second string representation of the number.
     * @param[in] steps The number of steps to perform the multiplication.
     * @return The product of the two numbers as a string.
     */
    std::string multiply(const std::string_view& a, const std::string_view& b, int steps = 2);

    /**
     * @brief Raises a string representation of a number to a power.
     *
     * @param[in] _number The string representation of the number.
     * @param[in] raiseTo The string representation of the power to raise the number to.
     * @param[in] steps The number of steps to perform the power operation.
     * @return The result of the power operation as a string.
     */
    std::string power(std::string_view _number, const std::string_view& raiseTo, int steps = 2);

    /**
     * @brief Subtracts one string representation of a number from another string representation of a number.
     *
     * @param[in] a The string representation of the minuend.
     * @param[in] b The string representation of the subtrahend.
     * @param[in] steps The number of steps to perform the subtraction.
     * @param[in] noMinus Flag indicating whether to display a minus sign or not.
     * @return The difference between the two numbers as a string.
     */
    std::string subtract(const std::string_view& a, const std::string_view& b, int steps = 2, bool noMinus = false);

    /**
     * @brief Takes the n-th root of a numer.
     *
     * @param _number The number to take root of.
     * @param base The base of the root.
     * @param decimals The decimals of the operation.
     * @param steps The steps to show while taking the root.
     *
     * @return The result of the root operation.
     */
    std::string root(const std::string& _number, const std::string& base, size_t decimals = 8);

    /**
     * @brief Converts a root operation into a surd.
     *
     * @param _number The number to convert to a surd.
     * @param base The base of the root.
     * @return The surd object.
     */
    Surd rootSurd(const std::string& _number, const std::string& base);

    /**
     * @brief Gets the integer part of the root of a number.
     *
     * @param _number The number to get the root of.
     * @param base The base of the root.
     *
     * @return The integer part of the root of the number.
     */
    std::string rootIntPart(const std::string& _number, const std::string& base);

    /**
     * @brief Executes a given predicate function a specified number of times.
     *
     * @param[in] times The number of times to execute the predicate function.
     * @param[in] predicate The predicate function to execute.
     */
    template<typename Pred>
    void loop(const std::string_view& times, Pred predicate)
    {
        // We're done already!
        if (times == "0")
            return;
        if (times == "1")
            return predicate("1");

        std::string current = "0";
        auto result = compare(current, times, 0);

        while (result == "0")
        {
            try
            {
                predicate(current);
            }
            catch (std::exception& e)
            {
                output::error("loop", "Exception occurred in predicate."s);
                output::error("loop", "Exception message: %s"s, e.what());
            }
            current = add(current, "1", 0);
            result = compare(current, times, 0);
        }
    }

} // namespace steppable::__internals::arithmetic
