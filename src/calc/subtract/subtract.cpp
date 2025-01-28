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
 * @file subtract.cpp
 * @brief This file contains the implementation of the subtract function, which subtracts two numbers using the column
 * method.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 */

#include "argParse.hpp"
#include "fn/calc.hpp"
#include "getString.hpp"
#include "subtractReport.hpp"
#include "symbols.hpp"
#include "util.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace steppable::__internals::numUtils;
using namespace steppable::output;
using namespace steppable::localization;
using namespace steppable::__internals::calc;

namespace steppable::__internals::calc
{
    std::string subtract(const std::string& a, const std::string& b, const int steps, const bool noMinus)
    {
        auto [splitNumberArray, aIsNegative, bIsNegative] = splitNumber(a, b);
        auto [aInteger, aDecimal, bInteger, bDecimal] = splitNumberArray;
        bool resultIsNegative = false;
        const bool aIsDecimal = not isZeroString(aDecimal);
        const bool bIsDecimal = not isZeroString(bDecimal);

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
                // Adding {0} and {1} since {0} is negative
                std::cout << $("subtract", "063f0bd2-a4ca-4433-97c0-8baa73cd0e7c", { a.substr(1), b }) << "\n";
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
            if (steps == 1)
            {
                std::stringstream ss;
                ss << THEREFORE << ' ' << a << " - " << b << " = -" << res;
                return ss.str();
            }
            return "-" + addResult;
        }
        if (bIsNegative)
        {
            if (steps == 2)
                // Adding {0} and {1} since {1} is negative
                std::cout << $("subtract", "063f0bd2-a4ca-4433-97c0-8baa73cd0e7c", { a, b.substr(1) }) << "\n";
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
            if (steps == 1)
            {
                std::stringstream ss;
                ss << THEREFORE << ' ' << a << " - " << b << " = -"
                   << subtractResult.substr(subtractResult.find_last_of(' ') + 1);
                return ss.str();
            }
            return "-" + subtractResult;
        }

        std::string aStr = aInteger + aDecimal;
        std::string bStr = bInteger + bDecimal;
        std::ranges::reverse(aStr);
        std::ranges::reverse(bStr);

        std::vector<int> diffDigits(aStr.length(), 0);
        std::vector<int> borrows(aStr.length());
        std::ranges::copy(aStr, borrows.begin());
        std::ranges::for_each(borrows, [](int& c) { c -= '0'; });
        for (int index = 0; index < aStr.length(); index++)
        {
            int aDigit = borrows[index];
            int bDigit = bStr[index] - '0';
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
            const auto itSumDigits = diffDigits.cbegin();
            const auto itCarries = borrows.cbegin();

            diffDigits.insert(itSumDigits + static_cast<long>(decimalPos), -1); // -1 indicating a decimal point
            borrows.insert(itCarries + static_cast<long>(decimalPos), -1); // Reserve the space
        }

        std::ranges::reverse(borrows);
        std::ranges::reverse(diffDigits);
        if (diffDigits.empty())
            diffDigits.push_back(0);
        if (diffDigits.front() == -1)
        {
            diffDigits.insert(diffDigits.cbegin(), -2);
            borrows.insert(borrows.cbegin(), -2);
        }

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
} // namespace steppable::__internals::calc

#ifndef NO_MAIN
int main(int _argc, const char* _argv[])
{
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', $("subtract", "3db38a7c-58e9-44f2-ba36-47e355b60294"));
    program.addPosArg('b', $("subtract", "a697967c-5010-423c-9a84-201c955310de"));
    program.addKeywordArg("steps", 2, $("subtract", "645b0f26-3c2a-49ae-a9d6-1e06c11fe15e"));
    program.addSwitch("noMinus", false, $("subtract", "7704320c-1391-405f-8147-0b4023d769f6"));
    program.addSwitch("profile", false, $("subtract", "4c13dd96-fb5b-4e99-b8e6-08e8be07b446"));
    program.parseArgs();

    int steps = program.getKeywordArgument("steps");
    bool profile = program.getSwitch("profile");
    bool noMinus = program.getSwitch("noMinus");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(Column Method Subtraction)
        std::cout << $("subtract", "4dee3c00-c204-4cb0-afad-e57e41763bf5") << "\n"
                  << subtract(aStr, bStr, steps, noMinus) << '\n';
        TOC()
    }
    else
        std::cout << subtract(aStr, bStr, steps, noMinus) << '\n';
}
#endif
