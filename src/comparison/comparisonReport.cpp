#include "comparisonReport.hpp"

#include "symbols.hpp"

#include <sstream>
#include <string>

const std::string reportComparisonAtInteger(const std::string& a, const std::string& b, const bool bigger)
{
    std::stringstream ss;
    ss << "Comparing the integer part of a and b" << std::endl;
    if (bigger)
    {
        ss << BECAUSE " The integer part of " << a << " is bigger than the integer part of " << b << std::endl;
        ss << "Therefore, " << a + " > " + b << std::endl;
    }
    else
    {
        ss << BECAUSE " The integer part of " << b << " is bigger than the integer part of " << a << std::endl;
        ss << b + " > " + a << std::endl;
    }

    return std::move(ss.str());
}

const std::string reportComparisonByDigit(const std::string& a,
                                          const std::string& b,
                                          const unsigned int _digit,
                                          const bool bigger)
{
    std::stringstream ss;
    int digit = _digit;
    if (not bigger)
        digit = -digit;
    ss << "a = " << a << std::endl;
    ss << "b = " << b << std::endl;

    if (bigger)
    {
        ss << std::string(digit + 4, ' ') << "^~~~~ " BECAUSE " At digit " << digit + 1 << ", " << a[digit]
           << " is bigger than " << b[digit] << std::endl;
        ss << THEREFORE " " << a << " is bigger than " << b;
    }
    else
    {
        ss << std::string(digit + 4, ' ') << "^~~~~ " BECAUSE " At digit " << digit + 1 << ", " << b[digit]
           << " is bigger than " << a[digit] << std::endl;
        ss << THEREFORE " " << b << " is bigger than " << a;
    }

    return std::move(ss.str());
}
