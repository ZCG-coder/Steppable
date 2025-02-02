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
 * @file trig.cpp
 * @brief This file contains the implementation of trigonometric functions.
 *
 * @author Andy Zhang
 * @date 5th June 2024
 */

#include "argParse.hpp"
#include "constants.hpp"
#include "fn/calc.hpp"
#include "fn/calculus.hpp"
#include "getString.hpp"
#include "rounding.hpp"
#include "trigReport.hpp"
#include "util.hpp"

#include <functional>
#include <iostream>
#include <string>

using namespace std::literals;
using namespace steppable::output;
using namespace steppable::localization;
using namespace steppable::__internals::utils;
using namespace steppable::__internals::numUtils;

namespace steppable::__internals::calc
{
    std::string degToRad(const std::string& _deg)
    {
        // rad = deg * (pi / 180)
        auto deg = divideWithQuotient(_deg, "360").remainder;
        auto rad = multiply(deg, static_cast<std::string>(constants::PI_OVER_180), 0);
        return rad;
    }

    std::string gradToRad(const std::string& _grad)
    {
        // rad = grad * (pi / 200)
        auto grad = divideWithQuotient(_grad, "400").remainder;
        auto rad = multiply(grad, static_cast<std::string>(constants::PI_OVER_200), 0);
        return rad;
    }

    std::string radToDeg(const std::string& _rad, const int decimals)
    {
        // deg = rad * (180 / pi)
        auto rad = _rad;
        rad = divideWithQuotient(rad, static_cast<std::string>(constants::TWO_PI)).remainder;
        rad = standardizeNumber(rad);
        auto deg = divide(rad, static_cast<std::string>(constants::PI_OVER_180), 0, decimals);
        deg = standardizeNumber(deg);
        deg = divideWithQuotient(deg, "90").remainder;
        return standardizeNumber(deg);
    }

    std::string radToGrad(const std::string& _rad, const int decimals)
    {
        // grad = rad * (200 / pi)
        auto rad = divideWithQuotient(_rad, static_cast<std::string>(constants::TWO_PI)).remainder;
        rad = standardizeNumber(rad);
        auto grad = divide(rad, static_cast<std::string>(constants::PI_OVER_200), 0, decimals);
        grad = standardizeNumber(grad);
        grad = divideWithQuotient(grad, "100").remainder;
        return standardizeNumber(grad);
    }

    std::string gradToDeg(const std::string& _grad)
    {
        // deg = grad * (9 / 10)
        auto deg = divideWithQuotient(_grad, "400").remainder;
        return deg;
    }

    std::string _cos(const std::string& x, const int _decimals)
    {
        int decimals = _decimals;
        checkDecimalArg(&_decimals);

        //          .,,.   .,    /=====================================================================\
        //         //%,   .(     | NOTE: DO NOT CALL THIS METHOD DIRECTLY IN PRODUCTION CODE!          |
        //       /%(       .,    |   /-\    THIS METHOD ONLY ACCEPTS RADIANS AS INPUT, AND DOES        |
        //       %#,   #%%,(%#   |  / ! \  NOT ROUND CORRECTLY. CALL `cos(std::string x, int decimals) |
        //       ,,/   ..  ,#(   | /-----\     INSTEAD!                                                |
        //        .,/..,.*%&#%   \=====================================================================/
        //         /%&&&%&@%&*  /
        //       (( ((&&%&&#&#
        //   ,#%(((#% *%#@@&#(*
        // (##&&%##%%&@@#&@@@@@&&&   +------------+
        // %@%&&&%%&&&. .&*@@@@@@@@& | Henri Padé |
        // %&%&&&%&&&%&@&@@@@@@@@@@@ +------------+

        if (compare(abs(x, 0), "0.001", 0) == "0") // If small, use polynomial approximant
        {
            // double x2 = x * x;
            auto x2 = multiply(x, x, 0, decimals);
            auto x4 = multiply(x2, x2, 0, decimals);
            // (313*x^4 - 6900*x^2 + 15120)/(13*x^4 + 660*x^2 + 15120) // Padé approximant
            //      4        2
            //  313x  - 6900x  + 15120
            // ------------------------
            //     4       2
            //  13x  + 660x  + 15120
            auto a = add(subtract(multiply("313", x4, 0, decimals), multiply("6900", x2, 0, decimals), 0), "15120", 0);
            auto b = add(add(multiply("13", x4, 0, decimals), multiply("660", x2, 0, decimals), 0), "15120", 0);
            return standardizeNumber(divide(a, b, 0, decimals + 2));
        }
        // otherwise use recursion
        // double C = cos(x / 4);
        auto result = _cos(standardizeNumber(divide(x, "4", 0, decimals + 1)), decimals + 2);
        auto result2 = roundOff(multiply(result, result, 0, decimals + 2), static_cast<long>(decimals) + 2);
        // return 8 * C2 * (C2 - 1) + 1;
        return standardizeNumber(
            add(multiply("8", multiply(result2, subtract(result2, "1", 0), 0, decimals), 0), "1", 0));
    }

