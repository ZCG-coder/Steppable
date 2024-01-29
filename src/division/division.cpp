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
#include "output.hpp"
#include "util.hpp"

#include <ostream>
#include <sstream>
#include <string>

auto getQuotient(const auto& _temp, const auto& _divisor)
{
    auto temp = _temp;
    const auto& divisor = _divisor;
    if (compare(temp, divisor, 0) == "0")
        return std::string("0");
    if (compare(temp, divisor, 0) == "2")
        return std::string("1"); // Equal

    int out = 0;
    while (compare(temp, divisor, 0) == "1" or compare(temp, divisor, 0) == "2")
    {
        out++;
        temp = subtract(temp, divisor, 0);
    }

    return std::to_string(out);
}

auto getRemainder(const auto& quotient, const auto& temp, const auto& divisor)
{
    return subtract(temp, multiply(quotient, divisor, 0), 0);
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

    auto splitNumberResult = splitNumber(_number, _divisor, false, true);
    bool numberIsNegative = splitNumberResult.aIsNegative, divisorIsNegative = splitNumberResult.bIsNegative;
    auto [numberInteger, numberDecimal, divisorInteger, divisorDecimal] = splitNumberResult.splitNumberArray;
    auto numberIntegerOrig = numberInteger, divisorIntegerOrig = divisorInteger;
    auto decimals = _decimals;

    if (numberIntegerOrig.empty())
        numberIntegerOrig = "0";
    if (divisorIntegerOrig.empty())
        divisorIntegerOrig = "0";

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
        resultIsNegative = false;
    else if (numberIsNegative or divisorIsNegative)
        resultIsNegative = true;
    else if (not numberIsNegative and not divisorIsNegative)
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
    auto number = numberInteger + numberDecimal;
    auto divisor = divisorInteger + divisorDecimal;
    std::string quotient;
    std::stringstream tempFormattedAns, formattedAns;

    for (int i = 0; i < decimals + 1; i++) // Additional 0 is for rounding
        number += '0';

    unsigned long long idx = 0;
    std::string remainder(1, number[0]), lastRemainder, header = makeWider(divisor) + ") " + makeWider(number);
    tempFormattedAns << header << '\n';
    auto width = static_cast<int>(header.length());

    while (number.length() > idx)
    {
        auto currentQuotient = getQuotient(remainder, divisor);
        auto currentRemainder = getRemainder(currentQuotient, remainder, divisor);

        quotient += currentQuotient;
        if (steps == 2)
            tempFormattedAns << reportDivisionStep(
                currentRemainder, currentQuotient, divisor, width, quotient.length() - 1, lastRemainder);
        lastRemainder = remainder = currentRemainder;
        if (number.length() - 1 >= ++idx)
            remainder += number[idx];
    }

    quotient = removeLeadingZeros(quotient);
    // Here, we attempt to round the result.
    // - Length of integer in output  = Length of integers in number - Length of integers in divisor  (*)
    // - Length of decimals in output = Length of output - Length of integers
    // Note: It can be negative!
    auto numberIntegers = static_cast<long long>(numberInteger.length() - divisorInteger.length());
    auto diffNumberDivisor = subtract(numberIntegerOrig, divisorIntegerOrig, 0);
    if (compare(abs(_number, 0), abs(_divisor, 0), 0) != "0" and compare(diffNumberDivisor, "9", 0) != "1")
        numberIntegers++;
    long long numberDecimals = quotient.length() - numberIntegers;
    // Scenario 1: No decimal places returned
    // Solution  : Do nothing
    if (static_cast<size_t>(numberIntegers) == quotient.length() - 1)
        quotient = quotient.substr(0, quotient.length() - 1);
    // Scenario 2: Decimal places more than requested
    // Solution  : Round to the nearest decimal place
    else if (numberDecimals >= decimals and numberIntegers > 0)
    {
        auto beforeDecimal = quotient.substr(0, numberIntegers),
             afterDecimal = quotient.substr(numberIntegers, numberDecimals);
        if (not afterDecimal.empty() and afterDecimal.back() > '4')
            afterDecimal = add(afterDecimal, "1", 0);
        if (beforeDecimal.empty())
            beforeDecimal = "0";
        if (not afterDecimal.empty())
            quotient = beforeDecimal + "." + afterDecimal;
        else
            quotient = beforeDecimal;
    }
    // Scenario 3: Result is less than one
    // Solution  : 1. Append "0." to the beginning
    //             2. Append appropriate amount of zeros
    else if (numberIntegers <= 0)
        quotient = "0." + std::string(-numberIntegers, '0') + quotient.substr(0, quotient.length() - 1);

    // Scenario 4: Decimal places less than requested
    // Solution  : Pad with trailing zeros
    if (numberDecimals < decimals and numberDecimals >= 0)
    {
        auto difference = decimals - numberDecimals;
        quotient += std::string(difference, '0');
    }

    return reportDivision(
        tempFormattedAns, remainder, quotient, divisor, _divisor, _number, steps, width, resultIsNegative);
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
