#include "comparisonReport.hpp"

#include "symbols.hpp"

#include <sstream>
#include <string>

const std::string reportComparisonAtInteger(const std::string& a,
                                            const std::string& b,
                                            const bool bigger,
                                            const bool steps)
{
    std::stringstream ss;

    if (steps)
    {
        ss << "Comparing the integer part of a and b" << std::endl;
        if (bigger)
        {
            ss << BECAUSE " The integer part of " << a << " is bigger than the integer part of " << b << std::endl;
            ss << THEREFORE " " << a << " is greater than " << b;
        }
        else
        {
            ss << BECAUSE " The integer part of " << b << " is bigger than the integer part of " << a << std::endl;
            ss << THEREFORE " " << a << " is less than " << b;
        }
    }
    else
    {
        if (bigger)
            ss << a << " > " << b;
        else
            ss << a << " < " << b;
    }

    return ss.str();
}

const std::string reportComparisonByDigit(const std::string& a,
                                          const std::string& b,
                                          const unsigned int _digit,
                                          const bool bigger,
                                          const bool steps)
{
    std::stringstream ss;
    int digit = _digit;
    if (not bigger)
        digit = -digit;
    if (steps)
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
    else
    {
        if (bigger)
            ss << a << " > " << b;
        else
            ss << a << " < " << b;
    }

    return ss.str();
}
