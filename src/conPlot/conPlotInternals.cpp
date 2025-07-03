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

#include "conPlot/conPlotInternals.hpp"

#include "conPlot/conPlot.hpp"
#include "conPlot/conPlotInterpolation.hpp"
#include "conPlot/conPlotTypes.hpp"
#include "steppable/number.hpp"
#include "symbols.hpp"

#include <cstddef>
#include <map>
#include <string>

namespace steppable::graphing::__internals
{
    void conPlotLine(const Number& xGridSize,
                     const Number& yGridSize,
                     const Number& yMax,
                     const GraphOptions* graphOptions,
                     const LineOptions* lineOptions,
                     prettyPrint::ConsoleOutput* canvas,
                     std::map<Number, Number>& fnValues)
    {
        // Plot function
        std::map<long long, long long> gridPos;
        for (const auto& [i, y] : fnValues)
        {
            auto gridY = std::stoll(((yMax - y) / yGridSize).present());
            auto gridX = std::stoll(((graphOptions->xMax - i) / xGridSize).present());
            gridPos[gridX] = gridY;
        }
        if (lineOptions->samplesSpacing > 1)
            cubicInterpolateFill(&gridPos, 0, graphOptions->width);

        long long lastGridY = gridPos[0];
        for (const auto& [gridX, gridY] : gridPos)
        {
            // Plot point
            const long long diffY = gridY - lastGridY;
            const long long absDiffY = std::abs(diffY);
            long long sgn = 1;
            if (absDiffY != 0)
                sgn = diffY / absDiffY;
            if (absDiffY > graphOptions->height / 2)
            {
                // Create more points to connect the dots
                for (long long j = 1; j < absDiffY + 1; j++)
                    canvas->write(lineOptions->lineDot,
                                  { .x = gridX, .y = 3 + gridY + (-sgn * j) },
                                  false,
                                  lineOptions->lineColor);
            }
            canvas->write(lineOptions->lineDot, { .x = gridX, .y = 3 + gridY }, false, lineOptions->lineColor);
            lastGridY = 3 + gridY;
        }
    }

    void drawTicks(prettyPrint::ConsoleOutput* canvas,
                   const Number& xGridSize,
                   const Number& yGridSize,
                   const Number& yMax,
                   const GraphOptionsBase* graphOptions)
    {
        // Axis positions
        Number yTickValue = yMax;

        for (long long j = 0; j < graphOptions->height; ++j)
        {
            yTickValue -= yGridSize;
            // Write y ticks
            if (j % graphOptions->yTickSpacing == 0 and yGridSize != 0)
            {
                yTickValue.setPrec(2);
                canvas->write(yTickValue.present(), { .x = graphOptions->width + 2, .y = 3 + j });
                for (long long i = 0; i < graphOptions->width; ++i)
                    canvas->write(BoxDrawing::DOTTED_HORIZONTAL, { .x = i, .y = 3 + j });
                canvas->write(BoxDrawing::VERTICAL_LEFT, { .x = graphOptions->width, .y = 3 + j });
            }
        }

        // Draw grid
        for (long long i = 0; i < graphOptions->width - 2; ++i)
        {
            Number x = graphOptions->xMin + Number(i) * xGridSize;
            // Write grid label
            if (i % graphOptions->xTickSpacing == 0 and xGridSize != 0)
            {
                // Write vertical gridlines
                for (long long j = 0; j < graphOptions->height; ++j)
                    canvas->write(BoxDrawing::DOTTED_VERTICAL, { .x = i, .y = 3 + j });
                canvas->write(BoxDrawing::HORIZONTAL_UP, { .x = i, .y = 3 + graphOptions->height });
                x.setPrec(2);
                canvas->write(x.present(), { .x = i, .y = 3 + graphOptions->height + 1 });
            }
        }
    }

    void drawGrid(prettyPrint::ConsoleOutput* canvas, const GraphOptionsBase* graphOptions)
    {
        canvas->write(
            graphOptions->title, { .x = 0, .y = 1 }, false, formats::bold, prettyPrint::HorizontalAlignment::CENTER);
        for (long long i = 0; i <= graphOptions->width; ++i)
        {
            // Write base frame
            canvas->write(BoxDrawing::HORIZONTAL, { .x = i, .y = 3 + graphOptions->height });
        }

        // Write side frame
        for (long long j = 0; j < graphOptions->height; ++j)
            canvas->write(BoxDrawing::VERTICAL, { .x = graphOptions->width, .y = 3 + j });

        // Axis Titles
        canvas->write(BoxDrawing::BOTTOM_RIGHT_CORNER, { .x = graphOptions->width, .y = 3 + graphOptions->height });
        canvas->write(std::string((graphOptions->width - ::steppable::__internals::stringUtils::getUnicodeDisplayWidth(
                                                             graphOptions->xAxisTitle)) /
                                      2,
                                  ' ') +
                          graphOptions->xAxisTitle,
                      { .x = 0, .y = 5 + graphOptions->height },
                      false,
                      formats::bold);
        canvas->write(graphOptions->yAxisTitle,
                      { .x = graphOptions->width + 10, .y = (graphOptions->height / 2) + 1 },
                      false,
                      formats::bold);
    }
} // namespace steppable::graphing::__internals
