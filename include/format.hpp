#pragma once

#include <cstdarg>
#include <string>
#include <vector>

// https://stackoverflow.com/a/49812356/14868780
template<typename CharT>
std::basic_string<CharT> vFormat(const std::basic_string<CharT> sFormat, ...)
{
    const CharT* const zcFormat = sFormat.c_str();

    // Initialize a variable argument array
    va_list vaArgs;
    va_start(vaArgs, sFormat);

    // Reliably acquire the size from a copy of the variable argument array
    // and a functionally reliable call to mock the formatting
    va_list vaCopy;
    va_copy(vaCopy, vaArgs);
    const int iLen = std::vsnprintf(nullptr, 0, zcFormat, vaCopy);
    va_end(vaCopy);

    // Return a formatted string without risking memory mismanagement
    // and without assuming any compiler or platform specific behavior
    std::vector<CharT> zc(iLen + 1);
    std::vsnprintf(zc.data(), zc.size(), zcFormat, vaArgs);
    va_end(vaArgs);
    return std::string(zc.data(), zc.size());
}

template<typename CharT>
std::basic_string<CharT> vFormat(const CharT* sFormat, ...)
{
    const CharT* const zcFormat = sFormat;

    va_list vaArgs;
    va_start(vaArgs, sFormat);

    va_list vaCopy;
    va_copy(vaCopy, vaArgs);
    const int iLen = std::vsnprintf(nullptr, 0, zcFormat, vaCopy); // NOLINT(clang-diagnostic-format-nonliteral)
    va_end(vaCopy);

    std::vector<CharT> zc(iLen + 1);
    static_cast<void>(
        std::vsnprintf(zc.data(), zc.size(), zcFormat, vaArgs)); // NOLINT(clang-diagnostic-format-nonliteral)
    va_end(vaArgs);
    return std::string(zc.data(), zc.size());
}
