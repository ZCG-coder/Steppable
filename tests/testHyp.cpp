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

#include "colors.hpp"
#include "fn/calc.hpp"
#include "output.hpp"
#include "testing.hpp"
#include "util.hpp"

#include <iomanip>
#include <iostream>

TEST_START()

using namespace steppable::__internals::calc;

SECTION(Test hyperbolic sine)
_.assertIsEqual(sinh("10", 3), "11013.233");
SECTION_END()

SECTION(Test hyperbolic cosine)
_.assertIsEqual(cosh("4.75", 4), "57.7965");
SECTION_END()

SECTION(Test hyperbolic tangent)
_.assertIsEqual(tanh("0.5", 5), "0.46212");
SECTION_END()

SECTION(Test hyperbolic cotangent)
_.assertIsEqual(coth("1.25", 5), "1.17885");
SECTION_END()

SECTION(Test hyperbolic secant)
_.assertIsEqual(sech("0.75", 4), "0.7724");
SECTION_END()

SECTION(Test hyperbolic cosecant)
_.assertIsEqual(csch("0.25", 4), "3.9588");
SECTION_END()

SECTION(Test inverse hyperbolic sine)
_.assertIsEqual(asinh("0.5", 4), "0.4812");
SECTION_END()

SECTION(Test inverse hyperbolic cosine)
_.assertIsEqual(acosh("1.25", 4), "0.6931");
SECTION_END()

SECTION(Test inverse hyperbolic tangent)
_.assertIsEqual(atanh("0.75", 4), "0.9730");
SECTION_END()

SECTION(Test inverse hyperbolic cotangent)
_.assertIsEqual(acoth("5", 4), "0.2028");
_.assertIsEqual(acoth("1.5", 4), "0.8047");
SECTION_END()

SECTION(Test inverse hyperbolic secant)
_.assertIsEqual(asech("0.75", 4), "0.7953");
SECTION_END()

SECTION(Test inverse hyperbolic cosecant)
_.assertIsEqual(acsch("0.25", 4), "2.0947");
SECTION_END()

TEST_END()
