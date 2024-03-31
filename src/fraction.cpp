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

#include "fraction.hpp"

#include "exceptions.hpp"
#include "fn/basicArithm.hpp"
#include "util.hpp"

#include <string>

Fraction::Fraction()
{
    this->top = "1";
    this->bottom = "1";
}

Fraction::Fraction(const std::string& top, const std::string& bottom)
{
    if (isZeroString(bottom))
        throw ZeroDenominatorException();
    this->top = top;
    this->bottom = bottom;
}

Fraction Fraction::operator+(const Fraction& rhs)
{
    auto newTop = add(multiply(top, rhs.bottom, 0), multiply(rhs.top, bottom, 0), 0);
    auto newBottom = multiply(bottom, rhs.bottom, 0);

    return Fraction(newTop, newBottom);
}

Fraction Fraction::operator-(const Fraction& rhs)
{
    auto newTop = subtract(multiply(top, rhs.bottom, 0), multiply(rhs.top, bottom, 0), 0);
    auto newBottom = multiply(bottom, rhs.bottom, 0);

    return Fraction(newTop, newBottom);
}

Fraction Fraction::operator*(const Fraction& rhs)
{
    auto newTop = multiply(top, rhs.top, 0);
    auto newBottom = multiply(bottom, rhs.bottom, 0);

    return Fraction(newTop, newBottom);
}

Fraction Fraction::operator/(const Fraction& rhs)
{
    auto newTop = multiply(top, rhs.bottom, 0);
    auto newBottom = multiply(bottom, rhs.top, 0);

    return Fraction(newTop, newBottom);
}

Fraction& Fraction::operator+=(const Fraction& rhs)
{
    *this = *this + rhs;
    return *this;
}

Fraction& Fraction::operator-=(const Fraction& rhs)
{
    *this = *this - rhs;
    return *this;
}

Fraction& Fraction::operator*=(const Fraction& rhs)
{
    *this = *this * rhs;
    return *this;
}

Fraction& Fraction::operator/=(const Fraction& rhs)
{
    *this = *this / rhs;
    return *this;
}

void Fraction::simplify()
{
    auto gcd = getGCD(top, bottom);
    top = divide(top, gcd, 0);
    bottom = divide(bottom, gcd, 0);
}
