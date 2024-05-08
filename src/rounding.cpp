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

#include "rounding.hpp"

#include "fn/basicArithm.hpp"
#include "util.hpp"

#include <string>

namespace steppable::__internals::numUtils
{
    std::string roundOff(const std::string& _number)
    {
        auto number = _number;
        if (number.empty())
            return "0";
        if (number.find('.') == std::string::npos)
            return number;
        auto splitNumberResult = splitNumber(number, "0", false, false, true).splitNumberArray;
        auto integer = splitNumberResult[0], decimal = splitNumberResult[1];

        if (arithmetic::compare(decimal, "5", 0) != "1")
            return integer + "." + decimal;
        return arithmetic::add(integer, "1", 0) + "." + decimal;
    }

    std::string moveDecimalPlaces(const std::string& _number, const long places)
    {
        auto number = _number;
        // No change
        if (not places)
            return number;

        // Is the number an integer?
        if (isInteger(number))
            number += ".0";
        auto splitNumberResult = splitNumber(number, "0", false, false, true, false).splitNumberArray;
        auto integer = splitNumberResult[0], decimal = splitNumberResult[1];
        auto repetitions = std::abs(places);

        // Move decimal places to the right
        if (places > 0)
        {
            for (size_t _ = 0; _ < repetitions; _++)
                if (decimal.length() > 0)
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
                if (integer.length() > 0)
                {
                    decimal = integer.back() + decimal;
                    integer.pop_back();
                }
                else
                    decimal = '0' + decimal;
        }

        auto result = integer + "." + decimal;
        return standardizeNumber(result);
    }
} // namespace steppable::__internals::numUtils
