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

#include "argParse.hpp"
#include "divisionReport.hpp"
#include "fn/basicArithm.hpp"
#include "output.hpp"
#include "util.hpp"

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

auto getQuotient(const auto& _temp, const auto& _divisor)
{
    auto temp = _temp;
    auto divisior = _divisor;
    if (compare(temp, divisior, 0) == "0")
        return std::string("0");
    if (compare(temp, divisior, 0) == "2")
        return std::string("1"); // Equal

    int out = 0;
    while (compare(temp, divisior, 0) == "1" or compare(temp, divisior, 0) == "2")
    {
        out++;
        temp = subtract(temp, divisior, 0);
    }

    return std::to_string(out);
}

inline auto getRemainder(const auto& quotient, const auto& temp, const auto& divisor)
{
    return subtract(temp, multiply(quotient, divisor, 0), 0);
}

std::string divide(const std::string_view& _number,
                   const std::string_view& _divisor,
                   const int steps,
                   const int _decimals)
{
    if (isZeroString(_number) and isZeroString(_divisor))
    {
        // Easter egg in open-source code
        error("Imagine that you have zero cookies and you split them evenly among zero friends, how many cookies does "
              "each person get? See? It doesn't make sense. And Cookie Monster is sad that there are no cookies, and "
              "you are sad that you have no friends.");
        return "Indeterminate";
    }
    if (isZeroString(_divisor))
    {
        error("Division of %s by zero leads to infinity.", std::string(_number).c_str());
        return "Infinity";
    }

    auto [numberInteger, numberDecimal, divisorInteger, divisorDecimal] = splitNumber(_number, _divisor, false, true);
    auto decimals = _decimals;

    while (not divisorDecimal.empty())
    {
        divisorInteger += divisorDecimal[0];
        divisorDecimal.erase(divisorDecimal.begin());
        if (not numberDecimal.empty())
        {
            numberInteger += numberDecimal[0];
            numberDecimal.erase(numberDecimal.begin());
        }
        else
            numberInteger += '0';
    }
    auto number = numberInteger + numberDecimal;
    auto divisor = divisorInteger + divisorDecimal;
    std::string ans;
    std::stringstream tempFormattedAns, formattedAns;

    int numDecimals;
    for (int i = 0; i < decimals + 1; i++) // Additional 0 is for rounding
        number += '0';

    int idx = 0;
    std::string temp(1, number[idx]), lastRemainder = "", header = makeWider(divisor) + ") " + makeWider(number);
    tempFormattedAns << header << std::endl;
    auto width = header.length();

    while (compare(temp, divisor, 0) == "0")
        temp += number[++idx];
    while (number.length() > idx)
    {
        if (isZeroString(temp))
        {
            idx++;
            ans += "0";
            continue;
        }
        auto quotient = getQuotient(temp, divisor);
        auto rem = getRemainder(quotient, temp, divisor);

        ans += quotient;
        if (steps == 2)
            tempFormattedAns << reportDivisionStep(temp, quotient, divisor, width, ans.length() - 1, lastRemainder);
        lastRemainder = temp = rem;
        if (number.length() - 1 >= ++idx)
            temp += number[idx];
    }

    // Only does this when it is a decimal
    if ((not numberDecimal.empty()) or decimals)
    {
        if (not numberDecimal.empty() and numberDecimal.length() < decimals)
            decimals = numberDecimal.length();
        int decimalPos = static_cast<int>(ans.length()) - decimals - 1;
        if (decimalPos < 0)
        {
            decimals = 0;
            decimalPos = ans.length() - 1;
        }
        auto beforeDecimal = ans.substr(0, decimalPos), afterDecimal = ans.substr(decimalPos, ans.length() - 1);

        if (afterDecimal.back() > '4')
            afterDecimal = add(afterDecimal, "1", 0);
        if (beforeDecimal.empty())
            beforeDecimal = "0";
        ans = beforeDecimal + "." + afterDecimal;
    }

    return reportDivision(tempFormattedAns, temp, ans, divisor, number, _divisor, _number, steps, decimals, width);
}

#ifndef NO_MAIN
int main(const int _argc, const char* _argv[])
{
    UTF8CodePage();
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', "Number 1");
    program.addPosArg('b', "Number 2");
    program.addKeywordArg("steps", 2, "Amount of steps while dividing. 0 = No steps, 2 = All steps.");
    program.addKeywordArg("decimals", 5, "Decimals to output");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    const int steps = program.getKeywordArgument("steps");
    const int decimals = program.getKeywordArgument("decimals");
    const bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(Column Method Division)
        std::cout << "Column Method Division :\n" << divide(aStr, bStr, steps, decimals) << std::endl;
        TOC()
    }
    else
        std::cout << divide(aStr, bStr, steps, decimals) << std::endl;
}
#endif
