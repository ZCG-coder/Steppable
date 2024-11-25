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
 * @file abs.cpp
 * @brief This file contains the implementation of the abs function, which gets the absolute value of a number string.
 *
 * @author Andy Zhang
 * @date 12th January 2024
 */

#include "absReport.hpp"
#include "argParse.hpp"
#include "getString.hpp"
#include "util.hpp"

#include <fn/calc.hpp>
#include <iostream>
#include <string>

using namespace steppable::__internals::utils;
using namespace steppable::__internals::arithmetic;
using namespace steppable::localization;

namespace steppable::__internals::arithmetic
{
    std::string abs(const std::string& _number, const int steps)
    {
        std::string number = static_cast<std::string>(_number);
        return reportAbs(number, steps);
    }
} // namespace steppable::__internals::arithmetic

#ifndef NO_MAIN
int main(const int _argc, const char* _argv[])
{
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', $("abs", "ca70a6a7-d1d8-4e43-a94e-014d8f9839c9"));
    program.addKeywordArg("steps", 2, $("abs", "3860a4ae-1073-4a6d-a75e-f64426291573"));
    program.addSwitch("profile", false, $("abs", "5d7bddda-e33f-4f9c-81b2-d30baad2ec5c"));
    program.parseArgs();

    const int steps = program.getKeywordArgument("steps");
    const bool profile = program.getSwitch("profile");
    const auto& number = program.getPosArg(0);

    if (profile)
    {
        TIC(Column Method Addition)
        std::cout << "Taking absolute value :"
                  << "\n"
                  << abs(number, steps) << '\n';
        TOC()
    }
    else
        std::cout << abs(number, steps) << '\n';
}
#endif
