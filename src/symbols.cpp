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

    ConsoleOutput::ConsoleOutput(size_t height, size_t width) : height(height), width(width)
    {
        buffer = std::vector<std::vector<char>>(height, std::vector<char>(width, ' '));
    }

    void ConsoleOutput::write(const char c, const Position& pos, bool updatePos)
    {
        std::vector<char> vector = buffer[pos.y];
        vector[pos.x] = c;
        buffer[pos.y] = vector;

        if (updatePos)
            curPos = pos;
    }

    void ConsoleOutput::write(const char c, const long long dLine, const long long dCol, bool updatePos)
    {
        if (dLine < 0)
        {
            // We need to add extra lines for printing at the very top
            buffer.insert(buffer.begin(), -dLine, std::vector<char>(width, ' '));
            curPos.y = 0;
            height -= dLine;
        }
        if (dCol < 0)
        {
            for (auto& i : buffer)
            {
                std::vector<char> vector = i;
                vector.resize(vector.size() - dCol, ' ');
                i = vector;
            }

            curPos.x -= dCol;
            width -= dCol;
        }
        else
            curPos.x += dCol;
        write(c, curPos, updatePos);
    }

    void ConsoleOutput::write(const std::string& s, const Position& pos, bool updatePos)
    {
        Position p = pos;
        for (const auto& c : s)
        {
            if (c == '\n')
            {
                p.y++;
                p.x = pos.x;
                continue;
            }
            write(c, p, false);
            p.x++;
            if (updatePos)
                curPos = p;
        }
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
            max = std::max(max, string.length());
        return max;
    }

    size_t getStringHeight(const std::string& s) { return split(s, '\n').size(); }
} // namespace steppable::prettyPrint

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
