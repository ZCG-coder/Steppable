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

#include "symbols.hpp"

#include "util.hpp"

#include <sstream>
#include <string>

namespace steppable::__internals::symbols
{
    using namespace steppable::__internals::stringUtils;

    const std::array<std::string_view, 10>& SUPERSCRIPTS = { "\u2070", "\u00b9", "\u00b2", "\u00b3", "\u2074",
                                                             "\u2075", "\u2076", "\u2077", "\u2078", "\u2079" };

    std::string makeSubscript(const std::string& normal)
    {
        std::string out;
        for (const char c : normal)
            out += unicodeToUtf8(c + SUB_MAGIC_NUMBER);
        return out;
    }

    std::string makeSubscript(const int normal) { return unicodeToUtf8(normal + SUB_MAGIC_NUMBER); }

    std::string makeSuperscript(const std::string& normal)
    {
        std::stringstream ss;
        for (const char c : normal)
            if (isnumber(c))
                ss << SUPERSCRIPTS[c - '0'];
            else
                ss << ABOVE_DOT;
        std::string string = ss.str();
        return string;
    }

    std::string_view makeSuperscript(const char normal)
    {
        if (normal == '-')
            return "\u207B";

        return SUPERSCRIPTS[normal - '0'];
    }

    std::string makeSurd(const std::string& radicand)
    {
        std::stringstream ss;
        ss << SURD;
        for (char c : radicand)
            ss << c << COMBINE_MACRON;

        return ss.str();
    }
} // namespace steppable::__internals::symbols
