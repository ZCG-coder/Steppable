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

#include "rounding.hpp"

#include "fn/calc.hpp"
#include "util.hpp"

#include <string>

namespace steppable::__internals::numUtils
{
    std::string roundDown(const std::string& _number)
    {
        auto number = _number;
        if (number.empty())
            return "0";
        if (number.find('.') == std::string::npos)
            return number;
        // Round down the number
        auto splitNumberResult = splitNumber(number, "0", false, false, false, false).splitNumberArray;
        return splitNumberResult[0]; // Return the integer part
    }

    std::string roundUp(const std::string& _number)
    {
        auto number = _number;
        if (number.empty())
            return "0";
        if (number.find('.') == std::string::npos)
            return number;
        // Round up the number
        auto splitNumberResult = splitNumber(number, "0", false, true, true, false).splitNumberArray;
        auto integer = splitNumberResult[0];
        const auto& decimal = splitNumberResult[1]; // Return the integer part
        if (decimal.front() > '5')
            integer = calc::add(integer, "1", 0);
        return integer;
    }

    std::string roundOff(const std::string& _number, const size_t digits, Rounding mode)
    {
        auto number = _number;
        if (number.empty())
            return "0";
        if (number.find('.') == std::string::npos)
            return number;
        auto splitNumberResult = splitNumber(number, "0", true, true, false, false);

        // Round off the number
        auto splitNumberArray = splitNumberResult.splitNumberArray;
        auto integer = splitNumberArray[0];
        auto decimal = splitNumberArray[1];
        bool isNegative = splitNumberResult.aIsNegative;

        if (decimal.length() < digits)
            return _number;

        // Preserve one digit after the rounded digit
        decimal = decimal.substr(0, digits + 1);
        // Modify the integer part if the digit is greater than 5
        if (decimal.front() >= '5' and digits == 0)
        {
            integer = calc::add(integer, "1", 0);
            return integer;
        }
        auto newDecimal = decimal.substr(0, digits);
        std::ranges::reverse(newDecimal.begin(), newDecimal.end());
        bool condition = false;
        switch (mode)
        {
        case Rounding::ROUND_OFF:
            condition = decimal.back() >= '5';
            break;
        case Rounding::ROUND_DOWN:
            condition = false;
            break;
        case Rounding::ROUND_UP:
            condition = true;
        default:
            break;
        }

        if (condition)
        {
            // Need to round up the digit
            for (size_t i = 0; i < newDecimal.length(); i++)
            {
                if (newDecimal[i] == '.')
                    continue;
                if (newDecimal[i] == '9')
                {
                    newDecimal[i] = '0';
                    if (i == newDecimal.length() - 1)
                        integer = calc::add(integer, "1", 0);
                }
                else
                {
                    newDecimal[i]++;
                    break;
                }
            }
        }
        std::ranges::reverse(newDecimal.begin(), newDecimal.end());

        std::string result;
        decimal = newDecimal.substr(0, digits);
        if (isNegative)
            integer = '-' + integer;
        else if (decimal.empty() and digits > 0)
            result = integer + "." + std::string(digits, '0');
        else if (decimal.empty())
            result = integer;
        else
            result = integer + "." + decimal;

        result = simplifyPolarity(result);
        return result;
    }

    std::string moveDecimalPlaces(const std::string& _number, const long places)
    {
        auto number = _number;
        // No change
        if (places == 0)
            return number;

        // Is the number an integer?
        if (isInteger(number))
            number += ".0";
        auto splitNumberResult = splitNumber(number, "0", false, false, true, false);
        auto splitNumberArray = splitNumberResult.splitNumberArray;
        auto integer = splitNumberArray[0];
        auto decimal = splitNumberArray[1];
        auto repetitions = std::abs(places);

        // Move decimal places to the right
        if (places > 0)
        {
            for (size_t _ = 0; _ < repetitions; _++)
                if (not decimal.empty())
                {
                    integer += decimal[0];
                    decimal.erase(decimal.cbegin());
                }
                else
                    integer += '0';
        }
        // Move decimal places to the left
        else if (places < 0)
        {
            for (size_t _ = 0; _ < repetitions; _++)
                if (not integer.empty())
                {
                    decimal = integer.back() + decimal; // NOLINT(performance-inefficient-string-concatenation)
                    integer.pop_back();
                }
                else
                    decimal = '0' + decimal; // NOLINT(performance-inefficient-string-concatenation)
        }

        auto result = integer + "." + decimal;
        return standardizeNumber(removeLeadingZeros(result));
    }
} // namespace steppable::__internals::numUtils
