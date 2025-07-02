/**************************************************************************************************
 * Copyright (c) 2023-2025 NWSOFT                                                                 *
 *                                                                                                *
 * Permission is hereby granted, free of charge, to any person obtaining a copy                   *
 * of this software and associated documentation files (the "Software"), to deal                  *
 * in the Software without restriction, including without limitation the rights                   *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                      *
 * copies of the Software, and to permit persons to whom the Software is                          *
 * furnished to do so, subject to the following conditions:                                       *
 *                                                                                                *
 * The above copyright notice and this permission notice shall be included in all                 *
 * copies or substantial portions of the Software.                                                *
 *                                                                                                *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                     *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                       *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE                    *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                         *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,                  *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE                  *
 * SOFTWARE.                                                                                      *
 **************************************************************************************************/

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

    /**
     * @namespace steppable::graphing::GraphDot
     * @brief Contains string values of dots to be graphed on the screen.
     */
    namespace GraphDot
    {
        constexpr std::string_view ROUND_DOT = "\u25CF"; ///< Round dot
        constexpr std::string_view BLOCK = "\u2588"; ///< Solid-filled block
        constexpr std::string_view LIGHT_BLOCK_1 = "\u2591"; ///< Lightly-filled block
        constexpr std::string_view LIGHT_BLOCK_2 = "\u2592"; ///< Medium-lightly-filled block
        constexpr std::string_view LIGHT_BLOCK_3 = "\u2593"; ///< More densly-filled block
    } // namespace GraphDot

    /**
     * @struct steppable::graphing::GraphOptions
     * @brief Stores the opotions for each graph shown on screen.
     */
    struct GraphOptions
    {
        Number xMin = -1; ///< Minimum `x` value.
        Number xMax = 1; ///< Maximum `x` value.
        long long width = 30; ///< Width of the graph.
        long long height = 20; ///< Height of the graph.
        long long xTickSpacing = 10; ///< Spacing between each `x` axis tick.
        long long yTickSpacing = 5; ///< Spacing between each `y` axis tick.
        std::string title = "Graph"; ///< Title of the graph.
        std::string xAxisTitle = "X Axis Title"; ///< Title of the `x` axis.
        std::string yAxisTitle = "Y Axis Title"; ///< Title of the `y` axis.

        /**
         * @brief Initializes a new `GraphOptions` instance.
         *
         * @param params The parameters to be passed to initialize the instance.
         */
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

    /**
     * @struct steppable::graphing::LineOptions
     * @brief Stores options for each line graphed on screen.
     */
    struct LineOptions
    {
        std::string_view lineDot = GraphDot::BLOCK; ///< Dot type to be drawn on screen.
        ColorFunc lineColor = colors::green; ///< Color of the dot to output.
        std::string title = "Line"; ///< Name of the line to be shown in the legend.
        long long samplesSpacing = 2; ///< Frequency to take a sample, units: grids.

        /**
         * @brief Initializes a new `LineOptions` instance.
         *
         * @param params The parameters to be passed to initialize the instance.
         */
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
