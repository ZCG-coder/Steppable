/**************************************************************************************************
 * Copyright (c) 2023 NWSOFT                                                                      *
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

constexpr const std::array<std::string_view, 10>& SUPERSCRIPTS = { "⁰", "¹", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "⁹" };

std::string makeSubscript(const std::string& normal)
{
    std::string out;
    for (char c : normal)
        out += unicodeToUtf8(c + SUB_MAGIC_NUMBER);
    return out;
}

std::string makeSubscript(const int normal) { return unicodeToUtf8(normal + SUB_MAGIC_NUMBER); }

std::string makeSuperscript(const std::string& normal)
{
    std::stringstream ss;
    for (char c : normal)
        ss << SUPERSCRIPTS[c - '0'];
    std::string string = ss.str();
    return string;
}

std::string_view makeSuperscript(const char normal) { return SUPERSCRIPTS[normal - '0']; }
