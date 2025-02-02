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
 * @file fraction.cpp
 * @brief This file contains the implementation of the Fraction class, which represents a fraction in math.
 *
 * @author Andy Zhang
 * @date 13th March 2024
 */

#include "fraction.hpp"

#include "exceptions.hpp"
#include "fn/calc.hpp"
#include "number.hpp"
#include "symbols.hpp"
#include "util.hpp"

#include <string>
#include <utility>

#ifdef WINDOWS
    #undef max
    #undef min
#endif

using namespace steppable::__internals::calc;
using namespace steppable::__internals::numUtils;

namespace steppable::prettyPrint::printers
{
    std::string ppFraction(const std::string& top, const std::string& bottom, const bool inLine)
    {
        // Output in single line
        if (inLine)
            return top + "/" + bottom;
        // Output in three lines, with top and bottom aligned to center.
        auto topWidth = prettyPrint::getStringWidth(top);
        auto bottomWidth = prettyPrint::getStringWidth(bottom);
        auto width = std::max(topWidth, bottomWidth) + 2;
        auto topSpacing = std::string((width - topWidth) / 2, ' ');
        auto bottomSpacing = std::string((width - bottomWidth) / 2, ' ');
        return topSpacing + top + '\n' + std::string(width, '-') + '\n' + bottomSpacing + bottom;
    }
} // namespace steppable::prettyPrint::printers

namespace steppable
{
    Fraction::Fraction() : top("1"), bottom("1") {}

    Fraction::Fraction(const std::string& top, const std::string& bottom)
    {
        if (isZeroString(bottom))
            throw exceptions::ZeroDenominatorException();
        this->top = top;
        this->bottom = bottom;
        simplify();
    }

    Fraction::Fraction(const Number& number) : bottom("1")
    {
        this->top = number.present();
        simplify();
    }

    std::string Fraction::present(const bool inLine)
    {
        simplify();
        return prettyPrint::printers::ppFraction(top, bottom, inLine);
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

    void Fraction::reciprocal()
    {
        std::ranges::swap(top, bottom);
        simplify();
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
