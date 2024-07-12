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
#include <string>

using namespace steppable::__internals;

TEST_START()
SECTION(Test format)
const std::string& formatOrig = "Hello, {0}!";
const std::string& arg = "world";
const std::string& expected = "Hello, world!";

const std::string& result = format::format(formatOrig, { arg });
_.assertIsEqual(result, expected);
SECTION_END()

SECTION(Test format with multiple values)
const std::string& formatOrig = "{0}, {1}!";
const std::string& arg1 = "Hello";
const std::string& arg2 = "world";
const std::string& expected = "Hello, world!";

const std::string& result = format::format(formatOrig, { arg1, arg2 });
_.assertIsEqual(result, expected);
SECTION_END()

SECTION(Test format with multiple values reversed)
const std::string& formatOrig = "{1}, {0}!";
const std::string& arg1 = "world";
const std::string& arg2 = "Hello";
const std::string& expected = "Hello, world!";

const std::string& result = format::format(formatOrig, { arg1, arg2 });
_.assertIsEqual(result, expected);
SECTION_END()

TEST_END()
