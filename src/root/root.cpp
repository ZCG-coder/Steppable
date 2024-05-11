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
#include "fraction.hpp"
#include "rootReport.hpp"
#include "symbols.hpp"
#include "util.hpp"

#include <string>

#ifdef WINDOWS
    #undef max
    #undef min
#endif

using namespace steppable::__internals::arithmetic;
using namespace steppable::__internals::utils;
using namespace steppable::__internals::stringUtils;
using namespace std::literals;

namespace steppable::prettyPrint::printers
{
    std::string ppRoot(const std::string& radicand, const std::string& index)
    {
        // Result looks something like:
        //   3/---------
        //   /        2
        // \/ radicand
        auto indexWidth = prettyPrint::getStringWidth(index);
        auto width = prettyPrint::getStringWidth(radicand) + indexWidth + 3,
             height = prettyPrint::getStringHeight(radicand) + 1;
        auto spacingWidth = std::max(height, indexWidth), firstLineSpacingWidth = spacingWidth - indexWidth;
        auto lines = split(radicand, '\n');
        auto spacing = std::string(firstLineSpacingWidth, ' '),
             topBar = std::string(prettyPrint::getStringWidth(radicand), '-');

        prettyPrint::ConsoleOutput output(height, width);
        prettyPrint::Position pos;
        output.write(spacing + index + '/' + topBar + '\n', { 0, 0 }, false);
        for (size_t i = 0; i < lines.size(); i++)
        {
            const auto& line = lines[i];
            pos.y++;
            pos.x = spacingWidth - i - 1;
            output.write('/' + line, pos, true);
        }
        output.write("\\/"s, { pos.x - 1, pos.y }, true);

        return output.asString();
    }
} // namespace steppable::prettyPrint::printers

namespace steppable::__internals::arithmetic
{
    std::string root(const std::string& _number, const std::string& base, const size_t _decimals, const int steps)
    {
        if (numUtils::isDecimal(base))
        {
            const auto& fraction = Fraction(base);
            const auto& [top, bottom] = fraction.asArray();
            const auto &powerResult = power(_number, bottom, 0), rootResult = root(powerResult, top, _decimals, 0);
            return reportRootPower(_number, base, fraction, rootResult, steps);
        }

        if (compare(base, "1", 0) == "2")
            return _number;

        auto decimals = _decimals + 1;
        size_t raisedTimes = 0;
        std::string number = static_cast<std::string>(_number);
        while (compare(number, "1", 0) == "0")
        {
            number = multiply(number, power("10", base, 0), 0);
            raisedTimes++;
        }

        auto x = number, y = "0"s, allowedError = "0." + std::string(decimals - 1, '0') + "1";
        size_t idx = 0;
        auto denominator = "1" + std::string(raisedTimes, '0');

        while (true)
        {
            auto newAvg = divide(subtract(x, y, 0), "2", 0, decimals + 1);
            auto radicand = add(y, newAvg, 0);
            auto test = power(radicand, base, 0);

            if (compare(newAvg, "0", 0) == "2")
                return numUtils::standardizeNumber(divide(radicand, denominator, 0, _decimals));
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
    const auto& number = static_cast<std::string>(program.getPosArg(0));
    const auto& base = static_cast<std::string>(program.getPosArg(1));

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
