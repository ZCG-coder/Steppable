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

#include "testing.hpp"

#include "format.hpp"
#include "getString.hpp"
#include "output.hpp"

#include <string>
#include <utility>

using namespace std::literals;
using namespace steppable::output;
using namespace steppable::localization;
using namespace steppable::utils;

namespace steppable::testing
{
    TestCase::TestCase(std::string testCaseName) : testCaseName(std::move(testCaseName)) {}

    void TestCase::_assertCondition(const bool condition, const std::string& _conditionName)
    {
        std::string conditionName = _conditionName;
        if (condition)
        {
            conditionName = conditionName.substr(0, 50) + " /* snip */";
            info("TestCase::assert"s,
                 $("steppable::testing", "21357416-4f5d-4681-9724-bfcd95d222ea", { conditionName }));
            return;
        }
        error("TestCase::assert",
              $("steppable::testing",
                "db27423d-347d-47c6-ba24-66a551a54281",
                { std::to_string(errorCount + 1), conditionName }));
        errorCount++;
    }

    void TestCase::assertIsEqual(const std::string& a, const std::string& b)
    {
        const std::string& conditionName = $("steppable::testing", "40d80afc-fc96-4718-b5cd-4252923f3226", { a, b });
        _assertCondition(a == b, conditionName);
    }

    void TestCase::assertIsNotEqual(const std::string& a, const std::string& b)
    {
        const std::string& conditionName = $("steppable::testing", "bdc4cbb7-57ee-4bc5-99e9-07c771d67677", { a, b });
        _assertCondition(a != b, conditionName);
    }

    void TestCase::assertTrue(const bool value)
    {
        const std::string& conditionName = $(
            "steppable::testing", "20edcf43-774e-4933-a500-313cde4076c9", { std::to_string(static_cast<int>(value)) });
        _assertCondition(value, conditionName);
    }

    void TestCase::assertFalse(const bool value)
    {
        const std::string& conditionName = $(
            "steppable::testing", "f888ae76-1e1b-4174-8ae2-e20fcab98876", { std::to_string(static_cast<int>(value)) });
        _assertCondition(not value, conditionName);
    }

    void TestCase::summarize() const
    {
        if (errorCount != 0)
            std::cout << colors::red
                      << $("steppable::testing",
                           "21309d90-48eb-4ba1-a7f1-1683509b7119",
                           { testCaseName, std::to_string(errorCount) })
                      << reset << '\n';
        else
            std::cout << colors::brightGreen << $("steppable::testing", "262c6c76-8078-47de-b782-0085f543bb6e") << reset
                      << '\n';
    }
} // namespace steppable::testing
