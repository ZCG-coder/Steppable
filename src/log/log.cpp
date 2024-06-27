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
 * @file log.cpp
 * @brief Contains the implementation of the logarithmic functions.
 *
 * @author Andy Zhang
 * @date 23rd June 2024
 */

#include "argParse.hpp"
#include "fn/basicArithm.hpp"
#include "logReport.hpp"
#include "output.hpp"
#include "rounding.hpp"
#include "util.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

using namespace steppable::__internals::arithmetic;
using namespace steppable::__internals::utils;
using namespace std::literals;

namespace steppable::__internals::arithmetic
{
    std::string _log(const std::string& _number, const size_t _decimals)
    {
        //   /-\   +--------------------------------------------+
        //  / ! \  | WARNING: DO NOT CALL THIS METHOD DIRECTLY! |
        // /-----\ +--------------------------------------------+
        //                      4        3         2
        //          (x - 1)(137x  + 1762x  + 3762x  + 1762x + 137)
        // ln(x) = ------------------------------------------------
        //                 5      4       3       2
        //             30(x  + 25x  + 100x  + 100x  + 25x + 1)

        auto x2 = power(_number, "2", 0);
        auto x3 = power(_number, "3", 0);
        auto x4 = multiply(x2, x2, 0);
        auto x5 = multiply(x2, x3, 0);

        auto xMinus1 = subtract(_number, "1", 0);
        auto numerator = multiply(x4, "137", 0);
        numerator = add(numerator, multiply(x3, "1762", 0), 0);
        numerator = add(numerator, multiply(x2, "3762", 0), 0);
        numerator = add(numerator, multiply(_number, "1762", 0), 0);
        numerator = add(numerator, "137", 0);
        numerator = multiply(xMinus1, numerator, 0);

        auto denominator = add(x5, multiply(x4, "25", 0), 0);
        denominator = add(denominator, multiply(x3, "100", 0), 0);
        denominator = add(denominator, multiply(x2, "100", 0), 0);
        denominator = add(denominator, multiply(_number, "25", 0), 0);
        denominator = add(denominator, "1", 0);
        denominator = multiply("30", denominator, 0);

        auto result = divide(numerator, denominator, 0, static_cast<int>(_decimals));
        return result;
    }

    // Common logarithms
    std::string logb(const std::string& _number, const std::string& _base, const size_t _decimals)
    {
        //            ln(a)
        // log (x) = -------
        //    b       ln(b)
        auto lnX = _log(_number, _decimals + 2);
        auto lnB = _log(_base, _decimals + 2);
        auto result = divide(lnX, lnB, 0, static_cast<int>(_decimals));

        return numUtils::roundOff(result, _decimals);
    }

    std::string log10(const std::string& _number, const size_t _decimals) { return logb(_number, "10", _decimals); }

    std::string log2(const std::string& _number, const size_t _decimals) { return logb(_number, "2", _decimals); }

    std::string ln(const std::string& _number, const size_t _decimals) { return _log(_number, _decimals); }
} // namespace steppable::__internals::arithmetic

#ifndef NO_MAIN
int main(int _argc, const char* _argv[])
{
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('c', "Command", false);
    program.addPosArg('n', "Number", true);
    program.addPosArg('b', "Base", true);
    program.addKeywordArg("mode", 0, "The mode to calculate in. 0 = radians (default), 1 = degrees, 2 = gradians.");
    program.addKeywordArg("decimals", 5, "Amount of decimals while calculating.");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    const int mode = program.getKeywordArgument("mode");
    const bool profile = program.getSwitch("profile");
    const int decimals = program.getKeywordArgument("decimals");
    const auto& command = static_cast<std::string>(program.getPosArg(0));
    const auto& arg = static_cast<std::string>(program.getPosArg(1));
    const auto& base = static_cast<std::string>(program.getPosArg(2));

    using namespace steppable::__internals;
    using namespace steppable::output;

    if (command == "logb")
        std::cout << arithmetic::logb(arg, base, decimals) << "\n";
    else if (command == "log10")
        std::cout << arithmetic::log10(arg, decimals) << "\n";
    else if (command == "log2")
        std::cout << arithmetic::log2(arg, decimals) << "\n";
    else if (command == "ln")
        std::cout << arithmetic::ln(arg, decimals) << "\n";
    else
    {
        error("log"s, "Unknown command: "s + command);
        return EXIT_FAILURE;
    }
}
#endif
