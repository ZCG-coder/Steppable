#include "colors.hpp"

#include <ostream>

#ifdef WINDOWS
#include <Windows.h>
#include <io.h>
#include <stdio.h>
#define isatty _isatty
#define fileno _fileno

#else
#include <unistd.h>
#endif

bool isTerminal(const std::ostream& stream)
{
#ifdef WINDOWS
    return isatty(fileno(stdout)) != 0;
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
