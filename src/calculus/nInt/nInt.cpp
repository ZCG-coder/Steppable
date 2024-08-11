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

#include "fn/basicArithm.hpp"
#include "rounding.hpp"

#include <cmath>
#include <functional>
#include <string>
#include <vector>

using namespace steppable::__internals::arithmetic;
using namespace steppable::__internals::numUtils;
using namespace std::literals;

namespace steppable::__internals::calculus
{
    std::string romberg(const std::function<std::string(std::string)>& f,
                        const std::string& a,
                        const std::string& b,
                        const int max_steps,
                        const int decimals)
    {
        auto acc = "0." + std::string(decimals - 1, '0') + "1";
        auto Rp = std::vector(max_steps, "0"s);
        auto Rc = std::vector(max_steps, "0"s);

        auto h = subtract(b, a, 0);
        auto fAB = add(f(a), f(b), 0);
        auto halfH = multiply(h, "0.5", 0);
        Rp.front() = multiply(halfH, fAB, 0);

        for (int i = 1; i < max_steps; i++)
        {
            h = multiply(h, "0.5", 0);
            auto c = "0"s;
            long ep = 1 << (i - 1); // 2^(i - 1)
            for (long j = 1; j < (ep + 1); j++)
            {
                auto d = multiply(std::to_string((2 * j) - 1), h, 0);
                c = add(c, f(add(a, d, 0)), 0);
            }
            Rc.front() = add(multiply(h, c, 0), multiply("0.5", Rp.front(), 0), 0);

            for (int j = 1; j < (i + 1); j++)
            {
                long double n_k = pow(4, j);
                auto one = multiply(std::to_string(n_k), Rc.at(j - 1), 0);
                auto top = subtract(one, Rp.at(j - 1), 0);
                Rc.at(j) = divide(top, std::to_string(n_k - 1), 0, decimals + 1);

                if (i > 1 and compare(abs(subtract(Rp.at(i - 1), Rc.at(i), 0), 0), acc, 0) == "0")
                    return roundOff(Rc.at(i), decimals);
            }

            std::ranges::swap(Rp, Rc);
        }

        return roundOff(Rp.at(max_steps - 1), decimals);
    }
} // namespace steppable::__internals::calculus

#ifndef NO_MAIN
int main() {}
#endif