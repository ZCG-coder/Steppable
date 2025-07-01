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
 * @file division.cpp
 * @brief Performs division of two numbers represented in strings.
 *
 * @author Andy Zhang
 * @date 23rd November 2023
 */

#include "argParse.hpp"
#include "divisionReport.hpp"
#include "fn/calc.hpp"
#include "getString.hpp"
#include "output.hpp"
#include "rounding.hpp"
#include "util.hpp"

#include <cstddef>
#include <cstdlib>
#include <sstream>
#include <string>

using namespace steppable::__internals::numUtils;
using namespace steppable::__internals::stringUtils;
using namespace steppable::output;
using namespace steppable::localization;
using namespace steppable::__internals::calc;

namespace steppable::__internals::calc
{
    QuotientRemainder getQuotientRemainder(const auto& _currentRemainder, const auto& divisor)
    {
        auto currentRemainder = removeLeadingZeros(_currentRemainder);
        if (compare(currentRemainder, divisor, 0) == "0")
            return { "0", currentRemainder };
        if (compare(currentRemainder, divisor, 0) == "2")
            return { .quotient = "1", .remainder = "0" }; // Equal

        int out = 0;
        while (compare(currentRemainder, divisor, 0) != "0")
        {
            out++;
            currentRemainder = subtract(currentRemainder, divisor, 0);
        }

        const auto& quotient = std::to_string(out);
        const auto remainder = currentRemainder;
        return { quotient, remainder };
    }

    /**
     * @brief Determines the scale of the quotient of division.
     * @param[in] _number The number to be divided.
     * @param[in] _divisor The divisor of the division.
     * @return The scale of the result.
     * @see https://worldmentalcalculation.com/how-to-divide-by-long-numbers-in-mental-math/
     */
    long long determineResultScale(const std::string& _number, const std::string& _divisor)
    {
        std::string number = _number;
        std::string divisor = _divisor;
        long long numberScale = determineScale(number);
        long long divisorScale = determineScale(divisor);
        long long diffScale = std::abs(numberScale - divisorScale);

        // Step 1: Make divisor the same scale as number
        // Method: If divisorScale > numberScale -> Scale up number.
        //         If numberScale > divisorScale -> Scale up divisor.
        // Eg.   : 1. 500, 20 => 20 -> 200 (diffScale = 1 -> 20 * 10^1 = 200)
        //         2. 50, 500 => 50 -> 500 (diffScale = 1 -> 50 * 10^1 = 500)
        auto scaleFactor = power("10", std::to_string(diffScale), 0);
        if (divisorScale > numberScale)
        {
            number = multiply(number, scaleFactor, 0);
            if (diffScale > 0)
                diffScale = -diffScale;
        }
        else if (numberScale > divisorScale)
        {
            divisor = multiply(divisor, scaleFactor, 0);
        }
        // Special cases - Needs to minus 1.
        else if (numberScale == divisorScale and compare(_number, _divisor, 0) == "0")
            return 0;
        else if (numberScale == divisorScale and compare(_number, _divisor, 0) != "0")
            return 1;

        // Step 2: Squeeze!
        // Method: If number >= divisor -> return diffScale + 1.
        //         Else                 -> return diffScale.
        if (compare(number, divisor, 0) != "0")
            return diffScale + 1;
        return diffScale;
    }

