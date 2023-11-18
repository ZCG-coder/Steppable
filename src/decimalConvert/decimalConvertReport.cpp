#include "decimalConvertReport.hpp"

#include "symbols.hpp"

#include <iomanip>
#include <sstream>
#include <string>
#include <string_view>

std::string reportDecimalConvertStep(const std::string_view& baseString,
                                     const char digit,
                                     const long powerIndex,
                                     const std::string_view& convertedDigit,
                                     const long maxWidth)
{
    std::stringstream ss;

    ss << digit << " " MULTIPLY " ";
    ss << baseString << makeSuperscript(powerIndex + '0');
    ss << " = " << std::setw(maxWidth) << convertedDigit << std::setw(0);
    return ss.str();
}

std::string reportDecimalConvert(const std::string_view& inputString,
                                 const std::string_view& baseString,
                                 const std::string_view& convertedString,
                                 const int steps)
{
    if (steps == 0)
        return static_cast<std::string>(convertedString);

    std::stringstream ss;
    if (steps == 2)
        ss << THEREFORE " ";
    ss << inputString << makeSubscript(static_cast<std::string>(baseString)) << " = ";
    ss << convertedString << makeSubscript("10");
    return ss.str();
}
