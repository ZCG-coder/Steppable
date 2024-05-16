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
#include "factors.hpp"
#include "output.hpp"
#include "testing.hpp"
#include "util.hpp"

#include <iomanip>
#include <iostream>

TEST_START()
using namespace steppable::__internals::numUtils;

SECTION(Prime Test)
_.assertTrue(isPrime("2"));
_.assertTrue(isPrime("3"));
_.assertFalse(isPrime("16"));
_.assertFalse(isPrime("100"));
_.assertFalse(isPrime("1000"));
_.assertFalse(isPrime("10000"));
SECTION_END()

SECTION(Greatest Square Number Test)
_.assertIsEqual(getGreatestRootNum("2"), "1");
_.assertIsEqual(getGreatestRootNum("3"), "1");
_.assertIsEqual(getGreatestRootNum("4"), "4");
_.assertIsEqual(getGreatestRootNum("5"), "4");
SECTION_END()

SECTION(Greatest Root Factor Test)
_.assertIsEqual(getRootFactor("24", "2").getOutput(), "4");
_.assertIsEqual(getRootFactor("13", "2").getOutput(), "1");
_.assertIsEqual(getRootFactor("27", "2").getOutput(), "9");
_.assertIsEqual(getRootFactor("72", "2").getOutput(), "36");
SECTION_END()

TEST_END()
