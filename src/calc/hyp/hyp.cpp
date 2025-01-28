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
 * @file hyp.cpp
 * @brief Hyperbolic trigonometric functions.
 *
 * @author Andy Zhang
 * @date 20th June 2024
 */

#include "argParse.hpp"
#include "constants.hpp"
#include "fn/calc.hpp"
#include "getString.hpp"
#include "hypReport.hpp"
#include "output.hpp"
#include "rounding.hpp"
#include "util.hpp"

#include <functional>
#include <iostream>
#include <string>

using namespace std::literals;
using namespace steppable::output;
using namespace steppable::localization;
using namespace steppable::__internals::utils;
using namespace steppable::__internals::numUtils;

namespace steppable::__internals::calc
{
    std::string sinh(const std::string& x, const int decimals)
    {
        checkDecimalArg(&decimals);

        const auto& twoX = multiply(x, "2", 0);
        const auto& eTwoX = roundOff(power(static_cast<std::string>(constants::E), twoX, 0), decimals + 2);
        const auto& eX = roundOff(power(static_cast<std::string>(constants::E), x, 0), decimals + 2);

        const auto& numerator = subtract(eTwoX, "1", 0);
        const auto& denominator = multiply("2", eX, 0);

        return divide(numerator, denominator, 0, decimals);
    }

    std::string cosh(const std::string& x, const int decimals)
    {
        checkDecimalArg(&decimals);

        const auto& twoX = multiply(x, "2", 0);
        const auto& eTwoX = roundOff(power(static_cast<std::string>(constants::E), twoX, 0), decimals + 2);
        const auto& eX = roundOff(power(static_cast<std::string>(constants::E), x, 0), decimals + 2);

        const auto& numerator = add(eTwoX, "1", 0);
        const auto& denominator = multiply("2", eX, 0);

        return divide(numerator, denominator, 0, decimals);
    }

    std::string tanh(const std::string& x, const int decimals)
    {
        checkDecimalArg(&decimals);

        const auto& numerator = sinh(x, decimals);
        const auto& denominator = cosh(x, decimals);

        return divide(numerator, denominator, 0, decimals);
    }

    std::string coth(const std::string& x, const int decimals)
    {
        checkDecimalArg(&decimals);

        const auto& denominator = tanh(x, decimals);
        if (isZeroString(denominator))
        {
            error("hyp::coth"s, $("hyp", "e1f6e8db-64cd-4882-b5b2-ddd1c79c1e57"));
            return "Infinity";
        }

        return divide("1", denominator, 0, decimals);
    }

    std::string csch(const std::string& x, const int decimals)
    {
        checkDecimalArg(&decimals);

        const auto& denominator = sinh(x, decimals);
        if (isZeroString(denominator))
        {
            error("hyp::csch"s, $("hyp", "30735b1c-5f92-4d2a-ab4a-056dd0f03c9b"));
            return "Infinity";
        }

        return divide("1", denominator, 0, decimals);
    }

    std::string sech(const std::string& x, const int decimals)
    {
        checkDecimalArg(&decimals);

        const auto& denominator = cosh(x, decimals);
        if (isZeroString(denominator))
        {
            error("hyp::sech"s, $("hyp", "1f091fa2-47c1-4432-8951-c7db1dff0995"));
            return "Infinity";
        }

        return divide("1", denominator, 0, decimals);
    }

    std::string asinh(const std::string& x, const int decimals)
    {
        checkDecimalArg(&decimals);

        //                      /------|
        //                     / 2
        // asinh(x) = ln(x + \/ x  + 1  )

        const auto& x2 = power(x, "2", 0);
        const auto& radicand = add(x2, "1", 0);
        const auto& rootResult = root(radicand, "2", decimals);
        const auto& result = add(x, rootResult, 0);
        return ln(result, decimals);
    }

    std::string acosh(const std::string& x, const int decimals)
    {
        checkDecimalArg(&decimals);

        //                      /------|
        //                     / 2
        // acosh(x) = ln(x + \/ x  - 1  )

        const auto& x2 = power(x, "2", 0);
        const auto& radicand = subtract(x2, "1", 0);
        const auto& rootResult = root(radicand, "2", decimals);
        const auto& result = add(x, rootResult, 0);
        return ln(result, decimals);
    }

