#include "util.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

std::array<std::string, 4> splitNumber(const std::string_view& a,
                                       const std::string_view& b,
                                       const bool padInteger,
                                       const bool padDecimal)
{
    std::vector<std::string_view> aParts = split(a, '.'), bParts = split(b, '.');
    std::string aInteger = static_cast<std::string>(aParts.front()), aDecimal = static_cast<std::string>(aParts.back()),
                bInteger = static_cast<std::string>(bParts.front()), bDecimal = static_cast<std::string>(bParts.back());
    // If the numbers are integers, discard their decimal points
    if (isZeroString(aDecimal) or aParts.size() == 1)
        aDecimal = "";
    if (isZeroString(bDecimal) or bParts.size() == 1)
        bDecimal = "";

    // Pad with zeros
    if (padInteger)
    {
        auto diffLengthInteger = aInteger.length() - bInteger.length();

        if (diffLengthInteger > 0)
            bInteger.insert(0, diffLengthInteger, ' ');
        else
            aInteger.insert(0, -diffLengthInteger, ' ');
    }
    if (padDecimal)
    {
        auto diffLengthDecimal = aDecimal.length() - bDecimal.length();

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

[[maybe_unused]] int utf8_to_unicode(const std::string& utf8_code)
{
    unsigned utf8_size = utf8_code.length();
    int unicode = 0;

    for (unsigned p = 0; p < utf8_size; ++p)
    {
        auto bit_count = (p ? 6 : 8 - utf8_size - (utf8_size == 1 ? 0 : 1)),
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
            if (k < 6)
                c2 |= (unicode % 64) & (1 << k);
            else
                c1 |= (unicode >> 6) & (1 << (k - 6));

        s = static_cast<char>(c1);
        s += static_cast<char>(c2);

        return s;
    }
    else if (unicode <= 0xffff) // 0xFFFF(16) = 65535(10)
    {
        unsigned char c1 = 224, c2 = 128, c3 = 128;

        for (int k = 0; k < 16; ++k)
            if (k < 6)
                c3 |= (unicode % 64) & (1 << k);
            else if (k < 12)
                c2 |= (unicode >> 6) & (1 << (k - 6));
            else
                c1 |= (unicode >> 12) & (1 << (k - 12));

        s = static_cast<char>(c1);
        s += static_cast<char>(c2);
        s += static_cast<char>(c3);

        return s;
    }
    else if (unicode <= 0x1fffff) // 1 * 0xFFFFF(16) = 2097151(10)
    {
        unsigned char c1 = 240, c2 = 128, c3 = 128, c4 = 128;

        for (int k = 0; k < 21; ++k)
            if (k < 6)
                c4 |= (unicode % 64) & (1 << k);
            else if (k < 12)
                c3 |= (unicode >> 6) & (1 << (k - 6));
            else if (k < 18)
                c2 |= (unicode >> 12) & (1 << (k - 12));
            else
                c1 |= (unicode >> 18) & (1 << (k - 18));

        s = static_cast<char>(c1);
        s += static_cast<char>(c2);
        s += static_cast<char>(c3);
        s += static_cast<char>(c4);

        return s;
    }
    else
        ; // Incorrect unicode (< 0 or > 2147483647)

    return "";
}
