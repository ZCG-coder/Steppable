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
#include "fraction.hpp"
#include "output.hpp"
#include "testing.hpp"
#include "util.hpp"

#include <iomanip>
#include <iostream>

TEST_START()

using namespace steppable;

SECTION(Fraction Add)
_.assertIsEqual((Fraction("13122", "54251") + Fraction("22451", "3423")).present(), "1262905807/185701173");
_.assertIsEqual((Fraction("22451", "3423") + Fraction("13122", "54251")).present(), "1262905807/185701173");
SECTION_END()

SECTION(Fraction Subtract)
_.assertIsEqual((Fraction("13122", "54251") - Fraction("22451", "3423")).present(), "-1173072595/185701173");
_.assertIsEqual((Fraction("22451", "3423") - Fraction("13122", "54251")).present(), "1173072595/185701173");
SECTION_END()

SECTION(Fraction Multiply)
_.assertIsEqual((Fraction("13122", "54251") * Fraction("22451", "3423")).present(), "98200674/61900391");
_.assertIsEqual((Fraction("22451", "3423") * Fraction("13122", "54251")).present(), "98200674/61900391");
SECTION_END()

SECTION(Fraction Division)
_.assertIsEqual((Fraction("13122", "54251") / Fraction("22451", "3423")).present(), "44916606/1217989201");
_.assertIsEqual((Fraction("22451", "3423") / Fraction("13122", "54251")).present(), "1217989201/44916606");
SECTION_END()

TEST_END()
