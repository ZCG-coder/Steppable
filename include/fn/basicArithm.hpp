#pragma once

#include "output.hpp"

#include <exception>
#include <string>
#include <string_view>

std::string add(const std::string_view& a, const std::string_view& b, int steps = 2);
std::string compare(const std::string_view& a, const std::string_view& b, int steps = 2);
std::string multiply(const std::string_view& a, const std::string_view& b, int steps = 2);
std::string subtract(const std::string_view& a, const std::string_view& b, int steps = 2);
std::string decimalConvert(const std::string& inputStr, const std::string& baseStr, int steps = 2);
std::string power(const std::string_view _number, const std::string_view& raiseTo, const int steps = 2);

template<typename Pred>
void loop(const std::string_view& times, Pred predicate)
{
    std::string current = "0";
    auto result = compare(current, times, 0);

    while (result == "0")
    {
        try
        {
            predicate(current);
        }
        catch (std::exception e)
        {
            error("Exception occured in predicate.");
            error("Exception message: {}", e.what());
        }
        current = add(current, "1", 0);
        result = compare(current, times, 0);
    }
}
