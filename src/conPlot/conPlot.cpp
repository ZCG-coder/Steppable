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

#include "conPlot/conPlot.hpp"

#include "conPlot/conPlotInternals.hpp"
#include "conPlot/conPlotTypes.hpp"
#include "debugging.hpp"
#include "steppable/number.hpp"
#include "symbols.hpp"

#include <map>
#include <string>

namespace steppable::graphing
{
    namespace
    {
        template<LineOptionsDerivation LineOptionsDerivationT>
        void conPlotLegend(const GraphOptionsBase* graphOptions,
                           const std::vector<LineOptionsDerivationT>* lineOptions,
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
    } // namespace

    void conPlotBar(const std::vector<std::vector<Number>>& numbers,
                    const BarGraphOptions& graphOptions,
                    const std::vector<BarOptions>& barsOptions)
    {
        // Create buffer
        prettyPrint::ConsoleOutput canvas(graphOptions.height + 10,
                                          graphOptions.width + 12 +
                                              steppable::__internals::stringUtils::getUnicodeDisplayWidth(
                                                  graphOptions.yAxisTitle)); // Extra space for labels

        Number maxValue = 0;
        size_t datasetSize = numbers[0].size();
        for (const auto& dataset : numbers)
        {
            if (dataset.size() != datasetSize)
            {
                output::error("conPlotBar"s, "Bar plot datasets are not of the same size"s);
                programSafeExit(1);
            }
            for (const auto& number : dataset)
                maxValue = std::max(maxValue, number);
        }
        const auto& gridSize = maxValue / graphOptions.height;

        __internals::drawGrid(&canvas, &graphOptions);
        __internals::drawTicks(&canvas, 0, gridSize, maxValue, &graphOptions);

        for (long long i = 0; i < numbers.size(); i++)
        {
            const auto& dataset = numbers[i];

            std::vector<long long> yValues;
            std::vector<long long> xValues;
            long long xGridLoc = graphOptions.xTickSpacing * (1 + i);
            for (const auto& number : dataset)
            {
                long long yGridLoc = std::stoll(((maxValue - number) / gridSize).present());
                yValues.emplace_back(yGridLoc);
                xValues.emplace_back(xGridLoc);

                canvas.write(
                    barsOptions[i].lineDot, { .x = xGridLoc, .y = 3 + yGridLoc }, false, barsOptions[i].lineColor);
                for (long long x = 0; x < graphOptions.xTickSpacing; x++)
                    for (long long y = yGridLoc; y < graphOptions.height; y++)
                        canvas.write(
                            barsOptions[i].lineDot, { .x = xGridLoc + x, .y = 3 + y }, false, barsOptions[i].lineColor);

                xGridLoc += graphOptions.xTickSpacing * (1 + numbers.size());
            }
        }

        conPlotLegend(&graphOptions, &barsOptions, &canvas);
        std::cout << canvas.asString() << "\n";
    }

    void conPlot(const std::vector<GraphFn>& f,
                 const GraphOptions& graphOptions,
                 const std::vector<LineOptions>& linesOptions)
    {
        // Create buffer
        prettyPrint::ConsoleOutput canvas(graphOptions.height + 10,
                                          graphOptions.width + 12 +
                                              steppable::__internals::stringUtils::getUnicodeDisplayWidth(
                                                  graphOptions.yAxisTitle)); // Extra space for labels
        std::map<size_t, std::map<Number, Number>> fnValues;

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
                if (i % linesOptions[fnIdx].samplesSpacing == 0)
                {
                    Number x = graphOptions.xMin + Number(i) * xGridSize;
                    Number y = f[fnIdx](x);
                    fnValues[fnIdx][x] = y;
                    yMin = std::min(y, yMin);
                    yMax = std::max(y, yMax);
                }
            }

            if ((yMax - yMin).abs() < 1e-12)
            {
                yMin -= 1.0;
                yMax += 1.0;
            }
        }

        // Axis positions
        Number yGridSize = (yMax - yMin) / graphOptions.height;
        __internals::drawGrid(&canvas, &graphOptions);
        __internals::drawTicks(&canvas, xGridSize, yGridSize, yMax, &graphOptions);

        // Plot function
        for (size_t fnIdx = 0; fnIdx < f.size(); ++fnIdx)
            __internals::conPlotLine(
                xGridSize, yGridSize, yMax, &graphOptions, &linesOptions[fnIdx], &canvas, fnValues[fnIdx]);
        conPlotLegend(&graphOptions, &linesOptions, &canvas);
        std::cout << canvas.asString() << "\n";
    }
} // namespace steppable::graphing
