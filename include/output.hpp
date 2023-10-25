#pragma once

#include "colors.hpp"

#include <iostream>
#include <string>

template<typename T>
void error(const T msg...)
{
    std::cerr << colors::red << formats::bold << "Error: " << reset << colors::red;
    std::cerr << msg << reset << std::endl;
}

template<typename T>
void warning(const T msg...)
{
    std::cout << colors::yellow << formats::bold << "Warning: " << reset << colors::yellow;
    std::cout << msg << reset << std::endl;
}