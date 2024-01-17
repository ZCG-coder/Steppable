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

/**
 * @file format.hpp
 * @brief This file contains the definition of the vFormat function template.
 *
 * The vFormat function template provides a convenient way to format strings using variable arguments.
 * It supports both C-style format strings and std::basic_string format strings.
 * The formatted string is returned as a std::basic_string object.
 *
 * Example usage:
 * @code
 * std::string formatted = vFormat("Hello, %s!", "world");
 * @endcode
 *
 * @author Andy Zhang
 * @date 27th November 2023
 */

#pragma once

#include <cstdarg>
#include <string>
#include <vector>

// https://stackoverflow.com/a/49812356/14868780
/**
 * @brief Formats a string using a variable number of arguments.
 *
 * This function takes a format string and a variable number of arguments,
 * and returns a formatted string. It uses the same format specifiers as
 * the standard library's `printf` function.
 *
 * @tparam CharT The character type of the string.
 * @param sFormat The format string.
 * @param ... The variable arguments.
 * @return The formatted string.
 */
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

/**
 * @brief Formats a string using a format specifier and variable arguments.
 *
 * This function takes a format specifier and variable arguments, similar to the printf function,
 * and returns a formatted string. The format specifier is a string that may contain placeholders
 * for the variable arguments. The function uses the vsnprintf function to perform the formatting.
 *
 * @tparam CharT The character type of the string.
 * @param sFormat The format specifier string.
 * @param ... The variable arguments.
 * @return The formatted string.
 */
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
