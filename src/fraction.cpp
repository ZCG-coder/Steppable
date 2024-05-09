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
 * @file fraction.cpp
 * @brief This file contains the implementation of the Fraction class, which represents a fraction in math.
 *
 * @author Andy Zhang
 * @date 13th March 2024
 */

#include "fraction.hpp"

#include "exceptions.hpp"
#include "fn/basicArithm.hpp"
#include "number.hpp"
#include "util.hpp"

#include <string>

using namespace steppable::__internals::arithmetic;
using namespace steppable::__internals::numUtils;

namespace steppable
{
    Fraction::Fraction()
    {
        this->top = "1";
        this->bottom = "1";
    }

    Fraction::Fraction(const std::string& top, const std::string& bottom)
    {
        if (isZeroString(bottom))
            throw exceptions::ZeroDenominatorException();
        this->top = top;
        this->bottom = bottom;
        simplify();
    }

    Fraction::Fraction(const Number& number)
    {
        this->top = number.present();
        this->bottom = "1";
        simplify();
    }

    std::string Fraction::present()
    {
        simplify();
        return top + "/" + bottom;
    }

    std::array<std::string, 2> Fraction::asArray() const { return { top, bottom }; }

    Fraction Fraction::operator+(const Fraction& rhs) const
    {
        auto newTop = add(multiply(top, rhs.bottom, 0), multiply(rhs.top, bottom, 0), 0);
        auto newBottom = multiply(bottom, rhs.bottom, 0);

        auto newFrac = Fraction(newTop, newBottom);
        newFrac.simplify();
        return newFrac;
    }

    Fraction Fraction::operator-(const Fraction& rhs) const
    {
        auto newTop = subtract(multiply(top, rhs.bottom, 0), multiply(rhs.top, bottom, 0), 0);
        auto newBottom = multiply(bottom, rhs.bottom, 0);

        auto newFrac = Fraction(newTop, newBottom);
        newFrac.simplify();
        return newFrac;
    }

    Fraction Fraction::operator*(const Fraction& rhs) const
    {
        auto newTop = multiply(top, rhs.top, 0);
        auto newBottom = multiply(bottom, rhs.bottom, 0);

        auto newFrac = Fraction(newTop, newBottom);
        newFrac.simplify();
        return newFrac;
    }

    Fraction Fraction::operator/(const Fraction& rhs) const
    {
        auto newTop = multiply(top, rhs.bottom, 0);
        auto newBottom = multiply(bottom, rhs.top, 0);

        auto newFrac = Fraction(newTop, newBottom);
        newFrac.simplify();
        return newFrac;
    }

    Fraction Fraction::operator^(const Number& rhs)
    {
        auto newTop = power(top, rhs.present(), 0);
        auto newBottom = power(bottom, rhs.present(), 0);

        auto newFrac = Fraction(newTop, newBottom);
        newFrac.simplify();
        return newFrac;
    }

    Fraction& Fraction::operator+=(const Fraction& rhs)
    {
        *this = *this + rhs;
        simplify();
        return *this;
    }

    Fraction& Fraction::operator-=(const Fraction& rhs)
    {
        *this = *this - rhs;
        simplify();
        return *this;
    }

    Fraction& Fraction::operator*=(const Fraction& rhs)
    {
        *this = *this * rhs;
        simplify();
        return *this;
    }

    Fraction& Fraction::operator/=(const Fraction& rhs)
    {
        *this = *this / rhs;
        simplify();
        return *this;
    }

    Fraction& Fraction::operator^=(const Number& rhs)
    {
        *this = *this ^ rhs;
        simplify();
        return *this;
    }

    bool Fraction::operator==(const Fraction& rhs) const
    {
        const auto& newBottom = multiply(bottom, rhs.bottom, 0);
        const auto& thisNewTop = multiply(top, rhs.bottom, 0);
        const auto& otherNewTop = multiply(rhs.top, bottom, 0);

        return compare(thisNewTop, otherNewTop, 0) == "2";
    }

    bool Fraction::operator!=(const Fraction& rhs) const
    {
        const auto& newBottom = multiply(bottom, rhs.bottom, 0);
        const auto& thisNewTop = multiply(top, rhs.bottom, 0);
        const auto& otherNewTop = multiply(rhs.top, bottom, 0);

        return compare(thisNewTop, otherNewTop, 0) != "2";
    }

    bool Fraction::operator>(const Fraction& rhs) const
    {
        const auto& newBottom = multiply(bottom, rhs.bottom, 0);
        const auto& thisNewTop = multiply(top, rhs.bottom, 0);
        const auto& otherNewTop = multiply(rhs.top, bottom, 0);

        return compare(thisNewTop, otherNewTop, 0) == "1";
    }

    bool Fraction::operator<(const Fraction& rhs) const
    {
        const auto& newBottom = multiply(bottom, rhs.bottom, 0);
        const auto& thisNewTop = multiply(top, rhs.bottom, 0);
        const auto& otherNewTop = multiply(rhs.top, bottom, 0);

        return compare(thisNewTop, otherNewTop, 0) == "0";
    }

    bool Fraction::operator<=(const Fraction& rhs) const
    {
        const auto& newBottom = multiply(bottom, rhs.bottom, 0);
        const auto& thisNewTop = multiply(top, rhs.bottom, 0);
        const auto& otherNewTop = multiply(rhs.top, bottom, 0);

        return compare(thisNewTop, otherNewTop, 0) != "1";
    }

    bool Fraction::operator>=(const Fraction& rhs) const
    {
        const auto& newBottom = multiply(bottom, rhs.bottom, 0);
        const auto& thisNewTop = multiply(top, rhs.bottom, 0);
        const auto& otherNewTop = multiply(rhs.top, bottom, 0);

        return compare(thisNewTop, otherNewTop, 0) != "0";
    }

    void Fraction::simplify()
    {
        // Make sure the fraction does not contain decimal points.
        while (isDecimal(top) or isDecimal(bottom))
        {
            top = multiply(top, "10", 0);
            bottom = multiply(bottom, "10", 0);
        }
        auto gcd = getGCD(top, bottom);
        top = divide(top, gcd, 0, 0);
        bottom = divide(bottom, gcd, 0, 0);
    }
} // namespace steppable
