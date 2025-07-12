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
 * @file add.cpp
 * @brief This file contains the implementation of the add function, which add two number strings together.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 */

#include "addReport.hpp"
#include "argParse.hpp"
#include "fn/calc.hpp"
#include "getString.hpp"
#include "util.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace steppable::__internals::numUtils;
using namespace steppable::__internals::utils;
using namespace steppable::__internals::calc;
using namespace steppable::__internals::symbols;
using namespace steppable::localization;

namespace steppable::__internals::calc
{
    std::string add(const std::string& a,
                    const std::string& b,
                    const int steps,
                    const bool negative,
                    const bool properlyFormat)
    {
        if (isZeroString(a))
        {
            std::stringstream ss;
            if (steps == 2)
            {
                // The result is...
                ss << BECAUSE << " a = 0" << $("add", "ca3f0783-02d8-4006-8bbe-2311ffd708fa") << b << '\n';
                ss << THEREFORE << " " << a << " + " << b << " = " << b;
            }
            else if (steps == 1)
                ss << a << " + " << b << " = " << b;
            else
                ss << b;

            return ss.str();
        }

        if (isZeroString(b))
        {
            std::stringstream ss;
            if (steps == 2)
            {
                // The result is...
                ss << BECAUSE << " b = 0" << $("add", "ca3f0783-02d8-4006-8bbe-2311ffd708fa") << a << '\n';
                ss << THEREFORE << " " << a << " + " << b << " = " << a;
            }
            else if (steps == 1)
                ss << a << " + " << b << " = " << a;
            else
                ss << a;

            return ss.str();
        }
        auto [splitNumberArray, aIsNegative, bIsNegative] = splitNumber(a, b, true, true, properlyFormat);
        auto [aInteger, aDecimal, bInteger, bDecimal] = splitNumberArray;
        bool resultIsNegative = false;
        const bool aIsDecimal = not isZeroString(aDecimal);
        const bool bIsDecimal = not isZeroString(bDecimal);

        if (negative or (aIsNegative and bIsNegative))
            resultIsNegative = true;
        else if (aIsNegative)
        {
            if (steps == 2)
                // Subtracting {0} from {1} since {2} is negative
                std::cout << $("add", "547d6d96-de8d-4f2e-af3b-2da475d8d161", { b, a.substr(1), a }) << "\n";
            return subtract(b, a.substr(1), steps);
        }
        else if (bIsNegative)
        {
            if (steps == 2)
                // Subtracting {0} from {1} since {2} is negative
                std::cout << $("add", "547d6d96-de8d-4f2e-af3b-2da475d8d161", { a, b.substr(1), b }) << "\n";
            return subtract(a, b.substr(1), steps);
        }

        auto aStr = aInteger + aDecimal;
        auto bStr = bInteger + bDecimal;
        std::ranges::reverse(aStr);
        std::ranges::reverse(bStr);

        std::vector<int> sumDigits(aStr.length() + 1, 0);
        std::vector<int> carries(aStr.length() + 1, 0);

        for (size_t index = 0; index < aStr.length(); index++)
        {
            int aDigit = aStr[index] - '0';
            int bDigit = bStr[index] - '0';
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
                carries[index + 1] = 1;
            }
        }

        // Add a decimal point
        if (aIsDecimal or bIsDecimal)
        {
            const auto decimalPos = aDecimal.length();
            const auto& itSumDigits = sumDigits.begin();
            const auto& itCarries = carries.begin();

            sumDigits.insert(itSumDigits + static_cast<long>(decimalPos), -1); // -1 indicating a decimal point
            carries.insert(itCarries + static_cast<long>(decimalPos), 0); // Reserve the space
        }

        std::ranges::reverse(carries);
        std::ranges::reverse(sumDigits);
        if (sumDigits.front() == 0 and properlyFormat)
            sumDigits.erase(sumDigits.begin());

        if (aIsNegative)
            aInteger = "-" + aInteger;
        if (bIsNegative)
            bInteger = "-" + bInteger;

        return reportAdd(
            aInteger, aDecimal, bInteger, bDecimal, sumDigits, carries, resultIsNegative, steps, properlyFormat);
    }
} // namespace steppable::__internals::calc

#ifndef NO_MAIN
int main(const int _argc, const char* _argv[])
{
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    // Number 1
    program.addPosArg('a', $("add", "6e1121d2-75a4-4173-a54b-0b6c2f98abfc"));
    // Number 2
    program.addPosArg('b', $("add", "852e4cdb-cb19-4717-95b3-eaec08777ebc"));
    // Steps while adding...
    program.addKeywordArg("steps", 2, $("add", "c935c960-609c-4ecd-97f5-d4f36d3bbc9f"));
    // Profiling
    program.addSwitch("profile", false, $("add", "6959b967-151d-44b0-a250-464f871d6dc1"));
    program.parseArgs();

    const int steps = program.getKeywordArgument("steps");
    const bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(Column Method Addition)
        std::cout << $("add", "0c7e9691-2777-4cb8-8ae6-e21206859c5d") << "\n" << add(aStr, bStr) << '\n';
        TOC()
    }
    else
        std::cout << add(aStr, bStr, steps) << '\n';
}
#endif
