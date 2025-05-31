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
 * @file powerReport.cpp
 * @brief This file contains the implementation for the function reportPower, which reports the result of raising a
 * number to a power to the user.
 *
 * @author Andy Zhang
 * @date 8rd November 2023
 */

#include "powerReport.hpp"

#include "fn/calc.hpp"
#include "steppable/fraction.hpp"
#include "getString.hpp"
#include "rounding.hpp"
#include "symbols.hpp"
#include "util.hpp"

#include <sstream>

using namespace std::literals;
using namespace steppable::output;
using namespace steppable::localization;
using namespace steppable::prettyPrint;
using namespace steppable::__internals::symbols;
using namespace steppable::__internals::calc;

std::string reportPowerRoot(const std::string& _number,
                            const std::string& raiseTo,
                            const steppable::Fraction& fraction,
                            const std::string& result,
                            const int steps)
{
    auto array = fraction.asArray();
    std::stringstream ss;

    if (steps == 2)
        // The exponent is a decimal, so the result is a root.
        ss << $("power", "7b3b39ff-c3fa-4998-b9e2-8989fb6846f9", { raiseTo }) << '\n';
    if (steps >= 1)
    {
        ss << _number << makeSuperscript(static_cast<std::string>(raiseTo));
        ss << " = " << makeSuperscript(array[1]) << makeSurd(_number + makeSuperscript(array[0])) << " = ";
    }
    ss << result;
    return ss.str();
}

std::string reportPower(const std::string& _number,
                        const std::string& raiseTo,
                        const size_t numberTrailingZeros,
                        const bool negativePower,
                        const int steps,
                        const int decimals)
{
    std::stringstream ss;
    auto result = "1"s;

    // Here, we attempt to give a quick answer, instead of doing pointless iterations.
    if (_number == "1")
        goto finish; // NOLINT(cppcoreguidelines-avoid-goto)
    if (_number == "0")
    {
        if (steps == 2)
            // The number is 0, so the result is 0.
            return $("power", "261e4299-0132-4ab5-a37d-aa376efbdd5f");
        if (steps == 1)
            return printers::ppSuperscript("0", static_cast<std::string>(raiseTo)) + " = 0";
        return "0";
    }

    loop(raiseTo, [&](const auto& i) {
        if (not negativePower)
            result = multiply(result, _number, 0, decimals + 1);
        else
            result = divide("1", result, 0, decimals + 1);
        auto currentPower = add(i, "1", 0);
        if (steps == 2)
        {
            if (not negativePower)
                ss << BECAUSE << " " << multiply(result, _number, 1) << '\n';
            else
                ss << BECAUSE << " " << divide("1", result, 1) << '\n';
            if (negativePower)
                currentPower = "-" + currentPower;

            ss << printers::ppSuperscript(_number, currentPower) << " = " << result << '\n';
        }
    });

finish:
    result = numUtils::standardizeNumber(result);
    result = numUtils::roundOff(result, decimals);

    if (negativePower)
    {
        if (steps == 2)
            ss << BECAUSE << " " << divide("1", result, 1, decimals) << '\n';
        else if (steps == 1)
        {
            const auto& divisionResult = divide("1", result, 0, decimals);
            ss << _number << makeSuperscript('-') << makeSuperscript(static_cast<std::string>(raiseTo)) << " = "
               << divisionResult;
        }
        else
            ss << result;
    }

    if (steps >= 1)
        ss << _number << makeSuperscript(raiseTo) << " = " << result;
    else if (steps == 0)
        ss << result;

    loop(multiply(raiseTo, std::to_string(numberTrailingZeros), 0, 0), [&](const auto& _) { ss << "0"; });

    return ss.str();
}