    std::string divide(const std::string& _number, const std::string& _divisor, const int steps, const int _decimals)
    {
        checkDecimalArg(&_decimals);

        if (isZeroString(_number) and isZeroString(_divisor))
        {
            // Easter egg in open-source code
            error("division", $("division", "e8ad759d-fcb8-4280-a7a8-a637ae834ffc"));
            return "Indeterminate";
        }
        if (isZeroString(_divisor))
        {
            // Division by zero leads to infinity.
            error("division", $("division", "977f3c9f-01c3-49e4-bf4a-94d7c58bbe82", { _number }));
            return "Infinity";
        }
        if (isZeroString(_number))
        {
            return "0";
        }

        if (compare(_number, _divisor, 0) == "2")
        {
            std::stringstream ss;
            if (steps == 2)
                // Since the number is equal to the divisor, the result is 1.
                ss << $("division", "b4cace82-0076-40f3-85de-92aa1a81df44", { _number, _divisor });
            else if (steps == 1)
                ss << _number << " " << DIVIDED_BY << " " << _divisor << " = 1";
            else
                ss << "1";
            return ss.str();
        }

        if (compare(_divisor, "1", 0) == "2")
            return roundOff(static_cast<std::string>(_number), _decimals);

        auto splitNumberResult = splitNumber(_number, _divisor, false, true);
        bool numberIsNegative = splitNumberResult.aIsNegative;
        bool divisorIsNegative = splitNumberResult.bIsNegative;
        auto [numberInteger, numberDecimal, divisorInteger, divisorDecimal] = splitNumberResult.splitNumberArray;
        auto numberIntegerOrig = numberInteger;
        auto divisorIntegerOrig = divisorInteger;
        auto numberDecimalOrig = numberDecimal;
        auto divisorDecimalOrig = divisorDecimal;
        auto decimals = _decimals;

        // Here, we determine the polarity of the result.
        // Scenario 1: Both positive
        // Solution  : Do nothing
        //
        // Scenario 2: Both negative
        // Solution  : Do nothing
        //
        // Scenario 3: One positive, one negative
        // Solution  : Result is negative, but make it positive
        bool resultIsNegative = false;
        if (numberIsNegative and divisorIsNegative)
            ;
        else if (numberIsNegative or divisorIsNegative)
            resultIsNegative = true;
        else
            resultIsNegative = false;

        while (not divisorDecimal.empty())
        {
            divisorInteger += divisorDecimal[0];
            divisorDecimal.erase(divisorDecimal.begin());
            if (not numberDecimal.empty())
            {
                numberInteger += numberDecimal[0];
                numberDecimal.erase(numberDecimal.begin());
            }
            else
                numberInteger += '0';
        }
        auto number = removeLeadingZeros(numberInteger + numberDecimal);
        auto divisor = removeLeadingZeros(divisorInteger);
        std::string quotient;
        std::stringstream tempFormattedAns;

        for (int i = 0; i < decimals + 1; i++) // Additional 0 is for rounding
            number += '0';

        unsigned long long idx = 0;
        std::string remainder(1, number[0]);
        std::string lastRemainder;
        std::string header = makeWider(divisor) + ") " + makeWider(number);
        tempFormattedAns << header << '\n';
        auto width = static_cast<int>(header.length());

        while (number.length() > idx)
        {
            auto [currentQuotient, currentRemainder] = getQuotientRemainder(remainder, divisor);

            quotient += currentQuotient;
            if (steps == 2)
                tempFormattedAns << reportDivisionStep(
                    currentRemainder, currentQuotient, divisor, width, quotient.length() - 1, lastRemainder);
            lastRemainder = remainder = currentRemainder;
            if (number.length() - 1 >= ++idx)
                remainder += number[idx];
        }

        // Here, we attempt to round the result.
        // Note: It can be negative!
        auto numberIntegers = determineResultScale(numberIntegerOrig + "." + numberDecimalOrig,
                                                   divisorIntegerOrig + "." + divisorDecimalOrig);
        auto numberDecimals = quotient.length() - numberIntegers;
        quotient = removeLeadingZeros(quotient);
        std::string finalQuotient = quotient;
        if ((numberIntegers < 0) and (-numberIntegers >= decimals))
        {
            if (steps != 0)
                // Warn the user that the result is inaccurate.
                warning("division"s, $("division", "d38c283c-e75d-4cc2-a634-bf1b3361d489"));
            return "0";
        }

        // Scenario 1: No decimal places returned
        // Solution  : Do nothing
        if (static_cast<size_t>(numberIntegers) == quotient.length() - 1)
            finalQuotient = quotient.substr(0, quotient.length() - 1);
        // Scenario 2: Decimal places more than requested
        // Solution  : Round to the nearest decimal place
        else if (numberDecimals >= decimals and numberIntegers > 0)
        {
            auto beforeDecimal = quotient.substr(0, numberIntegers);
            auto afterDecimal = quotient.substr(numberIntegers, numberDecimals);
            if (beforeDecimal.empty())
                beforeDecimal = "0";
            if (not afterDecimal.empty())
                finalQuotient = beforeDecimal + "." + afterDecimal;
            else
                finalQuotient = beforeDecimal;
            finalQuotient = roundOff(finalQuotient, _decimals);
        }
        // Scenario 3: Result is less than one
        // Solution  : 1. Append "0." to the beginning
        //             2. Append appropriate amount of zeros
        //             3. Apply rounding
        else if (numberIntegers <= 0)
        {
            auto afterDecimal = std::string(-numberIntegers, '0') + quotient;
            finalQuotient = roundOff("0." + afterDecimal, _decimals);
        }

        // Scenario 4: Decimal places less than requested
        // Solution  : Pad with trailing zeros
        if (numberDecimals < decimals)
        {
            auto difference = decimals - numberDecimals;
            finalQuotient += std::string(difference, '0');
        }

        return reportDivision(
            tempFormattedAns, remainder, finalQuotient, divisor, _divisor, _number, steps, width, resultIsNegative);
    }

