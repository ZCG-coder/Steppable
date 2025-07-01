#pragma once

#include "colors.hpp"
#include "steppable/number.hpp"
#include "steppable/parameter.hpp"

#include <string>
#include <string_view>

namespace steppable::graphing
{
    using namespace steppable::__internals::utils;
    using namespace steppable::__internals::symbols;
    using namespace steppable::__internals::parameter;

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

        template<typename... Params>
        GraphOptions(Params... params)
        {
            auto map = processParams(params...);

            PARAM_GET_FALLBACK(map, Number, _xMin, -1);
            PARAM_GET_FALLBACK(map, Number, _xMax, 1);
            PARAM_GET_FALLBACK(map, long long, _width, 30);
            PARAM_GET_FALLBACK(map, long long, _height, 20);
            PARAM_GET_FALLBACK(map, long long, _xTickSpacing, 10);
            PARAM_GET_FALLBACK(map, long long, _yTickSpacing, 5);
            PARAM_GET_FALLBACK(map, std::string, _title, "Graph");
            PARAM_GET_FALLBACK(map, std::string, _xAxisTitle, "X Axis Title");
            PARAM_GET_FALLBACK(map, std::string, _yAxisTitle, "Y Axis Title");

            xMin = _xMin;
            xMax = _xMax;
            width = _width;
            height = _height;
            xTickSpacing = _xTickSpacing;
            yTickSpacing = _yTickSpacing;
            title = _title;
            xAxisTitle = _xAxisTitle;
            yAxisTitle = _yAxisTitle;
        }
    };

    struct LineOptions
    {
        std::string_view lineDot = GraphDot::BLOCK;
        ColorFunc lineColor = colors::green;
        std::string title = "Line";
        long long samplesSpacing = 2;

        template <typename... Params>
        LineOptions(Params... params)
        {
            auto map = processParams(params...);
            PARAM_GET_FALLBACK(map, std::string_view, _lineDot, GraphDot::BLOCK);
            PARAM_GET_FALLBACK(map, ColorFunc, _lineColor, colors::green);
            PARAM_GET_FALLBACK(map, std::string, _title, "Line");
            PARAM_GET_FALLBACK(map, long long, _samplesSpacing, 2);
        }
    };
} // namespace steppable::graphing
