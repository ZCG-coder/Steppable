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

// ReSharper disable All
#include "colors.hpp"
#include "fn/basicArithm.hpp"
#include "output.hpp"
#include "testing.hpp"
#include "util.hpp"

#include <iomanip>
#include <iostream>
#include <rounding.hpp>

TEST_START()

using namespace steppable::__internals::numUtils;
using namespace steppable::__internals::stringUtils;

SECTION(isZeroString)
const std::string& string1 = "0";
const std::string& string2 = "3";
const std::string& string3 = "a";
const bool isZeroString1 = isZeroString(string1);
const bool isZeroString2 = isZeroString(string2);
const bool isZeroString3 = isZeroString(string3);

_.assertTrue(isZeroString1);
_.assertFalse(isZeroString2);
_.assertFalse(isZeroString3);
SECTION_END()

SECTION(isNumber)
const std::string& string1 = "123";
const std::string& string2 = "113241.43152";
const std::string& string3 = "a13489b";
const bool isNumber1 = isNumber(string1);
const bool isNumber2 = isNumber(string2);
const bool isNumber3 = isNumber(string3);

_.assertTrue(isNumber1);
_.assertTrue(isNumber2);
_.assertFalse(isNumber3);
SECTION_END()

SECTION(split)
const std::string& string1 = "1,2,3";
const std::string& string2 = "1";
const std::string& string3 = ",,,";
const std::string& string4 = "";
const auto& out1 = split(string1, ',');
const auto& out2 = split(string2, ',');
const auto& out3 = split(string3, ',');
const auto& out4 = split(string4, ',');

_.assertIsEqual(static_cast<int>(out1.size()), 3);
_.assertIsEqual(static_cast<int>(out2.size()), 1);
_.assertIsEqual(static_cast<int>(out3.size()), 3);
_.assertIsEqual(static_cast<int>(out4.size()), 0);
SECTION_END()

SECTION(splitNumber without padInteger or padDecimal)
const std::string& number1 = "1.24";
const std::string& number2 = "2";
const auto& out = splitNumber(number1, number2, false, false).splitNumberArray;

_.assertIsEqual(out[0], "1");
_.assertIsEqual(out[1], "24");
_.assertIsEqual(out[2], "2");
_.assertIsEqual(out[3], "");
SECTION_END()

SECTION(splitNumber with padInteger except padDecimal)
const std::string& number1 = "11.24";
const std::string& number2 = "2";
const auto& out = splitNumber(number1, number2, true, false).splitNumberArray;

_.assertIsEqual(out[0], "11");
_.assertIsEqual(out[1], "24");
_.assertIsEqual(out[2], " 2");
_.assertIsEqual(out[3], "");
SECTION_END()

SECTION(splitNumber with padInteger and padDecimal)
const std::string& number1 = "11.24";
const std::string& number2 = "2.2";
const auto& out = splitNumber(number1, number2, true, true).splitNumberArray;

_.assertIsEqual(out[0], "11");
_.assertIsEqual(out[1], "24");
_.assertIsEqual(out[2], " 2");
_.assertIsEqual(out[3], "20");
SECTION_END()

SECTION(lReplace)
const std::string& string1 = "aaaaaab";
const std::string& string2 = "bbb";
const auto& out1 = lReplace(string1, 'a');
const auto& out2 = lReplace(string2, 'a');
const auto& out3 = lReplace(string1, 'a', 'c');
const auto& out4 = lReplace(string2, 'a', 'c');

_.assertIsEqual(out1, "b");
_.assertIsEqual(out2, "bbb");
_.assertIsEqual(out3, "ccccccb");
_.assertIsEqual(out4, "bbb");
SECTION_END()

SECTION(rReplace)
const std::string& string1 = "baaaaaa";
const std::string string2 = "bbb";
const auto& out1 = rReplace(string1, 'a');
const auto out2 = rReplace(string2, 'a');
const auto& out3 = rReplace(string1, 'a', 'c');
const auto& out4 = rReplace(string2, 'a', 'c');

_.assertIsEqual(out1, "b");
_.assertIsEqual(out2, "bbb");
_.assertIsEqual(out3, "bcccccc");
_.assertIsEqual(out4, "bbb");
SECTION_END()

SECTION(bothEndsReplace)
const std::string& string1 = "baaaabb";
const std::string& string2 = "aaa";
const auto& out1 = bothEndsReplace(string1, 'b');
const auto& out2 = bothEndsReplace(string2, 'b');
const auto& out3 = bothEndsReplace(string1, 'b', 'c');
const auto& out4 = bothEndsReplace(string2, 'b', 'c');

_.assertIsEqual(out1, "aaaa");
_.assertIsEqual(out2, "aaa");
_.assertIsEqual(out3, "caaaacc");
_.assertIsEqual(out4, "aaa");
SECTION_END()

SECTION(removeLeadingZeros)
const std::vector<int>& vector = { 0, 0, 142, 0, 142, 0, 0 };
const auto& out = replaceLeadingZeros(vector);

_.assertIsEqual(static_cast<int>(out.size()), 7);
_.assertIsEqual(out[0], out[1]);
_.assertIsEqual(out[0], -2);
SECTION_END()

SECTION(MAKE_WIDER)
const std::string& in = "abcdefg";
const auto& out = makeWider(in);

_.assertIsEqual(out, "a  b  c  d  e  f  g");
SECTION_END()

SECTION(Test Rounding)
const std::string& number1 = "1.565";
_.assertIsEqual(roundOff(number1, 0), "2");
_.assertIsEqual(roundOff(number1, 1), "1.6");

const std::string& number2 = "1.9";
_.assertIsEqual(roundOff(number2, 0), "2");
_.assertIsEqual(roundOff(number2, 1), "2.0");

const std::string& number3 = "1.9";
_.assertIsEqual(roundDown(number2), "1");
_.assertIsEqual(roundUp(number2), "2");
SECTION_END()

SECTION(Test isPowerOfTen)
_.assertTrue(isPowerOfTen("10"));
_.assertTrue(isPowerOfTen("0.1"));
_.assertTrue(isPowerOfTen("0.01"));
_.assertFalse(isPowerOfTen("20"));
SECTION_END()

TEST_END()
