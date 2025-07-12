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
 * @file steppable/number.hpp
 * @brief Contains the definition of the Number class, which offers an API for arbitrary precision arithmetic.
 *
 * @author Andy Zhang
 * @date 1st April 2024
 */

#pragma once

#include "rounding.hpp"
#include "testing.hpp"
#include "types/rounding.hpp"
#include "util.hpp"

#include <functional>
#include <string>
#include <utility>

/**
 * @namespace steppable
 * @brief The public namespace for the Steppable library.
 */
namespace steppable
{
    /**
     * @class Number
     * @brief Represents a number with arbitrary precision. It basically stores the value as a string.
     */
    class Number
    {
        /// @brief The value of the number.
        std::string value;

        /// @brief The precision of the number.
        size_t prec;

        /// @brief The rounding mode of the number.
        RoundingMode mode = RoundingMode::USE_CURRENT_PREC;

        template<__internals::utils::StringLiteral fnName>
        [[nodiscard]] size_t determinePrec(const Number& rhs) const
        {
            size_t usePrec = 0;
            if (mode == RoundingMode::USE_MAXIMUM_PREC)
                usePrec = std::max(prec, rhs.prec);
            else if (mode == RoundingMode::USE_MINIMUM_PREC)
                usePrec = std::min(prec, rhs.prec);
            else if (mode == RoundingMode::USE_CURRENT_PREC)
                usePrec = prec;
            else if (mode == RoundingMode::USE_OTHER_PREC)
                usePrec = rhs.prec;
            else if (mode == RoundingMode::DISCARD_ALL_DECIMALS)
                usePrec = 0;
            else
            {
                usePrec = 0;
                output::warning(std::string(fnName.value), "Invalid precision specified"s);
            }

            return usePrec;
        }

    public:
        /**
         * @brief Initializes a number with a specified value.
         * @note By default, the value is 0.
         */
        Number(std::string value = "0", size_t prec = 10, RoundingMode mode = RoundingMode::USE_CURRENT_PREC);

        /**
         * @brief Initializes a number with a C/C++ long double value.
         * @note No matter how the number is specified, it will always be converted to a string for storage.
         */
        template<concepts::Numeric ValueT>
        Number(ValueT value, size_t prec = 10, RoundingMode mode = RoundingMode::USE_CURRENT_PREC) :
            value(std::to_string(value)), prec(prec), mode(mode)
        {
        }

        void set(std::string newVal) { value = std::move(newVal); }

        void setPrec(size_t newPrec, RoundingMode mode = RoundingMode::USE_CURRENT_PREC)
        {
            this->mode = mode;
            prec = newPrec;
            value = __internals::numUtils::roundOff(value, prec);
        }

        /**
         * @brief Adds two numbers together.
         * @param rhs The number to add.
         * @return The sum of the two numbers.
         */
        Number operator+(const Number& rhs) const;

        /**
         * @brief Subtracts two numbers.
         * @param rhs The number to subtract.
         * @return The difference of the two numbers.
         */
        Number operator-(const Number& rhs) const;

        /**
         * @brief Multiplies two numbers.
         * @param rhs The number to multiply.
         * @return The product of the two numbers.
         */
        Number operator*(const Number& rhs) const;

        /**
         * @brief Divides two numbers.
         * @param rhs The number to divide.
         * @return The quotient of the two numbers.
         */
        Number operator/(const Number& rhs) const;

        /**
         * @brief Takes a modulus operation.
         * @details Divides and takes the nearest quotient.
         *
         * @param rhs The other number.
         * @return The modulus of the two numbers.
         */
        [[nodiscard]] Number mod(const Number& rhs) const;

        /**
         * @brief Calculates the remainder of two numbers. (Modulus)
         * @param rhs The number to divide.
         * @return The remainder of the two numbers.
         */
        Number operator%(const Number& rhs) const;

        /**
         * @brief Raises the number to a power.
         * @param rhs The power to raise the number to.
         * @return The result of the power operation.
         */
        Number operator^(const Number& rhs);

