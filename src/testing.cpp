/**************************************************************************************************
 * Copyright (c) 2023 NWSOFT                                                                      *
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

#include "testing.hpp"

#include "format.hpp"
#include "output.hpp"

#include <string_view>

TestCase::TestCase(const std::string& testCaseName) { this->testCaseName = testCaseName; }

void TestCase::assert(bool condition, const std::string_view& conditionName)
{
    if (condition)
    {
        info("%s PASSED", conditionName);
        return;
    }
    error("%i: Condition %s evaluates to false. FAILED", errorCount + 1, conditionName);
    errorCount++;
}

void TestCase::assertIsEqual(const std::string& a, const std::string& b)
{
    const std::string& conditionName = vFormat("String %s == %s", a.c_str(), b.c_str());
    assert(a == b, conditionName);
}

void TestCase::assertIsNotEqual(const std::string& a, const std::string& b)
{
    const std::string& conditionName = vFormat("String %s != %s", a.c_str(), b.c_str());
    assert(a != b, conditionName);
}

void TestCase::assertIsEqual(const int a, const int b)
{
    const std::string& conditionName = vFormat("Integer %i == %i", a, b);
    assert(a == b, conditionName);
}

void TestCase::assertIsNotEqual(const int a, const int b)
{
    const std::string& conditionName = vFormat("Integer %i != %i", a, b);
    assert(a != b, conditionName);
}

void TestCase::assertTrue(const bool value)
{
    const std::string& conditionName = vFormat("%i is True", value);
    assert(value, conditionName);
}

void TestCase::assertFalse(const bool value)
{
    const std::string& conditionName = vFormat("%i is False", value);
    assert(not value, conditionName);
}

void TestCase::summarize()
{
    if (errorCount == 1)
        std::cout << colors::red << '[' << testCaseName << ": Total " << errorCount << " error]" << reset << std::endl;
    else if (errorCount > 1)
        std::cout << colors::red << '[' << testCaseName << ": Total " << errorCount << " errors]" << reset << std::endl;
    else
        std::cout << colors::brightGreen << '[' << testCaseName << ": All tests passed]" << reset << std::endl;
}
