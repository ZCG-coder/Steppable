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
#include "number.hpp"
#include "output.hpp"
#include "testing.hpp"
#include "util.hpp"

#include <iomanip>
#include <iostream>

TEST_START()

using namespace steppable;

SECTION(Test Addition)
_.assertIsEqual((Number("123") + Number("456")).present(), "579");
_.assertIsEqual((Number("456") + Number("123")).present(), "579");
SECTION_END()

SECTION(Test Subtraction)
_.assertIsEqual((Number("123") - Number("456")).present(), "-333");
_.assertIsEqual((Number("456") - Number("123")).present(), "333");
SECTION_END()

SECTION(Test Multiplication)
_.assertIsEqual((Number("123") * Number("456")).present(), "56088");
_.assertIsEqual((Number("456") * Number("123")).present(), "56088");
SECTION_END()

SECTION(Test Division)
_.assertIsEqual((Number("123", 4, RoundingMode::USE_CURRENT_PREC) / Number("456")).present(), "0.2697");
SECTION_END()

SECTION(Test Remainder)
_.assertIsEqual((Number("456") % Number("123")).present(), "87");
SECTION_END()

SECTION(Test Power)
_.assertIsEqual((Number("12") ^ Number("45")).present(), "3657261988008837196714082302655030834027437228032");
SECTION_END()

SECTION(Test Equalities and Inequalities)
_.assertTrue(Number("123") == Number("123"));
_.assertTrue(Number("123") != Number("456"));
_.assertTrue(Number("123") < Number("456"));
_.assertTrue(Number("456") > Number("123"));
_.assertTrue(Number("123") <= Number("456"));
_.assertTrue(Number("456") >= Number("123"));
SECTION_END()

TEST_END()
