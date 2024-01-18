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

#include "divisionReport.hpp"

#include "fn/basicArithm.hpp"
#include "symbols.hpp"
#include "util.hpp"

#include <sstream>
#include <string>
#include <string_view>
#include <iomanip>

std::string reportDivision(std::stringstream& tempFormattedAns,
                           const std::string_view& temp,
                           const std::string_view& ans,
                           const std::string_view& divisor,
                           const std::string_view& number,
                           const std::string_view& _divisor,
                           const std::string_view& _number,
                           const int steps,
                           const int decimals,
                           const int width,
                           const bool resultIsNegative)
{
    std::stringstream formattedAns;

    if (steps == 2)
    {
        tempFormattedAns << std::setw(width) << std::setfill(' ') << std::right
                         << makeWider(static_cast<std::string>(temp)) << '\n';

        formattedAns << std::setw(width) << std::setfill(' ') << std::right << makeWider(static_cast<std::string>(ans))
                     << '\n';
        formattedAns << std::setw(divisor.length() * 3 - 1) << std::setfill(' ') << "";
        formattedAns << std::setw(width - divisor.length() * 2) << std::setfill('_') << "" << '\n';
        formattedAns << tempFormattedAns.rdbuf();

        formattedAns << THEREFORE " ";
    }

    if (steps >= 1)
    {
        formattedAns << _number << " " << DIVIDED_BY << " " << _divisor << " = ";
        if (resultIsNegative)
            formattedAns << '-';
        formattedAns << ans;
        return formattedAns.str();
    }
    if (resultIsNegative)
        return "-" + static_cast<std::string>(ans);
    else
        return static_cast<std::string>(ans);
}

std::string reportDivisionStep(const std::string_view& temp,
                               const std::string_view& quotient,
                               const std::string_view& divisor,
                               size_t width,
                               size_t index,
                               const std::string_view lastRemainder)
{
    std::stringstream ss;

    const auto result = subtract(temp, multiply(divisor, quotient, 0), 2, true);

    // Remove the summary line and the result
    auto splitResult = split(result, '\n');
    // splitResult.pop_back();
    // splitResult.pop_back();
    const auto normalWidth = divisor.length() + 1;

    const auto outputWidth = index == 0 ? (divisor.length() - 1) * 3 :
                                          3 * (divisor.length() + index + normalWidth - lastRemainder.length() - 2);
    for (auto i : splitResult)
        ss << std::string(outputWidth, ' ') << i << '\n';

    return ss.str();
}
