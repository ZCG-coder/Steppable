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
 * @file comparisonReport.cpp
 * @brief This file contains the implementation of functions reportComparisonAtInteger, reportComparisonByPolarity and
 * reportComparisonByDigit, which reports the result of the comparison from the integer part, polarity and digit
 * respectively.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 */

#include "comparisonReport.hpp"

#include "getString.hpp"
#include "symbols.hpp"

#include <sstream>
#include <string>

using namespace steppable::__internals::symbols;
using namespace steppable::localization;

std::string reportComparisonAtInteger(const std::string& a, const std::string& b, const bool bigger, const int steps)
{
    std::stringstream ss;

    if (steps == 2)
    {
        ss << $("calc::comparison", "0095d521-ccba-4c5b-b33f-9d9f2b3d18e3", { a, b }) << '\n';
        if (bigger)
        {
            // The integer part of {0} is greater than that of {1}
            ss << BECAUSE << $("calc::comparison", "1b7ea6d8-9909-4589-8d59-b3eb7121cdee", { a, b }) << '\n';
            // {0} is greater than {1}
            ss << THEREFORE << $("calc::comparison", "aaad3a6a-1257-478a-b3d1-245c4dc0e6fb", { a, b });
        }
        else
        {
            // The integer part of {0} is greater than that of {1}
            ss << BECAUSE << $("calc::comparison", "1b7ea6d8-9909-4589-8d59-b3eb7121cdee", { b, a }) << '\n';
            // {0} is less than {1}
            ss << THEREFORE << $("calc::comparison", "ec120274-c8f2-4a41-9e64-b7b0d011d20e", { a, b });
        }
    }
    else if (steps == 1)
        ss << a << (bigger ? " > " : " < ") << b;
    else
        ss << (bigger ? '1' : '0');

    return ss.str();
}

std::string reportComparisonByPolarity(const std::string& a, const std::string& b, const bool greater, const int steps)
{
    std::stringstream ss;

    if (steps == 2)
    {
        // Comparing the polarities of {0} and {1}
        ss << $("calc::comparison", "09a9b12d-7b58-4626-b7c8-62a16933bfce", { a, b }) << '\n';
        if (greater)
        {
            // {0} is positive and {1} is negative
            ss << BECAUSE << $("calc::comparison", "eb150ad5-09a5-4be6-8400-988e6f0eb252", { a, b }) << '\n';
            ss << THEREFORE << $("calc::comparison", "aaad3a6a-1257-478a-b3d1-245c4dc0e6fb", { a, b });
        }
        else
        {
            ss << BECAUSE << $("calc::comparison", "237615f7-6c35-4ca2-a791-43d8ccc925dd", { a, b }) << '\n';
            ss << THEREFORE << $("calc::comparison", "ec120274-c8f2-4a41-9e64-b7b0d011d20e", { a, b });
        }
    }
    else if (steps == 1)
        ss << a << (greater ? " > " : " < ") << b;
    else
        ss << (greater ? '1' : '0');

    return ss.str();
}

std::string reportComparisonByDigit(const std::string& a,
                                    const std::string& b,
                                    const size_t _digit,
                                    const bool greater,
                                    const bool bothNegative,
                                    const int steps)
{
    std::stringstream ss;
    size_t digit = _digit;
    if (steps == 2)
    {
        ss << "a = " << a << '\n';
        ss << "b = " << b << '\n';

        if (greater)
        {
            // At digit {0}...
            ss << std::string(digit + 4, ' ') << "^~~~~ " << BECAUSE
               << $("calc::comparison",
                    "ab1363eb-bfdb-44a9-89ee-b125a8d60cbd",
                    { std::to_string(digit + 1), std::string(1, a[digit]), std::string(1, b[digit]) })
               << '\n';
            ss << THEREFORE << $("calc::comparison", "aaad3a6a-1257-478a-b3d1-245c4dc0e6fb", { a, b });
        }
        else
        {
            // At digit {0}...
            ss << std::string(digit + 4, ' ') << "^~~~~ " << BECAUSE
               << $("calc::comparison",
                    "ab1363eb-bfdb-44a9-89ee-b125a8d60cbd",
                    { std::to_string(digit + 1), std::string(1, b[digit]), std::string(1, a[digit]) })
               << '\n';
            ss << THEREFORE << $("calc::comparison", "ec120274-c8f2-4a41-9e64-b7b0d011d20e", { a, b });
        }
    }
    else if (steps == 1)
        ss << a << (greater ? " > " : " < ") << b;
    else
        ss << (greater ? '1' : '0');

    return ss.str();
}
