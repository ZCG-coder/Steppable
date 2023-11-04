#include "argParse.hpp"
#include "subtractReport.hpp"
#include "util.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

auto subtract(const std::string_view& a, const std::string_view& b, const bool steps = true)
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
        auto decimalPos = aDecimal.length();
        auto itSumDigits = diffDigits.begin();
        auto itCarries = borrows.begin();

        diffDigits.insert(itSumDigits + static_cast<long>(decimalPos), -1); // -1 indicating a decimal point
        borrows.insert(itCarries + static_cast<long>(decimalPos), -1); // Reserve the space
    }

    std::reverse(borrows.begin(), borrows.end());
    std::reverse(diffDigits.begin(), diffDigits.end());
    return reportSubtract(aInteger, aDecimal, bInteger, bDecimal, aIsDecimal, bIsDecimal, diffDigits, borrows, steps);
}

int main(int _argc, const char* _argv[])
{
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', "");
    program.addPosArg('b', "");
    program.addSwitch("steps", true, "steps while adding");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    bool steps = program.getSwitch("steps");
    bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(Column Method Addition)
        std::cout << "Column Method Addition :\n" << subtract(aStr, bStr) << std::endl;
        TOC()
    }
    else
        std::cout << subtract(aStr, bStr, steps) << std::endl;
}
