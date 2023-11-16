#pragma once

#include "util.hpp"

#include <iostream>
#include <string>

#define BECAUSE "\u2235"
#define THEREFORE "\u2234"

#define MULTIPLY "\u00D7"

// Subscripts
#define SUB_0 "\u2080"
#define SUB_Z "\u1D69"
#define SUB_MAGIC_NUMBER 8272

extern const std::array<std::string_view, 10>& SUPERSCRIPTS;

std::string makeSubscript(const std::string& normal);

std::string makeSubscript(const int normal);

// Superscripts
#define SUP_0 "\u2070"
#define SUP_Z "\u1DBB"
#define SUP_MAGIC_NUMBER 8304

std::string makeSuperscript(const std::string& normal);

std::string_view makeSuperscript(const char normal);
