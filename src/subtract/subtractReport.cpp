#include "subtractReport.hpp"

#include "symbols.hpp"
#include "util.hpp"

#include <sstream>
#include <string>
#include <utility>
#include <vector>

const std::string reportSubtract(const std::string& aInteger,
                           const std::string& aDecimal,
                           const std::string& bInteger,
                           const std::string& bDecimal,
                           const bool aIsDecimal,
                           const bool bIsDecimal,
                           const std::vector<int>& _diffDigits,
                           const std::vector<int>& borrows,
                           const bool steps)
{
    std::stringstream ss;
    std::string aStr = aInteger + '.' + aDecimal;
    auto diffDigits = _diffDigits;
    if (diffDigits.front() == 0 and not steps)
        diffDigits.erase(diffDigits.begin());
    else if (diffDigits.front() == 0)
        diffDigits[0] = -2;

    std::string aOut = aInteger, bOut = bInteger;
    if (aIsDecimal)
        aOut += '.' + aDecimal;
    if (bIsDecimal)
        bOut += '.' + bDecimal;

    if (aIsDecimal and not bIsDecimal and not steps)
        bOut += std::string(aDecimal.length() + 1, ' ');
    if (not aIsDecimal and bIsDecimal and not steps)
        aOut += std::string(bDecimal.length() + 1, ' ');

    if (steps)
    {
        ss << "      "; // Reserve space for the minus
        for (int i = 0; i < borrows.size(); i++)
        {
            int currentBorrowDigit = borrows[i];
            if (currentBorrowDigit != aStr[i] - '0' and currentBorrowDigit >= 10)
                ss << currentBorrowDigit << ' ';
            else if (currentBorrowDigit != aStr[i] - '0' and currentBorrowDigit < 10 and currentBorrowDigit > 0)
                ss << currentBorrowDigit << "  ";
            else
                ss << "   ";
        }
        ss << std::endl << "      "; // Reserve space for the minus
        for (char aChar : aOut)
            ss << aChar << "  ";

        ss << std::endl << "-     "; // Print a subtract sign before printing b
        if (aOut.length() > bOut.length())
            ss << std::string(aOut.length() - bOut.length(), ' ');
        for (char bChar : bOut)
            ss << bChar << "  ";

        ss << std::endl << std::string(diffDigits.size() * 3 + 6, '_') << std::endl << "      ";

        for (int outputDigit : diffDigits)
        {
            char outputChar = outputDigit + '0';
            if (outputDigit == -1)
                outputChar = '.';
            else if (outputDigit == -2)
                outputChar = ' ';
            ss << outputChar << "  "; // Two spaces
        }
        ss << std::endl << THEREFORE " ";
    }
    ss << aOut << " - " << bOut << " = ";
    for (int outputDigit : diffDigits)
    {
        char outputChar = outputDigit + '0';
        if (outputDigit == -1)
            outputChar = '.';
        else if (outputDigit == -2)
            outputChar = ' ';
        ss << outputChar; // No spaces
    }

    return std::move(ss.str());
}
