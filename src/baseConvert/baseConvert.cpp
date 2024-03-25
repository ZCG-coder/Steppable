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

#include "baseConvertReport.hpp"
#include "fn/basicArithm.hpp"
#include "output.hpp"
#include "util.hpp"

#include <string>
#include <vector>

using namespace std::literals;

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

std::string baseConvert(const std::string& inputStr, const std::string& baseStr, const int steps = 2)
{
    const int base = std::stoi(baseStr);
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
    std::string number = inputStr;
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
            std::cout << reportBaseConvertStep(number, baseStr, quotient, representNumber(remainder)) << '\n';

        number = quotient;
        digits.push_back(remainder);
    }
    return join(digits, "");
}

int main() { baseConvert("10", "2"); }
