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

#include "number.hpp"

#include "fn/basicArithm.hpp"
#include "output.hpp"

namespace steppable
{
    using namespace steppable::__internals::arithmetic;

    Number::Number() { value = "0"; }

    Number::Number(const std::string& value, size_t prec, RoundingMode mode)
    {
        this->value = value;
        this->prec = prec;
        this->mode = mode;
    }

    Number Number::operator+(const Number& rhs) { return add(value, rhs.value, 0); }

    Number Number::operator-(const Number& rhs) { return subtract(value, rhs.value, 0); }

    Number Number::operator*(const Number& rhs) { return multiply(value, rhs.value, 0); }

    Number Number::operator/(const Number& rhs)
    {
        size_t usePrec;
        if (mode == USE_MAXIMUM_PREC)
            usePrec = std::max(prec, rhs.prec);
        else if (mode == USE_MINIMUM_PREC)
            usePrec = std::min(prec, rhs.prec);
        else if (mode == USE_CURRENT_PREC)
            usePrec = prec;
        else if (mode == USE_OTHER_PREC)
            usePrec = rhs.prec;
        else if (mode == DISCARD_ALL_DECIMALS)
            usePrec = 0;
        else
        {
            usePrec = 0;
            output::warning("Invalid precision specified");
        }
        return divide(value, rhs.value, 0, usePrec);
    }

    Number Number::operator%(const Number& rhs) { return divideWithQuotient(value, rhs.value).remainder; }

    Number Number::operator^(const Number& rhs) { return power(value, rhs.value, 0); }

    Number& Number::operator+=(const Number& rhs)
    {
        *this = *this + rhs;
        return *this;
    }

    Number& Number::operator-=(const Number& rhs)
    {
        *this = *this - rhs;
        return *this;
    }

    Number& Number::operator*=(const Number& rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    Number& Number::operator/=(const Number& rhs)
    {
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

    bool Number::operator==(const Number& rhs)
    {
        if (compare(value, rhs.value, 0) == "2")
            return true;
        return false;
    }

    bool Number::operator!=(const Number& rhs)
    {
        if (compare(value, rhs.value, 0) != "2")
            return true;
        return false;
    }

    bool Number::operator<(const Number& rhs)
    {
        if (compare(value, rhs.value, 0) == "0")
            return true;
        return false;
    }

    bool Number::operator>(const Number& rhs)
    {
        if (compare(value, rhs.value, 0) == "1")
            return true;
        return false;
    }

    bool Number::operator<=(const Number& rhs)
    {
        if (compare(value, rhs.value, 0) != "1")
            return true;
        return false;
    }

    bool Number::operator>=(const Number& rhs)
    {
        if (compare(value, rhs.value, 0) != "0")
            return true;
        return false;
    }

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

    std::string Number::present() { return value; }
} // namespace steppable
