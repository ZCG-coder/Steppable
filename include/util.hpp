#pragma once

#include "colors.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <iomanip>
#include <string>
#include <string_view>
#include <sstream>
#include <vector>

#ifndef TIC
    /// FMCRO: TIC
    /// DESC : Start a timer to measure the time it takes to execute a section of code.
    #define TIC(...)                                                                                       \
        {                                                                                                  \
            const char* nameSection = #__VA_ARGS__;                                                        \
            std::cout << colors::brightBlue << std::setw(80) << std::setfill('-') << reset << std::endl;   \
            std::cout << colors::brightBlue << "[Profiling: " << nameSection << ']' << reset << std::endl; \
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
                  << reset << std::endl;                                                                              \
        std::cout << colors::brightBlue << std::setw(80) << std::setfill('-');                                        \
        std::cout << reset << std::endl;                                                                              \
        }
#endif

#ifdef WINDOWS
    #include <Windows.h>
    #include <fcntl.h>
    #include <io.h>

inline DWORD EnableVTMode()
{
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
        return -1;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
        return -1;
    DWORD dwModeOrig = dwMode;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
        return -1;
    return dwModeOrig;
}

inline bool RestoreVTMode(DWORD dwModeOrig)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
        return false;

    if (!SetConsoleMode(hOut, dwModeOrig))
        return false;
    return true;
}

class UTF8CodePage
{
public:
    UTF8CodePage() : oldCodePage(::GetConsoleOutputCP())
    {
        ::SetConsoleOutputCP(CP_UTF8);
        dwModeOrig = EnableVTMode();
    }

    ~UTF8CodePage()
    {
        ::SetConsoleOutputCP(oldCodePage);
        RestoreVTMode(dwModeOrig);
    }

private:
    UINT oldCodePage;

    DWORD dwModeOrig;
};
#else
class UTF8CodePage
{
};
#endif

/// INFN : isZeroString
/// OUT  : bool
/// IN   : std::string string - The string to check.
/// DESC : Check if a string is a zero string.
constexpr inline bool isZeroString(std::string_view string)
{
    return std::all_of(string.begin(), string.end(), [](char c) { return c == '0'; });
}

/// INFN : isZeroString
/// OUT  : bool
/// IN   : std::string string - The string to check.
/// DESC : Check if a string represents a number.
constexpr inline bool isNumber(const std::string_view& s)
{
    if (s.empty())
        return false;
    int decimalPointCount = 0;
    for (char c : s)
    {
        if (c == '.')
        {
            if (decimalPointCount > 0)
                return false;
            decimalPointCount++;
            continue;
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
std::vector<std::basic_string<CharT>> split(std::basic_string<CharT> s, CharT separator)
{
    std::vector<std::string> substrings;
    std::stringstream ss(s);
    std::string token;

    while (getline(ss, token, separator))
        substrings.push_back(token);

    return substrings;
}

template<typename CharT>
std::vector<std::basic_string_view<CharT>> split(std::basic_string_view<CharT> s, CharT separator)
{
    std::vector<std::basic_string_view<CharT>> result;
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

std::array<std::string, 4> splitNumber(const std::string_view& a,
                                       const std::string_view& b,
                                       bool padInteger = true,
                                       bool padDecimal = true);

/// Trim from end of string (right)
template<typename CharT>
inline auto rReplace(const std::basic_string<CharT> s, const CharT t, const CharT replacement = '\0') -> decltype(s)
{
    std::basic_string<CharT> out = s;
    typename std::basic_string<CharT>::size_type count = 0;
    while (out.back() == t)
    {
        out.pop_back();
        count++;
    }
    if (replacement != '\0')
        out += std::basic_string<CharT>(count, replacement);
    return out;
}

/// Trim from beginning of string (left)
template<typename CharT>
inline auto lReplace(const std::basic_string<CharT> s, const CharT t, const CharT replacement = '\0') -> decltype(s)
{
    std::basic_string<CharT> out = s;
    typename std::basic_string<CharT>::size_type count = 0;
    while (out[0] == t)
    {
        out.erase(out.begin());
        count++;
    }
    if (replacement != '\0')
        out = std::basic_string<CharT>(count, replacement) + out;
    return out;
}

/// Trim from both ends of string (right then left)
template<typename CharT>
inline auto bothEndsReplace(const std::basic_string<CharT> s, const CharT t, const CharT replacement = '\0')
    -> decltype(s)
{
    return lReplace(rReplace(s, t, replacement), t, replacement);
}

auto removeLeadingZeros(const std::vector<int> vector) -> decltype(vector);

std::string makeWider(const std::string& orig);

[[maybe_unused]] int utf8ToUnicode(const std::string& utf8_code);

std::string unicodeToUtf8(int unicode);
