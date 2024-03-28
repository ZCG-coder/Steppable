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

#include "fn/basicArithm.hpp"

#ifdef WINDOWS
    #undef min
    #undef max
#endif

#include <algorithm>
#include <array>
#include <sstream>
#include <string>
#include <vector>

std::string simplifyZeroPolarity(const std::string_view& string)
{
    // Check if the string is zero
    if (isZeroString(string))
        return "0";
    return static_cast<std::string>(string);
}

std::string simplifyPolarity(const std::string_view& _string)
{
    auto string = simplifyZeroPolarity(_string);
    while (string[0] == '-' and string[1] == '-')
        string = string.substr(2);
    return string;
}

std::string standardizeNumber(const std::string_view& _number)
{
    auto number = simplifyPolarity(_number);
    // Remove the trailing decimal point
    if (number.back() == '.')
        number.pop_back();

    if (number.empty())
        return "0";
    if (number.front() == '+')
        number.erase(0, 1);
    if (number.front() == '.')
        number.insert(0, 1, '0');
    if (number.substr(0, 2) == "-.")
        number.insert(1, 1, '0');
    return number;
}

SplitNumberResult splitNumber(const std::string_view& _a,
                              const std::string_view& _b,
                              const bool padInteger,
                              const bool padDecimal,
                              bool properlyFormat)
{
    bool aIsNegative = false, bIsNegative = false;

    std::string a = static_cast<std::string>(_a), b = static_cast<std::string>(_b);
    if (properlyFormat)
    {
        a = simplifyPolarity(_a), b = simplifyPolarity(_b);
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
    }
    const std::vector<std::string> aParts = split(a, '.'), bParts = split(b, '.');
    auto aInteger = static_cast<std::string>(aParts.front()), aDecimal = static_cast<std::string>(aParts.back()),
         bInteger = static_cast<std::string>(bParts.front()), bDecimal = static_cast<std::string>(bParts.back());
    // If the numbers are integers, discard their decimal points
    if (isZeroString(aDecimal) or aParts.size() == 1)
        aDecimal = "";
    if (isZeroString(bDecimal) or bParts.size() == 1)
        bDecimal = "";
    aInteger = simplifyZeroPolarity(aInteger);
    bInteger = simplifyZeroPolarity(bInteger);
    aDecimal = removeTrailingZeros(aDecimal);
    bDecimal = removeTrailingZeros(bDecimal);

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

std::string roundOff(const std::string& number)
{
    if (number.empty())
        return "0";
    auto num = number;
    if (num.find('.') == std::string::npos)
        return num;
    auto splitNum = split(num, '.');
    auto integer = splitNum[0], decimal = splitNum[1];
    if (compare(decimal, "5", 0) != "1")
        return integer + "." + decimal;
    return add(integer, "1", 0) + "." + decimal;
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
        std::replace_if(out.begin(), firstNonZero, [](const int num) { return num == 0; }, -2);
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

auto removeTrailingZeros(const std::vector<int>& _vector) -> std::decay_t<decltype(_vector)>
{
    std::vector vector = _vector;
    auto i = vector.size() - 1;
    while (vector[i] == 0)
    {
        vector.pop_back();
        i--;
    }
    return vector;
}

auto removeTrailingZeros(const std::string& numStr) -> std::decay_t<decltype(numStr)>
{
    size_t i = numStr.size() - 1;
    while (i > 0 && numStr[i] == '0')
        i--;

    std::string result = numStr.substr(0, i + 1);
    return result;
}

long long determineScale(const std::string_view& number)
{
    auto splitNumberResult = splitNumber(number, "0", false, false).splitNumberArray;
    auto numberInteger = splitNumberResult[0], numberDecimal = splitNumberResult[1];

    // If there is an integer component, determine the scale of it
    if (not isZeroString(numberInteger))
        return static_cast<long long>(numberInteger.length() - 1);

    // If there is no integer component but a decimal one, count the number of zeros preceeding the most significant
    // figure. Scale = -(numberOfZeros + 1)
    // E.g.: 0.1 => 0 leading zeros => scale = -(0 + 1) = -1; 0.0325 => 1 leading zero => scale = -(1 + 1) = -2.
    auto newNumberDecimal = removeLeadingZeros(numberDecimal);
    long long numberOfZeros = static_cast<long long>(numberDecimal.length()) - newNumberDecimal.length();
    return -(numberOfZeros + 1);
}
