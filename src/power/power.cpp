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
 * @file power.cpp
 * @brief This file contains the implementation for the function power, which raises a number to a power.
 *
 * @author Andy Zhang
 * @date 8rd November 2023
 */
#include "argParse.hpp"
#include "fn/basicArithm.hpp"
#include "powerReport.hpp"
#include "util.hpp"

std::string power(const std::string_view _number, const std::string_view& _raiseTo, const int steps)
{
    std::string raiseTo = static_cast<std::string>(_raiseTo);
    bool negative = false;
    if (compare(raiseTo, "0", 0) == "0")
    {
        // raiseTo is negative
        raiseTo = raiseTo.substr(1);
        negative = true;
    }
    std::string numberOrig = static_cast<std::string>(_number), number = "1";
    return reportPower(_number, raiseTo, negative, steps);
}

#ifndef NO_MAIN
int main(const int _argc, const char* _argv[])
{
    Utf8CodePage();
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', "Number as the base");
    program.addPosArg('b', "Number as the exponent");
    program.addKeywordArg(
        "steps", 2, "Amount of steps while raising the power (i.e., multiplying). 0 = No steps, 2 = All steps.");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    int steps = program.getKeywordArgument("steps");
    bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(Power)
        std::cout << "Power :\n" << power(aStr, bStr, steps) << '\n';
        TOC()
    }
    else
        std::cout << power(aStr, bStr, steps) << '\n';
}
#endif
