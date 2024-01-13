/**************************************************************************************************
 * Copyright (c) 2024 NWSOFT                                                                      *
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

std::string add(const std::string_view& a, const std::string_view& b, const int steps, const bool negative)
{
    auto splittedNumber = splitNumber(a, b);
    auto [aInteger, aDecimal, bInteger, bDecimal] = splittedNumber.splittedNumberArray;
    bool aIsNegative = splittedNumber.aIsNegative, bIsNegative = splittedNumber.bIsNegative, resultIsNegative = false;
    const bool aIsDecimal = not isZeroString(aDecimal), bIsDecimal = not isZeroString(bDecimal);

    if (negative)
        resultIsNegative = true;
    else if (aIsNegative and bIsNegative)
    {
        resultIsNegative = true;
        aIsNegative = false;
        bIsNegative = false;
    }
    else if (aIsNegative)
    {
        if (steps == 2)
            std::cout << "Subtracting " << b << " from " << a << " since " << a << " is negative.\n";
        return subtract(b, a, steps);
    }
    else if (bIsNegative)
    {
        if (steps == 2)
            std::cout << "Subtracting " << a << " from " << b << " since " << b << " is negative.\n";
        return subtract(a, b, steps);
    }

    auto aStr = aInteger + aDecimal, bStr = bInteger + bDecimal;
    std::ranges::reverse(aStr);
    std::ranges::reverse(bStr);

    std::vector sumDigits(aStr.length() + 1, 0);
    std::vector carries(aStr.length() + 1, false);
    for (size_t index = 0; index < aStr.length(); index++)
    {
        int aDigit = aStr[index] - '0', bDigit = bStr[index] - '0';
        if (aStr[index] == ' ')
            aDigit = 0;
        if (bStr[index] == ' ')
            bDigit = 0;

        const int sumDigit = aDigit + bDigit;
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
        const auto decimalPos = aDecimal.length();
        const auto& itSumDigits = sumDigits.begin();
        const auto& itCarries = carries.begin();

        sumDigits.insert(itSumDigits + static_cast<long>(decimalPos), -1); // -1 indicating a decimal point
        carries.insert(itCarries + static_cast<long>(decimalPos), false); // Reserve the space
    }

    std::reverse(carries.begin(), carries.end());
    std::ranges::reverse(sumDigits);
    if (sumDigits.front() == 0)
        sumDigits.erase(sumDigits.begin());

    return reportAdd(aInteger, aDecimal, bInteger, bDecimal, sumDigits, carries, resultIsNegative, steps);
}

#ifndef NO_MAIN
int main(const int _argc, const char* _argv[])
{
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', "Number 1");
    program.addPosArg('b', "Number 2");
    program.addKeywordArg("steps", 2, "Amount of steps while adding. 0 = No steps, 2 = All steps.");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    const int steps = program.getKeywordArgument("steps");
    const bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(Column Method Addition)
        std::cout << "Column Method Addition :\n" << add(aStr, bStr) << '\n';
        TOC()
    }
    else
        std::cout << add(aStr, bStr, steps) << '\n';
}
#endif
