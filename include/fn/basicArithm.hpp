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

#include <string>
#include <string_view>
#include "output.hpp"

/**
 * @brief Calculates the absolute value of a string representation of a number.
 *
 * @param _number The string representation of the number.
 * @param steps The number of steps to perform the calculation.
 * @return The absolute value of the number as a string.
 */
std::string abs(const std::string_view& _number, int steps);

/**
 * @brief Adds two string representations of numbers, and performs with the column method.
 *
 * @param a The first string representation of the number.
 * @param b The second string representation of the number.
 * @param steps The number of steps to perform the addition. 2 = column method, 1 = normal addition, 0 = result only.
 * Default is 2.
 * @param negative Flag indicating whether the result should be negative.
 * @return The sum of the two numbers as a string.
 */
std::string add(const std::string_view& a, const std::string_view& b, int steps = 2, bool negative = false);

/**
 * @brief Compares two string representations of numbers.
 *
 * @param a The first string representation of the number.
 * @param b The second string representation of the number.
 * @param steps The number of steps to perform the comparison.
 * @return A string indicating the result of the comparison:
 *         "2" if a and b are equal,
 *         "1" if a is greater than b,
 *         "0" if a is less than b.
 */
std::string compare(const std::string_view& a, const std::string_view& b, int steps = 2);

/**
 * @brief Converts a string representation of a number from one base to another.
 *
 * @param _inputString The string representation of the number.
 * @param baseString The base of the input number.
 * @param steps The number of steps to perform the conversion.
 * @return The converted number as a string.
 *
 * @warning Still in development.
 */
std::string decimalConvert(const std::string_view& _inputString, const std::string_view& baseString, int steps = 2);

/**
 * @brief Divides a string representation of a number by another string representation of a number.
 *
 * @param number The string representation of the dividend.
 * @param divisor The string representation of the divisor.
 * @param steps The number of steps to perform the division.
 * @param decimals The number of decimal places in the result.
 * @return The quotient of the division as a string.
 */
std::string divide(const std::string_view& number, const std::string_view& divisor, int steps = 2, int decimals = 5);

/**
 * @brief Multiplies two string representations of numbers.
 *
 * @param a The first string representation of the number.
 * @param b The second string representation of the number.
 * @param steps The number of steps to perform the multiplication.
 * @return The product of the two numbers as a string.
 */
std::string multiply(const std::string_view& a, const std::string_view& b, int steps = 2);

/**
 * @brief Raises a string representation of a number to a power.
 *
 * @param _number The string representation of the number.
 * @param raiseTo The string representation of the power to raise the number to.
 * @param steps The number of steps to perform the power operation.
 * @return The result of the power operation as a string.
 */
std::string power(std::string_view _number, const std::string_view& raiseTo, int steps = 2);

/**
 * @brief Subtracts one string representation of a number from another string representation of a number.
 *
 * @param a The string representation of the minuend.
 * @param b The string representation of the subtrahend.
 * @param steps The number of steps to perform the subtraction.
 * @param noMinus Flag indicating whether to display a minus sign or not.
 * @return The difference between the two numbers as a string.
 */
std::string subtract(const std::string_view& a,
                     const std::string_view& b,
                     int steps = 2,
                     bool noMinus = false);

/**
 * @brief Executes a given predicate function a specified number of times.
 *
 * @param times The number of times to execute the predicate function.
 * @param predicate The predicate function to execute.
 */
template<typename Pred>
void loop(const std::string_view& times, Pred predicate)
{
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
            error("loop", static_cast<std::string>("Exception occurred in predicate."));
            error("loop", static_cast<std::string>("Exception message: %s"), e.what());
        }
        current = add(current, "1", 0);
        result = compare(current, times, 0);
    }
}
