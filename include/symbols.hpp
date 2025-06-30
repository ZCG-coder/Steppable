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

/**
 * @file symbols.hpp
 * @brief This file contains the definitions of various symbols used in the project.
 *
 * The symbols include mathematical operators, subscripts, and superscripts.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 */

#pragma once

#include "colors.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

/**
 * @namespace steppable::prettyPrint
 * @brief The namespace containing utilities for pretty printing.
 */
namespace steppable::prettyPrint
{
    using namespace __internals::utils;

    /**
     * @brief Represents a position in the console.
     */
    struct Position
    {
        long long x = 0;
        long long y = 0;
    };

    // // Not currently in use.
    // enum PrintingAlignment
    // {
    //     BASELINE = 0,
    //     MIDDLE = 1
    // };

    // struct PrintingObj
    // {
    //     std::string str;
    //     PrintingAlignment alignment;
    // };

    enum class HorizontalAlignment : std::uint8_t
    {
        LEFT = 0,
        CENTER = 1,
        RIGHT = 2
    };

    /**
     * @brief Represents a console output buffer.
     */
    class ConsoleOutput
    {
    private:
        /// @brief The current position.
        Position curPos;

        /// @brief The buffer object.
        std::vector<std::vector<std::string>> buffer;

        /// @brief The height of the buffer.
        size_t height = 10;

        /// @brief The width of the buffer.
        size_t width = 10;

        /**
         * @brief Writes a string to the buffer.
         *
         * @param s The string to write.
         * @param pos The position to write to.
         * @param updatePos Whether to update the current position.
         * @param color Color of the text to write.
         */
        void _write(const std::string& s,
                    const Position& pos,
                    bool updatePos = false,
                    const ColorFunc& color = colors::keepOriginal,
                    const HorizontalAlignment& alignment = HorizontalAlignment::LEFT);

    public:
        /**
         * @brief Creates a new console output buffer.
         *
         * @param height The height of the buffer.
         * @param width The width of the buffer.
         */
        ConsoleOutput(size_t height, size_t width);

        /**
         * @brief Writes a character to the buffer.
         *
         * @param c The character to write.
         * @param dLine The change in line.
         * @param dCol The change in column.
         * @param updatePos Whether to update the current position.
         * @param color Color of the text to write.
         */
        void write(char c,
                   long long dLine,
                   long long dCol,
                   bool updatePos = false,
                   const ColorFunc& color = colors::keepOriginal,
                   const HorizontalAlignment& alignment = HorizontalAlignment::LEFT);

        /**
         * @brief Writes a character to the buffer.
         *
         * @param c The character to write.
         * @param pos The position to write to.
         * @param updatePos Whether to update the current position.
         * @param color Color of the text to write.
         */
        void write(char c,
                   const Position& pos,
                   bool updatePos = false,
                   const ColorFunc& color = colors::keepOriginal,
                   const HorizontalAlignment& alignment = HorizontalAlignment::LEFT);

        /**
         * @brief Writes a `string_view` object to the buffer.
         *
         * @param s The string to write.
         * @param pos The position to write to.
         * @param updatePos Whether to update the current position.
         * @param color Color of the text to write.
         */
        void write(const std::string_view& s,
                   const Position& pos,
                   bool updatePos = false,
                   const ColorFunc& color = colors::keepOriginal,
                   const HorizontalAlignment& alignment = HorizontalAlignment::LEFT)
        {
            _write(static_cast<std::string>(s), pos, updatePos, color, alignment);
        }

        /**
         * @brief Gets the buffer as a string.
         * @return The buffer as a string.
         */
        [[nodiscard]] std::string asString() const;
    };

    /**
     * @brief Gets the minimal width needed to print a string.
     *
     * @param s The string.
     * @return The width of the string.
     */
    size_t getStringWidth(const std::string& s);

    /**
     * @brief Gets the minimal height needed to print a string.
     *
     * @param s The string.
     * @return The height of the string.
     */
    size_t getStringHeight(const std::string& s);
} // namespace steppable::prettyPrint

namespace steppable::__internals::stringUtils
{

