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
 * @file comparison.cpp
 * @brief This file contains the implementation of the compare function, which compares two numbers.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 */
#include "argParse.hpp"
#include "comparisonReport.hpp"
#include "fn/calc.hpp"
#include "getString.hpp"
#include "steppable/number.hpp"
#include "types/result.hpp"
#include "util.hpp"

#include <sstream>
#include <string>

using namespace steppable::__internals::numUtils;
using namespace steppable::__internals::symbols;
using namespace steppable::__internals::utils;
using namespace steppable::__internals::calc;
using namespace steppable::localization;

namespace steppable::__internals::calc
{
    std::string compare(const std::string& _a, const std::string& _b, const int steps)
    {
        if (standardizeNumber(_a) == standardizeNumber(_b))
        {
            std::stringstream ss;
            if (steps == 2)
            {
                ss << BECAUSE << $("comparison", "bd4f865a-ce08-4825-ac74-f824e4da2fed", { _a, _b }) << THEREFORE
                   << " a = b";
                return ss.str();
            }
            if (steps == 1)
                return _a + " = " + _b;
            return "2";
        }
        const auto [splitNumberArray, aIsNegative, bIsNegative] = splitNumber(_a, _b, false, true);
        const auto result = splitNumberArray;
        const bool bothNegative = aIsNegative and bIsNegative;
        auto [aIntegerReal, aDecimalReal, bIntegerReal, bDecimalReal] = result;
        if (aIntegerReal.empty())
            aIntegerReal = "0";
        if (bIntegerReal.empty())
            bIntegerReal = "0";

        auto a = aIntegerReal + "." + aDecimalReal;
        auto b = bIntegerReal + "." + bDecimalReal;
        if (
            // a is longer than b and is of different polarities
            aIntegerReal.length() != bIntegerReal.length() and aIsNegative == bIsNegative)
        {
            if (bothNegative)
                return reportComparisonAtInteger(a, b, aIntegerReal.length() < bIntegerReal.length(), steps);
            return reportComparisonAtInteger(a, b, aIntegerReal.length() > bIntegerReal.length(), steps);
        }

        // Here, we try to determine whether a or b is greater based on their polarities
        // Scenario 1: a and b are both positive
        // Action    : Continue, cannot determine
        //
        // Scenario 2: a and b are both negative
        // Action    : Continue, cannot determine
        //
        // Scenario 3: a is positive and b is negative
        // Action    : Return a > b
        //
        // Scenario 4: a is negative and b is positive
        // Action    : Return a < b
        if (not aIsNegative and bIsNegative)
            return reportComparisonByPolarity(a, b, true, steps);
        if (aIsNegative and not bIsNegative)
            return reportComparisonByPolarity(a, b, false, steps);

        for (long i = 0; static_cast<size_t>(i) < a.length(); i++)
        {
            if (a[i] == b[i] or (isdigit(a[i]) == 0) or (isdigit(b[i]) == 0))
                continue; // Negative sign, decimal point or equals
            if (a[i] > b[i] and not bothNegative)
                return reportComparisonByDigit(a, b, i, true, false, steps);
            if (a[i] < b[i] and not bothNegative)
                return reportComparisonByDigit(a, b, i, false, false, steps);
            if (a[i] > b[i] and bothNegative) // First digit is the negative sign
                return reportComparisonByDigit(a, b, i - 1, false, false, steps);
            if (a[i] < b[i] and bothNegative)
                return reportComparisonByDigit(a, b, i - 1, true, false, steps);
        }

        if (steps == 1)
            return $("comparison", "c49d968f-31df-4654-b13b-0f16212f4591");
        if (steps == 2)
        {
            std::stringstream ss;
            ss << a << " = " << b;
            return ss.str();
        }
        return "2";
    }
} // namespace steppable::__internals::calc

#ifndef NO_MAIN
int main(int _argc, const char** _argv)
{
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', $("comparison", "1d411edd-f7a6-4ad5-8a0a-cc8b5eea01b1"));
    program.addPosArg('b', $("comparison", "0972be2d-ce73-4226-82d8-778fb5293894"));
    program.addKeywordArg("steps", 2, $("comparison", "07ff2704-10c1-4eea-bba2-bd63116ca34b"));
    program.addSwitch("profile", false, $("comparison", "b930c709-22e7-46f8-9cdf-5ed193469964"));
    program.parseArgs();

    int steps = program.getKeywordArgument("steps");
    bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(Comparing...)
        std::cout << compare(aStr, bStr, steps) << '\n';
        TOC()
    }
    else
        std::cout << compare(aStr, bStr, steps) << '\n';
}
#endif
