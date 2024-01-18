/**************************************************************************************************
 * Copyright (c) 2023-2024 NWSOFT                                                                 *
 *                                                                                                *
 * Permission is hereby granted, free of charge, to any person obtaining a copy                   *
 * of this software and associated documentation files (the "Software"), to deal                  *
 * in the Software without restriction, including without limitation the rights                   *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                      *
 * copies of the Software, and to permit persons to whom the Software is                          *
 * furnished to do so, subject to the following conditions:                                       *
 *                                                                                                *
 * The above copyright notice and this permission notice shall be included in all                 *
 * copies or substantial portions of the Software.                                                *
 *                                                                                                *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                     *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                       *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE                    *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                         *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,                  *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE                  *
 * SOFTWARE.                                                                                      *
 **************************************************************************************************/

#include "util.hpp"

#ifdef WINDOWS
#undef min
#undef max
#endif

#include <algorithm>
#include <array>
#include <sstream>
#include <string>
#include <vector>

SplitNumberResult splitNumber(const std::string_view& _a,
                              const std::string_view& _b,
                              const bool padInteger,
                              const bool padDecimal)
{
    auto a = std::string(_a), b = std::string(_b);
    bool aIsNegative = false, bIsNegative = false;
    if (a.front() == '-')
    {
        aIsNegative = true;
        a.erase(a.begin());
    }
    if (b.front() == '-')
    {
        bIsNegative = true;
        b.erase(b.begin());
    }
    a = removeLeadingZeros(a);
    b = removeLeadingZeros(b);
    const std::vector<std::string> aParts = split(a, '.'), bParts = split(b, '.');
    auto aInteger = static_cast<std::string>(aParts.front()), aDecimal = static_cast<std::string>(aParts.back()),
         bInteger = static_cast<std::string>(bParts.front()), bDecimal = static_cast<std::string>(bParts.back());
    // If the numbers are integers, discard their decimal points
    if (isZeroString(aDecimal) or aParts.size() == 1)
        aDecimal = "";
    if (isZeroString(bDecimal) or bParts.size() == 1)
        bDecimal = "";

    // Pad with zeros
    if (padInteger)
    {
        if (const auto diffLengthInteger = static_cast<long>(aInteger.length()) - static_cast<long>(bInteger.length());
            diffLengthInteger > 0)
            bInteger.insert(0, diffLengthInteger, ' ');
        else
            aInteger.insert(0, -diffLengthInteger, ' ');
    }
    if (padDecimal)
    {
        if (const auto diffLengthDecimal = static_cast<long>(aDecimal.length()) - static_cast<long>(bDecimal.length());
            diffLengthDecimal > 0)
            bDecimal += std::string(diffLengthDecimal, '0');
        else
            aDecimal += std::string(-diffLengthDecimal, '0');
    }
    std::array splitNumberResult{ aInteger, aDecimal, bInteger, bDecimal };
    return SplitNumberResult{ splitNumberResult, aIsNegative, bIsNegative };
}

std::string makeWider(const std::string& orig)
{
    if (orig.empty())
        return "";
    std::stringstream out;
    for (const char origChar : orig)
        out << origChar << "  ";
    std::string outStr = out.str();
    outStr.resize(outStr.length() - 2); // Remove the last 2 spaces
    return outStr;
}

[[maybe_unused]] int utf8ToUnicode(const std::string& utf8_code)
{
    const auto utf8_size = utf8_code.length();
    int unicode = 0;

    for (unsigned p = 0; p < utf8_size; ++p)
    {
        const auto bit_count = p ? 6 : 8 - utf8_size - (utf8_size == 1 ? 0 : 1),
                   shift = p < utf8_size - 1 ? 6 * (utf8_size - p - 1) : 0;

        for (size_t k = 0; k < bit_count; ++k)
            unicode += (utf8_code[p] & 1 << k) << shift;
    }

    return unicode;
}

std::string unicodeToUtf8(const int unicode)
{
    std::string s;

    if (unicode >= 0 and unicode <= 0x7f) // 7F(16) = 127(10)
    {
        s = static_cast<char>(unicode);

        return s;
    }
    if (unicode <= 0x7ff) // 7FF(16) = 2047(10)
    {
        unsigned char c1 = 192, c2 = 128;

        for (int k = 0; k < 11; ++k)
            if (k < 6)
                c2 |= unicode % 64 & 1 << k;
            else
                c1 |= unicode >> 6 & 1 << (k - 6);

        s = static_cast<char>(c1);
        s += static_cast<char>(c2);

        return s;
    }
    if (unicode <= 0xffff) // 0xFFFF(16) = 65535(10)
    {
        unsigned char c1 = 224, c2 = 128, c3 = 128;

        for (int k = 0; k < 16; ++k)
            if (k < 6)
                c3 |= unicode % 64 & 1 << k;
            else if (k < 12)
                c2 |= unicode >> 6 & 1 << (k - 6);
            else
                c1 |= unicode >> 12 & 1 << (k - 12);

        s = static_cast<char>(c1);
        s += static_cast<char>(c2);
        s += static_cast<char>(c3);

        return s;
    }
    if (unicode <= 0x1fffff) // 1 * 0xFFFFF(16) = 2097151(10)
    {
        unsigned char c1 = 240, c2 = 128, c3 = 128, c4 = 128;

        for (int k = 0; k < 21; ++k)
            if (k < 6)
                c4 |= unicode % 64 & 1 << k;
            else if (k < 12)
                c3 |= unicode >> 6 & 1 << (k - 6);
            else if (k < 18)
                c2 |= unicode >> 12 & 1 << (k - 12);
            else
                c1 |= unicode >> 18 & 1 << (k - 18);

        s = static_cast<char>(c1);
        s += static_cast<char>(c2);
        s += static_cast<char>(c3);
        s += static_cast<char>(c4);

        return s;
    }
    // Incorrect unicode (< 0 or > 2147483647)

    return "";
}

auto replaceLeadingZeros(const std::vector<int>& vector) -> std::decay_t<decltype(vector)>
{
    auto out = vector;

    // Check if the first element is zero
    if (const auto firstNonZero = std::ranges::find_if(out, [](const int num) { return num != 0; });
        out.begin() != firstNonZero && out.front() == 0)
    {
        std::replace_if(
            out.begin(),
            firstNonZero,
            [](const int num) { return num == 0; },
            -2);
    }

    return out;
}

auto removeLeadingZeros(const std::vector<int>& vector) -> std::decay_t<decltype(vector)>
{
    const auto firstNonZero = std::ranges::find_if(vector, [](const int num) { return num != 0; });

    // Create a new vector with the non-zero elements
    std::vector result(firstNonZero, vector.end());
    return result;
}

auto removeLeadingZeros(const std::string& string) -> std::decay_t<decltype(string)>
{
    if (string == "0")
        return "0";
    auto out = string;
    out.erase(0, std::min(out.find_first_not_of('0'), out.size() - 1));
    return out;
}
