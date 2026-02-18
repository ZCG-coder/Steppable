/**************************************************************************************************
 * Copyright (c) 2023-2026 NWSOFT                                                                 *
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
#include "output.hpp"
#include "steppable/number.hpp"
#include "symbols.hpp"
#include "testing.hpp"
#include "util.hpp"

#include <iomanip>
#include <iostream>

TEST_START()

SECTION(Test table)

steppable::prettyPrint::Table table({
    { "Lorem\nipsum\ndolor"s, "sit\namet"s, "consectetur\nadipiscing\nelit"s, "sed\ndo"s, "eiusmod\ntempor"s },
    { "incididunt\nut"s, "labore\net\ndolore"s, "magna\naliqua"s, "ut\nenim\nad"s, "minim\nveniam"s },
    { "quis\nnostrud"s,
      { "CENTER\n\nALIGNED!!!", steppable::prettyPrint::HorizontalAlignment::CENTER },
      "laboris\nnisi\nut"s,
      "aliquip\nex"s,
      "ea\ncommodo"s },
    { "consequat\nduis"s, "aute\nirure\ndolor"s, "in\nreprehenderit"s, "in\nvoluptate\nvelit"s, "esse\ncillum"s },
    { "dolore\neu"s,
      "fugiat nulla\npariatur"s,
      { "RIGHT \nALIGNED!!!", steppable::prettyPrint::HorizontalAlignment::RIGHT },
      "occaecat\ncupidatat"s,
      "non\nproident"s },
    { "sunt\nin\nculpa"s, "qui\nofficia"s, "deserunt\nmollit"s, "anim\nid\nest"s, "laborum\nipsum"s },
    { "dolor\nsit"s, "amet\nconsectetur"s, "adipiscing\nelit\nsed"s, "do\neiusmod"s, "tempor\nincididunt\nut"s },
});

std::cout << table.present() << "\n";

SECTION_END()

TEST_END()