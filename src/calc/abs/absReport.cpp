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
 * @file absReport.cpp
 * @brief This file contains the implementation of the reportAbs function, which reports the absolute value of a number
 * string to the user.
 *
 * @author Andy Zhang
 * @date 12th January 2024
 */

#include "getString.hpp"
#include "symbols.hpp"

#include <sstream>
#include <string>
#include <util.hpp>

using namespace steppable::__internals::numUtils;
using namespace steppable::__internals::symbols;
using namespace steppable::localization;

std::string reportAbs(const std::string& number, int steps = 2)
{
    std::stringstream ss;

    if (steps == 2)
    {
        if (number[0] == '-')
        {
            // Since
            ss << $("abs", "f39c432d-9031-423a-a12f-1efcd3e113b2")
               << number
               // is negative,
               << $("abs", "5c8a89a7-4cb1-40d8-b926-6ae84fc3a3ef") << "abs(" << number << ") = -(" << number << ")\n";
            // The absolute value of...
            ss << THEREFORE
               << $("abs", "8fd01dbe-c921-4f22-a0ab-d1348967e4b0", { number })
               // is
               << $("abs", "7066c6e7-6b80-4671-bc61-6c0322204c87") << standardizeNumber(number.substr(1));
        }
        else
        {
            // Since
            ss << $("abs", "f39c432d-9031-423a-a12f-1efcd3e113b2")
               << number
               // Is positive,...
               << $("abs", "b119f705-751b-425e-a758-47d755307700") << "abs(" << number << ") = " << number << '\n';
            // The absolute value of...
            ss << THEREFORE
               << $("abs", "8fd01dbe-c921-4f22-a0ab-d1348967e4b0", { number })
               // is
               << $("abs", "7066c6e7-6b80-4671-bc61-6c0322204c87") << standardizeNumber(number);
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
