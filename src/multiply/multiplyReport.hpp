#pragma once

#include <string>
#include <vector>

std::string reportMultiply(const std::string& a,
                           const std::string& b,
                           const std::vector<int>& finalProdDigits,
                           const std::vector<int>& finalProdCarries,
                           const std::vector<std::vector<int>>& prodDigitsOut,
                           const std::vector<std::vector<int>>& carries);
