#include "argParse.hpp"
#include "fn/basicArithm.hpp"
#include "powerReport.hpp"
#include "util.hpp"

#include <iostream>

std::string power(const std::string_view _number, const std::string_view& raiseTo, const int steps)
{
    std::string numberOrig = static_cast<std::string>(_number), number = "1";
    return reportPower(_number, raiseTo, steps);
}

#ifndef NO_MAIN
int main(const int _argc, const char* _argv[])
{
    UTF8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', "Number as the base");
    program.addPosArg('b', "Number as the exponent");
    program.addKeywordArg(
        "steps", 2, "Amount of steps while raising the power (i.e., multiplying). 0 = No steps, 2 = All steps.");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    int steps = program.getKeywordArgument("steps");
    bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(Power)
        std::cout << "Power :\n" << power(aStr, bStr, steps) << std::endl;
        TOC()
    }
    else
        std::cout << power(aStr, bStr, steps) << std::endl;
}
#endif
