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

#include "refReport.hpp"
#include "steppable/mat2d.hpp"
#include "steppable/number.hpp"

#include <iostream>
#include <string>

namespace steppable::__internals::matrix
{
    std::string ref(/* Arguments... */) { return ""; }
} // namespace steppable::__internals::matrix

int main()
{
    using namespace steppable;
    std::vector<std::vector<Number>> matrix = { { 2, 1, -1, 3, 2, 8 },
                                                { 1, -2, 1, 0, 2, -4 },
                                                { 3, 1, -3, 4, 1, 6 },
                                                { 1, 1, 1, 1, 1, 5 },
                                                { 2, -1, 2, -1, 3, 3 } };
    auto mat = steppable::Matrix(matrix);
    mat = mat.rref();

    std::cout << mat.present(1) << "\n";
}
