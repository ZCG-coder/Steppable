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
 * @file absReport.cpp
 * @brief This file contains the implementation of the reportAbs function, which reports the absolute value of a number
 * string to the user.
 *
 * @author Andy Zhang
 * @date 12th January 2024
 */

#include "symbols.hpp"

#include <sstream>
#include <string>
#include <util.hpp>

using namespace steppable::__internals::numUtils;
using namespace steppable::__internals::symbols;

std::string reportAbs(const std::string& number, int steps = 2)
{
    std::stringstream ss;

    if (steps == 2)
    {
        if (number[0] == '-')
        {
            ss << "Since " << number << " is negative, "
               << "abs(" << number << ") = -(" << number << ")\n";
            ss << THEREFORE << " The absolute value of " << number << " is " << standardizeNumber(number.substr(1));
        }
        else
        {
            ss << "Since " << number << " is positive, "
               << "abs(" << number << ") = " << number << '\n';
            ss << THEREFORE << " The absolute value of " << number << " is " << standardizeNumber(number);
        }
    }
    else if (steps == 1)
    {
        if (number[0] == '-')
            ss << "abs(" << number << ") = " << standardizeNumber(number.substr(1));
        else
            ss << "abs(" << number << ") = " << standardizeNumber(number);
    }
    else
    {
        if (number[0] == '-')
            ss << standardizeNumber(number.substr(1));
        else
            ss << standardizeNumber(number);
    }

    return ss.str();
}