    std::string cos(const std::string& x, const int decimals, const int mode)
    {
        checkDecimalArg(&decimals);

        // Mode Options:
        // 0: Radians  (default)
        // 1: Degrees  (converts to radians)
        // 2: Gradians (converts to radians)
        std::string result;
        switch (mode)
        {
        case 0:
        {
            result = _cos(divideWithQuotient(x, static_cast<std::string>(constants::TWO_PI)).remainder, decimals + 2);
            break;
        }
        case 1:
        {
            result = _cos(degToRad(x), decimals + 2);
            break;
        }
        case 2:
        {
            result = _cos(gradToRad(x), decimals + 2);
            break;
        }
        default:
        {
            error("trig::cos"s, "Invalid mode. Defaulting to radians."s);
            result = _cos(x, decimals + 2);
        }
        }

        return roundOff(result, decimals);
    }

    std::string sin(const std::string& x, const int decimals, const int mode)
    {
        checkDecimalArg(&decimals);

        // Mode Options:
        // 0: Radians  (default)
        // 1: Degrees  (converts to radians)
        // 2: Gradians (converts to radians)
        std::string result;
        switch (mode)
        {
        case 0:
        {
            result = cos(subtract(divideWithQuotient(x, static_cast<std::string>(constants::TWO_PI)).remainder,
                                  static_cast<std::string>(constants::PI_OVER_2),
                                  0),
                         decimals);
            break;
        }
        case 1:
        {
            result = cos(subtract(degToRad(x), static_cast<std::string>(constants::PI_OVER_2), 0), decimals);
            break;
        }
        case 2:
        {
            result = cos(subtract(gradToRad(x), static_cast<std::string>(constants::PI_OVER_2), 0), decimals);
            break;
        }
        default:
        {
            error("trig::sin"s, "Invalid mode. Defaulting to radians."s);
            result = cos(subtract(x, static_cast<std::string>(constants::PI_OVER_2), 0), decimals);
        }
        }

        return roundOff(result, decimals);
    }

    std::string tan(const std::string& x, const int decimals, const int mode)
    {
        checkDecimalArg(&decimals);

        // Mode Options:
        // 0: Radians  (default)
        // 1: Degrees  (converts to radians)
        // 2: Gradians (converts to radians)
        std::string result;
        switch (mode)
        {
        case 0:
        {
            auto cosX = cos(divideWithQuotient(x, static_cast<std::string>(constants::TWO_PI)).remainder, decimals + 1);
            if (isZeroString(cosX))
            {
                error("trig::tan"s, $("trig", "a7ed4324-5cc3-48d2-9798-d3e743b809d3"));
                return "Infinity";
            }
            result = divide(sin(x, decimals + 1), cosX, 0, decimals);
            break;
        }
        case 1:
        {
            auto xRad = degToRad(x);
            auto cosX = cos(xRad, decimals + 1);
            if (isZeroString(cosX))
            {
                error("trig::tan"s, $("trig", "a7ed4324-5cc3-48d2-9798-d3e743b809d3"));
                return "Infinity";
            }
            result = divide(sin(xRad, decimals + 1), cosX, 0, decimals);
            break;
        }
        case 2:
        {
            auto xRad = gradToRad(x);
            auto cosX = cos(xRad, decimals + 1);
            if (isZeroString(cosX))
            {
                error("trig::tan"s, $("trig", "a7ed4324-5cc3-48d2-9798-d3e743b809d3"));
                return "Infinity";
            }
            result = divide(sin(xRad, decimals + 1), cosX, 0, decimals);
            break;
        }
        default:
        {
            error("trig::tan"s, "Invalid mode. Defaulting to radians."s);
            result = divide(sin(x, decimals + 1), cos(x, decimals + 1), decimals);
        }
        }

        return roundOff(result, decimals);
    }

