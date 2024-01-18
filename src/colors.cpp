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

#include "colors.hpp"

#include <ostream>

#ifdef WINDOWS
    #include <windows.h>
    #include <io.h>
    #include <cstdio>
    #include <versionhelpers.h>
    // ReSharper disable once CppInconsistentNaming
    #define isatty _isatty
    // ReSharper disable once CppInconsistentNaming
    #define fileno _fileno
#else
    #include <unistd.h>
#endif

bool isTerminal(const std::ostream& stream)
{
#ifdef WINDOWS
    if (IsWindows10OrGreater())
        return isatty(fileno(stdout)) != 0;
    return false; // The Windows console in Windows 7 does not support ANSI escapes
#else
    return isatty(STDOUT_FILENO) != 0;
#endif
}

std::ostream& reset(std::ostream& stream)
{
    if (isTerminal(stream))
        stream << "\x1b[0m";
    return stream;
}

namespace colors
{
    std::ostream& black(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[30m";
        return stream;
    }

    std::ostream& red(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[31m";
        return stream;
    }

    std::ostream& green(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[32m";
        return stream;
    }

    std::ostream& yellow(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[33m";
        return stream;
    }

    std::ostream& blue(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[34m";
        return stream;
    }

    std::ostream& magenta(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[35m";
        return stream;
    }

    std::ostream& cyan(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[36m";
        return stream;
    }

    std::ostream& white(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[37m";
        return stream;
    }

    std::ostream& brightBlack(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[90m";
        return stream;
    }

    std::ostream& brightRed(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[91m";
        return stream;
    }

    std::ostream& brightGreen(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[92m";
        return stream;
    }

    std::ostream& brightYellow(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[93m";
        return stream;
    }

    std::ostream& brightBlue(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[94m";
        return stream;
    }

    std::ostream& brightMagenta(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[95m";
        return stream;
    }

    std::ostream& brightCyan(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[96m";
        return stream;
    }

    std::ostream& brightWhite(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[97m";
        return stream;
    }
} // namespace colors

namespace colorsBg
{
    std::ostream& brightBlack(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[101m";
        return stream;
    }

    std::ostream& brightRed(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[102m";
        return stream;
    }

    std::ostream& brightGreen(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[103m";
        return stream;
    }

    std::ostream& brightYellow(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[104m";
        return stream;
    }

    std::ostream& brightBlue(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[105m";
        return stream;
    }

    std::ostream& brightCyan(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[106m";
        return stream;
    }

    std::ostream& brightWhite(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[107m";
        return stream;
    }
} // namespace colorsBg

namespace formats
{
    std::ostream& bold(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[1m";
        return stream;
    }

    std::ostream& dim(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[2m";
        return stream;
    }

    std::ostream& underline(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[4m";
        return stream;
    }

    std::ostream& blink(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[5m";
        return stream;
    }

    std::ostream& reverse(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[7m";
        return stream;
    }

    std::ostream& hidden(std::ostream& stream)
    {
        if (isTerminal(stream))
            stream << "\x1b[8m";
        return stream;
    }
} // namespace formats
