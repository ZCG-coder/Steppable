#pragma once

#include "colors.hpp"
#include "output.hpp"

#include <format>
#include <iostream>
#include <string>

template<typename T, typename... Args>
void error(const T msg, Args&&... args)
{
    std::cerr << colors::red << formats::bold << "Error: " << reset << colors::red;
    std::cerr << std::vformat(msg, std::make_format_args(args...)) << reset << std::endl;
}

template<typename T, typename... Args>
void warning(const T msg, Args&&... args)
{
    std::cout << colors::yellow << formats::bold << "Warning: " << reset << colors::yellow;
    std::cout << std::vformat(msg, std::make_format_args(args...)) << reset << std::endl;
}