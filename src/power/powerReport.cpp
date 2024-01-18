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

#include "powerReport.hpp"

#include "fn/basicArithm.hpp"
#include "symbols.hpp"

#include <sstream>

std::string reportPower(const std::string_view _number, const std::string_view& raiseTo, const int steps)
{
    std::stringstream ss;
    const auto numberOrig = static_cast<std::string>(_number);
    auto number = static_cast<std::string>("1");

    loop(raiseTo, [&](const auto& i) {
        number = multiply(number, numberOrig, 0);
        const auto& currentPower = add(i, "1", 0);
        if (steps == 2)
        {
            ss << BECAUSE " " << multiply(number, numberOrig, 1) << '\n';
            ss << THEREFORE " " << numberOrig << makeSuperscript(currentPower) << " = " << number << '\n';
        }
    });

    if (steps == 1)
        ss << numberOrig << makeSuperscript(static_cast<std::string>(raiseTo)) << " = " << number;
    else if (steps == 0)
        ss << number;

    return ss.str();
}
