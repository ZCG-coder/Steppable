#include "addReport.hpp"

#include "symbols.hpp"
#include "util.hpp"

#include <sstream>
#include <string>
#include <utility>
#include <vector>

const std::string reportAdd(const std::string& aInteger,
                      const std::string& aDecimal,
                      const std::string& bInteger,
                      const std::string& bDecimal,
                      const bool aIsDecimal,
                      const bool bIsDecimal,
                      const std::vector<int>& sumDigits,
                      const std::vector<bool>& carries,
                      const bool steps)
{
    std::stringstream ss;

    std::string aOut = aInteger, bOut = bInteger;
    if (aIsDecimal)
        aOut += '.' + aDecimal;
    else if (not steps)
        aOut += '\0'; // Don't use the spaced formatting
    if (bIsDecimal)
        bOut += '.' + bDecimal;
    else if (not steps)
        bOut += '\0'; // Don't use the spaced formatting

    if (aIsDecimal and not bIsDecimal and steps)
        bOut += std::string(aDecimal.length() + 1, ' ');
    if (bIsDecimal and not aIsDecimal and steps)
        aOut += std::string(bDecimal.length() + 1, ' ');

    if (steps)
    {
        ss << "      "; // Reserve space for the plus
        if (bOut.length() > aOut.length())
            ss << std::string(bOut.length() - aOut.length(), ' ');
        for (char aChar : aOut)
            ss << aChar << "  ";

        ss << std::endl << "+     "; // Print an add sign before printing b
        if (aOut.length() > bOut.length())
            ss << std::string(aOut.length() - bOut.length(), ' ');
        for (char bChar : bOut)
            ss << bChar << "  ";

        ss << std::endl << "   ";
        for (bool c : carries)
            if (c)
                ss << "1  ";
            else
                ss << "   ";
        ss << std::endl << std::string(sumDigits.size() * 3 + 6, '_') << std::endl << "      ";

        for (int outputChar : sumDigits)
        {
            if (outputChar == -1)
                ss << ".  ";
            else
                ss << outputChar << "  "; // Two spaces
        }
        ss << std::endl << THEREFORE " ";
    }

    ss << "a + b = ";
    for (auto c : sumDigits)
        if (c == -1)
            ss << '.';
        else
            ss << c;

    return std::move(ss.str());
}
