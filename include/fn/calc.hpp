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
 * @file calc.hpp
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
#include "steppable/number.hpp"
#include "types/result.hpp"

#include <string>
#include <util.hpp>

using namespace std::literals;

/**
 * @namespace steppable::__internals::calc
 * @brief The namespace containing number calculating functions for the Steppable library.
 */
namespace steppable::__internals::calc
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
    std::string abs(const std::string& _number, int steps);

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
    std::string add(const std::string& a,
                    const std::string& b,
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
    std::string compare(const std::string& _a, const std::string& _b, int steps = 2);

    /**
     * @brief Converts a string representation of a number from any base to decimal.
     *
     * @param[in] _inputString The string representation of the number.
     * @param[in] baseString The base of the input number.
     * @param[in] steps The number of steps to perform the conversion.
     * @return The converted number as a string.
     */
    std::string decimalConvert(const std::string& _inputString, const std::string& baseString, int steps = 2);

    /**
     * @brief Converts a string representation of a number from decimal to another one.
     *
     * @param[in] _number The string representation of the number.
     * @param[in] baseStr The desired base.
     * @param[in] steps The number of steps to perform the conversion.
     * @return The converted number as a string.
     */
    std::string baseConvert(const std::string& _number, const std::string& baseStr, int steps = 2);

    /**
     * @brief Divides a string representation of a number by another string representation of a number.
     *
     * @param[in] number The string representation of the dividend.
     * @param[in] divisor The string representation of the divisor.
     * @param[in] steps The number of steps to perform the division.
     * @param[in] decimals The number of decimal places in the result.
     * @return The quotient of the division as a string.
     */
    std::string divide(const std::string& number, const std::string& divisor, int steps = 2, int decimals = 5);

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
    std::string getGCD(const std::string& _a, const std::string& _b);

    /**
     * @brief Multiplies two string representations of numbers.
     *
     * @param[in] a The first string representation of the number.
     * @param[in] b The second string representation of the number.
     * @param[in] steps The number of steps to perform the multiplication.
     * @return The product of the two numbers as a string.
     */
    std::string multiply(const std::string& a, const std::string& b, int steps = 2, int decimals = MAX_DECIMALS);

    /**
     * @brief Raises a string representation of a number to a power.
     *
     * @param[in] _number The string representation of the number.
     * @param[in] raiseTo The string representation of the power to raise the number to.
     * @param[in] steps The number of steps to perform the power operation.
     * @param[in] decimals The number of decimals to output from the power operation.
     * @return The result of the power operation as a string.
     */
    std::string power(const std::string& _number, const std::string& raiseTo, int steps = 2, int decimals = 8);

    /**
     * @brief Calculates e^x. Shorthand of power(x, E, 0);
     *
     * @param x The string representation of the number.
     * @param decimals The number of decimals to output.
     * @return The exponent of the number.
     */
    std::string exp(const std::string& x, size_t decimals = 10);

    /**
     * @brief Subtracts one string representation of a number from another string representation of a number.
     *
     * @param[in] a The string representation of the minuend.
     * @param[in] b The string representation of the subtrahend.
     * @param[in] steps The number of steps to perform the subtraction.
     * @param[in] noMinus Flag indicating whether to display a minus sign or not.
     * @return The difference between the two numbers as a string.
     */
    std::string subtract(const std::string& a, const std::string& b, int steps = 2, bool noMinus = false);

    /**
     * @brief Calculate the error between values a and b.
     * @details Gets the absolute difference between a and b.
     *
     * @param a Value 1
     * @param b Value 2
     *
     * @return The absolute value of the differnece between the values.
     */
    types::Result<Number> error(const std::string& a, const std::string& b);

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
    std::string root(const std::string& _number, const std::string& base, size_t decimals = 8, int steps = 0);

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
     * @brief Calculates the factorial of a number.
     *
     * @param _number The number to calculate the factorial of.
     * @param steps The number of steps to calculate the factorial.
     *
     * @return The factorial of the number.
     */
    std::string factorial(const std::string& _number, int steps = 2);

    /**
     * @brief Converts degrees to radians.
     *
     * @param _deg The angle expressed in degrees.
     * @return The equivalent angle in radians.
     */
    std::string degToRad(const std::string& _deg);

    /**
     * @brief Converts gradians to radians.
     *
     * @param _grad The angle expressed in gradians.
     * @return The equivalent angle in radians.
     */
    std::string gradToRad(const std::string& _grad);

    /**
     * @brief Calculates the cosine of a number.
     *
     * @param x The number to calculate the cosine of.
     * @param decimals The number of decimal places to round off to.
     * @param mode The mode to calculate the cosine in. 0 = radians (default), 1 = degrees, 2 = gradians.
     *
     * @return The cosine of the number.
     */
    std::string cos(const std::string& x, int decimals, int mode = 0);

    /**
     * @brief Calculates the sine of a number.
     *
     * @param x The number to calculate the sine of.
     * @param decimals The number of decimal places to round off to.
     * @param mode The mode to calculate the sine in. 0 = radians (default), 1 = degrees, 2 = gradians.
     *
     * @return The sine of the number.
     */
    std::string sin(const std::string& x, int decimals, int mode = 0);

    /**
     * @brief Calculates the tangent of a number.
     *
     * @param x The number to calculate the tangent of.
     * @param decimals The number of decimal places to round off to.
     * @param mode The mode to calculate the tangent in. 0 = radians (default), 1 = degrees, 2 = gradians.
     *
     * @return The tangent of the number.
     */
    std::string tan(const std::string& x, int decimals, int mode = 0);

    /**
     * @brief Calculates the secant of a number.
     *
     * @param x The number to calculate the secant of.
     * @param decimals The number of decimal places to round off to.
     * @param mode The mode to calculate the secant in. 0 = radians (default), 1 = degrees, 2 = gradians.
     *
     * @return The secant of the number.
     */
    std::string sec(const std::string& x, int decimals, int mode = 0);

    /**
     * @brief Calculates the cosecant of a number.
     *
     * @param x The number to calculate the cosecant of.
     * @param decimals The number of decimal places to round off to.
     * @param mode The mode to calculate the cosecant in. 0 = radians (default), 1 = degrees, 2 = gradians.
     *
     * @return The cosecant of the number.
     */
    std::string csc(const std::string& x, int decimals, int mode = 0);

    /**
     * @brief Calculates the cotangent of a number.
     *
     * @param x The number to calculate the cotangent of.
     * @param decimals The number of decimal places to round off to.
     * @param mode The mode to calculate the cotangent in. 0 = radians (default), 1 = degrees, 2 = gradians.
     *
     * @return The cotangent of the number.
     */
    std::string cot(const std::string& x, int decimals, int mode = 0);

    /**
     * @brief Calculates the arc cosine of a number.
     *
     * @param x The number to calculate the arc cosine of.
     * @param decimals The number of decimal places to round off to.
     * @param mode The mode to calculate the arc cosine in. 0 = radians (default), 1 = degrees, 2 = gradians.
     *
     * @return The arc cosine of the number.
     */
    std::string acos(const std::string& x, int decimals, int mode = 0);

    /**
     * @brief Calculates the arc sine of a number.
     *
     * @param x The number to calculate the arc sine of.
     * @param decimals The number of decimal places to round off to.
     * @param mode The mode to calculate the arc sine in. 0 = radians (default), 1 = degrees, 2 = gradians.
     *
     * @return The arc sine of the number.
     */
    std::string asin(const std::string& x, int decimals, int mode = 0);

    /**
     * @brief Calculates the arc tangent of a number.
     *
     * @param x The number to calculate the arc tangent of.
     * @param decimals The number of decimal places to round off to.
     * @param mode The mode to calculate the arc tangent in. 0 = radians (default), 1 = degrees, 2 = gradians.
     *
     * @return The arc tangent of the number.
     */
    std::string atan(const std::string& x, int decimals, int mode = 0);

    /**
     * @brief Calculates the arc secant of a number.
     *
     * @param x The number to calculate the arc secant of.
     * @param decimals The number of decimal places to round off to.
     * @param mode The mode to calculate the arc secant in. 0 = radians (default), 1 = degrees, 2 = gradians.
     *
     * @return The arc secant of the number.
     */
    std::string asec(const std::string& x, int decimals, int mode = 0);

    /**
     * @brief Calculates the arc cosecant of a number.
     *
     * @param x The number to calculate the arc cosecant of.
     * @param decimals The number of decimal places to round off to.
     * @param mode The mode to calculate the arc cosecant in. 0 = radians (default), 1 = degrees, 2 = gradians.
     *
     * @return The arc cosecant of the number.
     */
    std::string acsc(const std::string& x, int decimals, int mode = 0);

    /**
     * @brief Calculates the arc cotangent of a number.
     *
     * @param x The number to calculate the arc cotangent of.
     * @param decimals The number of decimal places to round off to.
     * @param mode The mode to calculate the arc cotangent in. 0 = radians (default), 1 = degrees, 2 = gradians.
     *
     * @return The arc cotangent of the number.
     */
    std::string acot(const std::string& x, int decimals, int mode = 0);

    /**
     * @brief Hyperbolic sine function.
     *
     * @param x The number.
     * @param decimals The number of decimal places to round off to.
     *
     * @return The hyperbolic sine of the number.
     */
    std::string sinh(const std::string& x, int decimals);

    /**
     * @brief Hyperbolic cosine function.
     *
     * @param x The number.
     * @param decimals The number of decimal places to round off to.
     *
     * @return The hyperbolic cosine of the number.
     */
    std::string cosh(const std::string& x, int decimals);

    /**
     * @brief Hyperbolic tangent function.
     *
     * @param x The number.
     * @param decimals The number of decimal places to round off to.
     *
     * @return The hyperbolic tangent of the number.
     */
    std::string tanh(const std::string& x, int decimals);

    /**
     * @brief Hyperbolic tangent function.
     *
     * @param x The number.
     * @param decimals The number of decimal places to round off to.
     *
     * @return The hyperbolic tangent of the number.
     */
    std::string sech(const std::string& x, int decimals);

    /**
     * @brief Hyperbolic tangent function.
     *
     * @param x The number.
     * @param decimals The number of decimal places to round off to.
     *
     * @return The hyperbolic tangent of the number.
     */
    std::string csch(const std::string& x, int decimals);

    /**
     * @brief Hyperbolic tangent function.
     *
     * @param x The number.
     * @param decimals The number of decimal places to round off to.
     *
     * @return The hyperbolic tangent of the number.
     */
    std::string coth(const std::string& x, int decimals);

    /**
     * @brief Inverse hyperbolic sine function.
     *
     * @param x The number.
     * @param decimals The number of decimal places to round off to.
     *
     * @return The inverse hyperbolic sine of the number.
     */
    std::string asinh(const std::string& x, int decimals);

    /**
     * @brief Inverse hyperbolic cosine function.
     *
     * @param x The number.
     * @param decimals The number of decimal places to round off to.
     *
     * @return The inverse hyperbolic cosine of the number.
     */
    std::string acosh(const std::string& x, int decimals);

    /**
     * @brief Inverse hyperbolic tangent function.
     *
     * @param x The number.
     * @param decimals The number of decimal places to round off to.
     *
     * @return The inverse hyperbolic tangent of the number.
     */
    std::string atanh(const std::string& x, int decimals);

    /**
     * @brief Inverse hyperbolic cotangent function.
     *
     * @param x The number.
     * @param decimals The number of decimal places to round off to.
     *
     * @return The inverse hyperbolic cotangent of the number.
     */
    std::string acoth(const std::string& x, int decimals);

    /**
     * @brief Inverse hyperbolic secant function.
     *
     * @param x The number.
     * @param decimals The number of decimal places to round off to.
     *
     * @return The inverse hyperbolic secant of the number.
     */
    std::string asech(const std::string& x, int decimals);

    /**
     * @brief Inverse hyperbolic cosecant function.
     *
     * @param x The number.
     * @param decimals The number of decimal places to round off to.
     *
     * @return The inverse hyperbolic cosecant of the number.
     */
    std::string acsch(const std::string& x, int decimals);

    /**
     * @brief Calculates the logarithm with a given base.
     *
     * @param _number The number to calculate the logarithm of.
     * @param _base The base of the logarithm.
     * @param _decimals The number of decimal places to round off to.
     * @return The result of the logarithm operation.
     */
    std::string logb(const std::string& _number, const std::string& _base, size_t _decimals);

    /**
     * @brief Calculates the common logarithm of a number.
     *
     * @note The common logarithm is the logarithm with base 10.
     *
     * @param _number The number to calculate the common logarithm of.
     * @param _decimals The number of decimal places to round off to.
     * @return The result of the common logarithm operation.
     */
    std::string log10(const std::string& _number, size_t _decimals);

    /**
     * @brief Calculates the binary logarithm of a number.
     *
     * @note The binary logarithm is the logarithm with base 2.
     *
     * @param _number The number to calculate the binary logarithm of.
     * @param _decimals The number of decimal places to round off to.
     * @return The result of the binary logarithm operation.
     */
    std::string log2(const std::string& _number, size_t _decimals);

    /**
     * @brief Calculates the natural logarithm of a number.
     *
     * @note The natural logarithm is the logarithm with base e.
     *
     * @param _number The number to calculate the natural logarithm of.
     * @param _decimals The number of decimal places to round off to.
     * @return The result of the natural logarithm operation.
     */
    std::string ln(const std::string& _number, size_t _decimals);

    /**
     * @brief Executes a given predicate function a specified number of times.
     *
     * @param[in] times The number of times to execute the predicate function.
     * @param[in] predicate The predicate function to execute.
     */
    template<typename Pred>
    void loop(const std::string& times, Pred predicate)
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
                output::error("loop", "Exception message: {0}"s, { e.what() });
            }
            current = add(current, "1", 0);
            result = compare(current, times, 0);
        }
    }

} // namespace steppable::__internals::calc
