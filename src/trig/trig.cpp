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

/**
 * @file trig.cpp
 * @brief This file contains the implementation of trigonometric functions.
 *
 * @author Andy Zhang
 * @date 5th June 2024
 */

#include "argParse.hpp"
#include "constants.hpp"
#include "fn/basicArithm.hpp"
#include "rounding.hpp"
#include "trigReport.hpp"
#include "util.hpp"

#include <string>

using namespace std::literals;
using namespace steppable::output;
using namespace steppable::__internals::utils;
using namespace steppable::__internals::numUtils;

namespace steppable::__internals::arithmetic
{
    std::string degToRad(const std::string& _deg)
    {
        // rad = deg * (pi / 180)
        auto deg = divideWithQuotient(_deg, "360").remainder;
        auto rad = multiply(deg, constants::PI_OVER_180, 0);
        return rad;
    }

    std::string gradToRad(const std::string& _grad)
    {
        // rad = grad * (pi / 200)
        auto grad = divideWithQuotient(_grad, "400").remainder;
        auto rad = multiply(grad, constants::PI_OVER_200, 0);
        return rad;
    }

    std::string radToDeg(const std::string& _rad)
    {
        // deg = rad * (180 / pi)
        auto rad = divideWithQuotient(_rad, static_cast<std::string>(constants::TWO_PI)).remainder;
        auto deg = divide(rad, constants::PI_OVER_180, 0);
        return deg;
    }

    std::string radToGrad(const std::string& _rad)
    {
        // grad = rad * (200 / pi)
        auto rad = divideWithQuotient(_rad, static_cast<std::string>(constants::TWO_PI)).remainder;
        auto grad = divide(rad, constants::PI_OVER_200, 0);
        return grad;
    }

    std::string gradToDeg(const std::string& _grad)
    {
        // deg = grad * (9 / 10)
        auto deg = divideWithQuotient(_grad, "400").remainder;
        return deg;
    }

    std::string _cos(const std::string& x, const int decimals)
    {
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

        if (compare(abs(x, 0), "0.01", 0) == "0") // If small, use polynomial approximant
        {
            // double x2 = x * x;
            auto x2 = multiply(x, x, 0);
            // return (12 - 5 * x2) / (12 + x2); // Padé approximant
            auto a = subtract("12", multiply("5", x2, 0), 0);
            auto b = add("12", x2, 0);
            return standardizeNumber(divide(a, b, 0, decimals * 2));
        }
        // otherwise use recursion
        // double C = cos(x / 4);
        auto result = _cos(standardizeNumber(divide(x, "4", 0, decimals + 1)), decimals * 2);
        auto result2 = roundOff(multiply(result, result, 0), static_cast<long>(decimals) * 2);
        // return 8 * C2 * (C2 - 1) + 1;
        return standardizeNumber(add(multiply("8", multiply(result2, subtract(result2, "1", 0), 0), 0), "1", 0));
    }

    std::string cos(const std::string& x, const int decimals, const int mode)
    {
        // Mode Options:
        // 0: Radians  (default)
        // 1: Degrees  (converts to radians)
        // 2: Gradians (converts to radians)
        std::string result;
        switch (mode)
        {
        case 0:
        {
            result = _cos(divideWithQuotient(x, static_cast<std::string>(constants::TWO_PI)).remainder, decimals);
            break;
        }
        case 1:
        {
            result = _cos(degToRad(x), decimals);
            break;
        }
        case 2:
        {
            result = _cos(gradToRad(x), decimals);
            break;
        }
        default:
        {
            error("trig::cos"s, "Invalid mode. Defaulting to radians."s);
            result = _cos(x, decimals);
        }
        }

        return roundOff(result, decimals);
    }

