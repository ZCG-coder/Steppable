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
 * @file decimalConvert.cpp
 * @brief This file contains the implementation of the decimalConvert function, which converts a number from one base to
 * decimal.
 */
#include "argParse.hpp"
#include "decimalConvertReport.hpp"
#include "fn/calc.hpp"
#include "getString.hpp"
#include "util.hpp"

#include <cctype>
#include <string>

using namespace std::literals;
using namespace steppable::__internals::numUtils;
using namespace steppable::__internals::utils;
using namespace steppable::__internals::symbols;
using namespace steppable::output;
using namespace steppable::localization;
using namespace steppable::__internals::arithmetic;

namespace steppable::__internals::arithmetic
{
    /**
     * @brief Converts a numeral character to a number string.
     *
     * @param[in] _input The character to convert.
     * @return The number string.
     */
    std::string toNumber(const char _input)
    {
        const char input = static_cast<char>(toupper(_input));
        if ('0' <= input and input <= '9')
            return { input };
        // If letters are used in counting, it should be like this:
        // 0 1 2 3 4 5 6 7 8 9 A B C D E ...
        // Where A is the 10th numeral.
        if ('A' <= input and input <= 'Z')
            return std::to_string(input - 'A' + 10);
        // Do not localize.
        throw std::runtime_error("Cannot convert "s + _input + " to Number");
    }

    std::string decimalConvert(const std::string& _inputString, const std::string& baseString, int steps)
    {
        if (compare(baseString, "36", 0) == "1")
        {
            error("decimalConvert", $("decimalConvert", "cbb9ed62-1127-4e1d-95ef-e75cc7fb2837"));
            return "Impossible";
        }

        std::string converted = "0";
        std::string inputString = _inputString;
        std::ranges::reverse(inputString);

        auto maxWidth = power(baseString, std::to_string(_inputString.length()), 0).length();

        std::stringstream ss;
        for (auto iterator = inputString.begin(); iterator < inputString.end(); ++iterator)
        {
            auto index = iterator - inputString.begin();
            auto digit = toNumber(inputString[index]);

            if (compare(digit, baseString, 0) != "0")
            {
                error("decimalConvert",
                      $("decimalConvert", "e97b6539-8f69-4ccb-a50e-82a66aff2898", { digit, baseString }));
                return "Impossible";
            }
            auto placeValue = power(baseString, std::to_string(index), 0);
            auto convertedDigit = multiply(placeValue, digit, 0);
            converted = add(converted, convertedDigit, 0);

            if (steps == 2)
                ss << reportDecimalConvertStep(baseString, digit, index, convertedDigit, maxWidth) << '\n';
        }
        ss << reportDecimalConvert(_inputString, baseString, converted, steps);
        return ss.str();
    }
} // namespace steppable::__internals::arithmetic

#ifndef NO_MAIN

int main(int _argc, const char* _argv[])
{
    [[maybe_unused]] Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', $("decimalConvert", "53053bf2-84ba-4b63-9f27-d334dc38b60d"), false);
    program.addPosArg('b', $("decimalConvert", "b771e8bc-9b66-4b4d-b9ff-fd4111111cf4"));
    program.addKeywordArg("steps", 2, $("decimalConvert", "b461a3e5-12c3-48ea-aaba-2b4e234f3234"));
    program.addSwitch("profile", false, $("decimalConvert", "d14e05b6-cb8e-43a5-9ab2-11f960f4e199"));
    program.parseArgs();

    int steps = program.getKeywordArgument("steps");
    bool profile = program.getSwitch("profile");
    const auto& inputString = program.getPosArg(0);
    const auto baseString = program.getPosArg(1);

    if (profile)
    {
        TIC(Decimal Conversion)
        std::cout << $("decimalConvert", "d1536a73-2eb9-4bf9-8b25-00ff88038dab") << "\n"
                  << decimalConvert(inputString, baseString, steps) << '\n';
        TOC()
    }
    else
        std::cout << decimalConvert(inputString, baseString, steps) << '\n';
}

#endif
