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

#include "argParse.hpp"
#include "fn/basicArithm.hpp"
#include "subtractReport.hpp"
#include "symbols.hpp"
#include "util.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

std::string subtract(const std::string_view& a, const std::string_view& b, const int steps, const bool noMinus)
{
    auto [splitNumberArray, aIsNegative, bIsNegative] = splitNumber(a, b);
    auto [aInteger, aDecimal, bInteger, bDecimal] = splitNumberArray;
    bool resultIsNegative;
    const bool aIsDecimal = not isZeroString(aDecimal), bIsDecimal = not isZeroString(bDecimal);

    // Here, we try to determine if the result is negative or not
    // Scenario 1: a is negative and b is positive
    // Polarity  : Negative
    // Action    : Add a and b, negate the result
    //
    // Scenario 2: a is positive and b is negative
    // Polarity  : Positive
    // Action    : Add a and b
    //
    // Scenario 3: Both a and b are negative
    // Polarity  : Negative
    // Action    : Subtract positive b from positive a
    resultIsNegative = aIsNegative and bIsNegative or compare(a, b, 0) == "0";

    if (aIsNegative and not bIsNegative)
    {
        resultIsNegative = true;
        if (steps == 2)
            std::cout << "Adding " << a.substr(1) << " and " << b << " since " << a << " is negative\n";
        auto addResult = add(a.substr(1), b, steps, true);
        auto res = addResult.substr(addResult.find_last_of(' ') + 1);
        if (steps == 2)
        {
            // Replace last line with a subtraction report
            std::stringstream ss;
            ss << addResult.substr(0, addResult.find_last_of('\n')) << '\n';
            ss << THEREFORE << ' ' << a << " - " << b << " = -" << res;
            return ss.str();
        }
        else if (steps == 1)
        {
            std::stringstream ss;
            ss << THEREFORE << ' ' << a << " - " << b << " = -" << res;
            return ss.str();
        }
        else
        {
            return "-" + addResult;
        }
    }
    else if (bIsNegative and not aIsNegative)
    {
        if (steps == 2)
            std::cout << "Adding " << a << " and " << b.substr(1) << " since " << b << " is negative\n";
        resultIsNegative = false;
        return add(a, b.substr(1), steps);
    }
    if (compare(a, b, 0) == "0")
    {
        auto subtractResult = subtract(b, a, steps);
        if (steps == 2)
        {
            // Replace last line with a subtraction report
            std::stringstream ss;
            ss << subtractResult.substr(0, subtractResult.find_last_of('\n')) << '\n';
            ss << THEREFORE << ' ' << a << " - " << b << " = -"
               << subtractResult.substr(subtractResult.find_last_of(' ') + 1);
            return ss.str();
        }
        else if (steps == 1)
        {
            std::stringstream ss;
            ss << THEREFORE << ' ' << a << " - " << b << " = -"
               << subtractResult.substr(subtractResult.find_last_of(' ') + 1);
            return ss.str();
        }
        else
        {
            return "-" + subtractResult;
        }
    }

    std::string aStr = aInteger + aDecimal, bStr = bInteger + bDecimal;
    std::ranges::reverse(aStr);
    std::ranges::reverse(bStr);

    std::vector<int> diffDigits(aStr.length(), 0);
    std::vector<int> borrows(aStr.length());
    std::ranges::copy(aStr, borrows.begin());
    std::ranges::for_each(borrows, [](int& c) { c -= '0'; });
    for (int index = 0; index < aStr.length(); index++)
    {
        int aDigit = borrows[index], bDigit = bStr[index] - '0';
        if (aStr[index] == ' ')
            aDigit = 0;
        if (bStr[index] == ' ')
            bDigit = 0;

        const int diffDigit = aDigit - bDigit;
        diffDigits[index] = diffDigit;
        if (diffDigits[index] < 0)
        {
            diffDigits[index] += 10;
            borrows[index] += 10;
            diffDigits[index + 1]--;
            borrows[index + 1]--;
        }
    }

    // Add a decimal point
    if (aIsDecimal or bIsDecimal)
    {
        const auto decimalPos = aDecimal.length();
        const auto itSumDigits = diffDigits.begin();
        const auto itCarries = borrows.begin();

        diffDigits.insert(itSumDigits + static_cast<long>(decimalPos), -1); // -1 indicating a decimal point
        borrows.insert(itCarries + static_cast<long>(decimalPos), -1); // Reserve the space
    }

    std::ranges::reverse(borrows);
    std::ranges::reverse(diffDigits);
    if (diffDigits.empty())
        diffDigits.push_back(0);

    return reportSubtract(aInteger,
                          aDecimal,
                          bInteger,
                          bDecimal,
                          aIsDecimal,
                          bIsDecimal,
                          diffDigits,
                          borrows,
                          steps,
                          resultIsNegative,
                          noMinus);
}

#ifndef NO_MAIN
int main(int _argc, const char* _argv[])
{
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', "");
    program.addPosArg('b', "");
    program.addKeywordArg("steps", 2, "steps while adding");
    program.addSwitch("noMinus", false, "shows the minus sign");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    int steps = program.getKeywordArgument("steps");
    bool profile = program.getSwitch("profile"), noMinus = program.getSwitch("noMinus");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(Column Method Addition)
        std::cout << "Column Method Addition :\n" << subtract(aStr, bStr, steps, noMinus) << '\n';
        TOC()
    }
    else
        std::cout << subtract(aStr, bStr, steps, noMinus) << '\n';
}
#endif
