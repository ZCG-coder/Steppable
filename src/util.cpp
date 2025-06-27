/**************************************************************************************************
 * Copyright (c) 2023-2025 NWSOFT                                                                 *
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

#include <cstddef>

#ifdef WINDOWS
    #undef min
    #undef max
#endif

#include <algorithm>
#include <array>
#include <sstream>
#include <string>
#include <vector>

using namespace std::literals;

namespace steppable::__internals::numUtils
{
    bool isNumber(const std::string& s)
    {
        if (s.empty())
            return false;
        int decimalPointCount = 0;
        int minusCount = 0;

        for (const char c : s)
        {
            if (c == '.')
            {
                if (decimalPointCount > 0)
                    return false;
                decimalPointCount++;
            }
            else if (c == '-')
            {
                if (minusCount > 0)
                    return false;
                minusCount++;
            }
            else if (isdigit(c) == 0)
                return false;
        }
        return true;
    }

    std::string simplifyZeroPolarity(const std::string& string)
    {
        if (string.empty())
            return "0";
        // Check if the string is zero
        if (isZeroString(string))
            return "0";
        return string;
    }

    std::string simplifyPolarity(const std::string& _string)
    {
        if (_string.empty())
            return "0";

        auto string = _string;
        string = simplifyZeroPolarity(string);
        while (string[0] == '-' and string[1] == '-')
            string = string.substr(2);
        return string;
    }

    std::string standardizeNumber(const std::string& _number)
    {
        if (_number.empty())
            return "0";

        auto number = simplifyPolarity(_number);
        // Remove the trailing decimal point
        if (number.back() == '.')
            number.pop_back();

        if (number.empty())
            return "0";
        if (number == "-")
            return "-0";
        if (number.front() == '+')
            number.erase(0, 1);
        if (number.front() == '.')
            number.insert(0, 1, '0');
        if (number.substr(0, 2) == "-.")
            number.insert(1, 1, '0');
        return number;
    }

    SplitNumberResult splitNumber(const std::string& _a,
                                  const std::string& _b,
                                  const bool padInteger,
                                  const bool padDecimal,
                                  bool properlyFormat,
                                  bool preserveNegative)
    {
        bool aIsNegative = false;
        bool bIsNegative = false;

        auto a = static_cast<std::string>(_a);
        auto b = static_cast<std::string>(_b);
        if (a.front() == '-')
        {
            aIsNegative = true;
            if (not preserveNegative)
                a.erase(a.begin());
        }
        if (b.front() == '-')
        {
            bIsNegative = true;
            if (not preserveNegative)
                b.erase(b.begin());
        }
        const std::vector<std::string> aParts = stringUtils::split(a, '.');
        const std::vector<std::string> bParts = stringUtils::split(b, '.');
        auto aInteger = static_cast<std::string>(aParts.front());
        auto aDecimal = static_cast<std::string>(aParts.back());
        auto bInteger = static_cast<std::string>(bParts.front());
        auto bDecimal = static_cast<std::string>(bParts.back());
        if (properlyFormat)
        {
            // If the numbers are integers, discard their decimal points
            if (isZeroString(aDecimal) or aParts.size() == 1)
                aDecimal = "";
            if (isZeroString(bDecimal) or bParts.size() == 1)
                bDecimal = "";
            aInteger = simplifyZeroPolarity(aInteger);
            bInteger = simplifyZeroPolarity(bInteger);
            aDecimal = removeTrailingZeros(aDecimal);
            bDecimal = removeTrailingZeros(bDecimal);
        }

        // Pad with zeros
        if (padInteger)
        {
            if (const auto diffLengthInteger =
                    static_cast<long>(aInteger.length()) - static_cast<long>(bInteger.length());
                diffLengthInteger > 0)
                bInteger.insert(0, diffLengthInteger, ' ');
            else
                aInteger.insert(0, -diffLengthInteger, ' ');
        }
        if (padDecimal)
        {
            if (const auto diffLengthDecimal =
                    static_cast<long>(aDecimal.length()) - static_cast<long>(bDecimal.length());
                diffLengthDecimal > 0)
                bDecimal += std::string(diffLengthDecimal, '0');
            else
                aDecimal += std::string(-diffLengthDecimal, '0');
        }
        std::array splitNumberResult{ aInteger, aDecimal, bInteger, bDecimal };
        return SplitNumberResult{ .splitNumberArray = splitNumberResult,
                                  .aIsNegative = aIsNegative,
                                  .bIsNegative = bIsNegative };
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
        bool negative = false;
        if (out.front() == '-')
        {
            negative = true;
            out.erase(0, 1);
        }
        // Remove all the leading zeros, EXCEPT the last one.
        while (out.front() == '0' and out.length() > 1)
            out.erase(0, 1);

        if (negative)
            out.insert(0, 1, '-');
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
        if (numStr.empty())
            return "";
        size_t i = numStr.size() - 1;
        while (i > 0 && numStr[i] == '0')
            i--;

        std::string result = numStr.substr(0, i + 1);
        return result;
    }

    long long determineScale(const std::string& number)
    {
        auto splitNumberResult = splitNumber(number, "0", false, false).splitNumberArray;
        const auto& numberInteger = splitNumberResult[0];
        const auto& numberDecimal = splitNumberResult[1];

        // If there is an integer component, determine the scale of it
        if (not isZeroString(numberInteger))
            return static_cast<long long>(numberInteger.length() - 1);

        // If there is no integer component but a decimal one, count the number of zeros preceeding the most significant
        // figure. Scale = -(numberOfZeros + 1)
        // E.g.: 0.1 => 0 leading zeros => scale = -(0 + 1) = -1; 0.0325 => 1 leading zero => scale = -(1 + 1) = -2.
        auto newNumberDecimal = removeLeadingZeros(numberDecimal);

        // NOLINTNEXTLINE(bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions)
        long long numberOfZeros = static_cast<long long>(numberDecimal.length()) - newNumberDecimal.length();
        return -(numberOfZeros + 1);
    }

    bool isInteger(const std::string& number)
    {
        auto splitNumberResult = splitNumber(number, "0", false, false, true).splitNumberArray;
        // If the decimal part is zero, it is an integer.
        return isZeroString(splitNumberResult[1]);
    }

    bool isDecimal(const std::string& number) { return not isInteger(number); }

    bool isPowerOfTen(const std::string& _number)
    {
        auto number = _number;
        if (number.front() == '-')
            number = number.substr(1, number.length() - 1); // Remove negative sign as it does nothing here.
        if (isDecimal(number))
        {
            return not std::ranges::any_of(number.substr(0, number.length() - 1), [](const auto& c) {
                return c != '0' and c != '.';
            }) and number.back() == '1';
        }
        if (number == "1")
            return true; // 1 is a power of 10.
        if (number.front() != '1')
            return false; // The number must start with 1.

        number = number.substr(1, number.length() - 1);
        return not std::ranges::any_of(number, [](const auto& c) { return c != '0' and c != '.'; });
    }

    bool isOdd(const std::string& number)
    {
        if (isDecimal(number))
            return false; // Decimals cannot be classified.
        if (isZeroString(number))
            return false; // Zero is neither even nor odd.

        const char lastDigit = number.back();
        return (lastDigit - '0') % 2 == 1;
    }

    bool isEven(const std::string& number)
    {
        if (isDecimal(number))
            return false; // Decimals cannot be classified.
        if (isZeroString(number))
            return false; // Zero is neither even nor odd.

        return not isOdd(number);
    }
} // namespace steppable::__internals::numUtils

namespace steppable::__internals::stringUtils
{
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
            const auto bit_count = p != 0U ? 6 : 8 - utf8_size - (utf8_size == 1 ? 0 : 1);
            const auto shift = p < utf8_size - 1 ? 6 * (utf8_size - p - 1) : 0;

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
            unsigned char c1 = 192;
            unsigned char c2 = 128;

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
            unsigned char c1 = 224;
            unsigned char c2 = 128;
            unsigned char c3 = 128;

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
            unsigned char c1 = 240;
            unsigned char c2 = 128;
            unsigned char c3 = 128;
            unsigned char c4 = 128;

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
} // namespace steppable::__internals::stringUtils
