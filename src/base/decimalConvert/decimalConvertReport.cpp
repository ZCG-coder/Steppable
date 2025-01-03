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

#include "decimalConvertReport.hpp"

#include "symbols.hpp"

#include <iomanip>
#include <sstream>
#include <string>

using namespace steppable::__internals::symbols;

std::string reportDecimalConvertStep(const std::string& baseString,
                                     const std::string& digit,
                                     const size_t powerIndex,
                                     const std::string& convertedDigit,
                                     const size_t maxWidth)
{
    std::stringstream ss;

    ss << digit << " " << MULTIPLY << " ";
    ss << baseString << makeSuperscript(static_cast<char>(powerIndex + '0'));
    ss << " = " << std::setw(static_cast<int>(maxWidth)) << convertedDigit << std::setw(0);
    return ss.str();
}

std::string reportDecimalConvert(const std::string& inputString,
                                 const std::string& baseString,
                                 const std::string& convertedString,
                                 const int steps)
{
    if (steps == 0)
        return static_cast<std::string>(convertedString);

    std::stringstream ss;
    if (steps == 2)
        ss << THEREFORE << " ";
    ss << inputString << makeSubscript(static_cast<std::string>(baseString)) << " = ";
    ss << convertedString << makeSubscript("10");
    return ss.str();
}
