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

// We can just test the basics of the trigonometric functions, as the rest are based on them.
SECTION(Test sine and cosine)
_.assertIsEqual(sin("30", 2, 1), "0.50");
_.assertIsEqual(cos("60", 2, 1), "0.50");
SECTION_END()

SECTION(Test tangent)
_.assertIsEqual(tan("45", 2, 1), "1.00");
// Zero check test
_.assertIsEqual(tan("90", 2, 1), "Infinity");
SECTION_END()

SECTION(Test arc cosine)
_.assertIsEqual(acos("0.5", 2, 1), "60");
// Zero check test
_.assertIsEqual(acos("1", 2, 1), "0");
SECTION_END()

SECTION(Test arc sine)
_.assertIsEqual(asin("0.5", 2, 1), "30.00");
// Zero check test
_.assertIsEqual(asin("0", 2, 1), "0");
SECTION_END()

SECTION(Test arc tangent)
_.assertIsEqual(atan("0", 2, 1), "0");
SECTION_END()

TEST_END()
