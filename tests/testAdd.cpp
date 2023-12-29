/**************************************************************************************************
 * Copyright (c) 2023 NWSOFT                                                                      *
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
SECTION(Addition with multiple digits of different length)
const std::string &a = "6453.55", &b = "54329.334";
const auto& addResult1 = add(a, b, 0);
const auto& addResult2 = add(b, a, 0); // Makes sure it works when a and b are reordered.
_.assertIsEqual(addResult1, "60782.884");
_.assertIsEqual(addResult1, addResult2);
SECTION_END()

SECTION(Addition with multiple digits of equal length)
const std::string &a = "65943.595", &b = "54329.334";
const auto& addResult1 = add(a, b, 0);
const auto& addResult2 = add(b, a, 0); // Makes sure it works when a and b are reordered.
_.assertIsEqual(addResult1, "120272.929");
_.assertIsEqual(addResult1, addResult2);
SECTION_END()
TEST_END()
