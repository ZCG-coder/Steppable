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

/**
 * @file util.hpp
 * @brief This file contains utility functions and macros for the Steppable project.
 *
 * The functions and macros in this file provide various utility functionalities such as profiling code execution time,
 * string manipulation, and Unicode conversion. It also includes a structure for storing split numbers and a class for
 * handling UTF-8 code page settings.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 */

#pragma once

#include "colors.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <locale.h>
#include <locale>
#include <sstream>
#include <string>
#include <vector>

#ifndef TIC
    /**
     * @brief Starts a timer for profiling code execution time.
     * @param[in] ... The name of the section to profile.
     */
    #define TIC(...)                                                                                  \
        {                                                                                             \
            const char* nameSection = #__VA_ARGS__;                                                   \
            std::cout << colors::brightBlue << std::setw(80) << std::setfill('-') << reset << '\n';   \
            std::cout << colors::brightBlue << "[Profiling: " << nameSection << ']' << reset << '\n'; \
            auto start = std::chrono::high_resolution_clock::now();
#endif

#ifndef TOC
    /// @brief Stops the timer and prints the time taken to execute the section.
    #define TOC()                                                                                                     \
        auto duration =                                                                                               \
            std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start)  \
                .count();                                                                                             \
        std::cout << colors::brightBlue << '[' << nameSection << " took " << duration << "(microseconds) to execute]" \
                  << reset << '\n';                                                                                   \
        std::cout << colors::brightBlue << std::setw(80) << std::setfill('-');                                        \
        std::cout << reset << '\n';                                                                                   \
        }
#endif

namespace steppable::__internals::utils
{
#ifndef MS_STDLIB_BUGS
    #if (_MSC_VER || __MINGW32__ || __MSVCRT__)
        #define MS_STDLIB_BUGS 1
    #else
        #define MS_STDLIB_BUGS 0
    #endif
#endif

#if MS_STDLIB_BUGS
    #include <fcntl.h>
    #include <io.h>
#endif

    void initLocale();
#ifdef WINDOWS
    #include <fcntl.h>
    #include <windows.h>

    /**
     * @brief Enables VT mode.
     *
     * @return The result code indicating the success or failure of enabling VT mode.
     */
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

    /**
     * @brief Restores the VT mode to the original mode.
     *
     * @param[in] dwModeOrig The original mode to restore.
     * @return true if the VT mode is successfully restored, false otherwise.
     */
    inline bool restoreVtMode(const DWORD dwModeOrig)
    {
        const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE)
            return false;

        if (!SetConsoleMode(hOut, dwModeOrig))
            return false;
        return true;
    }

    /**
     * @class Utf8CodePage
     * @brief A class that sets the console output code page to UTF-8 and enables VT mode.
     *
     * This class is responsible for setting the console output code page to UTF-8 and enabling VT mode.
     * It automatically restores the original code page and VT mode when the object is destroyed.
     */
    class Utf8CodePage
    {
    public:
        /**
         * @brief Constructs a Utf8CodePage object.
         *
         * This constructor sets the console output code page to UTF-8 and enables VT mode.
         * It also saves the original code page and VT mode for restoration later.
         */
        Utf8CodePage() : oldCodePage(GetConsoleOutputCP())
        {
            initLocale();
            SetConsoleOutputCP(CP_UTF8);
            dwModeOrig = enableVtMode();
        }

        /**
         * @brief Destroys the Utf8CodePage object.
         *
         * This destructor restores the original code page and VT mode.
         */
        ~Utf8CodePage()
        {
            SetConsoleOutputCP(oldCodePage);
            restoreVtMode(dwModeOrig);
        }

    private:
        UINT oldCodePage; ///< The original console output code page.
        DWORD dwModeOrig; ///< The original VT mode.
    };
#else

    /**
     * @class Utf8CodePage
     * @brief A class that sets the console output code page to UTF-8 and enables VT mode.
     *
     * This class is responsible for setting the console output code page to UTF-8 and enabling VT mode.
     * It automatically restores the original code page and VT mode when the object is destroyed.
     */
    class Utf8CodePage
    {
    public:
        Utf8CodePage() { initLocale(); }
    };
#endif
} // namespace steppable::__internals::utils

