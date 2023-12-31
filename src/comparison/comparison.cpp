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
#include "comparisonReport.hpp"
#include "fn/basicArithm.hpp"
#include "util.hpp"

#include <sstream>
#include <string>
#include <string_view>

std::string compare(const std::string_view& a, const std::string_view& b, const int steps)
{
    const auto result = splitNumber(a, b, false, true).splittedNumberArray;
    const auto& aIntegerReal = result[0];
    if (const auto& bIntegerReal = result[2]; aIntegerReal.length() != bIntegerReal.length())
        return reportComparisonAtInteger(a, b, aIntegerReal.length() > bIntegerReal.length(), steps);

    for (long i = 0; static_cast<size_t>(i) < a.length(); i++)
    {
        if (a[i] == b[i] or not isdigit(a[i]) or not isdigit(b[i]))
            continue; // Decimal point or equals
        if (const bool bigger = a[i] > b[i])
            return reportComparisonByDigit(a, b, i, bigger, steps);
        else
            return reportComparisonByDigit(a, b, -i, bigger, steps);
    }

    if (steps == 1)
        return "Equal";
    if (steps == 2)
    {
        std::stringstream ss;
        ss << a << " = " << b;
        return ss.str();
    }
    return "2";
}

#ifndef NO_MAIN
int main(int _argc, const char** _argv)
{
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', "Number 1");
    program.addPosArg('b', "Number 2");
    program.addKeywordArg("steps", 2, "Amount of steps while comparing");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    int steps = program.getKeywordArgument("steps");
    bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(Comparing...)
        std::cout << compare(aStr, bStr, steps) << '\n';
        TOC()
    }
    else
        std::cout << compare(aStr, bStr, steps) << '\n';
}
#endif