    QuotientRemainder divideWithQuotient(const std::string& number, const std::string& divisor)
    {
        const auto& divisionResult = divide(number, divisor, 0);
        const auto& splitNumberResult = splitNumber(divisionResult, "0", false, false, true, true).splitNumberArray;

        const auto& quotient = splitNumberResult[0];
        const auto nearestResult = multiply(divisor, quotient, 0);
        const auto& remainder = removeLeadingZeros(subtract(number, nearestResult, 0));

        return { .quotient = quotient, .remainder = remainder };
    }

    std::string getGCD(const std::string& _a, const std::string& _b)
    {
        // Sign for GCD does not matter.
        // https://proofwiki.org/wiki/GCD_for_Negative_Integers
        auto splitNumberResult = splitNumber(_a, _b, false, false, true, false).splitNumberArray;
        auto a = splitNumberResult[0] + splitNumberResult[1];
        auto b = splitNumberResult[2] + splitNumberResult[3];

        // Ensure that a is greater than or equal to b
        if (b > a)
            return getGCD(b, a);

        // Euclidean algorithm
        while (compare(b, "0", 0) != "2")
        {
            auto temp = b;
            b = getQuotientRemainder(a, b).remainder;
            a = temp;
        }

        // The GCD is the absolute value of a
        return abs(a, 0);
    }
} // namespace steppable::__internals::calc

#ifndef NO_MAIN
int main(const int _argc, const char* _argv[])
{
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', $("division", "e7bbfa43-684d-498a-b10f-d8a76a371583"));
    program.addPosArg('b', $("division", "9e6d7430-7006-4c77-ad4a-00955080765c"));
    program.addKeywordArg("steps", 2, $("division", "797de85c-787c-4c05-bc42-763da058f9e0"));
    program.addKeywordArg("decimals", 5, $("division", "e10fcce8-4bb3-4b3b-9820-33571065a8ee"));
    program.addSwitch("profile", false, $("division", "98a3f915-5e93-4417-942a-071b2d9a13b3"));
    program.parseArgs();

    const int steps = program.getKeywordArgument("steps");
    const int decimals = program.getKeywordArgument("decimals");
    const bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (steps == 5)
    {
        std::cout << getGCD(aStr, bStr) << '\n';
        return 0;
    }
    if (profile)
    {
        TIC(Column method division)
        std::cout << $("division", "bc2c8ff9-2d67-45e9-8824-2bc971e21cc9") << "\n"
                  << divide(aStr, bStr, steps, decimals) << '\n';
        TOC()
    }
    else
        std::cout << divide(aStr, bStr, steps, decimals) << '\n';
}
#endif