        /**
         * @brief Adds the number to another number and assigns the result to the current number.
         * @param rhs The number to add.
         * @return The sum of the two numbers.
         */
        Number& operator+=(const Number& rhs);

        /**
         * @brief Subtracts the number from another number and assigns the result to the current number.
         * @param rhs The number to subtract.
         * @return The difference of the two numbers.
         */
        Number& operator-=(const Number& rhs);

        /**
         * @brief Multiplies the number by another number and assigns the result to the current number.
         * @param rhs The number to multiply.
         * @return The product of the two numbers.
         */
        Number& operator*=(const Number& rhs);

        /**
         * @brief Divides the number by another number and assigns the result to the current number.
         * @param rhs The number to divide.
         * @return The quotient of the two numbers.
         */
        Number& operator/=(const Number& rhs);

        /**
         * @brief Calculates the remainder of two numbers and assigns the result to the current number.
         * @param rhs The number to divide.
         * @return The remainder of the two numbers.
         */
        Number& operator%=(const Number& rhs);

        /**
         * @brief Raises the number to a power and assigns the result to the current number.
         * @param rhs The power to raise the number to.
         * @return The result of the power operation.
         */
        Number& operator^=(const Number& rhs);

        /**
         * @brief Compares two numbers for equality.
         * @param rhs The number to compare.
         * @return True if the numbers are equal, false otherwise.
         */
        bool operator==(const Number& rhs) const;

        /**
         * @brief Compares two numbers for inequality.
         * @param rhs The number to compare.
         * @return True if the numbers are not equal, false otherwise.
         */
        bool operator!=(const Number& rhs) const;

        /**
         * @brief Compares two numbers for less than.
         * @param rhs The number to compare.
         * @return True if the current number is less than the other number, false otherwise.
         */
        bool operator<(const Number& rhs) const;

        /**
         * @brief Compares two numbers for greater than.
         * @param rhs The number to compare.
         * @return True if the current number is greater than the other number, false otherwise.
         */
        bool operator>(const Number& rhs) const;

        /**
         * @brief Compares two numbers for less than or equal to.
         * @param rhs The number to compare.
         * @return True if the current number is less than or equal to the other number, false otherwise.
         */
        bool operator<=(const Number& rhs) const;

        /**
         * @brief Compares two numbers for greater than or equal to.
         * @param rhs The number to compare.
         * @return True if the current number is greater than or equal to the other number, false otherwise.
         */
        bool operator>=(const Number& rhs) const;

        /**
         * @brief Increments the number by one.
         * @return The number after incrementing.
         */
        Number operator++();

        /**
         * @brief Decrements the number by one.
         * @return The number after decrementing.
         */
        Number operator--();

        /**
         * @brief Unary minus operator.
         * @details Converts the number to itself with the opposite sign. Returns a new instance of the number.
         * @return A number equal in value but opposite in sign.
         */
        Number operator-() const;

        /**
         * @brief Unary plus operator.
         * @details Does nothing. Simply returns a new instance of the number.
         * @return A number equal in value and equal in sign.
         */
        Number operator+() const;

        /**
         * @brief Presents the number in a human-readable format.
         * @return The number as a string.
         */
        [[nodiscard]] std::string present() const;

        /**
         * @brief Gets the absolute value of the number.
         * @return The absolute value of the current number.
         */
        [[nodiscard]] Number abs() const
        {
            if (*this > 0)
                return *this;
            return -(*this);
        }
    };

    /**
     * @namespace steppable::literals
     * @brief Literal suffixes for literals to be converted to Steppable objects.
     */
    namespace literals
    {
        inline Number operator""_n(long double value) { return Number(value); }

        inline Number operator""_n(unsigned long long value) { return Number(value); }
    } // namespace literals
} // namespace steppable

template<>
struct std::hash<steppable::Number>
{
    size_t operator()(const steppable::Number& n) const { return hash<std::string>()(n.present()); }
};

std::ostream& operator<<(std::ostream& os, const steppable::Number& number);
