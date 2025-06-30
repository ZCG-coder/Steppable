#pragma once

#include "colors.hpp"
#include "steppable/number.hpp"

#include <string>
#include <string_view>

namespace steppable::graphing
{
    using namespace steppable::__internals::utils;
    using namespace steppable::__internals::symbols;

    using GraphFn = std::function<Number(Number)>;

    namespace GraphDot
    {
        constexpr std::string_view ROUND_DOT = "\u25CF";
        constexpr std::string_view BLOCK = "\u2588";
        constexpr std::string_view LIGHT_BLOCK_1 = "\u2591";
        constexpr std::string_view LIGHT_BLOCK_2 = "\u2592";
        constexpr std::string_view LIGHT_BLOCK_3 = "\u2593";
    } // namespace GraphDot

    struct GraphOptions
    {
        Number xMin = -1;
        Number xMax = 1;
        long long width = 30;
        long long height = 20;
        long long xTickSpacing = 10;
        long long yTickSpacing = 5;
        std::string title = "Graph";
        std::string xAxisTitle = "X Axis Title";
        std::string yAxisTitle = "Y Axis Title";
    };

    struct LineOptions
    {
        std::string_view lineDot = GraphDot::BLOCK;
        ColorFunc lineColor = colors::green;
        std::string title = "Line";
        long long samplesSpacing = 2;
    };
} // namespace steppable::graphing
