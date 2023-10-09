#include "comparisonReport.hpp"
#include "util.hpp"
#include <string>
#include <iostream>
#include "argParse.hpp"

auto compare(const std::string& a, const std::string& b)
{
    auto [aInteger, aDecimal, bInteger, bDecimal] = splitNumber(a, b);
    std::string aIntegerReal = split(a, '.').front(), bIntegerReal = split(b, '.').front();
    if (aIntegerReal.length() != bIntegerReal.length())
        return reportComparisonAtInteger(a, b, aIntegerReal.length() > bIntegerReal.length());

    for (int i = 0; i < a.length(); i++)
    {
        if (a[i] == b[i])
            continue; // Equals
        bool bigger = a[i] > b[i];
        if (not isdigit(a[i]) or not isdigit(b[i]))
            continue;
        if (bigger)
            return reportComparisonByDigit(a, b, i, bigger);
        else
            return reportComparisonByDigit(a, b, -i, bigger);
    }
    return (std::string) "Equal";
}

int main(int _argc, const char** _argv)
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
        std::cout << "Column Method Addition :\n" << compare(aStr, bStr) << std::endl;
        TOC()
    }
    else
        std::cout << compare(aStr, bStr) << std::endl;
}
