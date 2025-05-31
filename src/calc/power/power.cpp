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
 * @file power.cpp
 * @brief This file contains the implementation for the function power, which raises a number to a power.
 *
 * @author Andy Zhang
 * @date 8rd November 2023
 */
#include "argParse.hpp"
#include "constants.hpp"
#include "fn/calc.hpp"
#include "steppable/fraction.hpp"
#include "getString.hpp"
#include "powerReport.hpp"
#include "rounding.hpp"
#include "symbols.hpp"
#include "util.hpp"

using namespace steppable::__internals::numUtils;
using namespace steppable::output;
using namespace steppable::localization;
using namespace steppable::__internals::calc;

namespace steppable::prettyPrint::printers
{
    std::string ppSuperscript(const std::string& base, const std::string& superscript)
    {
        auto width = prettyPrint::getStringWidth(base) + 1;
        auto height = prettyPrint::getStringHeight(base) + 1; // +1 for the superscript

        prettyPrint::ConsoleOutput output(height, width);
        prettyPrint::Position pos{ .x = static_cast<long long>(width - 1), .y = 0 };
        output.write(superscript, pos, false);
        output.write(base, { .x = 0, .y = 1 }, false);
        return output.asString();
    }
} // namespace steppable::prettyPrint::printers

namespace steppable::__internals::calc
{
    std::string power(const std::string& _number, const std::string& _raiseTo, const int steps, const int decimals)
    {
        std::string raiseTo = static_cast<std::string>(_raiseTo);
        std::string number = static_cast<std::string>(_number);

        if (isDecimal(raiseTo))
        {
            // Raising to decimal power.
            //  b    b ln(a)
            // a  = e
            const auto lnNumber = ln(_number, decimals + 2);
            const auto bLnNumber = multiply(lnNumber, raiseTo, 0, decimals + 2);
            // return reportPowerRoot(number, raiseTo, fraction, rootResult, steps);
            return exp(bLnNumber, decimals);
        }

        // Here, we attempt to give a quick answer, instead of doing pointless iterations.
        if (number == "1")
        {
            if (steps == 2)
                return $("power", "7c866c46-d67e-4c1e-8fd5-b3bfa07d005d");
            if (steps == 1)
                return "1"s + symbols::makeSuperscript(raiseTo) + " = 1";
            return "1";
        }
        if (number == "0")
        {
            if (steps == 2)
                return $("power", "261e4299-0132-4ab5-a37d-aa376efbdd5f");
            if (steps == 1)
                return "0"s + symbols::makeSuperscript(raiseTo) + " = 0";
            return "0";
        }

        auto numberNoTrailingZeros = standardizeNumber(number);
        size_t numberTrailingZeros = 0;
        auto result = splitNumber(number, "0", false, false, true, true);
        if (isInteger(number))
        {
            number = result.splitNumberArray[0];
            numberNoTrailingZeros = removeTrailingZeros(number);
            numberTrailingZeros = number.length() - numberNoTrailingZeros.length();
        }
        else
            numberTrailingZeros = 0;
        // Remove the zeros to reduce the workload.
        number = numberNoTrailingZeros;

        bool negativePower = false;

        if (compare(raiseTo, "0", 0) == "0")
        {
            // raiseTo is negative
            raiseTo = raiseTo.substr(1);
            negativePower = true;
        }
        return reportPower(number, raiseTo, numberTrailingZeros, negativePower, steps, decimals);
    }

    std::string _exp(const std::string& x, const size_t decimals) // NOLINT(*-no-recursion)
    {
        if (compare(x, "4", 0) == "1")
        {
            std::string halfX = divide(x, "2", 0, static_cast<int>(decimals) + 2);
            std::string result = _exp(halfX, decimals + 2);
            return multiply(result, result, 0, static_cast<int>(decimals + 2));
        }

        std::string sum = "1";
        std::string term = "1";
        const auto errorStr = "0." + std::string(decimals + 1, '0') + "1";
        for (int i = 1;; i++)
        {
            std::string frac = divide(x, std::to_string(i), 0, static_cast<int>(decimals) + 2);
            term = multiply(term, frac, 0, static_cast<int>(decimals) + 2);
            if (compare(term, errorStr, 0) != "1")
                break;

            sum = add(sum, term, 0);
        }
        return roundOff(sum, decimals);
    }

    std::string exp(const std::string& x, const size_t decimals)
    {
        const auto result = _exp(x, decimals + 2);
        return roundOff(result, decimals);
    }
} // namespace steppable::__internals::calc

#ifndef NO_MAIN
int main(const int _argc, const char* _argv[])
{
    Utf8CodePage();
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', $("power", "4252ac37-a36b-4605-9ec1-d69e70b91b46"));
    program.addPosArg('b', $("power", "1fefffaf-7731-430b-989f-42e74017a2eb"));
    program.addKeywordArg("steps", 2, $("power", "cb935566-6125-49ce-9ebc-e157410a3005"));
    program.addKeywordArg("decimals", 2, $("power", "03c15572-a5aa-4b1c-a705-105770999741"));
    program.addSwitch("profile", false, $("power", "e5d48237-e161-494d-940b-e2457411fcfb"));
    program.parseArgs();

    int steps = program.getKeywordArgument("steps");
    int decimals = program.getKeywordArgument("decimals");
    bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    #if DEBUG
    if (steps == 475)
    {
        std::cout << steppable::__internals::calc::exp(aStr, decimals) << '\n';
        return 0;
    }
    #endif

    if (profile)
    {
        TIC(Power)
        std::cout << $("power", "2a9fd067-59a3-4a65-b1a6-2ca479e0f1a1") << "\n" << power(aStr, bStr, steps) << '\n';
        TOC()
    }
    else
        std::cout << power(aStr, bStr, steps) << '\n';
}
#endif
