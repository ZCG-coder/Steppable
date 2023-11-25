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
#include "util.hpp"

#include <iomanip>
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

std::string divide(const std::string_view& number, const std::string_view& divisor, int steps = 2)
{
    std::string ans;
    std::stringstream tempFormattedAns, formattedAns;

    int idx = 0;
    std::string temp(1, number[idx]),
        lastRemainder = "",
        header = makeWider(static_cast<std::string>(divisor)) + ") " + makeWider(static_cast<std::string>(number));
    tempFormattedAns << header << std::endl;
    auto width = header.length();

    while (compare(temp, divisor, 0) == "0")
        temp += number[++idx];
    while (number.length() > idx)
    {
        auto quotient = getQuotient(temp, divisor);
        auto rem = getRemainder(quotient, temp, divisor);

        ans += quotient;
        tempFormattedAns << reportDivisionStep(temp, quotient, divisor, width, ans.length() - 1, lastRemainder);
        lastRemainder = temp = rem;
        if (number.length() - 1 >= ++idx)
            temp += number[idx];
    }
    if (ans.length() == 0)
        return "0";

    tempFormattedAns << std::setw(width) << std::setfill(' ') << std::right << makeWider(temp) << std::endl;
    tempFormattedAns << ans << " ... " << temp << std::endl;

    formattedAns << std::setw(width) << std::setfill(' ') << std::right << makeWider(ans) << std::endl;
    formattedAns << std::setw(divisor.length() * 3 - 1) << std::setfill(' ') << "";
    formattedAns << std::setw(width - divisor.length() * 2) << std::setfill('_') << "" << std::endl;
    formattedAns << tempFormattedAns.rdbuf();

    return formattedAns.str();
}

#ifndef NO_MAIN
int main(const int _argc, const char* _argv[])
{
    UTF8CodePage();
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', "Number 1");
    program.addPosArg('b', "Number 2");
    program.addKeywordArg("steps", 2, "Amount of steps while dividing. 0 = No steps, 2 = All steps.");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    int steps = program.getKeywordArgument("steps");
    bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(Column Method Division)
        std::cout << "Column Method Division :\n" << divide(aStr, bStr, steps) << std::endl;
        TOC()
    }
    else
        std::cout << divide(aStr, bStr, steps) << std::endl;
}
#endif
