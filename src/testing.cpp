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

#include "testing.hpp"

#include "format.hpp"
#include "output.hpp"

#include <string>
#include <utility>

using namespace std::literals;
using namespace steppable::output;

namespace steppable::testing
{
    TestCase::TestCase(std::string testCaseName) : testCaseName(std::move(testCaseName)) {}

    void TestCase::assert(const bool condition, const std::string& conditionName)
    {
        if (condition)
        {
            info("TestCase::assert"s, "{0} PASSED"s, { conditionName });
            return;
        }
        error("TestCase::assert",
              "{0}: Condition {1} evaluates to false. FAILED"s,
              { std::to_string(errorCount + 1), conditionName });
        errorCount++;
    }

    void TestCase::assertIsEqual(const std::string& a, const std::string& b)
    {
        const std::string& conditionName = format::format("String {0} == {1}", { a, b });
        assert(a == b, conditionName);
    }

    void TestCase::assertIsNotEqual(const std::string& a, const std::string& b)
    {
        const std::string& conditionName = format::format("String {0} != {1}", { a, b });
        assert(a != b, conditionName);
    }

    void TestCase::assertIsEqual(const int a, const int b)
    {
        const std::string& conditionName =
            format::format("Integer {0} == {1}", { std::to_string(a), std::to_string(b) });
        assert(a == b, conditionName);
    }

    void TestCase::assertIsNotEqual(const int a, const int b)
    {
        const std::string& conditionName =
            format::format("Integer {0} != {1}", { std::to_string(a), std::to_string(b) });
        assert(a != b, conditionName);
    }

    void TestCase::assertTrue(const bool value)
    {
        const std::string& conditionName = format::format("{0} is True", { std::to_string(static_cast<int>(value)) });
        assert(value, conditionName);
    }

    void TestCase::assertFalse(const bool value)
    {
        const std::string& conditionName = format::format("{0} is False", { std::to_string(static_cast<int>(value)) });
        assert(not value, conditionName);
    }

    void TestCase::summarize() const
    {
        if (errorCount != 0)
            std::cout << colors::red << '[' << testCaseName << ": Total " << errorCount << " error(s)]" << reset
                      << '\n';
        else
            std::cout << colors::brightGreen << '[' << testCaseName << ": All tests passed]" << reset << '\n';
    }
} // namespace steppable::testing
