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

using namespace steppable::__internals::numUtils;
using namespace steppable::output;
using namespace steppable::__internals::arithmetic;

namespace steppable::__internals::arithmetic
{
    std::string power(const std::string_view _number, const std::string_view& _raiseTo, const int steps)
    {
        std::string raiseTo = static_cast<std::string>(_raiseTo), number = static_cast<std::string>(_number);

        // Here, we attempt to give a quick answer, instead of doing pointless iterations.
        if (number == "1")
        {
            if (steps == 2)
                return "Since the number is 1, the result is 1.";
            else if (steps == 1)
                return "1"s + symbols::makeSuperscript(static_cast<std::string>(raiseTo)) + " = 1";
            else
                return "1";
        }
        else if (number == "0")
        {
            if (steps == 2)
                return "Since the number is 0, the result is 0.";
            else if (steps == 1)
                return "0"s + symbols::makeSuperscript(static_cast<std::string>(raiseTo)) + " = 0";
            else
                return "0";
        }

        auto numberNoTrailingZeros = removeTrailingZeros(number);
        size_t numberTrailingZeros = number.length() - numberNoTrailingZeros.length();
        // Remove the zeros to reduce the workload.
        number = numberNoTrailingZeros;

        bool negative = false;
        if (compare(raiseTo, "0", 0) == "0")
        {
            // raiseTo is negative
            raiseTo = raiseTo.substr(1);
            negative = true;
        }
        return reportPower(number, raiseTo, numberTrailingZeros, negative, steps);
    }
} // namespace steppable::__internals::arithmetic

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
