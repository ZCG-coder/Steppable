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
 * @file hyp.cpp
 * @brief Hyperbolic trigonometric functions.
 *
 * @author Andy Zhang
 * @date 20th June 2024
 */

#include "argParse.hpp"
#include "constants.hpp"
#include "fn/basicArithm.hpp"
#include "hypReport.hpp"
#include "output.hpp"
#include "util.hpp"

#include <functional>
#include <iostream>
#include <string>

using namespace std::literals;
using namespace steppable::output;
using namespace steppable::__internals::utils;
using namespace steppable::__internals::numUtils;

namespace steppable::__internals::arithmetic
{
    std::string sinh(const std::string& x, const int decimals)
    {
        const auto& twoX = multiply(x, "2", 0);
        const auto& eTwoX = power(constants::E, twoX, 0);
        const auto& eX = power(constants::E, x, 0);

        const auto& numerator = subtract(eTwoX, "1", 0);
        const auto& denominator = multiply("2", eX, 0);

        return divide(numerator, denominator, 0, decimals);
    }

    std::string cosh(const std::string& x, const int decimals)
    {
        const auto& twoX = multiply(x, "2", 0);
        const auto& eTwoX = power(constants::E, twoX, 0);
        const auto& eX = power(constants::E, x, 0);

        const auto& numerator = add(eTwoX, "1", 0);
        const auto& denominator = multiply("2", eX, 0);

        return divide(numerator, denominator, 0, decimals);
    }

    std::string tanh(const std::string& x, const int decimals)
    {
        const auto& numerator = sinh(x, decimals);
        const auto& denominator = cosh(x, decimals);

        return divide(numerator, denominator, 0, decimals);
    }

    std::string coth(const std::string& x, const int decimals)
    {
        const auto& denominator = tanh(x, decimals);
        if (isZeroString(denominator))
        {
            error("hyp::coth"s, "Hyperbolic cotangent is not defined here."s);
            return "Infinity";
        }

        return divide("1", denominator, 0, decimals);
    }

    std::string csch(const std::string& x, const int decimals)
    {
        const auto& denominator = sinh(x, decimals);
        if (isZeroString(denominator))
        {
            error("hyp::csch"s, "Hyperbolic cosecant is not defined here."s);
            return "Infinity";
        }

        return divide("1", denominator, 0, decimals);
    }

    std::string sech(const std::string& x, const int decimals)
    {
        const auto& denominator = cosh(x, decimals);
        if (isZeroString(denominator))
        {
            error("hyp::sech"s, "Hyperbolic secant is not defined here."s);
            return "Infinity";
        }

        return divide("1", denominator, 0, decimals);
    }
} // namespace steppable::__internals::arithmetic

#ifndef NO_MAIN
int main(int _argc, const char* _argv[])
{
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('c', "Command", false);
    program.addPosArg('n', "Number", false);
    program.addKeywordArg("decimals", 5, "Amount of decimals while calculating.");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    const bool profile = program.getSwitch("profile");
    const int decimals = program.getKeywordArgument("decimals");
    const auto& command = program.getPosArg(0);
    const auto& arg = static_cast<std::string>(program.getPosArg(1));

    using namespace steppable::__internals;

    std::function<std::string(const std::string& x, const int decimals)> function;

    // Basic trigonometric functions
    if (command == "sinh")
        function = arithmetic::sinh;
    else if (command == "cosh")
        function = arithmetic::cosh;
    else if (command == "tanh")
        function = arithmetic::tanh;
    // Reciprocal trigonometric functions
    else if (command == "csch")
        function = arithmetic::csch;
    else if (command == "sech")
        function = arithmetic::sech;
    else if (command == "coth")
        function = arithmetic::coth;
    // Invalid command
    else
    {
        error("hyp::main", "Invalid command."s);
        return EXIT_FAILURE;
    }
    std::cout << function(arg, decimals) << '\n';
}
#endif