    std::string csc(const std::string& x, const int decimals, const int mode)
    {
        checkDecimalArg(&decimals);

        auto sinX = sin(x, decimals + 1, mode);
        if (isZeroString(sinX))
        {
            error("trig::csc"s, $("trig", "0dd11fcc-bdd0-48d1-9b4a-7ebcccb4915f"));
            return "Infinity";
        }
        return divide("1", sinX, 0, decimals);
    }

    std::string sec(const std::string& x, const int decimals, const int mode)
    {
        checkDecimalArg(&decimals);

        auto cosX = cos(x, decimals + 1, mode);
        if (isZeroString(cosX))
        {
            error("trig::sec"s, $("trig", "62792c6c-6751-4850-bf66-5e6366322cc0"));
            return "Infinity";
        }
        return divide("1", cosX, 0, decimals);
    }

    std::string cot(const std::string& x, const int decimals, const int mode)
    {
        checkDecimalArg(&decimals);

        auto tanX = tan(x, decimals + 1, mode);
        if (isZeroString(tanX))
        {
            error("trig::cot"s, $("trig", "65650a93-4298-4e19-8c81-f5fbd9f14ac2"));
            return "Infinity";
        }
        return divide("1", tanX, 0, decimals);
    }

    std::string atan(const std::string& _x, const int decimals, const int mode)
    {
        checkDecimalArg(&decimals);

        auto x = _x;
        // Zero check
        if (isZeroString(x))
            return "0";

        bool isReduced = false;
        if (compare(abs(x, 0), "1", 0) != "0")
        {
            isReduced = true;
            // Reduce x to a small number
            x = divide("1", x, 0, decimals + 2);
        }
        // Otherwise, use integration.
        //                      1                       / x
        //   d              ---------  ==>              |       1
        // ---- arctan(x) =     2           arctan(x) = |   ----------  dt
        //  dx                 x + 1                    |      2
        //                                              / 0   t  + 1
        auto fx = [&](const std::string& y) {
            const auto& y2 = multiply(y, y, 0);
            const auto& denominator = add(y2, "1", 0);
            return divide("1", denominator, 0, decimals * 2);
        };
        auto result = calculus::romberg(fx, "0", x, 10, decimals + 2);
        if (isReduced)
        {
            // If x was reduced, use the identity
            //              pi            1
            // arctan(x) = ---- - arctan(---)
            //               2            x
            result = subtract(static_cast<std::string>(constants::PI_OVER_2), result, 0);
        }

        // Convert the result as needed.
        switch (mode)
        {
        case 1:
            result = radToDeg(result, decimals + 1);
            break;
        case 2:
            result = radToGrad(result, decimals + 1);
            break;
        default:
            break;
        }

        if (_x.front() == '-')
            result = "-" + result;
        return roundOff(result, decimals);
    }

    std::string asin(const std::string& x, const int decimals, const int mode)
    {
        checkDecimalArg(&decimals);

        if (compare(abs(x, 0), "1", 0) == "1")
        {
            error("trig::asin", $("trig", "b06650e0-7101-4734-9647-5abb56beb492"));
            return "Infinity";
        }
        if (compare(abs(x, 0), "0", 0) == "2")
            return "0";

        // / x
        // |           1
        // |  ---------------- dy
        // |       /------|
        // |      /     2
        // |    \/ 1 - y
        // / 0
        auto integrand = [&](const std::string& y) {
            auto y2 = power(y, "2", 0);
            auto oneMinusY2 = subtract("1", y2, 0);
            auto denominator = root(oneMinusY2, "2", decimals + 2);
            return divide("1", denominator, 0, decimals + 2);
        };
        auto result = calculus::romberg(integrand, "0", x, 10, decimals + 2);

        switch (mode)
        {
        case 1:
            result = radToDeg(result, decimals + 1);
            break;
        case 2:
            result = radToGrad(result, decimals + 1);
            break;
        default:
            break;
        }

        return roundOff(result, decimals);
    }

