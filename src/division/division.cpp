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

#include "argParse.hpp"
#include "divisionReport.hpp"
#include "fn/basicArithm.hpp"
#include "logging.hpp"
#include "output.hpp"
#include "util.hpp"

#include <cstddef>
#include <cstdlib>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>

QuotientRemainder getQuotientRemainder(const auto& _currentRemainder, const auto& divisor)
{
    auto currentRemainder = removeLeadingZeros(_currentRemainder);
    if (compare(currentRemainder, divisor, 0) == "0")
        return { "0", currentRemainder };
    if (compare(currentRemainder, divisor, 0) == "2")
        return { "1", "0" }; // Equal

    int out = 0;
    while (compare(currentRemainder, divisor, 0) != "0")
    {
        out++;
        currentRemainder = subtract(currentRemainder, divisor, 0);
    }

    const auto &quotient = std::to_string(out), remainder = currentRemainder;
    return { quotient, remainder };
}

/**
 * @brief Determines the scale of the quotient of division.
 * @param _number The number to be divided.
 * @param _divisor The divisor of the division.
 * @return The scale of the result.
 * @see https://worldmentalcalculation.com/how-to-divide-by-long-numbers-in-mental-math/
 */
long long determineResultScale(const std::string& _number, const std::string& _divisor)
{
    std::string number = _number, divisor = _divisor;
    long long numberScale = determineScale(number);
    long long divisorScale = determineScale(divisor), diffScale = std::abs(numberScale - divisorScale);

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
    // Method: If number >= divisor -> return numberScale.
    //         Else                 -> return numberScale - 1.
    if (compare(number, divisor, 0) != "0")
        return diffScale + 1;
    return diffScale;
}

std::string divide(const std::string_view& _number,
                   const std::string_view& _divisor,
                   const int steps,
                   const int _decimals)
{
    if (isZeroString(_number) and isZeroString(_divisor))
    {
        // Easter egg in open-source code
        error("division",
              "Imagine that you have zero cookies and you split them evenly among zero friends, how many "
              "cookies does "
              "each person get? See? It doesn't make sense. And Cookie Monster is sad that there are no "
              "cookies, and "
              "you are sad that you have no friends."s);
        return "Indeterminate";
    }
    if (isZeroString(_divisor))
    {
        error("division", "Division of %s by zero leads to infinity."s, std::string(_number).c_str());
        return "Infinity";
    }

    if (compare(_number, _divisor, 0) == "2")
    {
        std::stringstream ss;
        if (steps == 2)
            ss << "Since " << _number << " is equal to " << _divisor << ", " THEREFORE " the result is 1";
        else if (steps == 1)
            ss << _number << " " DIVIDED_BY " " << _divisor << " = 1";
        else
            ss << "1";
        return ss.str();
    }

    auto splitNumberResult = splitNumber(_number, _divisor, false, true);
    bool numberIsNegative = splitNumberResult.aIsNegative, divisorIsNegative = splitNumberResult.bIsNegative;
    auto [numberInteger, numberDecimal, divisorInteger, divisorDecimal] = splitNumberResult.splitNumberArray;
    auto numberIntegerOrig = numberInteger, divisorIntegerOrig = divisorInteger, numberDecimalOrig = numberDecimal,
         divisorDecimalOrig = divisorDecimal;
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
    std::string remainder(1, number[0]), lastRemainder, header = makeWider(divisor) + ") " + makeWider(number);
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

    // Scenario 1: No decimal places returned
    // Solution  : Do nothing
    if (static_cast<size_t>(numberIntegers) == quotient.length() - 1 or decimals == 0)
        finalQuotient = quotient.substr(0, quotient.length() - 1);
    // Scenario 2: Decimal places more than requested
    // Solution  : Round to the nearest decimal place
    else if (numberDecimals >= decimals and numberIntegers > 0)
    {
        bool carry = false;
        if (not quotient.empty() and quotient.back() > '4')
        {
            quotient = add(quotient, "10", 0, false, false);

            if (quotient.front() == '0')
                quotient.erase(0, 1);
            else
            {
                carry = true;
                quotient += '0';
            }
        }
        quotient.pop_back();
        auto beforeDecimal = quotient.substr(0, numberIntegers),
             afterDecimal = quotient.substr(numberIntegers, numberDecimals);
        if (beforeDecimal.empty())
            beforeDecimal = "0";
        if (not afterDecimal.empty())
            finalQuotient = beforeDecimal + "." + afterDecimal;
        else
            finalQuotient = beforeDecimal;

        if (afterDecimal.length() > decimals)
            finalQuotient = multiply(finalQuotient, "10", 0);
    }
    // Scenario 3: Result is less than one
    // Solution  : 1. Append "0." to the beginning
    //             2. Append appropriate amount of zeros
    //             3. Apply rounding
    else if (numberIntegers <= 0)
    {
        if (not quotient.empty() and quotient.back() > '4')
        {
            quotient = add(quotient, "10", 0, false, false);
            if (quotient.front() == '0')
                quotient.erase(0, 1);
            else
                quotient += '0';
        }
        quotient.pop_back();
        auto afterDecimal = std::string(-numberIntegers, '0') + quotient;
        finalQuotient = "0." + afterDecimal;

        if (afterDecimal.length() > decimals)
            finalQuotient = multiply(finalQuotient, "10", 0);
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

#ifndef NO_MAIN
int main(const int _argc, const char* _argv[])
{
    Utf8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', "Number 1");
    program.addPosArg('b', "Number 2");
    program.addKeywordArg("steps", 2, "Amount of steps while dividing. 0 = No steps, 2 = All steps.");
    program.addKeywordArg("decimals", 5, "Decimals to output");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    const int steps = program.getKeywordArgument("steps");
    const int decimals = program.getKeywordArgument("decimals");
    const bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(Column Method Division)
        std::cout << "Column Method Division :\n" << divide(aStr, bStr, steps, decimals) << '\n';
        TOC()
    }
    else
        std::cout << divide(aStr, bStr, steps, decimals) << '\n';
}
#endif
