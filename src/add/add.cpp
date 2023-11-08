#include "addReport.hpp"
#include "argParse.hpp"
#include "fn/basicArithm.hpp"
#include "util.hpp"

#include <algorithm>
#include <iostream>
#include <string_view>
#include <vector>

std::string add(const std::string_view& a, const std::string_view& b, const int steps)
{
    auto [aInteger, aDecimal, bInteger, bDecimal] = splitNumber(a, b);
    bool aIsDecimal = not isZeroString(aDecimal), bIsDecimal = not isZeroString(bDecimal);

    std::string aStr = aInteger + aDecimal, bStr = bInteger + bDecimal;
    std::reverse(aStr.begin(), aStr.end());
    std::reverse(bStr.begin(), bStr.end());

    std::vector<int> sumDigits(aStr.length() + 1, 0);
    std::vector<bool> carries(aStr.length() + 1, false);
    for (int index = 0; index < aStr.length(); index++)
    {
        int aDigit = aStr[index] - '0', bDigit = bStr[index] - '0';
        if (aStr[index] == ' ')
            aDigit = 0;
        if (bStr[index] == ' ')
            bDigit = 0;

        int sumDigit = aDigit + bDigit;
        sumDigits[index] += sumDigit;
        if (sumDigits[index] >= 10)
        {
            sumDigits[index] -= 10;
            sumDigits[index + 1] += 1;
            carries[index + 1] = true;
        }
    }

    // Add a decimal point
    if (aIsDecimal or bIsDecimal)
    {
        auto decimalPos = aDecimal.length();
        const auto& itSumDigits = sumDigits.begin();
        const auto& itCarries = carries.begin();

        sumDigits.insert(itSumDigits + static_cast<long>(decimalPos), -1); // -1 indicating a decimal point
        carries.insert(itCarries + static_cast<long>(decimalPos), false); // Reserve the space
    }

    std::reverse(carries.begin(), carries.end());
    std::reverse(sumDigits.begin(), sumDigits.end());
    if (sumDigits.front() == 0)
        sumDigits.erase(sumDigits.begin());

    return reportAdd(aInteger, aDecimal, bInteger, bDecimal, sumDigits, carries, steps);
}

#ifndef NO_MAIN
int main(const int _argc, const char* _argv[])
{
    UTF8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', "Number 1");
    program.addPosArg('b', "Number 2");
    program.addKeywordArg("steps", 2, "Amount of steps while adding. 0 = No steps, 2 = All steps.");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    int steps = program.getKeywordArgument("steps");
    bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(Column Method Addition)
        std::cout << "Column Method Addition :\n" << add(aStr, bStr) << std::endl;
        TOC()
    }
    else
        std::cout << add(aStr, bStr, steps) << std::endl;
}
#endif