#pragma once

#include "colors.hpp"

#include <any>
#include <array>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <map>
#include <string>
#include <string_view>
#include <vector>

#ifndef TIC
/// FMCRO: TIC
/// DESC : Start a timer to measure the time it takes to execute a section of code.
#define TIC(...)                                                                                             \
    {                                                                                                        \
        const char* nameSection = #__VA_ARGS__;                                                              \
        std::cout << colors::brightBlue << std::setw(80) << std::setfill('-') << '\0' << reset << std::endl; \
        std::cout << colors::brightBlue << "[Profiling: " << nameSection << ']' << reset << std::endl;       \
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
    std::cout << colors::brightBlue << std::setw(80) << std::setfill('-') << '\0';                                \
    std::cout << reset << std::endl;                                                                              \
    }
#endif

/// INFN : isZeroString
/// OUT  : bool
/// IN   : std::string string - The string to check.
/// DESC : Check if a string is a zero string.
constexpr inline bool isZeroString(std::string_view string)
{
    for (char c : string)
        if (c != '0')
            return false;
    return true;
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
std::vector<std::basic_string<CharT>> split(std::basic_string<CharT> s, CharT separator);

template<typename CharT>
std::vector<std::basic_string_view<CharT>> split(std::basic_string_view<CharT> s, CharT separator);

std::array<std::string, 4> splitNumber(const std::string_view& a,
                                       const std::string_view& b,
                                       const bool padInteger = true,
                                       const bool padDecimal = true);

/// Trim from end of string (right)
template<typename CharT>
inline auto rReplace(std::basic_string<CharT>& s, const CharT t, const CharT replacement = '\0') -> decltype(s)
{
    typename std::basic_string<CharT>::size_type count = 0;
    while (s.back() == t)
    {
        s.pop_back();
        count++;
    }
    s += std::basic_string<CharT>(count, replacement);
    return s;
}

/// Trim from beginning of string (left)
template<typename CharT>
inline auto lReplace(std::basic_string<CharT>& s, const CharT t, const CharT replacement = '\0') -> decltype(s)
{
    typename std::basic_string<CharT>::size_type count = 0;
    while (s[0] == t)
    {
        s.erase(s.begin());
        count++;
    }
    s = std::basic_string<CharT>(count, replacement) + s;
    return s;
}

/// Trim from both ends of string (right then left)
template<typename CharT>
inline auto replace(std::basic_string<CharT>& s, const CharT t, const CharT replacement = '\0') -> decltype(s)
{
    return lReplace(rReplace(s, t, replacement), t, replacement);
}

std::string makeWider(const std::string& orig);

[[maybe_unused]] int utf8_to_unicode(const std::string& utf8_code);

std::string unicode_to_utf8(int unicode);
