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

#include "addReport.hpp"
#include "argParse.hpp"
#include "fn/basicArithm.hpp"
#include "util.hpp"

#include <algorithm>
#include <iostream>
#include <string_view>
#include <vector>

std::string add(const std::string_view& a, const std::string_view& b, const int steps)
{
    auto [aInteger, aDecimal, bInteger, bDecimal] = splitNumber(a, b);
    bool aIsDecimal = not isZeroString(aDecimal), bIsDecimal = not isZeroString(bDecimal);

    auto aStr = aInteger + aDecimal, bStr = bInteger + bDecimal;
    std::reverse(aStr.begin(), aStr.end());
    std::reverse(bStr.begin(), bStr.end());

    std::vector<int> sumDigits(aStr.length() + 1, 0);
    std::vector<bool> carries(aStr.length() + 1, false);
    for (int index = 0; index < aStr.length(); index++)
    {
        int aDigit = aStr[index] - '0', bDigit = bStr[index] - '0';
        if (aStr[index] == ' ')
            aDigit = 0;
        if (bStr[index] == ' ')
            bDigit = 0;

        int sumDigit = aDigit + bDigit;
        sumDigits[index] += sumDigit;
        if (sumDigits[index] >= 10)
        {
            sumDigits[index] -= 10;
            sumDigits[index + 1] += 1;
            carries[index + 1] = true;
        }
    }

    // Add a decimal point
    if (aIsDecimal or bIsDecimal)
    {
        auto decimalPos = aDecimal.length();
        const auto& itSumDigits = sumDigits.begin();
        const auto& itCarries = carries.begin();

        sumDigits.insert(itSumDigits + static_cast<long>(decimalPos), -1); // -1 indicating a decimal point
        carries.insert(itCarries + static_cast<long>(decimalPos), false); // Reserve the space
    }

    std::reverse(carries.begin(), carries.end());
    std::reverse(sumDigits.begin(), sumDigits.end());
    if (sumDigits.front() == 0)
        sumDigits.erase(sumDigits.begin());

    return reportAdd(aInteger, aDecimal, bInteger, bDecimal, sumDigits, carries, steps);
}

#ifndef NO_MAIN
int main(const int _argc, const char* _argv[])
{
    UTF8CodePage();
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', "Number 1");
    program.addPosArg('b', "Number 2");
    program.addKeywordArg("steps", 2, "Amount of steps while adding. 0 = No steps, 2 = All steps.");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    int steps = program.getKeywordArgument("steps");
    bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(Column Method Addition)
        std::cout << "Column Method Addition :\n" << add(aStr, bStr) << std::endl;
        TOC()
    }
    else
        std::cout << add(aStr, bStr, steps) << std::endl;
}
#endif
