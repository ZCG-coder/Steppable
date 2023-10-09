#include "util.hpp"

#include "colors.hpp"

#include <algorithm>
#include <any>
#include <array>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

template<typename CharT>
std::vector<std::basic_string<CharT>> split(std::basic_string<CharT> s, CharT separator)
{
    std::vector<std::string> substrings;
    std::stringstream ss(s);
    std::string token;

    while (getline(ss, token, separator))
        substrings.push_back(token);

    return substrings;
}

std::array<std::string, 4> splitNumber(std::string a, std::string b, bool padInteger, bool padDecimal)
{
    std::vector<std::string> aParts = split(a, '.'), bParts = split(b, '.');
    std::string aInteger = aParts.front(), aDecimal = aParts.back(), bInteger = bParts.front(),
                bDecimal = bParts.back();
    // If the numbers are integers, discard their decimal points
    if (isZeroString(aDecimal) or aParts.size() == 1)
        aDecimal = "";
    if (isZeroString(bDecimal) or bParts.size() == 1)
        bDecimal = "";

    // Pad with zeros
    if (padInteger)
    {
        int diffLengthInteger = aInteger.length() - bInteger.length();

        if (diffLengthInteger > 0)
            bInteger.insert(0, diffLengthInteger, ' ');
        else
            aInteger.insert(0, -diffLengthInteger, ' ');
    }
    if (padDecimal)
    {
        int diffLengthDecimal = aDecimal.length() - bDecimal.length();

        if (diffLengthDecimal > 0)
            bDecimal += std::string(diffLengthDecimal, '0');
        else
            aDecimal += std::string(-diffLengthDecimal, '0');
    }
    return { aInteger, aDecimal, bInteger, bDecimal };
}
