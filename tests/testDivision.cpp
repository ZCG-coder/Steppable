/**************************************************************************************************
 * Copyright (c) 2023 NWSOFT                                                                      *
 *                                                                                                *
 * Permission is hereby granted free of charge, to any person obtaining a copy                   *
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
SECTION(Integer division)
// A googol divided by 50
std::string a = "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
            b = "50", res = divide(a, b, 0, 0);

_.assertIsEqual(res,
                "2000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
SECTION_END()

SECTION(Integer divided by decimal)
// A googol divided by 79
std::string a = "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
            b = "79", res = divide(a, b, 0, 8);

_.assertIsEqual(
    res,
    "126582278481012658227848101265822784810126582278481012658227848101265822784810126582278481012658227.848101266");
SECTION_END()

SECTION(Decimal divided by decimal)
std::string a = "532.532132", b = "53524.2353", res = divide(a, b, 0, 8);

_.assertIsEqual(res, "0.009949364");
SECTION_END()

TEST_END()
