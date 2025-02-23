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
 * @file factorial.cpp
 * @brief This file contains the implementation of the factorial function, which calculates a factorial.
 *
 * @author Andy Zhang
 * @date 4th June 2024
 */

#include "argParse.hpp"
#include "factorialReport.hpp"
#include "fn/calc.hpp"
#include "getString.hpp"
#include "output.hpp"
#include "util.hpp"

#include <iostream>
#include <string>

using namespace steppable::__internals::numUtils;
using namespace steppable::__internals::utils;
using namespace steppable::__internals::calc;
using namespace steppable::__internals::symbols;
using namespace steppable::output;
using namespace steppable::localization;
using namespace std::literals;

namespace steppable::__internals::calc
{
    std::string factorial(const std::string& _number, const int steps)
    {
        auto number = standardizeNumber(_number);
        if (not isInteger(number))
        {
            // We cannot evaluate integrals yet, so this has to be returned.
            // Correct implementation of the gamma function should be
            //          / +inf
            //          |      z-1  -s
            //   G(z) = |     s    e   ds     ,where z is a non-zero decimal ............ (1)
            //          |
            //          / 0
            // and factorial is defined as
            //   n! = n * G(n)                ,where n is a non-zero decimal ............ (2)
            error("factorial"s, $("factorial", "4eeba5fa-a5b8-4abf-ae65-22a466da6d18", { number }));
            return "0";
        }
        if (isZeroString(number))
        {
            if (steps == 2)
                return $("factorial", "d023ddb5-8a71-441b-8c67-8836bd94e93d");
            return "1"; // By definition, 0! = 1
        }
        // Negative numbers do not have a factorial.
        if (number.front() == '-')
        {
            error("factorial"s, $("factorial", "69d93fb8-1bb7-4ed2-be6d-8eeafd5f23a6", { number }));
            return "0";
        }

        // Calculate the factorial of the number
        std::string result = "1";
        loop(_number, [&](const std::string& i) { result = multiply(result, add(i, "1", 0), 0); });

        return reportFactorial(_number, result, steps);
    }
} // namespace steppable::__internals::calc

#ifndef NO_MAIN
int main(const int _argc, const char* _argv[])
{
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', $("factorial", "135326d7-4e93-46d1-9e0e-8407eab6307b"));
    program.addKeywordArg("steps", 2, $("factorial", "7e1e72c2-256d-4b71-84b6-65166937d7ba"));
    program.addSwitch("profile", false, $("factorial", "b781d070-00e5-4c26-a56a-c0ad9504c0e3"));
    program.parseArgs();

    const int steps = program.getKeywordArgument("steps");
    const bool profile = program.getSwitch("profile");
    const auto& number = static_cast<std::string>(program.getPosArg(0));

    if (profile)
    {
        TIC(Factorial)
        std::cout << $("factorial", "3ab32522-695e-4551-9542-0eb1824c8bd2") << "\n" << factorial(number, steps) << '\n';
        TOC()
    }
    else
        std::cout << factorial(number, steps) << '\n';
}
#endif
