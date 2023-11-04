#pragma once

#include <string>
#include <string_view>

std::string reportComparisonAtInteger(const std::string_view& a,
                                      const std::string_view& b,
                                      const bool bigger,
                                      const bool steps = true);

std::string reportComparisonByDigit(const std::string_view& a,
                                    const std::string_view& b,
                                    const unsigned int digit,
                                    const bool bigger,
                                    const bool steps = true);
