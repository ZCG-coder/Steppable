#pragma once

#include <string>
#include <string_view>

std::string add(const std::string_view& a, const std::string_view& b, int steps = 2);
std::string compare(const std::string_view& a, const std::string_view& b, int steps = 2);
std::string multiply(const std::string_view& a, const std::string_view& b, int steps = 2);
std::string subtract(const std::string_view& a, const std::string_view& b, int steps = 2);
std::string decimalConvert(const std::string& inputStr, const std::string& baseStr, int steps = 2);