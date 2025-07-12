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
 * @file log.cpp
 * @brief Contains the implementation of the logarithmic functions.
 *
 * @author Andy Zhang
 * @date 23rd June 2024
 */

#include "argParse.hpp"
#include "fn/calc.hpp"
#include "getString.hpp"
#include "output.hpp"
#include "rounding.hpp"
#include "util.hpp"

#include <cstdlib>
#include <string>

using namespace steppable::__internals::calc;
using namespace steppable::__internals::utils;
using namespace steppable::localization;
using namespace std::literals;

namespace steppable::__internals::calc
{
    std::string _log(const std::string& x, const size_t _decimals)
    {
        checkDecimalArg(&_decimals);

        const auto& decimals = _decimals + 2;
        // Zero check
        if (numUtils::isZeroString(x))
        {
            output::error("log::_log"s, "The number cannot be zero."s);
            return "-Infinity";
        }
        if (compare(x, "1", 0) == "2")
            return "0";

        // ROUND 1 -- Padé approximant
        //                                          2
        //          3 * (x + 1) * (x - 1)     3 * (x  - 1)
        // ln(x) = ----------------------- = --------------
        //               2                     2
        //              x  + 4x + 1           x  + 4x + 1
        const auto& x2 = multiply(x, x, 0, static_cast<int>(decimals) + 2);
        const auto& x2Minus1 = subtract(x2, "1", 0);
        const auto& numerator = multiply("3", x2Minus1, 0, static_cast<int>(decimals) + 2);
        const auto& fourX = multiply(x, "4", 0, static_cast<int>(decimals) + 2);

        auto denominator = add(x2, fourX, 0);
        denominator = add(denominator, "1", 0);

        // ROUND 2 -- Newton's Method
        //                    x - exp(y )
        //                             n
        // y      = y  + 2 * --------------
        //  n + 1    n        x + exp(y )
        //                             n

        // ln(x) = y
        //          n + 1

        const auto& epsilon = "0." + std::string(_decimals + 1, '0') + "1";
        auto yn = divide(numerator, denominator, 0, static_cast<int>(decimals) + 2);
        auto yn1 = yn;

        auto error = abs(subtract(yn, yn1, 0), 0);
        do // NOLINT(cppcoreguidelines-avoid-do-while)
        {
            yn = yn1;
            auto expYN = exp(yn, decimals);
            auto xMinusExpYN = subtract(x, expYN, 0);
            auto xPlusExpYN = add(x, expYN, 0);
            auto fraction = divide(xMinusExpYN, xPlusExpYN, 0, static_cast<int>(decimals));
            auto twoXFraction = multiply(fraction, "2", 0, static_cast<int>(decimals));
            yn1 = add(yn, twoXFraction, 0);
            error = abs(subtract(yn, yn1, 0), 0);
        } while (compare(error, epsilon, 0) == "1");

        return numUtils::roundOff(yn1, _decimals);
    }

    // Common logarithms
    std::string logb(const std::string& _number, const std::string& _base, const size_t _decimals)
    {
        checkDecimalArg(&_decimals);

        //            -ln(1/a)
        // log (x) = ----------
        //    b       -ln(1/b)

        auto oneOverA = divide("1", _number, 0, static_cast<int>(_decimals + 2));
        auto oneOverB = divide("1", _base, 0, static_cast<int>(_decimals + 2));

        auto lnX = "-" + _log(oneOverA, _decimals + 2);
        auto lnB = "-" + _log(oneOverB, _decimals + 2);
        auto result = divide(lnX, lnB, 0, static_cast<int>(_decimals));

        return numUtils::roundOff(result, _decimals);
    }

    std::string log10(const std::string& _number, const size_t _decimals)
    {
        checkDecimalArg(&_decimals);
        return logb(_number, "10", _decimals);
    }

    std::string log2(const std::string& _number, const size_t _decimals)
    {
        checkDecimalArg(&_decimals);
        return logb(_number, "2", _decimals);
    }

    std::string ln(const std::string& _number, const size_t _decimals)
    {
        checkDecimalArg(&_decimals);
        return _log(_number, _decimals);
    }
} // namespace steppable::__internals::calc

#ifndef NO_MAIN
int main(int _argc, const char* _argv[])
{
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('c', $("calc::log", "e8227bec-443c-4d2d-a569-06e3d20c11ad"), false);
    program.addPosArg('n', $("calc::log", "d67686ce-2bad-48c9-a8ff-ec709d23ccea"), true);
    program.addPosArg('b', $("calc::log", "4a3f8558-00dd-430e-921c-792542d9c29a"), true);
    program.addKeywordArg("decimals", 5, $("calc::log", "56363a7f-4277-4805-95b2-ef3b8ccc1671"));
    program.addSwitch("profile", false, $("calc::log", "8623ed47-e7bd-46a2-a1db-3c0746520e2e"));
    program.parseArgs();

    const bool profile = program.getSwitch("profile");
    const int decimals = program.getKeywordArgument("decimals");
    const auto& command = program.getPosArg(0);
    const auto& arg = program.getPosArg(1);
    const auto& base = program.getPosArg(2);

    using namespace steppable::__internals;
    using namespace steppable::output;

    if (command == "logb")
        std::cout << calc::logb(arg, base, decimals) << "\n";
    else if (command == "log10")
        std::cout << calc::log10(arg, decimals) << "\n";
    else if (command == "log2")
        std::cout << calc::log2(arg, decimals) << "\n";
    else if (command == "ln")
        std::cout << calc::ln(arg, decimals) << "\n";
    else
    {
        error("log"s, $("calc::log", "0fc4245a-fee9-4e99-bbbd-378d091c5143", { command }));
        return EXIT_FAILURE;
    }
}
#endif
