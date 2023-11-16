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
