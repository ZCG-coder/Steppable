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
 * @file subtractReport.cpp
 * @brief This file contains the implementation of the reportSubtract function, which reports the result of a
 * subtraction to the user.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 */

#include "subtractReport.hpp"

#include "symbols.hpp"
#include "util.hpp"

#include <sstream>
#include <string>
#include <utility>
#include <vector>

std::string reportSubtract(const std::string& aInteger,
                           const std::string& aDecimal,
                           const std::string& bInteger,
                           const std::string& bDecimal,
                           const bool aIsDecimal,
                           const bool bIsDecimal,
                           const std::vector<int>& _diffDigits,
                           const std::vector<int>& borrows,
                           const int steps,
                           bool resultIsNegative,
                           const bool noMinus)
{
    std::stringstream ss;
    auto aStr = aInteger + '.' + aDecimal;
    auto diffDigits = _diffDigits;
    if (diffDigits.front() == 0 and not steps)
        diffDigits = removeLeadingZeros(diffDigits);
    else if (diffDigits.front() == 0)
        diffDigits = replaceLeadingZeros(diffDigits);

    auto aOut = aInteger, bOut = bInteger;
    if (aIsDecimal)
        aOut += '.' + aDecimal;
    if (bIsDecimal)
        bOut += '.' + bDecimal;

    if (aIsDecimal and not bIsDecimal and not steps)
        bOut += std::string(aDecimal.length() + 1, ' ');
    if (not aIsDecimal and bIsDecimal and not steps)
        aOut += std::string(bDecimal.length() + 1, ' ');

    if (steps == 2)
    {
        ss << "   "; // Reserve space for the minus
        for (int i = 0; i < borrows.size(); i++)
            if (int currentBorrowDigit = borrows[i]; currentBorrowDigit != aStr[i] - '0')
                ss << makeSubscript(std::to_string(currentBorrowDigit))
                   << std::string(2 - (currentBorrowDigit / 10), ' ');
            else
                ss << "   ";
        ss << '\n' << "   "; // Reserve space for the minus
        for (char aChar : aOut)
            ss << aChar << "  ";

        if (not noMinus)
            ss << '\n' << "-  "; // Print a subtraction sign before printing b
        else
            ss << '\n' << "   ";
        if (aOut.length() > bOut.length())
            ss << std::string(aOut.length() - bOut.length(), ' ');
        for (char bChar : bOut)
            ss << bChar << "  ";
        ss << '\n' << std::string(diffDigits.size() * 3 + 2, '_') << '\n' << "   ";

        for (int outputDigit : diffDigits)
        {
            char outputChar = static_cast<char>(outputDigit + '0');
            if (outputDigit == -1)
                outputChar = '.';
            else if (outputDigit == -2)
                outputChar = ' ';
            ss << outputChar << "  "; // Two spaces
        }
        ss << '\n' << THEREFORE " ";
    }

    if (steps >= 1)
        ss << aOut << " - " << bOut << " = ";
    if (diffDigits.empty())
        diffDigits = { 0 };

    if (resultIsNegative)
        ss << '-';
    for (int outputDigit : diffDigits)
    {
        char outputChar = static_cast<char>(outputDigit + '0');
        if (outputDigit == -1)
            outputChar = '.';
        else if (outputDigit == -2)
            outputChar = '0';
        ss << outputChar; // No spaces
    }

    return std::move(ss.str());
}
