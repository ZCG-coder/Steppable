#pragma once

#include <string>
#include <vector>

const std::string reportAdd(const std::string& aInteger,
                            const std::string& aDecimal,
                            const std::string& bInteger,
                            const std::string& bDecimal,
                            const std::vector<int>& sumDigits,
                            const std::vector<bool>& carries,
                            const int steps);