    /**
     * @brief Checks if a Unicode code point represents a zero-width character.
     *
     * Zero-width characters do not consume display space (e.g., combining marks, zero-width spaces).
     *
     * @param codepoint The Unicode code point to check.
     * @return true if the code point is a zero-width character, false otherwise.
     */
    bool isZeroWidthCharacter(uint32_t codepoint);

    /**
     * @brief Decodes a UTF-8 encoded string into a Unicode code point.
     *
     * This function reads one UTF-8 encoded character from the string, starting at index `i`,
     * and advances the index to the next character.
     *
     * @param str The UTF-8 encoded string.
     * @param i The current position in the string (updated after decoding).
     * @return The Unicode code point of the character at the given position.
     */
    uint32_t getCodepoint(const std::string& str, size_t& i);

    /**
     * @brief Calculates the display width of a UTF-8 encoded string.
     *
     * This function computes the total display width of a string, correctly handling wide, narrow,
     * zero-width, and CJK characters. CJK characters are counted as one character.
     *
     * @param utf8Str The UTF-8 encoded string.
     * @return The total display width of the string.
     */
    size_t getUnicodeDisplayWidth(const std::string& utf8Str);

    bool utf8Decode(const std::string& s, size_t& i, uint32_t& cp);

    bool isEmojiBase(uint32_t cp);

    bool isClusterExtender(uint32_t cp);

    class GraphemeIterator
    {
    public:
        GraphemeIterator(std::string s) : str(std::move(s)) {}

        // Returns false when there are no more clusters
        bool next(std::string& cluster)
        {
            if (pos >= str.size())
                return false;
            size_t start = pos;
            uint32_t cp = 0;
            size_t temp = pos;
            if (!utf8Decode(str, temp, cp))
                return false;

            // For emoji: group sequences with ZWJ or skin tone
            if (isEmojiBase(cp) || (cp >= 0x1F1E6 && cp <= 0x1F1FF))
            {
                pos = temp;
                while (true)
                {
                    size_t save = pos;
                    uint32_t nextcp = 0;
                    if (!utf8Decode(str, save, nextcp))
                        break;
                    if (isClusterExtender(nextcp) ||
                        // For flags: two regional indicators
                        ((cp >= 0x1F1E6 && cp <= 0x1F1FF) && (nextcp >= 0x1F1E6 && nextcp <= 0x1F1FF)))
                    {
                        pos = save;
                    }
                    else
                    {
                        break;
                    }
                }
                cluster = str.substr(start, pos - start);
                return true;
            }

            // For combining marks: group base + following combining
            pos = temp;
            while (true)
            {
                size_t save = pos;
                uint32_t nextcp = 0;
                if (!utf8Decode(str, save, nextcp))
                    break;
                if (isZeroWidthCharacter(nextcp))
                    pos = save;
                else
                    break;
            }
            cluster = str.substr(start, pos - start);
            return true;
        }

    private:
        std::string str;
        size_t pos{};
    };
} // namespace steppable::__internals::stringUtils

/**
 * @namespace steppable::__internals::symbols
 * @brief The namespace containing various unicode symbols.
 *
 * @deprecated This namespace is deprecated and will be removed in the future, as the unicode output is not flexible
 * enough.
 * @warning Usage of this namespace is strongly discouraged. Use the steppable::prettyPrint namespace for basic tools,
 * and implement yours in steppable::prettyPrint::printers.
 */
namespace steppable::__internals::symbols
{
    /// @brief The because symbol (3 dots in a triangle, Unicode U+2235)
    constexpr std::string_view BECAUSE = "\u2235";
    /// @brief The therefore symbol (3 dots in a triangle, Unicode U+2234)
    constexpr std::string_view THEREFORE = "\u2234";

    /// @brief The multiply symbol (Unicode U+00D7)
    constexpr std::string_view MULTIPLY = "\u00D7";
    /// @brief The divide symbol (Unicode U+00F7)
    constexpr std::string_view DIVIDED_BY = "\u00F7";

    constexpr std::string_view SURD = "\u221A";
    constexpr std::string_view COMBINE_MACRON = "\u0305";

    /// @brief The large dot symbol (Unicode U+25C9)
    constexpr std::string_view LARGE_DOT = "\u25C9";
    constexpr std::string_view ABOVE_DOT = "\u02D9";

