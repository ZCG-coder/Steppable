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
 * @file atan2.cpp
 * @brief Desciption
 *
 * @author Andy Zhang
 * @date 2nd August 2024
 */

#include "argParse.hpp"
#include "atan2Report.hpp"
#include "constants.hpp"
#include "fn/calc.hpp"
#include "getString.hpp"
#include "output.hpp"
#include "rounding.hpp"
#include "util.hpp"

#include <cstddef>
#include <string>

using namespace std::literals;
using namespace steppable::__internals::arithmetic;
using namespace steppable::__internals::numUtils;
using namespace steppable::localization;
using namespace steppable::output;

namespace steppable::__internals::arithmetic
{
    std::string atan2(const std::string& y, const std::string& x, const size_t decimals = 10)
    {
        //                /
        //                |         y
        //                | arctan(---)         if x > 0,               (1)
        //                |         x
        //                |
        //                |         y
        //                | arctan(---) + pi    if x < 0 and y >= 0,    (2)
        //                |         x
        //                |
        //                |         y
        //                | arctan(---) - pi    if x < 0 and y < 0,     (3)
        //                |         x
        //                |
        // atan2(x, y) = <
        //                |   pi
        //                | -----               if x = 0 and y > 0,     (4)
        //                |   2
        //                |
        //                |     pi
        //                | - -----             if x = 0 and y < 0,     (5)
        //                |     2
        //                |
        //                | undefined           if x = 0 and y = 0.     (6)
        //                \

        // (6)
        if (isZeroString(x) and isZeroString(y)) [[unlikely]]
        {
            error("atan2"s, $("atan2", "8d78a4a1-4b3e-431a-a0fc-9a0e663b3281"));
            return "Undefined";
        }

        // (4)
        if (isZeroString(x) and compare(y, "0", 0) == "1") [[unlikely]]
            return roundOff(static_cast<std::string>(constants::PI_OVER_2), decimals);

        // (5)
        if (isZeroString(x) and compare(y, "0", 0) == "0") [[unlikely]]
            return "-" + roundOff(static_cast<std::string>(constants::PI_OVER_2), decimals);

        const auto& yOverX = divide(y, x, 0, static_cast<int>(decimals + 2));
        const auto& atanYOverX = atan(yOverX, static_cast<int>(decimals + 2));

        // (1)
        if (compare(x, "0", 0) == "1") [[likely]]
            return atanYOverX;
        // (2)
        if (compare(x, "0", 0) == "0" and compare(y, "0", 0) != "0") [[likely]]
            return add(atanYOverX, static_cast<std::string>(constants::PI), 0);
        // (3)
        if (compare(x, "0", 0) == "0" and compare(y, "0", 0) == "0") [[likely]]
            return subtract(atanYOverX, static_cast<std::string>(constants::PI), 0);

        // Will never be executed. Just here for Clangd.
        return "Impossible! How did you get here?";
    }
} // namespace steppable::__internals::arithmetic

#ifndef NO_MAIN
int main(int _argc, const char* _argv[])
{
    Utf8CodePage();
    ProgramArgs program(_argc, _argv);
    program.addPosArg('y', $("atan2", "799378d1-3edd-4f97-97d2-8662b17a1819"));
    program.addPosArg('x', $("atan2", "7f146d0f-4f58-4dcd-9333-2e27d7e7dcf9"));
    program.addKeywordArg("decimals", 2, $("atan2", "fc72b8b9-bc77-4d44-9e99-65e1f11150e2"));
    program.parseArgs();

    int decimals = program.getKeywordArgument("decimals");
    const auto& yStr = program.getPosArg(0);
    const auto& xStr = program.getPosArg(1);

    std::cout << atan2(yStr, xStr, decimals) << '\n';
}
#endif