    std::string sin(const std::string& x, const int decimals, const int mode)
    {
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
                                  constants::PI_OVER_2,
                                  0),
                         decimals);
            break;
        }
        case 1:
        {
            result = cos(subtract(degToRad(x), constants::PI_OVER_2, 0), decimals);
            break;
        }
        case 2:
        {
            result = cos(subtract(gradToRad(x), constants::PI_OVER_2, 0), decimals);
            break;
        }
        default:
        {
            error("trig::sin"s, "Invalid mode. Defaulting to radians."s);
            result = cos(subtract(x, constants::PI_OVER_2, 0), decimals);
        }
        }

        return roundOff(result, decimals);
    }

    std::string tan(const std::string& x, const int decimals, const int mode)
    {
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
                error("trig::tan"s, "Tangent is undefined here."s);
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
                error("trig::tan"s, "Tangent is undefined here."s);
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
                error("trig::tan"s, "Tangent is undefined here."s);
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
        auto sinX = sin(x, decimals + 1, mode);
        if (isZeroString(sinX))
        {
            error("trig::csc"s, "Cosecant is undefined here."s);
            return "Infinity";
        }
        return divide("1", sinX, 0, decimals);
    }

    std::string sec(const std::string& x, const int decimals, const int mode)
    {
        auto cosX = cos(x, decimals + 1, mode);
        if (isZeroString(cosX))
        {
            error("trig::sec"s, "Secant is undefined here."s);
            return "Infinity";
        }
        return divide("1", cosX, 0, decimals);
    }

    std::string cot(const std::string& x, const int decimals, const int mode)
    {
        auto tanX = tan(x, decimals + 1, mode);
        if (isZeroString(tanX))
        {
            error("trig::cot"s, "Cotangent is undefined here."s);
            return "Infinity";
        }
        return divide("1", tanX, 0, decimals);
    }

    std::string atan(const std::string& _x, const int decimals, const int mode)
    {
        auto x = _x;
        bool isReduced = false;
        if (compare(abs(x, 0), "1", 0) != "0")
        {
            isReduced = true;
            // Reduce x to a small number
            x = divide("1", x, 0, decimals * 2);
        }
        // Otherwise, use Padé series.
        // (https://journalofinequalitiesandapplications.springeropen.com/articles/10.1186/s13660-017-1310-6/tables/1)
        //        3
        //     55x  + 105x
        // ------------------ ~= arctan(x)
        //    4      2
        //  9x  + 90x  + 105
        auto x2 = power(x, "2", 0);
        auto x3 = multiply(x2, x, 0); // Use multiply to reduce the number of operations.
        auto x4 = multiply(x3, x, 0);
        auto numerator = add(multiply("55", x3, 0), multiply("105", x, 0), 0);
        auto denominator = add(add(x4, multiply("90", x2, 0), 0), "105", 0);
        auto result = standardizeNumber(divide(numerator, denominator, 0, decimals * 2));

        if (isReduced)
        {
            // If x was reduced, use the identity
            // arctan(1/x) = pi/2 - arctan(x)
            result = subtract(constants::PI_OVER_2, result, 0);
        }
        result = roundOff(result, decimals);

        // Convert the result as needed.
        switch (mode)
        {
        case 1:
            result = radToDeg(result);
            break;
        case 2:
            result = radToGrad(result);
            break;
        default:
            break;
        }

        return result;
    }

    // std::string asin(const std::string& x, const int decimals, const int mode) {}
} // namespace steppable::__internals::arithmetic

#ifndef NO_MAIN
int main(int _argc, const char* _argv[])
{
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('c', "Command", false);
    program.addPosArg('n', "Number", false);
    program.addKeywordArg("mode", 0, "The mode to calculate in. 0 = radians (default), 1 = degrees, 2 = gradians.");
    program.addKeywordArg("decimals", 5, "Amount of decimals while calculating.");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    const int mode = program.getKeywordArgument("mode");
    const bool profile = program.getSwitch("profile");
    const int decimals = program.getKeywordArgument("decimals");
    const auto& command = program.getPosArg(0);
    const auto& arg = static_cast<std::string>(program.getPosArg(1));

    using namespace steppable::__internals::arithmetic;

    if (command == "sin")
        std::cout << sin(arg, decimals, mode) << '\n';
    else if (command == "cos")
        std::cout << cos(arg, decimals, mode) << '\n';
    else if (command == "tan")
        std::cout << tan(arg, decimals, mode) << '\n';
    else if (command == "csc")
        std::cout << csc(arg, decimals, mode) << '\n';
    else if (command == "sec")
        std::cout << sec(arg, decimals, mode) << '\n';
    else if (command == "cot")
        std::cout << cot(arg, decimals, mode) << '\n';
    else if (command == "atan")
        std::cout << atan(arg, decimals, mode) << '\n';
    else
        error("trig::main", "Invalid command."s);
}
#endif
