#pragma once

#include <string>
#include <string_view>

const std::string reportComparisonAtInteger(const std::string_view& a,
                                            const std::string_view& b,
                                            const bool bigger,
                                            const bool steps = true);

const std::string reportComparisonByDigit(const std::string_view& a,
                                          const std::string_view& b,
                                          const unsigned int digit,
                                          const bool bigger,
                                          const bool steps = true);
