#pragma once

#include <cstdio>
#include <iostream>
#include <ostream>
#include <string>

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