    std::string atanh(const std::string& x, const int decimals)
    {
        checkDecimalArg(&decimals);

        //             1         1 + x
        // atanh(x) = --- * ln( ------- )
        //             2         1 - x

        const auto& numerator = add("1", x, 0);
        const auto& denominator = subtract("1", x, 0);
        auto result = divide(numerator, denominator, 0, decimals + 2);
        result = ln(result, decimals + 2);
        return divide(result, "2", 0, decimals);
    }

    std::string acoth(const std::string& x, const int decimals)
    {
        checkDecimalArg(&decimals);

        //             1          1 + x
        // acoth(x) = ---  * ln( ------- )
        //             2          x - 1

        const auto& numerator = add("1", x, 0);
        const auto& denominator = subtract(x, "1", 0);
        auto result = divide(numerator, denominator, 0, decimals);
        result = ln(result, decimals);
        return divide(result, "2", 0, decimals);
    }

    std::string acsch(const std::string& x, const int decimals)
    {
        checkDecimalArg(&decimals);

        //                         /-------|
        //                1       / 1
        // acsch(x) = ln(--- +   / ---- + 1  )
        //                x     /    2
        //                    \/    x

        const auto& x2 = power(x, "2", 0);
        const auto& oneOverX = divide("1", x, 0, decimals);
        const auto& oneOverX2 = divide("1", x2, 0, decimals);

        const auto& radicand = add(oneOverX2, "1", 0);
        const auto& rootResult = root(radicand, "2", decimals);
        const auto& lnArg = add(oneOverX, rootResult, 0);
        return ln(lnArg, decimals);
    }

    std::string asech(const std::string& x, const int decimals)
    {
        checkDecimalArg(&decimals);

        //                         /-------|
        //                1       / 1
        // asech(x) = ln(--- +   / ---- - 1  )
        //                x     /    2
        //                    \/    x

        const auto& x2 = power(x, "2", 0);
        const auto& oneOverX = divide("1", x, 0, decimals);
        const auto& oneOverX2 = divide("1", x2, 0, decimals);

        const auto& radicand = subtract(oneOverX2, "1", 0);
        const auto& rootResult = root(radicand, "2", decimals);
        const auto& lnArg = add(oneOverX, rootResult, 0);
        return ln(lnArg, decimals);
    }

} // namespace steppable::__internals::calc

#ifndef NO_MAIN
int main(int _argc, const char* _argv[])
{
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('c', $("hyp", "4c28b4d6-3002-458a-88bd-9d7c03b9b614"), false);
    program.addPosArg('n', $("hyp", "1d369138-f330-42b2-9aa9-40ab5f7f3df8"), false);
    program.addKeywordArg("decimals", 5, $("hyp", "92717527-91df-4fa8-905c-cde0525612af"));
    program.addSwitch("profile", false, $("hyp", "ba4083c0-788f-4f3c-9748-df0cf7b7b41c"));
    program.parseArgs();

    const bool profile = program.getSwitch("profile");
    const int decimals = program.getKeywordArgument("decimals");
    const auto& command = program.getPosArg(0);
    const auto& arg = static_cast<std::string>(program.getPosArg(1));

    using namespace steppable::__internals;

    std::function<std::string(const std::string& x, const int decimals)> function;

    // Basic trigonometric functions
    if (command == "sinh")
        function = calc::sinh;
    else if (command == "cosh")
        function = calc::cosh;
    else if (command == "tanh")
        function = calc::tanh;
    // Reciprocal trigonometric functions
    else if (command == "csch")
        function = calc::csch;
    else if (command == "sech")
        function = calc::sech;
    else if (command == "coth")
        function = calc::coth;
    // Inverse trigonometric functions
    else if (command == "asinh")
        function = calc::asinh;
    else if (command == "acosh")
        function = calc::acosh;
    else if (command == "atanh")
        function = calc::atanh;
    else if (command == "acsch")
        function = calc::acsch;
    else if (command == "acoth")
        function = calc::acoth;
    else if (command == "asech")
        function = calc::asech;
    // Invalid command
    else
    {
        error("hyp::main", $("hyp", "b2f5e0cd-3c21-4fb6-8964-7b411c27785a"));
        return EXIT_FAILURE;
    }
    std::cout << function(arg, decimals) << '\n';
}
#endif
