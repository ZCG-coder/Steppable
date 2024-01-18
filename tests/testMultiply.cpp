/**************************************************************************************************
 * Copyright (c) 2023-2024 NWSOFT                                                                 *
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

#include "colors.hpp"
#include "fn/basicArithm.hpp"
#include "output.hpp"
#include "testing.hpp"
#include "util.hpp"

#include <iomanip>
#include <iostream>

TEST_START()
SECTION(Multiplication without carry)
const std::string &a = "2", &b = "4";
const auto& multiplyResult1 = multiply(a, b, 0);
const auto& multiplyResult2 = multiply(b, a, 0); // Makes sure it works when a and b are reordered.
_.assertIsEqual(multiplyResult1, "8");
_.assertIsEqual(multiplyResult1, multiplyResult2);
SECTION_END()

SECTION(Multiplication with one carry)
const std::string &a = "56", &b = "45";
const auto& multiplyResult1 = multiply(a, b, 0);
const auto& multiplyResult2 = multiply(b, a, 0); // Makes sure it works when a and b are reordered.
_.assertIsEqual(multiplyResult1, "2520");
_.assertIsEqual(multiplyResult1, multiplyResult2);
SECTION_END()

SECTION(Multiplication with two carries)
const std::string &a = "12", &b = "9";
const auto& multiplyResult1 = multiply(a, b, 0);
const auto& multiplyResult2 = multiply(b, a, 0); // Makes sure it works when a and b are reordered.
_.assertIsEqual(multiplyResult1, "108");
_.assertIsEqual(multiplyResult1, multiplyResult2);
SECTION_END()
TEST_END()
