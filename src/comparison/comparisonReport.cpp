#include "comparisonReport.hpp"

#include "symbols.hpp"

#include <sstream>
#include <string_view>

std::string reportComparisonAtInteger(const std::string_view& a,
                                      const std::string_view& b,
                                      const bool bigger,
                                      const int steps)
{
    std::stringstream ss;

    if (steps == 2)
    {
        ss << "Comparing the integer part of a and b" << std::endl;
        if (bigger)
        {
            ss << BECAUSE << " The integer part of " << a << " is bigger than the integer part of " << b << std::endl;
            ss << THEREFORE " " << a << " is greater than " << b;
        }
        else
        {
            ss << BECAUSE " The integer part of " << b << " is bigger than the integer part of " << a << std::endl;
            ss << THEREFORE " " << a << " is less than " << b;
        }
    }
    else if (steps == 1)
        ss << a << (bigger ? " > " : " < ") << b;
    else
        ss << bigger ? '1' : '0';

    return ss.str();
}

std::string reportComparisonByDigit(const std::string_view& a,
                                    const std::string_view& b,
                                    const unsigned int _digit,
                                    const bool bigger,
                                    const int steps)
{
    std::stringstream ss;
    int digit = static_cast<int>(_digit);
    if (not bigger)
        digit = -digit;
    if (steps == 2)
    {
        ss << "a = " << a << std::endl;
        ss << "b = " << b << std::endl;

        if (bigger)
        {
            ss << std::string(digit + 4, ' ') << "^~~~~ " BECAUSE " At digit " << digit + 1 << ", " << a[digit]
               << " is greater than " << b[digit] << std::endl;
            ss << THEREFORE " " << a << " is greater than " << b;
        }
        else
        {
            ss << std::string(digit + 4, ' ') << "^~~~~ " BECAUSE " At digit " << digit + 1 << ", " << a[digit]
               << " is less than " << b[digit] << std::endl;
            ss << THEREFORE " " << a << " is less than " << b;
        }
    }
    else if (steps == 1)
        ss << a << (bigger ? " > " : " < ") << b;
    else
        ss << bigger ? '1' : '0';

    return ss.str();
}
