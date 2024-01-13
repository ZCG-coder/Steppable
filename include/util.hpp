/**************************************************************************************************
 * Copyright (c) 2024 NWSOFT                                                                      *
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

#pragma once

#include "colors.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#ifndef TIC
    /// FMCRO: TIC
    /// DESC : Start a timer to measure the time it takes to execute a section of code.
    #define TIC(...)                                                                                       \
        {                                                                                                  \
            const char* nameSection = #__VA_ARGS__;                                                        \
            std::cout << colors::brightBlue << std::setw(80) << std::setfill('-') << reset << '\n';   \
            std::cout << colors::brightBlue << "[Profiling: " << nameSection << ']' << reset << '\n'; \
            auto start = std::chrono::high_resolution_clock::now();
#endif

#ifndef TOC
    /// FMCRO: TOC
    /// DESC : Stop the timer and print the time it took to execute the section of code.
    #define TOC()                                                                                                     \
        auto duration =                                                                                               \
            std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start)  \
                .count();                                                                                             \
        std::cout << colors::brightBlue << '[' << nameSection << " took " << duration << "(microseconds) to execute]" \
                  << reset << '\n';                                                                              \
        std::cout << colors::brightBlue << std::setw(80) << std::setfill('-');                                        \
        std::cout << reset << '\n';                                                                              \
        }
#endif

struct SplittedNumber
{
    std::array<std::string, 4> splittedNumberArray;
    bool aIsNegative, bIsNegative;
};

#ifdef WINDOWS
    #include <Windows.h>
    #include <fcntl.h>

inline DWORD enableVtMode()
{
    // Set output mode to handle virtual terminal sequences
    const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
        return -1;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
        return -1;
    const DWORD dwModeOrig = dwMode;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
        return -1;
    return dwModeOrig;
}

inline bool restoreVtMode(const DWORD dwModeOrig)
{
    const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
        return false;

    if (!SetConsoleMode(hOut, dwModeOrig))
        return false;
    return true;
}

class Utf8CodePage
{
public:
    Utf8CodePage() : oldCodePage(::GetConsoleOutputCP())
    {
        ::SetConsoleOutputCP(CP_UTF8);
        dwModeOrig = enableVtMode();
    }

    ~Utf8CodePage()
    {
        ::SetConsoleOutputCP(oldCodePage);
        restoreVtMode(dwModeOrig);
    }

private:
    UINT oldCodePage;

    DWORD dwModeOrig;
};
#else
class Utf8CodePage
{
};
#endif

/// INFN : isZeroString
/// OUT  : bool
/// IN   : std::string string - The string to check.
/// DESC : Check if a string is a zero string.
constexpr bool isZeroString(const std::string_view& string)
{
    return std::ranges::all_of(string, [](const char c) { return c == '0'; });
}

/// INFN : isZeroString
/// OUT  : bool
/// IN   : std::string string - The string to check.
/// DESC : Check if a string represents a number.
constexpr bool isNumber(const std::string_view& s)
{
    if (s.empty())
        return false;
    int decimalPointCount = 0, minusCount = 0;
    
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
        else if (not isdigit(c))
            return false;
    }
    return true;
}

/// INFN : isZeroString
/// OUT  : bool
/// IN   : std::string string - The string to check.
/// DESC : Check if a string is a zero string.
template<typename CharT>
auto split(std::basic_string<CharT> s, const CharT separator)
{
    std::vector<decltype(s)> substrings;
    std::basic_stringstream<CharT> ss(s);
    decltype(s) token;

    while (getline(ss, token, separator))
        substrings.push_back(token);

    return substrings;
}

template<typename CharT>
auto split(std::basic_string_view<CharT> s, const CharT separator)
{
    std::vector<decltype(s)> result;
    auto left = s.begin();
    for (auto it = left; it != s.end(); ++it)
    {
        if (*it == separator)
        {
            result.emplace_back(&*left, it - left);
            left = it + 1;
        }
    }
    if (left != s.end())
        result.emplace_back(&*left, s.end() - left);
    return result;
}

SplittedNumber splitNumber(const std::string_view& a,
                           const std::string_view& b,
                           bool padInteger = true,
                           bool padDecimal = true);

/// Trim from end of string (right)
template<typename CharT>
auto rReplace(const std::basic_string<CharT> s, const CharT t, const CharT replacement = '\0')
{
    std::basic_string<CharT> out = s;
    typename std::basic_string<CharT>::size_type count = 0;
    while (out.back() == t)
    {
        out.pop_back();
        ++count;
    }
    if (replacement != '\0')
        out += std::basic_string<CharT>(count, replacement);
    return out;
}

/// Trim from beginning of string (left)
template<typename CharT>
auto lReplace(const std::basic_string<CharT> s, const CharT t, const CharT replacement = '\0')
{
    std::basic_string<CharT> out = s;
    typename std::basic_string<CharT>::size_type count = 0;
    while (out[0] == t)
    {
        out.erase(out.begin());
        ++count;
    }
    if (replacement != '\0')
        out = std::basic_string<CharT>(count, replacement) + out;
    return out;
}

/// Trim from both ends of string (right then left)
template<typename CharT>
auto bothEndsReplace(const std::basic_string<CharT> s, const CharT t, const CharT replacement = '\0')
{
    return lReplace(rReplace(s, t, replacement), t, replacement);
}

auto replaceLeadingZeros(const std::vector<int>& vector) -> std::decay_t<decltype(vector)>;

auto removeLeadingZeros(const std::vector<int>& vector) -> std::decay_t<decltype(vector)>;

auto removeLeadingZeros(const std::string& string) -> std::decay_t<decltype(string)>;

std::string makeWider(const std::string& orig);

[[maybe_unused]] int utf8ToUnicode(const std::string& utf8_code);

std::string unicodeToUtf8(int unicode);
