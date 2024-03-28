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
 * @file multiply.cpp
 * @brief This file contains the implementation of the multiply function, which can multiply two strings together.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 */

#include "argParse.hpp"
#include "fn/basicArithm.hpp"
#include "multiplyReport.hpp"
#include "util.hpp"

#include <string>
#include <string_view>
#include <vector>

/**
 * @brief Determines the scale for a product of two numbers.
 *
 * @param[in] a Number 1,
 * @param[in] b Number 2.
 *
 * @return The correct scale for their product.
 */
long long determineProductScale(const std::string& a, const std::string& b)
{
    auto aScale = determineScale(roundOff(a));
    auto bScale = determineScale(roundOff(b));

    return aScale + bScale;
}

std::string multiply(const std::string_view& a, const std::string_view& b, const int steps)
{
    if (isZeroString(a) or isZeroString(b))
        return "0"; // Since a or b is zero, the result must be zero as well
    if (a == "1")
        return static_cast<std::string>(b);
    if (b == "1")
        return static_cast<std::string>(a);

    const auto& [splitNumberArray, aIsNegative, bIsNegative] = splitNumber(a, b, false, false);
    bool resultIsNegative = false;
    const auto& [aInteger, aDecimal, bInteger, bDecimal] = splitNumberArray;
    const std::string &aStr = aInteger + aDecimal, bStr = bInteger + bDecimal;
    std::vector<std::vector<int>> prodDigits, carries;

    if (aIsNegative and bIsNegative)
        resultIsNegative = false; // NOLINT(bugprone-branch-clone)
    else if (aIsNegative or bIsNegative)
        resultIsNegative = true;
    else
        resultIsNegative = false;

    for (size_t indexB = 0; indexB < bStr.length(); indexB++)
    {
        const int bDigit = static_cast<int>(bStr[indexB]) - '0';
        if (bDigit == 0)
            continue;
        std::vector<int> currentProdDigits(aStr.length() + bStr.length() + 1, 0),
            currentCarries(aStr.length() + bStr.length() + 1, 0);
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
        currentProdDigits[0] = currentCarries[0]; // The digit at index 0 is the carry, but was never added in the loop
        prodDigits.push_back(currentProdDigits);
        carries.push_back(currentCarries);
    }

    // Copy the original prodDigits to this new variable, because we'll be modifying prodDigits for output formatting.
    auto prodDigitsOut(prodDigits);
    for (size_t index = 0; index < prodDigits.size(); index++)
    {
        prodDigits[index].resize(prodDigits[index].size() - index - 1);
        prodDigitsOut[index].resize(prodDigitsOut[index].size() - index - 1);
        prodDigits[index].insert(prodDigits[index].begin(), index, 0);
    }

    // Add the vectors digit-wise together
    std::vector<int> finalProdDigits(prodDigits[0].size(), 0), finalProdCarries(prodDigits[0].size(), 0);
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

    const auto scale = determineProductScale(static_cast<std::string>(a), static_cast<std::string>(b));
    return reportMultiply(static_cast<std::string>(a),
                          static_cast<std::string>(b),
                          aStr,
                          bStr,
                          aDecimal,
                          bDecimal,
                          finalProdDigits,
                          finalProdCarries,
                          prodDigitsOut,
                          carries,
                          resultIsNegative,
                          scale,
                          steps);
}

#ifndef NO_MAIN
int main(const int _argc, const char* _argv[])
{
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', "Number 1");
    program.addPosArg('b', "Number 2");
    program.addKeywordArg("steps", 2, "Amount of steps while multiplying");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    int steps = program.getKeywordArgument("steps");
    bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(Column Method Multiplication)
        std::cout << "Column Method Multiplication :\n" << multiply(aStr, bStr, steps) << '\n';
        TOC()
    }
    else
        std::cout << multiply(aStr, bStr, steps) << '\n';
}
#endif
