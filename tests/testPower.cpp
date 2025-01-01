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
#include "rounding.hpp"
#include "testing.hpp"
#include "util.hpp"

#include <iomanip>
#include <iostream>

TEST_START()

using namespace steppable::__internals::arithmetic;

SECTION(Power)
const std::string number = "47";
const std::string raiseTo = "10";
const auto& result = power(number, raiseTo, 0);

_.assertIsEqual(result, "52599132235830049");
SECTION_END()

SECTION(Power with Decimals)
const std::string number = "47.5";
const std::string raiseTo = "10";
const auto& result = power(number, raiseTo, 0);

_.assertIsEqual(result, "58470404222497940.0634765625");
SECTION_END()

SECTION(Power with Decimals)
const std::string number = "0.5";
const std::string raiseTo = "10";
const auto& result = power(number, raiseTo, 0);

_.assertIsEqual(result, "0.0009765625");
SECTION_END()

SECTION(Power with Decimal Exponents)
const std::string number = "4";
const std::string raiseTo = "0.5";
const auto& result = power(number, raiseTo, 0);

_.assertIsEqual(numUtils::roundOff(result), "2");
SECTION_END()
TEST_END()
