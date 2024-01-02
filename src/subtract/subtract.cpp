/**************************************************************************************************
 * Copyright (c) 2023 NWSOFT                                                                      *
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

#include "fn/basicArithm.hpp"
#include "argParse.hpp"
#include "subtractReport.hpp"
#include "util.hpp"

#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

std::string subtract(const std::string_view& a, const std::string_view& b, const int steps, const bool noMinus)
{
    auto [aInteger, aDecimal, bInteger, bDecimal] = splitNumber(a, b);
    const bool aIsDecimal = not isZeroString(aDecimal), bIsDecimal = not isZeroString(bDecimal);

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
    return reportSubtract(
        aInteger, aDecimal, bInteger, bDecimal, aIsDecimal, bIsDecimal, diffDigits, borrows, steps, noMinus);
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
