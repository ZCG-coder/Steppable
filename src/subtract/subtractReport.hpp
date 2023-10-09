#pragma once

#include <string>
#include <vector>

const std::string reportSubtract(const std::string& aInteger,
                           const std::string& aDecimal,
                           const std::string& bInteger,
                           const std::string& bDecimal,
                           const bool aIsDecimal,
                           const bool bIsDecimal,
                           const std::vector<int>& _diffDigits,
                           const std::vector<int>& borrows,
                           const bool steps);
