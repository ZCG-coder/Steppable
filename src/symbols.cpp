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

#include "symbols.hpp"

#include "colors.hpp"
#include "util.hpp"

#include <sstream>
#include <string>
#include <vector>

#ifdef WINDOWS
    #undef max
    #undef min
#endif

namespace steppable::prettyPrint
{
    using namespace steppable::__internals::stringUtils;
    using namespace steppable::__internals::utils;

    ConsoleOutput::ConsoleOutput(size_t height, size_t width) : height(height), width(width)
    {
        buffer = std::vector(height, std::vector(width, " "s));
    }

    void ConsoleOutput::write(const std::string& s,
                              const Position& pos,
                              bool updatePos,
                              const ColorFunc& color,
                              const HorizontalAlignment& alignment)
    {
        auto outputString = s;
        switch (alignment)
        {
        case HorizontalAlignment::LEFT:
            break;
        case HorizontalAlignment::CENTER:
            outputString = std::string((width - getUnicodeDisplayWidth(outputString)) / 2, ' ') + outputString;
            break;
        case HorizontalAlignment::RIGHT:
            outputString = std::string(width - getUnicodeDisplayWidth(outputString), ' ') + outputString;
            break;
        }

        Position p = pos;
        if (s == "\n")
        {
            p.y++;
            p.x = pos.x;
            return;
        }
        size_t stringWidth = getUnicodeDisplayWidth(outputString);
        if (stringWidth <= 1)
        {
            std::stringstream ss;
            color(ss);
            ss << outputString << reset;
            buffer[p.y][p.x] = ss.str();
        }
        else
        {
            GraphemeIterator graphemeIterator(outputString);
            std::string cluster;
            size_t i = 0;
            while (graphemeIterator.next(cluster))
            {
                if (cluster == "\n")
                {
                    i = 0;
                    p.y++;
                    p.x = pos.x;
                    continue;
                }
                std::stringstream ss;
                color(ss);
                ss << cluster << reset;
                buffer[p.y][p.x + i] = ss.str();
                i++;
            }
        }

        if (updatePos)
            curPos = p;
    }

    void ConsoleOutput::write(const char c,
                              const long long dLine,
                              const long long dCol,
                              bool updatePos,
                              const ColorFunc& color,
                              const HorizontalAlignment& alignment)
    {
        if (dLine < 0)
        {
            // We need to add extra lines for printing at the very top
            buffer.insert(buffer.begin(), -dLine, std::vector(width, " "s));
            curPos.y = 0;
            height -= dLine;
        }
        if (dCol < 0)
        {
            for (auto& i : buffer)
            {
                std::vector<std::string> vector = i;
                vector.resize(vector.size() - dCol, " "s);
                i = vector;
            }

            curPos.x -= dCol;
            width -= dCol;
        }
        else
            curPos.x += dCol;
        write(c, curPos, updatePos, color, alignment);
    }

    void ConsoleOutput::write(const char c,
                              const Position& pos,
                              bool updatePos,
                              const ColorFunc& color,
                              const HorizontalAlignment& alignment)
    {
        write(std::string(1, c), pos, updatePos, color, alignment);
    }

    std::string ConsoleOutput::asString() const
    {
        std::string res;
        for (const auto& line : buffer)
        {
            for (const auto& c : line)
                res += c;
            res += '\n';
        }
        return res;
    }

    size_t getStringWidth(const std::string& s)
    {
        auto strings = split(s, '\n');
        size_t max = 0;
        for (const auto& string : strings)
            max = std::max(max, getUnicodeDisplayWidth(string));
        return max;
    }

    size_t getStringHeight(const std::string& s) { return split(s, '\n').size(); }
} // namespace steppable::prettyPrint

namespace steppable::__internals::stringUtils
{
    bool isZeroWidthCharacter(uint32_t codepoint)
    {
        return (codepoint >= 0x0300 && codepoint <= 0x036F) || // Combining diacritical marks
               (codepoint >= 0x200B && codepoint <= 0x200F) || // Zero-width space, non-joiners
               (codepoint == 0x2028 || codepoint == 0x2029 ||
                codepoint == 0x202F) || // Line separator, para separator, narrow no-break space
               (codepoint >= 0xFE00 && codepoint <= 0xFE0F) || // Variation selectors
               (codepoint >= 0xE0100 && codepoint <= 0xE01EF); // Supplemental variation selectors
    }

    bool isEmojiBase(uint32_t cp)
    {
        return (cp >= 0x1F600 && cp <= 0x1F64F) || // Emoticons
               (cp >= 0x1F300 && cp <= 0x1F5FF) || // Misc Symbols and Pictographs
               (cp >= 0x1F680 && cp <= 0x1F6FF) || // Transport & Map
               (cp >= 0x1F1E6 && cp <= 0x1F1FF) || // Regional indicators
               (cp >= 0x2600 && cp <= 0x26FF) || // Misc symbols
               (cp >= 0x2700 && cp <= 0x27BF) || // Dingbats
               (cp >= 0x1F900 && cp <= 0x1F9FF) || // Supplemental Symbols and Pictographs
               (cp >= 0x1FA70 && cp <= 0x1FAFF) || (cp == 0x200D); // ZWJ
    }

