#include "argParse.hpp"
#include "decimalConvertReport.hpp"
#include "fn/basicArithm.hpp"
#include "util.hpp"

#include <string>

std::string decimalConvert(const std::string_view& _inputString, const std::string_view& baseString, int steps)
{
    std::string larger = compare(baseString, "36");
    if (larger == "0")
    {
        error("The base is larger than 36, which means that it is impossible to represent the number.");
        return "";
    }

    std::string converted = "0", inputString = static_cast<std::string>(_inputString);
    std::reverse(inputString.begin(), inputString.end());

    auto maxWidth = power(baseString, std::to_string(_inputString.length()), 0).length();

    std::stringstream ss;
    for (auto iterator = inputString.begin(); iterator < inputString.end(); iterator++)
    {
        auto index = iterator - inputString.begin();
        auto currentIndex = std::to_string(index);
        auto digit = inputString[index];
        auto placeValue = power(baseString, std::to_string(index), 0),
             convertedDigit = multiply(placeValue, std::string(1, digit), 0);
        converted = add(converted, convertedDigit, 0);

        if (steps == 2)
            ss << reportDecimalConvertStep(baseString, digit, index, convertedDigit, maxWidth) << std::endl;
    }
    ss << reportDecimalConvert(_inputString, baseString, converted, steps);
    return ss.str();
}

#ifndef NO_MAIN
int main(int _argc, const char* _argv[])
{
    UTF8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', "Number in the base");
    program.addPosArg('b', "Base number");
    program.addKeywordArg("steps", 2, "Amount of steps while converting the number. 0 = No steps, 2 = All steps.");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    int steps = program.getKeywordArgument("steps");
    bool profile = program.getSwitch("profile");
    const auto &inputString = program.getPosArg(0), baseString = program.getPosArg(1);

    if (profile)
    {
        TIC(Decimal Conversion)
        std::cout << "Decimal Conversion :\n" << decimalConvert(inputString, baseString, steps) << std::endl;
        TOC()
    }
    else
        std::cout << decimalConvert(inputString, baseString, steps) << std::endl;
}
#endif
