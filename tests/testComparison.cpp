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

using namespace steppable::__internals::arithmetic;

SECTION(Comparison at integer)
const std::string &a = "6453.55";
const std::string &b = "54329.334";
const auto& compareResult1 = compare(a, b, 0);
const auto& compareResult2 = compare(b, a, 0); // Makes sure it works when a and b are reordered.
_.assertIsEqual(compareResult1, "0");
_.assertIsEqual(compareResult2, "1");
SECTION_END()

SECTION(Comparison by digit without decimal point)
const std::string &a = "659";
const std::string &b = "543";
const auto& compareResult1 = compare(a, b, 0);
const auto& compareResult2 = compare(b, a, 0); // Makes sure it works when a and b are reordered.
_.assertIsEqual(compareResult1, "1");
_.assertIsEqual(compareResult2, "0");
SECTION_END()

SECTION(Comparison by digit with decimal point)
const std::string &a = "659.2234";
const std::string &b = "659.5242";
const auto& compareResult1 = compare(a, b, 0);
const auto& compareResult2 = compare(b, a, 0); // Makes sure it works when a and b are reordered.
_.assertIsEqual(compareResult1, "0");
_.assertIsEqual(compareResult2, "1");
SECTION_END()
TEST_END()
