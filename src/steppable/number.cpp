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
 * @file number.cpp
 * @brief This file contains the implementation of the Number class, which represents a number in math.
 *
 * @author Andy Zhang
 * @date 1st April 2024
 */

#include "steppable/number.hpp"

#include "fn/calc.hpp"
#include "output.hpp"
#include "rounding.hpp"

#include <string>

#ifdef WINDOWS
    #undef max
    #undef min
#endif

namespace steppable
{
    using namespace steppable::__internals::calc;

    Number::Number() : value("0"), prec(8) {}

    Number::Number(const long double value, const size_t prec, const RoundingMode mode) :
        value(std::to_string(value)), prec(prec), mode(mode)
    {
    }
    Number::Number(std::string value, const size_t prec, const RoundingMode mode) :
        value(std::move(value)), prec(prec), mode(mode)
    {
    }

    Number Number::operator+(const Number& rhs) const { return Number(add(value, rhs.value, 0), prec, mode); }

    Number Number::operator-(const Number& rhs) const { return Number(subtract(value, rhs.value, 0), prec, mode); }

    Number Number::operator*(const Number& rhs) const
    {
        const size_t usePrec = determinePrec<"operator*">(rhs);
        const auto result = multiply(value, rhs.value, 0, static_cast<int>(usePrec) + 2);
        return Number{ __internals::numUtils::roundOff(result, usePrec), usePrec, mode };
    }

    Number Number::operator/(const Number& rhs) const
    {
        const size_t usePrec = determinePrec<"operator/">(rhs);
        const auto result = divide(value, rhs.value, 0, static_cast<int>(usePrec) + 2);
        return Number{ __internals::numUtils::roundOff(result, usePrec), usePrec, mode };
    }

    Number Number::operator%(const Number& rhs) const
    {
        return Number(divideWithQuotient(value, rhs.value).remainder, prec, mode);
    }

    Number Number::operator^(const Number& rhs)
    {
        const size_t usePrec = determinePrec<"operator^">(rhs);
        return Number(power(value, rhs.value, 0, static_cast<int>(usePrec)), usePrec, mode);
    }

    Number& Number::operator+=(const Number& rhs)
    {
        *this = *this + rhs;
        return *this;
    }

    Number& Number::operator-=(const Number& rhs)
    {
        determinePrec<"operator-=">(rhs);
        *this = *this - rhs;
        return *this;
    }

    Number& Number::operator*=(const Number& rhs)
    {
        determinePrec<"operator*=">(rhs);
        *this = *this * rhs;
        return *this;
    }

    Number& Number::operator/=(const Number& rhs)
    {
        determinePrec<"operator/=">(rhs);
        *this = *this / rhs;
        return *this;
    }

    Number& Number::operator%=(const Number& rhs)
    {
        *this = *this % rhs;
        return *this;
    }

    Number& Number::operator^=(const Number& rhs)
    {
        *this = *this ^ rhs;
        return *this;
    }

    bool Number::operator==(const Number& rhs) const { return compare(value, rhs.value, 0) == "2"; }

    bool Number::operator!=(const Number& rhs) const { return compare(value, rhs.value, 0) != "2"; }

    bool Number::operator<(const Number& rhs) const { return compare(value, rhs.value, 0) == "0"; }

    bool Number::operator>(const Number& rhs) const { return compare(value, rhs.value, 0) == "1"; }

    bool Number::operator<=(const Number& rhs) const { return compare(value, rhs.value, 0) != "1"; }

    bool Number::operator>=(const Number& rhs) const { return compare(value, rhs.value, 0) != "0"; }

    Number Number::operator++()
    {
        *this += Number("1");
        return *this;
    }

    Number Number::operator--()
    {
        *this -= Number("1");
        return *this;
    }

    std::string Number::present() const { return value; }
} // namespace steppable
