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

#pragma once

#include <ostream>

// RGB Text Colors (8-bit)
#define RGB_TEXT(r, g, b) "\x1b[38;2;" #r ";" #g ";" #b "m"

// RGB Background Colors (8-bit)
#define RGB_BG(r, g, b) "\x1b[48;2;" #r ";" #g ";" #b "m"

bool isTerminal(const std::ostream& stream);

std::ostream& reset(std::ostream& stream);

namespace colors
{
    std::ostream& black(std::ostream& stream);

    std::ostream& red(std::ostream& stream);

    std::ostream& green(std::ostream& stream);

    std::ostream& yellow(std::ostream& stream);

    std::ostream& blue(std::ostream& stream);

    std::ostream& magenta(std::ostream& stream);

    std::ostream& cyan(std::ostream& stream);

    std::ostream& white(std::ostream& stream);

    std::ostream& brightBlack(std::ostream& stream);

    std::ostream& brightRed(std::ostream& stream);

    std::ostream& brightGreen(std::ostream& stream);

    std::ostream& brightYellow(std::ostream& stream);

    std::ostream& brightBlue(std::ostream& stream);

    std::ostream& brightMagenta(std::ostream& stream);

    std::ostream& brightCyan(std::ostream& stream);

    std::ostream& brightWhite(std::ostream& stream);
} // namespace colors

namespace colorsBg
{
    std::ostream& brightBlack(std::ostream& stream);

    std::ostream& brightRed(std::ostream& stream);

    std::ostream& brightGreen(std::ostream& stream);

    std::ostream& brightYellow(std::ostream& stream);

    std::ostream& brightBlue(std::ostream& stream);

    std::ostream& brightCyan(std::ostream& stream);

    std::ostream& brightWhite(std::ostream& stream);
} // namespace colorsBg

namespace formats
{
    std::ostream& bold(std::ostream& stream);

    std::ostream& dim(std::ostream& stream);

    std::ostream& underline(std::ostream& stream);

    std::ostream& blink(std::ostream& stream);

    std::ostream& reverse(std::ostream& stream);

    std::ostream& hidden(std::ostream& stream);
} // namespace formats
