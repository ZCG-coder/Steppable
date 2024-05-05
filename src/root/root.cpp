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
 * @file root.cpp
 * @brief Takes the n-th root of a number represented as a string.
 *
 * @author Andy Zhang
 * @date 1st May 2024
 */

#include "argParse.hpp"
#include "fn/basicArithm.hpp"
#include "util.hpp"

#include <string>

using namespace steppable::__internals::arithmetic;
using namespace steppable::__internals::utils;
using namespace std::literals;

namespace steppable::__internals::arithmetic
{
    std::string root(const std::string_view& _number, const std::string_view& base, const size_t decimals)
    {
        size_t raised_times = 0;
        std::string number = static_cast<std::string>(_number);
        while (compare(number, "1", 0) == "0")
        {
            number = multiply(number, power("10", base, 0), 0);
            raised_times++;
        }

        auto x = number, y = "0"s, allowedError = "0." + std::string(decimals - 1, '0') + "1";
        size_t idx = 0;
        auto denominator = "1" + std::string(raised_times, '0');

        while (true)
        {
            auto newAvg = divide(subtract(x, y, 0), "2", 0, decimals + 1);
            auto radicand = add(y, newAvg, 0);
            auto test = power(radicand, base, 0);

            if (compare(newAvg, "0", 0) == "2")
                return divide(radicand, denominator, 0, decimals);
            if (compare(test, number, 0) == "1")
                x = radicand;
            else if (compare(test, number, 0) == "0")
                y = radicand;

            idx++;
            // std::cout << "iteration: " << idx << " error: " << error << " test: " << test << "\n";
        }
    }
} // namespace steppable::__internals::arithmetic

#ifndef NO_MAIN
int main(const int _argc, const char* _argv[])
{
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', "Number");
    program.addPosArg('n', "Base");
    program.addKeywordArg("decimals", 8, "Amount of decimals while taking the n-th root.");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    const int decimals = program.getKeywordArgument("decimals");
    const bool profile = program.getSwitch("profile");
    const auto& number = program.getPosArg(0);
    const auto& base = program.getPosArg(1);

    if (profile)
    {
        TIC(Nth root)
        std::cout << "Taking n-th root :\n" << root(number, base, decimals) << '\n';
        TOC()
    }
    else
        std::cout << root(number, base, decimals) << '\n';
}
#endif
