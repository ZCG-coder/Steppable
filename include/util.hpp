#pragma once

#include "colors.hpp"

#include <any>
#include <array>
#include <cmath>
#include <iomanip>
#include <map>
#include <string>
#include <vector>

#ifndef TIC
#define TIC(...)                                                                                          \
    {                                                                                                     \
        const char* nameSection = #__VA_ARGS__;                                                           \
        std::cout << BRIGHT_BLUE << std::setw(80) << std::setfill('-') << '\0';                           \
        std::cout << std::endl << BRIGHT_BLUE "[Profiling: " << nameSection << ']' << RESET << std::endl; \
        auto start = std::chrono::high_resolution_clock::now();
#endif

#ifndef TOC
#define TOC()                                                                                                    \
    auto duration =                                                                                              \
        std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start) \
            .count();                                                                                            \
    std::cout << BRIGHT_BLUE << '[' << nameSection << " took " << duration << "(microseconds) to execute]"       \
              << std::endl;                                                                                      \
    std::cout << BRIGHT_BLUE << std::setw(80) << std::setfill('-') << '\0';                                      \
    std::cout << RESET << std::endl;                                                                             \
    }
#endif

inline bool isZeroString(std::string string)
{
    for (char c : string)
        if (c != '0')
            return false;
    return true;
}

template<typename NumberT>
constexpr inline NumberT abs(NumberT number)
{
    if (number < 0)
        return -number;
    return number;
}

inline constexpr bool isNumber(const std::string& s)
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

template<typename CharT>
std::vector<std::basic_string<CharT>> split(std::basic_string<CharT> s, CharT separator);

std::array<std::string, 4> splitNumber(std::string a, std::string b, bool padInteger = true, bool padDecimal = true);

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
