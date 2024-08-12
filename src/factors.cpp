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

#include "factors.hpp"

#include "fn/calc.hpp"
#include "types/result.hpp"

#include <algorithm>
#include <vector>

using namespace steppable::__internals::arithmetic;
using namespace steppable::types;

namespace steppable::__internals::numUtils
{
    std::vector<std::string> getFactors(const std::string& _number)
    {
        std::vector<std::string> factors;
        // If the number is negative, add a negative sign to the factors
        if (_number[0] == '-')
            factors.emplace_back("-1");
        // Get the absolute value of the number
        auto number = abs(_number, 0);
        // Get the factors of the number
        loop(number, [&](const std::string& factor) {
            if (factor != "0")
            {
                auto quotientRemainder = divideWithQuotient(number, factor);
                if (quotientRemainder.remainder == "0")
                    factors.push_back(factor);
            }
        });
        factors.push_back(number);
        return factors;
    }

    ResultBool getRootFactor(const std::string& _number, const std::string& base)
    {
        auto factors = getFactors(_number);
        // Reverse the factors
        std::reverse(factors.begin(), factors.end());
        // Get the largest root factor
        for (const auto& factor : factors)
        {
            auto rootResult = isRoot(factor, base);
            if (rootResult.getStatus() == StatusBool::CALCULATED_SIMPLIFIED_YES)
                return { { _number, base, rootResult.getOutput() }, factor, StatusBool::CALCULATED_SIMPLIFIED_YES };
        }
        // The number has no root factors
        return { { _number, base }, "1", StatusBool::CALCULATED_SIMPLIFIED_YES };
    }

    std::string getGreatestRootNum(const std::string& _number, const std::string& base)
    {
        auto integralPart = rootIntPart(_number, base);
        return power(integralPart, base, 0);
    }

    bool isPrime(const std::string& _number)
    {
        auto factors = getFactors(_number);
        return factors.size() == 2; // Only 1 and the number itself are factors ==> prime!
    }

    ResultBool isRoot(const std::string& _number, const std::string& base)
    {
        auto iRoot = rootIntPart(_number, base);
        auto rootNum = power(iRoot, base, 0);
        if (compare(rootNum, _number, 0) == "2")
            return { { _number, base }, iRoot, StatusBool::CALCULATED_SIMPLIFIED_YES };
        return { { _number, base }, "1", StatusBool::CALCULATED_SIMPLIFIED_NO };
    }
} // namespace steppable::__internals::numUtils
