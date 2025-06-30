#include "colors.hpp"
#include "conPlotTypes.hpp"
#include "steppable/number.hpp"
#include "symbols.hpp" // Adjust the path as needed
#include "types/rounding.hpp"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <map>
#include <string>

namespace steppable::graphing
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
        for (long long i = 0; i < graphOptions->width; ++i)
        {
            Number x = graphOptions->xMin + Number(i) * xGridSize;
            Number y = fnValues[x];
            auto gridY = std::stoll(((yMax - y) / yGridSize).present());

            // Plot point
            canvas->write(lineOptions->lineDot, { .x = i, .y = 3 + gridY }, false, lineOptions->lineColor);
        }
    }

    void conPlot(const std::vector<GraphFn>& f,
                 const GraphOptions& graphOptions,
                 const std::vector<LineOptions>& lineOptions)
    {
        // Create buffer
        prettyPrint::ConsoleOutput canvas(
            graphOptions.height + 10,
            graphOptions.width + 12 +
                __internals::stringUtils::getUnicodeDisplayWidth(graphOptions.xAxisTitle)); // Extra space for labels
        std::map<size_t, std::map<Number, Number>> fnValues;

        canvas.write(
            graphOptions.title, { .x = 0, .y = 1 }, false, formats::bold, prettyPrint::HorizontalAlignment::CENTER);

        // Ticks spacing
        Number yMin;
        for (size_t fnIdx = 0; fnIdx < f.size(); ++fnIdx)
        {
            yMin = f[fnIdx](graphOptions.xMin);
            fnValues[fnIdx][graphOptions.xMin] = yMin;
        }
        Number yMax = yMin;
        // 1 grid = 1 character on screen
        Number xGridSize = (graphOptions.xMax - graphOptions.xMin) / graphOptions.width;

        // Calculate range of values
        for (size_t fnIdx = 0; fnIdx < f.size(); ++fnIdx)
        {
            for (long long i = 0; i <= graphOptions.width; ++i)
            {
                Number x = graphOptions.xMin + Number(i) * xGridSize;
                Number y = f[fnIdx](x);
                fnValues[fnIdx][x] = y;

                yMin = std::min(y, yMin);
                yMax = std::max(y, yMax);

                // Write base frame
                canvas.write(BoxDrawing::HORIZONTAL, { .x = i, .y = 3 + graphOptions.height });
            }

            if ((yMax - yMin).abs() < 1e-12)
            {
                yMin -= 1.0;
                yMax += 1.0;
            }
        }

        // Axis positions
        Number yGridSize = (yMax - yMin) / graphOptions.height;
        Number yTickValue = yMax;

        // Write side frame
        for (long long j = 0; j < graphOptions.height; ++j)
        {
            canvas.write(BoxDrawing::VERTICAL, { .x = graphOptions.width, .y = 3 + j });
            yTickValue -= yGridSize;

            // Write y ticks
            if (j % graphOptions.yTickSpacing == 0)
            {
                yTickValue.setPrec(2);
                canvas.write(yTickValue.present(), { .x = graphOptions.width + 2, .y = 3 + j });
                for (long long i = 0; i < graphOptions.width; ++i)
                    canvas.write(BoxDrawing::DOTTED_HORIZONTAL, { .x = i, .y = 3 + j });
                canvas.write(BoxDrawing::VERTICAL_LEFT, { .x = graphOptions.width, .y = 3 + j });
            }
        }
        canvas.write(BoxDrawing::BOTTOM_RIGHT_CORNER, { .x = graphOptions.width, .y = 3 + graphOptions.height });

        // Draw grid
        for (long long i = 0; i < graphOptions.width - 2; ++i)
        {
            Number x = graphOptions.xMin + Number(i) * xGridSize;
            // Write grid label
            if (i % graphOptions.xTickSpacing == 0)
            {
                // Write vertical gridlines
                for (long long j = 0; j < graphOptions.height; ++j)
                    canvas.write(BoxDrawing::DOTTED_VERTICAL, { .x = i, .y = 3 + j });
                canvas.write(BoxDrawing::HORIZONTAL_UP, { .x = i, .y = 3 + graphOptions.height });
                x.setPrec(2);
                canvas.write(x.present(), { .x = i, .y = 3 + graphOptions.height + 1 });
            }
        }

        // Axis Titles
        canvas.write(
            std::string(
                (graphOptions.width - __internals::stringUtils::getUnicodeDisplayWidth(graphOptions.xAxisTitle)) / 2,
                ' ') +
                graphOptions.xAxisTitle,
            { .x = 0, .y = 5 + graphOptions.height },
            false,
            formats::bold);
        canvas.write(graphOptions.yAxisTitle,
                     { .x = graphOptions.width + 10, .y = graphOptions.height / 2 + 1 },
                     false,
                     formats::bold);

        for (size_t fnIdx = 0; fnIdx < f.size(); ++fnIdx)
            conPlotLine(xGridSize, yGridSize, yMax, &graphOptions, &lineOptions[fnIdx], &canvas, fnValues[fnIdx]);
        std::cout << canvas.asString() << "\n";
    }
} // namespace steppable::graphing