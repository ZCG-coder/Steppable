/**************************************************************************************************
 * Copyright (c) 2023 NWSOFT                                                                      *
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

#include "divisionReport.hpp"
#include "fn/basicArithm.hpp"
#include "util.hpp"

#include <iostream>
#include <sstream>
#include <string>

auto getQuotient(const auto& _temp, const auto& _divisor)
{
    auto temp = _temp, divisior = _divisor;
    if (compare(temp, divisior, 0) == "0")
        return std::string("0");
    if (compare(temp, divisior, 0) == "2")
        return std::string("1"); // Equal

    int out = 0;
    while (compare(temp, divisior, 0) == "1" or compare(temp, divisior, 0) == "2")
    {
        out++;
        temp = subtract(temp, divisior, 0);
    }

    return std::to_string(out);
}

inline auto getRemainder(const auto& quotient, const auto& temp, const auto& divisor)
{
    return subtract(temp, multiply(quotient, divisor, 0), 0);
}

std::string divide(const std::string& number, const std::string& divisor, int steps = 2)
{
    std::string ans;
    std::stringstream formattedAns;

    int idx = 0;
    std::string temp(1, number[idx]);
    formattedAns << makeWider(divisor) << ") " << makeWider(number) << std::endl;
    while (compare(temp, divisor, 0) == "0")
        temp += number[++idx];
    while (number.length() > idx)
    {
        auto quotient = getQuotient(temp, divisor);
        ans += quotient;
        formattedAns << reportDivisionStep(temp, quotient, divisor) << std::endl;
        temp = getRemainder(quotient, temp, divisor);
        if (number.length() - 1 > ++idx)
            temp += number[idx];
    }
    if (ans.length() == 0)
        return "0";

    return formattedAns.str();
}

int main()
{
    std::cout << divide("102022", "44") << std::endl;
    return 0;
}