    std::string acos(const std::string& x, const int decimals, const int mode)
    {
        checkDecimalArg(&decimals);

        if (compare(x, "1", 0) == "2")
            return "0";
        std::string circleAngle;
        switch (mode)
        {
        case 1:
            circleAngle = "90";
            break;
        case 2:
            circleAngle = "100";
            break;
        default:
            circleAngle = static_cast<std::string>(constants::PI_OVER_2);
        }

        //             pi
        // acos(x) = ----- - asin(x)
        //             2
        auto result = subtract(circleAngle, asin(x, decimals + 2, mode), 0);
        return roundOff(result, decimals);
    }

    std::string asec(const std::string& x, const int decimals, const int mode)
    {
        checkDecimalArg(&decimals);

        if (compare(abs(x, 0), "1", 0) == "1")
        {
            error("trig::asec", $("trig", "fffb4742-3712-4c9a-a7ff-65cd51508a0a"));
            return "Infinity";
        }

        //                 1
        // asec(x) = acos(---)
        //                 x
        return acos(divide("1", x, 0, decimals), decimals, mode);
    }

    std::string acsc(const std::string& x, const int decimals, const int mode)
    {
        checkDecimalArg(&decimals);

        if (compare(abs(x, 0), "1", 0) != "0")
        {
            error("trig::acsc"s, $("trig", "c021dfde-300c-4d74-a6a1-87a514c1bbe0"));
            return "Infinity";
        }

        //                 1
        // acsc(x) = asin(---)
        //                 x
        return asin(divide("1", x, 0, decimals), decimals, mode);
    }

    std::string acot(const std::string& x, const int decimals, const int mode)
    {
        checkDecimalArg(&decimals);

        if (compare(abs(x, 0), "1", 0) != "0")
        {
            error("trig::acot"s, $("trig", "c0c6a29f-abda-4676-9662-1d00f94f10a4"));
            return "Infinity";
        }

        //                 1
        // acot(x) = atan(---)
        //                 x
        return atan(divide("1", x, 0, decimals), decimals, mode);
    }
} // namespace steppable::__internals::calc

#ifndef NO_MAIN
int main(int _argc, const char* _argv[])
{
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('c', $("trig", "47dcf91b-847c-48f0-9889-f5ce1b6831e3"), false);
    program.addPosArg('n', $("trig", "bcd0a3e9-3d89-4921-94b3-d7533d60911f"));
    program.addKeywordArg("mode", 0, $("trig", "03fdd1f2-6ea5-49d4-ac3f-27f01f04a518"));
    program.addKeywordArg("decimals", 5, $("trig", "d1df3b60-dac1-496c-99bb-ba763dc551df"));
    program.addSwitch("profile", false, $("trig", "162adb13-c4b2-4418-b3df-edb6f9355d64"));
    program.parseArgs();

    const int mode = program.getKeywordArgument("mode");
    const bool profile = program.getSwitch("profile");
    const int decimals = program.getKeywordArgument("decimals");
    const auto& command = program.getPosArg(0);
    const auto& arg = static_cast<std::string>(program.getPosArg(1));

    using namespace steppable::__internals;

    std::function<std::string(const std::string& x, const int decimals, const int mode)> function;

    // Basic trigonometric functions
    if (command == "sin")
        function = calc::sin;
    else if (command == "cos")
        function = calc::cos;
    else if (command == "tan")
        function = calc::tan;
    // Reciprocal trigonometric functions
    else if (command == "csc")
        function = calc::csc;
    else if (command == "sec")
        function = calc::sec;
    else if (command == "cot")
        function = calc::cot;
    // Inverse trigonometric functions
    else if (command == "atan")
        function = calc::atan;
    else if (command == "asin")
        function = calc::asin;
    else if (command == "acos")
        function = calc::acos;
    else if (command == "asec")
        function = calc::asec;
    else if (command == "acsc")
        function = calc::acsc;
    else if (command == "acot")
        function = calc::acot;
    // Invalid command
    else
    {
        error("trig::main", $("trig", "6ad9958f-f127-4ee4-a4c6-94cf19576b9a", { command }));
        return EXIT_FAILURE;
    }
    std::cout << function(arg, decimals, mode) << '\n';
}
#endif
