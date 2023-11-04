#include "argParse.hpp"
#include "comparisonReport.hpp"
#include "util.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

auto compare(const std::string_view& a, const std::string_view& b, const int steps = 2)
{
    auto aIntegerReal = split(a, '.').front(), bIntegerReal = split(b, '.').front();
    if (aIntegerReal.length() != bIntegerReal.length())
        return reportComparisonAtInteger(a, b, aIntegerReal.length() > bIntegerReal.length(), steps);

    for (int i = 0; i < a.length(); i++)
    {
        if (a[i] == b[i] or not isdigit(a[i]) or not isdigit(b[i]))
            continue; // Decimal point or equals
        bool bigger = a[i] > b[i];
        if (bigger)
            return reportComparisonByDigit(a, b, i, bigger, steps);
        else
            return reportComparisonByDigit(a, b, -i, bigger, steps);
    }

    if (steps == 1)
        return (std::string) "Equal";
    else if (steps == 2)
    {
        std::stringstream ss;
        ss << a << " = " << b;
        return ss.str();
    }
    else
        return (std::string) "2";
}

int main(int _argc, const char** _argv)
{
    UTF8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', "Number 1");
    program.addPosArg('b', "Number 2");
    program.addKeywordArg("steps", 2, "Amount of steps while comparing");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    int steps = program.getKeywordArgument("steps");
    bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(Comparing...)
        std::cout << compare(aStr, bStr, steps) << std::endl;
        TOC()
    }
    else
        std::cout << compare(aStr, bStr, steps) << std::endl;
}
