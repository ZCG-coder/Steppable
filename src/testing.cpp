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

#include "testing.hpp"

#include "format.hpp"
#include "output.hpp"

#include <string>
#include <string_view>

using namespace std::literals;

TestCase::TestCase(const std::string& testCaseName) { this->testCaseName = testCaseName; }

void TestCase::assert(const bool condition, const std::string& conditionName)
{
    if (condition)
    {
        info("%s PASSED", conditionName.c_str());
        return;
    }
    error("TestCase::assert", "%i: Condition %s evaluates to false. FAILED"s, errorCount + 1, conditionName.c_str());
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

void TestCase::summarize() const
{
    if (errorCount == 1)
        std::cout << colors::red << '[' << testCaseName << ": Total " << errorCount << " error]" << reset << '\n';
    else if (errorCount > 1)
        std::cout << colors::red << '[' << testCaseName << ": Total " << errorCount << " errors]" << reset << '\n';
    else
        std::cout << colors::brightGreen << '[' << testCaseName << ": All tests passed]" << reset << '\n';
}