    bool utf8Decode(const std::string& s, size_t& i, uint32_t& cp)
    {
        if (i >= s.size())
            return false;
        unsigned char c = s[i];
        if (c < 0x80)
        {
            cp = c;
            i += 1;
        }
        else if ((c & 0xE0) == 0xC0 && i + 1 < s.size())
        {
            cp = ((c & 0x1F) << 6) | (s[i + 1] & 0x3F);
            i += 2;
        }
        else if ((c & 0xF0) == 0xE0 && i + 2 < s.size())
        {
            cp = ((c & 0x0F) << 12) | ((s[i + 1] & 0x3F) << 6) | (s[i + 2] & 0x3F);
            i += 3;
        }
        else if ((c & 0xF8) == 0xF0 && i + 3 < s.size())
        {
            cp = ((c & 0x07) << 18) | ((s[i + 1] & 0x3F) << 12) | ((s[i + 2] & 0x3F) << 6) | (s[i + 3] & 0x3F);
            i += 4;
        }
        else
        {
            i += 1;
            cp = 0xFFFD;
        }
        return true;
    }

    bool isClusterExtender(uint32_t cp)
    {
        return (cp >= 0x1F3FB && cp <= 0x1F3FF) || // Skin tone
               (cp == 0x200D) || // ZWJ
               (cp == 0xFE0F) || // VS16
               isZeroWidthCharacter(cp);
    }

    uint32_t getCodepoint(const std::string& str, size_t& i)
    {
        unsigned char c = str[i];
        if (c <= 0x7F) // Single-byte (ASCII)
            return c;
        if ((c & 0xE0) == 0xC0) // Two-byte sequence
            return ((c & 0x1F) << 6) | (str[++i] & 0x3F);
        if ((c & 0xF0) == 0xE0) // Three-byte sequence
        {
            unsigned char byte1 = c & 0x0F;
            unsigned char byte2 = str[++i] & 0x3F;
            unsigned char byte3 = str[++i] & 0x3F;

            return (byte1 << 12) | (byte2 << 6) | byte3;
        }
        if ((c & 0xF8) == 0xF0) // Four-byte sequence
        {
            unsigned char byte1 = (c & 0x07) << 18; // First byte
            unsigned char byte2 = (str[++i] & 0x3F) << 12; // Second byte (increment i)
            unsigned char byte3 = (str[++i] & 0x3F) << 6; // Third byte (increment i)
            unsigned char byte4 = str[++i] & 0x3F; // Fourth byte (increment i)

            return byte1 | byte2 | byte3 | byte4;
        }
        return 0; // Invalid UTF-8
    }

    size_t getUnicodeDisplayWidth(const std::string& utf8Str)
    {
        size_t width = 0;
        size_t len = utf8Str.size();
        for (size_t i = 0; i < len; ++i)
        {
            uint32_t codepoint = getCodepoint(utf8Str, i);

            if (isZeroWidthCharacter(codepoint))
                // Skip zero-width characters
                continue;
            width += 1;
        }

        return width;
    }
} // namespace steppable::__internals::stringUtils

namespace steppable::__internals::symbols
{
    using namespace steppable::__internals::stringUtils;

    // NOLINTNEXTLINE(cert-err58-cpp)
    const std::array<std::string, 10>& SUPERSCRIPTS = { "\u2070", "\u00b9", "\u00b2", "\u00b3", "\u2074",
                                                        "\u2075", "\u2076", "\u2077", "\u2078", "\u2079" };

    [[deprecated("Use steppable::prettyPrint instead")]] std::string makeSubscript(const std::string& normal)
    {
        std::string out;
        for (const char c : normal)
            out += unicodeToUtf8(c + SUB_MAGIC_NUMBER);
        return out;
    }

    [[deprecated("Use steppable::prettyPrint instead")]] std::string makeSubscript(const int normal)
    {
        return unicodeToUtf8(normal + SUB_MAGIC_NUMBER);
    }

    [[deprecated("Use steppable::prettyPrint instead")]] std::string makeSuperscript(const std::string& normal)
    {
        std::stringstream ss;
        for (const char c : normal)
            if (isdigit(c) != 0)
                ss << SUPERSCRIPTS.at(c - '0');
            else
                ss << ABOVE_DOT;
        std::string string = ss.str();
        return string;
    }

    [[deprecated("Use steppable::prettyPrint instead")]] std::string makeSuperscript(const char normal)
    {
        if (normal == '-')
            return "\u207B";

        return SUPERSCRIPTS.at(normal - '0');
    }

    [[deprecated("Use steppable::prettyPrint instead")]] std::string makeSurd(const std::string& radicand)
    {
        std::stringstream ss;
        ss << SURD;
        for (char c : radicand)
            ss << std::string(1, c) << COMBINE_MACRON;

        return ss.str();
    }
} // namespace steppable::__internals::symbols
