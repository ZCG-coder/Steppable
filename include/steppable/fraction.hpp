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
 * @file steppable/fraction.hpp
 * @brief This file contains the definition of the Fraction class, which represents a fraction in math.
 *
 * @author Andy Zhang
 * @date 13th March 2024
 */

#pragma once

#include "steppable/number.hpp"

#include <array>
#include <string>

namespace steppable
{
    /**
     * @class Fraction
     * @brief Acts as a fraction in math. It can be added, subtracted, multiplied and divided.
     */
    class Fraction
    {
    private:
        /// @brief The numerator. (Top component)
        std::string top;

        /// @brief The denominator. (Bottom component)
        std::string bottom;

    public:
        /**
         * @brief Initializes a fraction with a specified top component and bottom component.
         * @note By default, the top and bottom components are 1.
         * @throws ZeroDenominatorException when the bottom component is zero.
         */
        explicit Fraction(const std::string& top = "1", const std::string& bottom = "1");

        /**
         * @brief Initialized a fraction from a number.
         *
         * @param number The number to convert to a fraction.
         */
        explicit Fraction(const Number& number);

        /**
         * @brief Initializes a fraction with no top component and bottom component specified.
         * By default, this fraction equals to 1.
         */
        Fraction();

        /**
         * @brief Returns the fraction as a string.
         * The string is formatted as "top/bottom", and it will automatically simplify the fraction.
         *
         * @param inLine Whether to present the fraction in a single line.
         * @return The fraction as a string.
         */
        std::string present(bool inLine = true);

        /**
         * @brief Returns the fraction as an array of its top and bottom components.
         * @return The array of top and bottom components.
         */
        [[nodiscard]] std::array<std::string, 2> asArray() const;

        /**
         * @brief Adds two fractions together.
         * This function does it by doing a simple fraction addition and returns the sum.
         *
         * @param[in] rhs The other fraction.
         * @return The sum of fractions.
         */
        Fraction operator+(const Fraction& rhs) const;

        /**
         * @brief Unary plus operator.
         * @details Does nothing. Simply returns a new instance of the fraction.
         * @return A new instance of the fraction, with euqal value and equal in sign.
         */
        Fraction operator+() const;

        /**
         * @brief Subtracts a fraction from another fraction.
         * This function does it by doing a simple fraction subtraction and returns the difference.
         *
         * @param[in] rhs The other fraction.
         * @return The difference of fractions.
         */
        Fraction operator-(const Fraction& rhs) const;

        /**
         * @brief Unary minus operator.
         * @details Converts the fraction to itself with the opposite sign. Returns a new instance of the fraction.
         * @return A fraction equal in value but opposite in sign.
         */
        Fraction operator-() const;

        /**
         * @brief Multiplies two fractions together.
         * This function does it by doing a simple fraction multiplication and returns the sum.
         *
         * @param[in] rhs The other fraction.
         * @return The product of fractions.
         */
        Fraction operator*(const Fraction& rhs) const;

        /**
         * @brief Divides a fraction by abother fraction.
         * This function does it by doing a simple fraction division (multiply by inverse) and
         * returns the sum.
         *
         * @param[in] rhs The other fraction.
         * @return The sum of fractions.
         */
        Fraction operator/(const Fraction& rhs) const;

        /**
         * @brief Raises the fraction to a power.
         *
         * @param rhs Any number.
         * @return The result of the power operation.
         */
        Fraction operator^(const Number& rhs);

        /**
         * @brief Adds two fractions together and stores the result in the current one.
         * This function does it by doing a simple fraction addition and returns the sum.
         *
         * @param[in] rhs The other fraction.
         * @return The current fraction.
         */
        Fraction& operator+=(const Fraction& rhs);

        /**
         * @brief Subtracts a fraction from another fraction and stores the result in the current one.
         * This function does it by doing a simple fraction subtraction and returns the difference.
         *
         * @param[in] rhs The other fraction.
         * @return The current fraction.
         */
        Fraction& operator-=(const Fraction& rhs);

        /**
         * @brief Multiplies two fractions together and stores the result in the current one.
         * This function does it by doing a simple fraction multiplication and returns the sum.
         *
         * @param[in] rhs The other fraction.
         * @return The current fraction.
         */
        Fraction& operator*=(const Fraction& rhs);

        /**
         * @brief Divides a fraction by abother fraction and stores the result in the current one.
         * This function does it by doing a simple fraction division (multiply by inverse) and
         * returns the sum.
         *
         * @param[in] rhs The other fraction.
         * @return The sum of fractions.
         */
        Fraction& operator/=(const Fraction& rhs);

        /**
         * @brief Raises the fraction to a power and stores the result in the current one.
         *
         * @param rhs Any number.
         * @return The current fraction.
         */
        Fraction& operator^=(const Number& rhs);

        /**
         * @brief Compares two numbers for equality.
         *
         * @param rhs Another fraction.
         * @return True if the fractions are equal, false otherwise.
         */
        bool operator==(const Fraction& rhs) const;

        /**
         * @briefCompares two numbers for inequality.
         *
         * @param rhs Another fraction.
         * @return True if the numbers are not equal, false otherwise.
         */
        bool operator!=(const Fraction& rhs) const;

        /**
         * @brief Compares two numbers for greater than.
         *
         * @param rhs Another fraction.
         * @return True if the the fraction is greater than the other, false otherwise.
         */
        bool operator<(const Fraction& rhs) const;

        /**
         * @brief Compare two fractions for less than.
         *
         * @param rhs Another fraction.
         * @return True if the the fraction is less than the other, false otherwise.
         */
        bool operator>(const Fraction& rhs) const;

        /**
         * @brief Compare two fractions for less or equal than.
         *
         * @param rhs Another fraction.
         * @return True if the the fraction is less or equal than the other, false otherwise.
         */
        bool operator<=(const Fraction& rhs) const;

        /**
         * @brief Compare two fractions for greater or equal than.
         *
         * @param rhs Another fraction.
         * @return True if the the fraction is greater or equal than the other, false otherwise.
         */
        bool operator>=(const Fraction& rhs) const;

        /**
         * @brief Converts a fraction to its reciprocal.
         * This function converts the fraction to its reciprocal.
         */
        void reciprocal();

        /**
         * @brief Simplifies a fraction.
         * This function simplifies the fraction by dividing the top and bottom components by their greatest common
         * divisor.
         * @note The fraction will be simplified in-place.
         */
        void simplify();
    };
} // namespace steppable
