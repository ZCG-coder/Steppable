#include "argParse.hpp"
#include "subtractReport.hpp"
#include "util.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

auto subtract(const std::string& a, const std::string& b, const bool steps = true)
{
    auto [aInteger, aDecimal, bInteger, bDecimal] = splitNumber(a, b);
    bool aIsDecimal = not isZeroString(aDecimal), bIsDecimal = not isZeroString(bDecimal);

    std::string aStr = aInteger + aDecimal, bStr = bInteger + bDecimal;
    std::reverse(aStr.begin(), aStr.end());
    std::reverse(bStr.begin(), bStr.end());

    std::vector<int> diffDigits(aStr.length(), 0);
    std::vector<int> borrows(aStr.length());
    std::copy(aStr.begin(), aStr.end(), borrows.begin());
    std::for_each(borrows.begin(), borrows.end(), [](int& c) { c -= '0'; });
    for (int index = 0; index < aStr.length(); index++)
    {
        int aDigit = borrows[index], bDigit = bStr[index] - '0';
        if (aStr[index] == ' ')
            aDigit = 0;
        if (bStr[index] == ' ')
            bDigit = 0;

        int diffDigit = aDigit - bDigit;
        diffDigits[index] = diffDigit;
        if (diffDigits[index] < 0)
        {
            diffDigits[index] += 10;
            borrows[index] += 10;
            diffDigits[index + 1]--;
            borrows[index + 1]--;
        }
    }

    // Add a decimal point
    if (aIsDecimal or bIsDecimal)
    {
        int decimalPos = aDecimal.length();
        auto itSumDigits = diffDigits.begin();
        auto itCarries = borrows.begin();

        diffDigits.insert(itSumDigits + decimalPos, -1); // -1 indicating a decimal point
        borrows.insert(itCarries + decimalPos, -1); // Reserve the space
    }

    std::reverse(borrows.begin(), borrows.end());
    std::reverse(diffDigits.begin(), diffDigits.end());
    return reportSubtract(aInteger, aDecimal, bInteger, bDecimal, aIsDecimal, bIsDecimal, diffDigits, borrows, steps);
}

int main(int _argc, const char* _argv[])
{
    bool steps = true, profile = false;

    ProgramArgs program(_argc, _argv);
    program.addPosArg("a");
    program.addPosArg("b");
    program.addSwitch("steps", true, "steps while adding");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    steps = program.getSwitch("steps");
    profile = program.getSwitch("profile");
    const std::string& aStr = program.getPosArg(0);
    const std::string& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(Column Method Addition)
        std::cout << "Column Method Addition :\n" << subtract(aStr, bStr) << std::endl;
        TOC()
    }
    else
        std::cout << subtract(aStr, bStr, steps) << std::endl;
}
