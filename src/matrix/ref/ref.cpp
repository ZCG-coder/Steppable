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

/**
 * @file ref.cpp
 * @brief Desciption
 *
 * @author Andy Zhang
 * @date 31st May 2025
 */

#include "conPlot/conPlot.hpp"
#include "fn/calc.hpp"
#include "refReport.hpp"
#include "steppable/number.hpp"
#include "steppable/parameter.hpp"

#include <string>
#include <string_view>

using namespace std::literals;

namespace steppable::__internals::matrix
{
    std::string ref(/* Arguments... */) { return ""; }
} // namespace steppable::__internals::matrix

int main()
{
    using namespace steppable;
    using namespace steppable::__internals::parameter;

    Utf8CodePage _;
    // std::vector<std::vector<Number>> matrix = { { 2, 1, -1, 3, 2, 8 },
    //                                             { 1, -2, 1, 0, 2, -4 },
    //                                             { 3, 1, -3, 4, 1, 6 },
    //                                             { 1, 1, 1, 1, 1, 5 },
    //                                             { 2, -1, 2, -1, 3, 3 } };
    // auto mat = steppable::Matrix(matrix);
    // mat = mat.rref();

    // std::cout << mat.present(1) << "\n";
    graphing::conPlot({
                          [](const Number& x) { return steppable::__internals::calc::sin(x.present(), 2); },
                          [](const Number& x) { return steppable::__internals::calc::cos(x.present(), 2); },
                      },
                      {
                          "width"_p = 90LL,
                          "xMin"_p = Number(-6.28),
                          "xMax"_p = Number(6.28),
                          "title"_p = "Sine and cosine graphs from -pi to +pi"s,
                      },
                      { { "title"_p = "Sine"s },
                        {
                            "lineColor"_p = (ColorFunc)colors::red,
                            "lineDot"_p = graphing::GraphDot::LIGHT_BLOCK_2,
                            "shadeDot"_p = graphing::GraphDot::LIGHT_BLOCK_1,
                            "title"_p = "Cosine"s,
                            "shadeOptions"_p = graphing::ShadeOptions::SHADE_OUTSIDE_BOTH,
                            "shadeValues"_p = graphing::NumberPair{ 0.1, 0.5 },
                        } });

    graphing::conPlotBar(
        {
            { 10, 12, 50, 12, 56, 6 },
            { 13, 14, 42, 64, 23, 10 },
        },
        {
            "width"_p = 110LL,
            "height"_p = 20LL,
            "title"_p = "Bar plot"s,
            "xAxisTitle"_p = "X axis"s,
            "barWidth"_p = 5LL,
        },
        {
            {
                "title"_p = "Bar 1"s,
                "color"_p = static_cast<ColorFunc>(colors::blue),
                "block"_p = graphing::GraphDot::LIGHT_BLOCK_1,
            },
            {
                "title"_p = "Bar 2"s,
                "color"_p = static_cast<ColorFunc>(colors::red),
            },
        });
}
