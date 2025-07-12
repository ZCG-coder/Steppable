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
 * @file baseConvert.cpp
 * @brief This file contains the implementation of the baseConvert function, which converts any number to any base.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 */

#include "argParse.hpp"
#include "baseConvertReport.hpp"
#include "fn/calc.hpp"
#include "getString.hpp"
#include "output.hpp"
#include "symbols.hpp"
#include "util.hpp"

#include <string>
#include <vector>

using namespace std::literals;
using namespace steppable::__internals::stringUtils;
using namespace steppable::__internals::calc;
using namespace steppable::__internals::symbols;
using namespace steppable::localization;
using namespace steppable::output;

namespace steppable::prettyPrint::printers
{
    std::string ppSubscript(const std::string& base, const std::string& subscript)
    {
        auto subscriptWidth = prettyPrint::getStringWidth(subscript);
        auto width = prettyPrint::getStringWidth(base) + subscriptWidth + 1;
        auto height = prettyPrint::getStringHeight(base) + 1; // +1 for the superscript

        prettyPrint::ConsoleOutput output(height, width);
        prettyPrint::Position pos{ .x = static_cast<long long>(width - subscriptWidth - 1), .y = 1 };
        output.write(subscript, pos, false);
        output.write(base, { .x = 0, .y = 0 }, false);
        return output.asString();
    }
} // namespace steppable::prettyPrint::printers

namespace steppable::__internals::calc
{
    /**
     * @brief Represents a number using alphabets and numberals.
     * @param[in] _number The number in decimal form.
     * @returns The number represented using alphabets and numberals.
     */
    std::string representNumber(const std::string& _number)
    {
        if (compare(_number, "10", 0) != "1")
        {
            // Do nothing, the number can be represented as is
            return static_cast<std::string>(_number);
        }
        const int number = std::stoi(static_cast<std::string>(_number));
        if (number > 10)
            // Do not localize.
            throw std::invalid_argument("Number should be a single digit or a letter from A to Z");
        const unsigned char letter = 'A' + static_cast<char>(number) - 10;
        return { 1, static_cast<char>(letter) };
    }

    std::string baseConvert(const std::string& _number, const std::string& baseStr, const int steps)
    {
        const size_t base = std::stoll(baseStr);
        auto numberOrig = static_cast<std::string>(_number);
        auto number = static_cast<std::string>(_number);

        if (base > 36)
        {
            // It is impossible to convert to a base greater than 36.
            error("baseConvert"s, $("base::baseConvert", "4e5a4863-4e4a-44f1-a782-e74de6b93469"));
            return "Impossible";
        }
        if (base == 0 or base == 1)
        {
            // It is impossible to convert to a base of 0 or 1.
            error("baseConvert"s, $("base::baseConvert", "783e7915-f4a3-4973-9747-2d8de3de5545"));
            return "Impossible";
        }

        std::vector<std::string> digits;
        while (compare(number, "0", 0) != "2")
        {
            auto quotient = divide(number, baseStr, 0);
            quotient = split(quotient, '.')[0];
            auto remainder = subtract(number, multiply(quotient, baseStr, 0), 0);
            if (compare(remainder, "0", 0) == "0")
            {
                remainder = subtract(remainder, baseStr, 0);
                quotient = add(quotient, "1", 0);
            }

            if (steps == 2)
                std::cout << reportBaseConvertStep(
                                 number, static_cast<std::string>(baseStr), quotient, representNumber(remainder))
                          << '\n';

            number = quotient;
            digits.push_back(remainder);
        }

        return reportBaseConvert(numberOrig, static_cast<std::string>(baseStr), digits, steps);
    }
} // namespace steppable::__internals::calc

#ifndef NO_MAIN
int main(const int _argc, const char* _argv[])
{
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', $("base::baseConvert", "f3211410-9b0d-49f6-8797-c4756b2fee28"));
    program.addPosArg('b', $("base::baseConvert", "61826029-8d77-4133-8bc7-7f03365bd9a3"));
    program.addKeywordArg("steps", 2, $("base::baseConvert", "f988a0b2-decd-4d0c-a2e2-dd4127c1e83b"));
    program.addSwitch("profile", false, $("base::baseConvert", "0826ae41-c7f6-4e1f-a932-2f6c00930a05"));
    program.parseArgs();

    const int steps = program.getKeywordArgument("steps");
    const bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(baseConvert)
        std::cout << $("base::baseConvert", "74dd79f5-7c24-4b39-bf66-59a3570e4a03") << "\n"
                  << baseConvert(aStr, bStr) << '\n';
        TOC()
    }
    else
        std::cout << baseConvert(aStr, bStr, steps) << '\n';
}
#endif