namespace steppable::__internals::numUtils
{
    /**
     * @struct SplitNumberResult
     * @brief A structure for storing split numbers.
     *
     * This structure is used to store the result of splitting two numbers.
     * It contains the split numbers as strings, as well as flags indicating whether the numbers are negative.
     */
    struct SplitNumberResult
    {
        std::array<std::string, 4> splitNumberArray;
        bool aIsNegative = false, bIsNegative = false;
    };

    /**
     * @brief Simplifies a string that represents a number with non-standard polarity.
     *
     * This function takes a string that represents a number with a zero polarity and simplifies it to a standard
     * polarity. E.g. "-0" is simplified to "0".
     *
     * @param[in] string The input string to be simplified.
     * @return A simplified string with standard polarity.
     */
    std::string simplifyZeroPolarity(const std::string_view& string);

    /**
     * @brief Simplifies a string with non-standard polarity (e.g., --1, ---1, etc.).
     * @param[in] _string A string to simplify.
     * @return A simplified string with correct polarity.
     */
    std::string simplifyPolarity(const std::string_view& _string);

    /**
     * @brief Standardizes a number string.
     *
     * @param[in] _number The number string to standardize.
     * @return The standardized number string.
     */
    std::string standardizeNumber(const std::string_view& _number);

    /**
     * @fn constexpr bool isZeroString(const std::string_view& string)
     * @brief Checks if a given string is a zero string.
     *
     * A zero string is defined as a string that contains only the character '0'.
     *
     * @param[in] string The string to check.
     * @return True if the string is a zero string, false otherwise.
     */
    constexpr bool isZeroString(const std::string_view& string)
    {
        return std::ranges::all_of(string, [](const char c) { return c == '0' or c == '.' or c == '-'; });
    }

    /**
     * @brief Checks if a given string is a valid number.
     *
     * @param[in] s The string to be checked.
     * @return True if the string is a valid number, false otherwise.
     */
    bool isNumber(const std::string_view& s);

    /**
     * Splits two numbers represented as strings and returns the result.
     *
     * @param[in] a The first number as a string.
     * @param[in] b The second number as a string.
     * @param[in] padInteger Flag indicating whether to pad the integer part with spaces of the result.
     * @param[in] padDecimal Flag indicating whether to pad the decimal part with zeros of the result.
     * @param[in] properlyFormat
     * @return The result of splitting the two numbers.
     *
     * @see SplitNumberResult
     */
    SplitNumberResult splitNumber(const std::string_view& a,
                                  const std::string_view& b,
                                  bool padInteger = true,
                                  bool padDecimal = true,
                                  bool properlyFormat = true,
                                  bool preserveNegative = false);

    /**
     * Replaces leading zeros in the given vector with -2.
     *
     * @param[in] vector The vector to modify.
     * @return The modified vector with leading zeros replaced.
     */
    auto replaceLeadingZeros(const std::vector<int>& vector) -> std::decay_t<decltype(vector)>;

    /**
     * Removes leading zeros from a vector of integers.
     *
     * @param[in] vector The input vector.
     * @return The vector with leading zeros removed.
     */
    auto removeLeadingZeros(const std::vector<int>& vector) -> std::decay_t<decltype(vector)>;

    /**
     * Removes leading zeros from a string.
     *
     * @param[in] string The input string.
     * @return The string with leading zeros removed.
     */
    auto removeLeadingZeros(const std::string& string) -> std::decay_t<decltype(string)>;

    /**
     * Removes trailing zeros from a vector of integers.
     *
     * @param[in] _vector The input vector.
     * @return The vector with trailing zeros removed.
     */
    auto removeTrailingZeros(const std::vector<int>& _vector) -> std::decay_t<decltype(_vector)>;

    /**
     * Removes trailing zeros from a string.
     *
     * @param[in] numStr The input string.
     * @return The string with trailing zeros removed.
     */
    auto removeTrailingZeros(const std::string& numStr) -> std::decay_t<decltype(numStr)>;

    /**
     * @brief Determines the scale of a number, i.e., the power of 10 when it is expressed in
     * scientific notation.
     * @param[in] number The number to be processed.
     * @return The scale of the number
     */
    long long determineScale(const std::string_view& number);

