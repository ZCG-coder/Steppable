#include "symbols.hpp"

#include <string>

std::string makeSubscript(const std::string& normal)
{
    std::string out;
    for (char c : normal)
        out += unicode_to_utf8(c + SUB_MAGIC_NUMBER);
    return out;
}

std::string makeSubscript(const int normal) { return unicode_to_utf8(normal + SUB_MAGIC_NUMBER); }

std::string makeSuperscript(const std::string& normal)
{
    std::string out;
    for (int c : normal)
        out += c + SUP_MAGIC_NUMBER;
    return out;
}

std::string makeSuperscript(const char normal) { return unicode_to_utf8(normal + SUP_MAGIC_NUMBER); }
