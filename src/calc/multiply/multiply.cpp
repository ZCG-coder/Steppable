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
 * @file multiply.cpp
 * @brief This file contains the implementation of the multiply function, which can multiply two strings together.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 */

#include "argParse.hpp"
#include "fn/calc.hpp"
#include "getString.hpp"
#include "multiplyReport.hpp"
#include "rounding.hpp"
#include "util.hpp"

#include <sstream>
#include <string>
#include <vector>

using namespace steppable::__internals::numUtils;
using namespace steppable::__internals::stringUtils;
using namespace steppable::output;
using namespace steppable::localization;
using namespace steppable::__internals::calc;

namespace steppable::__internals::calc
{
    std::string multiply(const std::string& _a, const std::string& _b, const int steps)
    {
        auto a = static_cast<std::string>(_a);
        auto b = static_cast<std::string>(_b);
        const auto& [splitNumberArray, aIsNegative, bIsNegative] = splitNumber(a, b, false, false);
        bool resultIsNegative = false;

        // Determine the polarity of the result.
        if (aIsNegative and bIsNegative)
            resultIsNegative = false; // NOLINT(bugprone-branch-clone)
        else if (aIsNegative or bIsNegative)
            resultIsNegative = true;
        else
            resultIsNegative = false;

        const auto& [aInteger, aDecimal, bInteger, bDecimal] = splitNumberArray;
        std::stringstream out;
        // Multiply by zero gives zero.
        if (isZeroString(a) or isZeroString(b))
        {
            if (steps == 2)
                out << $("multiply", "9cdeff33-fefa-40ac-b867-a811f652d6e3") << "\n";
            out << "0"; // Since a or b is zero, the result must be zero as well
        }

        // Multiplying by 1 gives the another number.
        if (a == "1")
        {
            if (steps == 2)
                out << $("multiply", "36adc27f-07e8-4118-88ed-f148164044da", { a, b }) << "\n";
            out << b;
            return out.str();
        }
        if (b == "1")
        {
            if (steps == 2)
                out << $("multiply", "36adc27f-07e8-4118-88ed-f148164044da", { b, a }) << "\n";
            out << a;
            return out.str();
        }

        // Multiplying by a power of ten means moving the decimal places.
        if (isPowerOfTen(a))
        {
            if (steps == 2)
                out << $("multiply", "0e76c0f9-6d14-450d-abc4-f4a758787d06", { a }) << "\n";
            auto result = moveDecimalPlaces(b, determineScale(a));
            if (resultIsNegative)
                result = "-" + result; // NOLINT(performance-inefficient-string-concatenation)

            out << result;
            return out.str();
        }
        if (isPowerOfTen(b))
        {
            if (steps == 2)
                out << $("multiply", "0e76c0f9-6d14-450d-abc4-f4a758787d06", { b }) << "\n";
            auto result = moveDecimalPlaces(a, determineScale(b));
            if (resultIsNegative)
                result = "-" + result; // NOLINT(performance-inefficient-string-concatenation)

            out << result;
            return out.str();
        }

        const std::string& aStr = aInteger + aDecimal;
        const std::string bStr = bInteger + bDecimal;
        std::vector<std::vector<int>> prodDigits;
        std::vector<std::vector<int>> carries;

        for (size_t indexB = 0; indexB < bStr.length(); indexB++)
        {
            const int bDigit = static_cast<int>(bStr[indexB]) - '0';
            std::vector<int> currentProdDigits(aStr.length() + bStr.length() + 1, 0);
            std::vector<int> currentCarries(aStr.length() + bStr.length() + 1, 0);
            if (bDigit == 0)
                goto skip; // NOLINT(cppcoreguidelines-avoid-goto)
            for (long long indexA = static_cast<long long>(aStr.length()) - 1; indexA != -1; indexA--)
            {
                const int aDigit = aStr[indexA] - '0';
                int prodDigit = bDigit * aDigit + currentCarries[indexA + 1];
                currentCarries[indexA] = prodDigit / 10;
                if (currentCarries[indexA] > 10)
                {
                    currentCarries[indexA + 1]++;
                    currentCarries[indexA] /= 10;
                }
                prodDigit %= 10;
                currentProdDigits[indexA + 1] = prodDigit; // Move back 1 to make room for carry
            }

        skip:
            currentProdDigits[0] =
                currentCarries[0]; // The digit at index 0 is the carry, but was never added in the loop
            prodDigits.push_back(currentProdDigits);
            carries.push_back(currentCarries);
        }

        // Copy the original prodDigits to this new variable, because we'll be modifying prodDigits for output
        // formatting.
        auto prodDigitsOut(prodDigits);
        for (size_t index = 0; index < prodDigits.size(); index++)
        {
            prodDigits[index].resize(prodDigits[index].size() - index - 1);
            prodDigitsOut[index].resize(prodDigitsOut[index].size() - index - 1);
            prodDigits[index].insert(prodDigits[index].begin(), index, 0);
        }

        // Add the vectors digit-wise together
        std::vector<int> finalProdDigits(prodDigits[0].size(), 0);
        std::vector<int> finalProdCarries(prodDigits[0].size(), 0);
        for (long long indexDigit = static_cast<long long>(finalProdDigits.size()) - 1; indexDigit != -1; indexDigit--)
        {
            int sum = finalProdCarries[indexDigit];
            for (auto& prodDigitVector : prodDigits)
                sum += prodDigitVector[indexDigit];
            if (indexDigit != 0)
            {
                finalProdCarries[indexDigit - 1] = sum / 10;
                finalProdDigits[indexDigit - 1] += sum / 10;
            }
            else
            {
                finalProdCarries[indexDigit] = sum / 10;
                finalProdDigits[indexDigit] += sum / 10;
            }
            sum %= 10;
            finalProdDigits[indexDigit] = sum;
        }

        return reportMultiply(a,
                              b,
                              aStr,
                              bStr,
                              aDecimal,
                              bDecimal,
                              finalProdDigits,
                              finalProdCarries,
                              prodDigitsOut,
                              carries,
                              resultIsNegative,
                              steps);
    }
} // namespace steppable::__internals::calc

#ifndef NO_MAIN
int main(const int _argc, const char* _argv[])
{
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', $("multiply", "1d54da58-ec3c-4888-80a8-c40565efb603"));
    program.addPosArg('b', $("multiply", "3db8b80f-9667-476a-b096-9323615dd461"));
    program.addKeywordArg("steps", 2, $("multiply", "5ed5291e-6269-4d76-a8f8-db5eec807955"));
    program.addSwitch("profile", false, $("multiply", "eec47776-991b-40cc-9956-7227127d2c1f"));
    program.parseArgs();

    int steps = program.getKeywordArgument("steps");
    bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(Column Method Multiplication)
        std::cout << $("multiply", "776a33fd-982a-4888-8b42-83b0f3797dc2") << "\n"
                  << multiply(aStr, bStr, steps) << '\n';
        TOC()
    }
    else
        std::cout << multiply(aStr, bStr, steps) << '\n';
}
#endif