    /**
     * @brief Determines whether the number is an integer or not.
     *
     * @param number The number.
     * @return True if it is an integer, false otherwise.
     */
    bool isInteger(const std::string& number);

    /**
     * @brief Determines whether the number is a decimal or not.
     *
     * @param number The number.
     * @return False if it is an integer, true otherwise.
     */
    bool isDecimal(const std::string& number);

    /**
     * @brief Determines whether the number is a power of 10.
     *
     * @param number The number.
     * @return True if it is a power of 10, false otherwise.
     */
    bool isPowerOfTen(const std::string& number);
} // namespace steppable::__internals::numUtils

namespace steppable::__internals::stringUtils
{
    /**
     * @brief Splits a string into substrings based on a separator.
     *
     * @param[in] s The string to be split.
     * @param[in] separator The separator to split the string by.
     * @return A vector of substrings.
     */
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

    /**
     * @brief Splits a string view into substrings based on a separator.
     *
     * @param[in] s The string view to be split.
     * @param[in] separator The separator to split the string view by.
     * @return A vector of substrings.
     */
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

    /**
     * @brief Replaces the trailing occurrences of a character in a string with another character.
     *
     * This function takes a string `s` and replaces all trailing occurrences of the character `t` with the character
     * `replacement`. If `replacement` is not provided, the trailing occurrences of `t` are simply removed.
     *
     * @tparam CharT The character type of the string.
     * @param[in] s The input string.
     * @param[in] t The character to be replaced.
     * @param[in] replacement The character to replace `t` with. Default is '\0' (null character).
     * @return The modified string with trailing occurrences of `t` replaced by `replacement`.
     *
     * @see lReplace
     */
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

    /**
     * @brief Replaces the leading occurrences of a character in a string with a replacement character.
     *
     * @tparam CharT The character type of the string.
     * @param[in] s The input string.
     * @param[in] t The character to be replaced.
     * @param[in] replacement The replacement character (default is '\0').
     * @return The modified string with leading occurrences replaced.
     *
     * @see rReplace
     */
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

    /**
     * @brief Replaces the leading and trailing occurrences of a character in a string with a replacement character.
     *
     * @tparam CharT The character type of the string.
     * @param[in] s The input string.
     * @param[in] t The character to be replaced.
     * @param[in] replacement The replacement character (default is '\0').
     * @return The modified string with leading and trailing occurrences replaced.
     *
     * @note This function is equivalent to calling `lReplace(rReplace(s, t, replacement), t, replacement)`.
     *
     * @see lReplace
     * @see rReplace
     */
    template<typename CharT>
    auto bothEndsReplace(const std::basic_string<CharT> s, const CharT t, const CharT replacement = '\0')
    {
        return lReplace(rReplace(s, t, replacement), t, replacement);
    }

    /**
     * @brief Joins a vector of elements into a single string using a delimiter.
     *
     * @tparam T The type of the vector elements.
     * @param[in] vector The vector of strings to join.
     * @param[in] delimiter The delimiter to join the strings with.
     * @return The joined string.
     */
    template<typename T>
    auto join(const std::vector<T>& vector, const std::string& delimiter)
    {
        std::stringstream result;
        for (const auto& item : vector)
            result << item << delimiter;
        return result.str();
    }

    /**
     * @brief Makes the given string wider by adding 2 spaces between each character.
     *
     * @param[in] orig The original string.
     * @return The widened string.
     */
    std::string makeWider(const std::string& orig);

    /**
     * @brief Converts a UTF-8 encoded string to a Unicode string.
     *
     * @param[in] utf8_code The UTF-8 encoded string to convert.
     * @return The converted Unicode string.
     */
    [[maybe_unused]] int utf8ToUnicode(const std::string& utf8_code);

    /**
     * @brief Converts a Unicode character to UTF-8 encoding.
     *
     * @param[in] unicode The Unicode character to be converted.
     * @return The UTF-8 encoded string representation of the Unicode character.
     *
     * @note When output goes wrong, make sure to call this function when printing!
     * @see Utf8CodePage
     */
    std::string unicodeToUtf8(int unicode);
} // namespace steppable::__internals::stringUtils
