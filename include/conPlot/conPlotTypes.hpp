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

            PARAM_GET_FALLBACK(map, Number, xMin, -1);
            PARAM_GET_FALLBACK(map, Number, xMax, 1);
            PARAM_GET_FALLBACK(map, long long, width, 30LL);
            PARAM_GET_FALLBACK(map, long long, height, 20LL);
            PARAM_GET_FALLBACK(map, long long, xTickSpacing, 10LL);
            PARAM_GET_FALLBACK(map, long long, yTickSpacing, 5LL);
            PARAM_GET_FALLBACK(map, std::string, title, "Graph");
            PARAM_GET_FALLBACK(map, std::string, xAxisTitle, "X Axis Title");
            PARAM_GET_FALLBACK(map, std::string, yAxisTitle, "Y Axis Title");

            this->xMin = xMin;
            this->xMax = xMax;
            this->width = width;
            this->height = height;
            this->xTickSpacing = xTickSpacing;
            this->yTickSpacing = yTickSpacing;
            this->title = title;
            this->xAxisTitle = xAxisTitle;
            this->yAxisTitle = yAxisTitle;
        }
    };

    struct LineOptions
    {
        std::string_view lineDot = GraphDot::BLOCK;
        ColorFunc lineColor = colors::green;
        std::string title = "Line";
        long long samplesSpacing = 2;

        template<typename... Params>
        LineOptions(Params... params)
        {
            auto map = processParams(params...);
            PARAM_GET_FALLBACK(map, std::string_view, lineDot, GraphDot::BLOCK);
            PARAM_GET_FALLBACK(map, ColorFunc, lineColor, (ColorFunc)colors::green);
            PARAM_GET_FALLBACK(map, std::string, title, "Line"s);
            PARAM_GET_FALLBACK(map, long long, samplesSpacing, 2LL);

            this->lineDot = lineDot;
            this->lineColor = lineColor;
            this->title = title;
            this->samplesSpacing = samplesSpacing;
        }
    };
} // namespace steppable::graphing
