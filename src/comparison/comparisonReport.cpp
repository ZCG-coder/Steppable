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

#include "comparisonReport.hpp"

#include "symbols.hpp"

#include <sstream>
#include <string_view>

std::string reportComparisonAtInteger(const std::string_view& a,
                                      const std::string_view& b,
                                      const bool bigger,
                                      const int steps)
{
    std::stringstream ss;

    if (steps == 2)
    {
        ss << "Comparing the integer part of a and b" << '\n';
        if (bigger)
        {
            ss << BECAUSE << " The integer part of " << a << " is bigger than the integer part of " << b << '\n';
            ss << THEREFORE " " << a << " is greater than " << b;
        }
        else
        {
            ss << BECAUSE " The integer part of " << b << " is bigger than the integer part of " << a << '\n';
            ss << THEREFORE " " << a << " is less than " << b;
        }
    }
    else if (steps == 1)
        ss << a << (bigger ? " > " : " < ") << b;
    else
        ss << (bigger ? '1' : '0');

    return ss.str();
}

std::string reportComparisonByPolarity(const std::string_view& a,
                                        const std::string_view& b,
                                        const bool bigger,
                                        const int steps)
{
    std::stringstream ss;

    if (steps == 2)
    {
        ss << "Comparing the polarities of a and b" << '\n';
        if (bigger)
        {
            ss << BECAUSE << " " << a << " is positive and " << b << " is negative" << '\n';
            ss << THEREFORE " " << a << " is greater than " << b;
        }
        else
        {
            ss << BECAUSE << " " << a << " is negative and " << b << " is positive" << '\n';
            ss << THEREFORE " " << a << " is less than " << b;
        }
    }
    else if (steps == 1)
        ss << a << (bigger ? " > " : " < ") << b;
    else
        ss << (bigger ? '1' : '0');

    return ss.str();
}

std::string reportComparisonByDigit(const std::string_view& a,
                                    const std::string_view& b,
                                    const size_t _digit,
                                    const bool bigger,
                                    const bool bothNegative,
                                    const int steps)
{
    std::stringstream ss;
    size_t digit = _digit;
    if (steps == 2)
    {
        ss << "a = " << a << '\n';
        ss << "b = " << b << '\n';

        if (bigger)
        {
            ss << std::string(digit + 4, ' ') << "^~~~~ " BECAUSE " At digit " << digit + 1 << ", " << a[digit]
               << " is greater than " << b[digit] << '\n';
            ss << THEREFORE " " << a << " is greater than " << b;
        }
        else
        {
            ss << std::string(digit + 4, ' ') << "^~~~~ " BECAUSE " At digit " << digit + 1 << ", " << a[digit]
               << " is less than " << b[digit] << '\n';
            ss << THEREFORE " " << a << " is less than " << b;
        }
    }
    else if (steps == 1)
        ss << a << (bigger ? " > " : " < ") << b;
    else
        ss << (bigger ? '1' : '0');

    return ss.str();
}
