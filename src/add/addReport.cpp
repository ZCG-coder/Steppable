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

#include "addReport.hpp"

#include "symbols.hpp"
#include "util.hpp"

#include <sstream>
#include <string>
#include <vector>

std::string reportAdd(const std::string& aInteger,
                      const std::string& aDecimal,
                      const std::string& bInteger,
                      const std::string& bDecimal,
                      const std::vector<int>& sumDigits,
                      const std::vector<bool>& carries,
                      const bool resultIsNegative,
                      const int steps)
{
    std::stringstream ss;

    const bool aIsDecimal = not isZeroString(aDecimal), bIsDecimal = not isZeroString(bDecimal);
    std::string aOut = aInteger, bOut = bInteger;
    if (aIsDecimal)
        aOut += '.' + aDecimal;
    else if (not steps)
        ; // Don't use the spaced formatting
    if (bIsDecimal)
        bOut += '.' + bDecimal;
    else if (not steps)
        ; // Don't use the spaced formatting

    if (aIsDecimal and not bIsDecimal and steps)
        bOut += std::string(aDecimal.length() + 1, ' ');
    if (bIsDecimal and not aIsDecimal and steps)
        aOut += std::string(bDecimal.length() + 1, ' ');

    if (steps == 2)
    {
        ss << "      "; // Reserve space for the plus
        if (bOut.length() > aOut.length())
            ss << std::string(bOut.length() - aOut.length(), ' ');
        for (const char aChar : aOut)
            ss << aChar << "  ";

        ss << '\n' << "+     "; // Print an add sign before printing b
        if (aOut.length() > bOut.length())
            ss << std::string(aOut.length() - bOut.length(), ' ');
        for (const char bChar : bOut)
            ss << bChar << "  ";

        ss << '\n' << "   ";
        for (const bool c : carries)
            if (c)
                ss << makeSubscript("1") << "  ";
            else
                ss << "   ";

        ss << '\n' << std::string((sumDigits.size() + 2) * 3, '_') << '\n';
        if (sumDigits.size() <= aOut.length())
            ss << "   ";
        ss << "   ";
        for (const int outputChar : sumDigits)
            if (outputChar == -1)
                ss << ".  ";
            else
                ss << outputChar << "  "; // Two spaces
        ss << '\n' << THEREFORE " ";
    }

    if (steps >= 1)
        ss << aOut << " + " << bOut << " = ";

    std::string outStr;
    for (const auto c : sumDigits)
        if (c == -1)
            outStr += ".";
        else
            outStr += std::string(1, c + '0');
    ss << standardizeNumber(outStr);

    return ss.str();
}
