#include "colors.hpp"
#include "conPlot/conPlotInterpolation.hpp"
#include "conPlotTypes.hpp"
#include "steppable/number.hpp"
#include "symbols.hpp" // Adjust the path as needed

#include <algorithm>
#include <cstddef>
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

    void conPlotLegend(const GraphOptions* graphOptions,
                       const std::vector<LineOptions>* lineOptions,
                       prettyPrint::ConsoleOutput* canvas)
    {
        long long yLoc = graphOptions->height + 7;
        canvas->write("Legend", { .x = 0, .y = yLoc++ }, false, formats::bold);
        for (size_t fnIdx = 0; fnIdx < lineOptions->size(); fnIdx++)
        {
            const auto& lineOption = lineOptions->at(fnIdx);
            yLoc += static_cast<long long>(fnIdx);
            canvas->write(lineOption.title, { .x = 0, .y = yLoc }, false);

            for (int i = 0; i < graphOptions->xTickSpacing; i++)
                canvas->write(lineOption.lineDot,
                              { .x = static_cast<long long>(lineOption.title.length()) + 1 + i, .y = yLoc },
                              false,
                              lineOption.lineColor);
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

        // Sample min/max
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
                if (i % lineOptions[fnIdx].samplesSpacing == 0)
                {
                    Number x = graphOptions.xMin + Number(i) * xGridSize;
                    Number y = f[fnIdx](x);
                    fnValues[fnIdx][x] = y;
                    yMin = std::min(y, yMin);
                    yMax = std::max(y, yMax);
                }

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
                     { .x = graphOptions.width + 10, .y = (graphOptions.height / 2) + 1 },
                     false,
                     formats::bold);

        for (size_t fnIdx = 0; fnIdx < f.size(); ++fnIdx)
            conPlotLine(xGridSize, yGridSize, yMax, &graphOptions, &lineOptions[fnIdx], &canvas, fnValues[fnIdx]);
        conPlotLegend(&graphOptions, &lineOptions, &canvas);
        std::cout << canvas.asString() << "\n";
    }
} // namespace steppable::graphing
