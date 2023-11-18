#pragma once

#include <string>

std::string reportDecimalConvertStep(const std::string_view& baseString,
                                     const char digit,
                                     const long powerIndex,
                                     const std::string_view& convertedDigit,
                                     const long maxWidth);

std::string reportDecimalConvert(const std::string_view& inputString,
                                 const std::string_view& baseString,
                                 const std::string_view& convertedString,
                                 const int steps = 2);
