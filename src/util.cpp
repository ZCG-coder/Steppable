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

std::string makeWider(const std::string& orig)
{
    std::stringstream out;
    for (char origChar : orig)
        out << origChar << "  ";
    std::string outStr = out.str();
    outStr.resize(outStr.length() - 2); // Remove the last 2 spaces
    return outStr;
}

int utf8_to_unicode(const std::string& utf8_code)
{
    unsigned utf8_size = utf8_code.length();
    int unicode = 0;

    for (unsigned p = 0; p < utf8_size; ++p)
    {
        int bit_count = (p ? 6 : 8 - utf8_size - (utf8_size == 1 ? 0 : 1)),
            shift = (p < utf8_size - 1 ? (6 * (utf8_size - p - 1)) : 0);

        for (int k = 0; k < bit_count; ++k)
            unicode += ((utf8_code[p] & (1 << k)) << shift);
    }

    return unicode;
}

std::string unicode_to_utf8(int unicode)
{
    std::string s;

    if (unicode >= 0 and unicode <= 0x7f) // 7F(16) = 127(10)
    {
        s = static_cast<char>(unicode);

        return s;
    }
    else if (unicode <= 0x7ff) // 7FF(16) = 2047(10)
    {
        unsigned char c1 = 192, c2 = 128;

        for (int k = 0; k < 11; ++k)
        {
            if (k < 6)
                c2 |= (unicode % 64) & (1 << k);
            else
                c1 |= (unicode >> 6) & (1 << (k - 6));
        }

        s = c1;
        s += c2;

        return s;
    }
    else if (unicode <= 0xffff) // FFFF(16) = 65535(10)
    {
        unsigned char c1 = 224, c2 = 128, c3 = 128;

        for (int k = 0; k < 16; ++k)
        {
            if (k < 6)
                c3 |= (unicode % 64) & (1 << k);
            else if (k < 12)
                c2 |= (unicode >> 6) & (1 << (k - 6));
            else
                c1 |= (unicode >> 12) & (1 << (k - 12));
        }

        s = c1;
        s += c2;
        s += c3;

        return s;
    }
    else if (unicode <= 0x1fffff) // 1FFFFF(16) = 2097151(10)
    {
        unsigned char c1 = 240, c2 = 128, c3 = 128, c4 = 128;

        for (int k = 0; k < 21; ++k)
        {
            if (k < 6)
                c4 |= (unicode % 64) & (1 << k);
            else if (k < 12)
                c3 |= (unicode >> 6) & (1 << (k - 6));
            else if (k < 18)
                c2 |= (unicode >> 12) & (1 << (k - 12));
            else
                c1 |= (unicode >> 18) & (1 << (k - 18));
        }

        s = c1;
        s += c2;
        s += c3;
        s += c4;

        return s;
    }
    else if (unicode <= 0x3ffffff) // 3FFFFFF(16) = 67108863(10)
    {
        ; // Actually, there are no 5-bytes unicodes
    }
    else if (unicode <= 0x7fffffff) // 7FFFFFFF(16) = 2147483647(10)
    {
        ; // Actually, there are no 6-bytes unicodes
    }
    else
        ; // Incorrect unicode (< 0 or > 2147483647)

    return "";
}
