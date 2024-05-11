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
 * @file baseConvert.cpp
 * @brief This file contains the implementation of the baseConvert function, which converts any number to any base.
 * @warning Still work-in-progress.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 */

#include "argParse.hpp"
#include "baseConvertReport.hpp"
#include "fn/basicArithm.hpp"
#include "output.hpp"
#include "symbols.hpp"
#include "util.hpp"

#include <sstream>
#include <string>
#include <string_view>
#include <vector>

using namespace std::literals;
using namespace steppable::__internals::stringUtils;
using namespace steppable::__internals::arithmetic;
using namespace steppable::__internals::symbols;
using namespace steppable::output;

namespace steppable::prettyPrint::printers
{
    std::string ppSubscript(const std::string& base, const std::string& subscript)
    {
        auto subscriptWidth = prettyPrint::getStringWidth(subscript);
        auto width = prettyPrint::getStringWidth(base) + subscriptWidth + 1,
             height = prettyPrint::getStringHeight(base) + 1; // +1 for the superscript

        prettyPrint::ConsoleOutput output(height, width);
        prettyPrint::Position pos{ static_cast<long long>(width - subscriptWidth - 1), 1 };
        output.write(subscript, pos, false);
        output.write(base, { 0, 0 }, false);
        return output.asString();
    }
} // namespace steppable::prettyPrint::printers

namespace steppable::__internals::arithmetic
{
    /**
     * @brief Represents a number using alphabets and numberals.
     * @param[in] _number The number in decimal form.
     * @returns The number represented using alphabets and numberals.
     */
    std::string representNumber(const std::string_view& _number)
    {
        if (compare(_number, "10", 0) != "1")
        {
            // Do nothing, the number can be represented as is
            return static_cast<std::string>(_number);
        }
        const int number = std::stoi(static_cast<std::string>(_number));
        if (number > 10)
            throw std::invalid_argument("Number should be a single digit or a letter from A to Z");
        const unsigned char letter = 'A' + static_cast<char>(number) - 10;
        return { 1, static_cast<char>(letter) };
    }

    std::string baseConvert(const std::string_view& _number, const std::string_view& baseStr, const int steps)
    {
        const size_t base = std::stoll(static_cast<std::string>(baseStr));
        auto numberOrig = static_cast<std::string>(_number);
        auto number = static_cast<std::string>(_number);

        if (base > 36)
        {
            error("baseConvert"s, "It is impossilbe to represent a number in base greater than 36"s);
            return "Impossible";
        }
        if (base == 0 or base == 1)
        {
            error("baseConvert"s, "Conversion to base 0 or 1 is not possible"s);
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
} // namespace steppable::__internals::arithmetic

#ifndef NO_MAIN
int main(const int _argc, const char* _argv[])
{
    std::cout << steppable::prettyPrint::printers::ppSubscript("342", "32341");
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', "Number to convert");
    program.addPosArg('b', "Base of the number");
    program.addKeywordArg("steps", 2, "Amount of steps while converting. 0 = No steps, 2 = All steps.");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    const int steps = program.getKeywordArgument("steps");
    const bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(baseConvert)
        std::cout << "baseConvert :\n" << baseConvert(aStr, bStr) << '\n';
        TOC()
    }
    else
        std::cout << baseConvert(aStr, bStr, steps) << '\n';
}
#endif