    // Subscripts
    /**
     * @brief The subscript 0 (Unicode U+2080)
     * @note This is used to check if a subscript is converted correctly, do not use this in the program.
     */
    constexpr std::string_view SUB_0 = "\u2080";
    /**
     * @brief The subscript z (Unicode U+2098)
     * @note This is used to check if a subscript is converted correctly, do not use this in the program.
     */
    constexpr std::string_view SUB_Z = "\u1D69";
    /**
     * @brief The subscript magic number (8272)
     * @note This is used to check if a subscript is converted correctly, do not use this in the program.
     */
    constexpr int SUB_MAGIC_NUMBER = 8272;

    /// @brief A list of subscript characters.
    extern const std::array<std::string, 10>& SUPERSCRIPTS;

    /**
     * @brief Create a subscript string from a normal string.
     *
     * @param[in] normal The normal string.
     * @return The subscript string.
     */
    std::string makeSubscript(const std::string& normal);

    /**
     * @brief Create a subscript string from a normal integer.
     *
     * @param[in] normal The normal integer.
     * @return The subscript string.
     */
    std::string makeSubscript(int normal);

    // Superscripts
    /**
     * @brief The superscript 0 (Unicode U+2070)
     * @note This is used to check if a superscript is converted correctly, do not use this in the program.
     */
    constexpr std::string_view SUP_0 = "\u2070";
    /**
     * @brief The superscript z (Unicode U+1DBB)
     * @note This is used to check if a superscript is converted correctly, do not use this in the program.
     */
    constexpr std::string_view SUP_Z = "\u1DBB";
    /**
     * @brief The superscript magic number (8304)
     * @note This is used to check if a superscript is converted correctly, do not use this in the program.
     */
    constexpr int SUP_MAGIC_NUMBER = 8304;

    /**
     * @brief Create a superscript string from a normal string.
     *
     * @param[in] normal The normal string.
     * @return The superscript string.
     */
    std::string makeSuperscript(const std::string& normal);

    /**
     * @brief Create a superscript string from a normal character.
     *
     * @param[in] normal The normal character.
     * @return The superscript string.
     */
    std::string makeSuperscript(char normal);

    /**
     * @brief Makes a surd expression from a radicand.
     *
     * @param radicand The radicand.
     * @return The surd expression.
     */
    std::string makeSurd(const std::string& radicand);

    namespace BoxDrawing
    {
        constexpr std::string DOTTED_VERTICAL = "\u2575";
        constexpr std::string DOTTED_HORIZONTAL = "\u2574";

        constexpr std::string HORIZONTAL = "\u2500";
        constexpr std::string VERTICAL = "\u2502";

        constexpr std::string HORIZONTAL_UP = "\u2534";
        constexpr std::string VERTICAL_LEFT = "\u2524";

        constexpr std::string BOTTOM_RIGHT_CORNER = "\u2518";

        constexpr std::string CROSS = "\u253C";
    } // namespace BoxDrawing
} // namespace steppable::__internals::symbols

/**
 * @namespace steppable::prettyPrint::printers
 * @brief The custom-implemented printer engines for outputting expressions.
 */
namespace steppable::prettyPrint::printers
{
    /**
     * @brief Pretty print a root expression.
     *
     * @param radicand The radicand.
     * @param index The index.
     * @return The pretty printed root expression.
     */
    std::string ppRoot(const std::string& radicand, const std::string& index = "2");

    /**
     * @brief Pretty print a fraction.
     *
     * @param top The numerator.
     * @param bottom The denominator.
     * @param inLine Whether to print in a single line.
     * @return The pretty printed fraction.
     */
    std::string ppFraction(const std::string& top, const std::string& bottom, bool inLine = false);

    /**
     * @brief Pretty print a base expression, (aka, subscript).
     *
     * @param base The base.
     * @param subscript The subscript.
     * @return The pretty printed base expression.
     */
    std::string ppSubscript(const std::string& base, const std::string& subscript);

    /**
     * @brief Pretty print a power expression, (aka, superscript).
     *
     * @param base The base.
     * @param superscript The exponent.
     * @return The pretty printed power expression.
     */
    std::string ppSuperscript(const std::string& base, const std::string& superscript);
} // namespace steppable::prettyPrint::printers
