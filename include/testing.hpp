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

/**
 * @file testing.hpp
 * @brief This file contains the declaration of the TestCase class and macros for testing.
 *
 * The TestCase class provides methods for asserting test conditions and summarizing test results.
 * The macros TEST_START, SECTION, SECTION_END, and TEST_END are used to define test sections and execute tests.
 */

#pragma once

#include "format.hpp"
#include "types/concepts.hpp"

#include <string>

using namespace std::literals;

/// @brief This macro defines the main function and initializes the Utf8CodePage object, and prepares the error counter.
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define TEST_START()                                         \
    /* NOLINTNEXTLINE(bugprone-exception-escape) */          \
    int main()                                               \
    {                                                        \
        using namespace steppable::__internals::stringUtils; \
        using namespace steppable::__internals::utils;       \
        using namespace steppable::testing;                  \
        using namespace steppable::output;                   \
        Utf8CodePage use_utf8;                               \
        int errors = 0;

/// @brief This macro defines a test section with the given name.
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define SECTION(...)                                                                            \
    {                                                                                           \
        const std::string& nameSection = #__VA_ARGS__;                                          \
        std::cout << colors::brightBlue << std::setw(80) << std::setfill('-') << reset << '\n'; \
        std::cout << colors::brightBlue << "[Testing: " << nameSection << ']' << reset << '\n'; \
        auto start = std::chrono::high_resolution_clock::now();                                 \
        auto _ = TestCase(nameSection);

/// @brief This macro ends a test section and prints the time taken to execute the section.
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define SECTION_END()                                                                                            \
    auto end = std::chrono::high_resolution_clock::now();                                                        \
    auto duration =                                                                                              \
        std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start) \
            .count();                                                                                            \
    _.summarize();                                                                                               \
    std::cout << colors::brightBlue << '[' << nameSection << " took " << duration << "(microseconds) to finish]" \
              << reset << '\n';                                                                                  \
    std::cout << reset << '\n';                                                                                  \
    errors += _.errorCount;                                                                                      \
    }

/// @brief This macro ends the main function and prints the number of errors encountered.
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define TEST_END()                                                                                      \
    if (errors)                                                                                         \
        error("TEST_END"s, "Not all tests passed. There are {0} errors."s, { std::to_string(errors) }); \
    else                                                                                                \
        info("TEST_END"s, "All tests passed."s);                                                        \
    std::cout << colors::brightBlue << std::setw(80) << std::setfill('=') << reset << '\n';             \
    if (errors)                                                                                         \
        return 1;                                                                                       \
    }

/**
 * @namespace steppable::testing
 * @brief Includes testing utilities for Steppable.
 */
namespace steppable::testing
{
    /**
     * @class TestCase
     * @brief Represents a test case for unit testing.
     */
    class TestCase
    {
    private:
        /**
         * @brief Asserts a given condition and logs the condition name if it fails.
         * @param[in] condition The condition to be checked.
         * @param[in] conditionName The name of the condition.
         */
        void _assertCondition(bool condition, const std::string& conditionName);

        std::string testCaseName;

    public:
        int errorCount = 0; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)

        /**
         * @brief Constructs a new TestCase object with the given name.
         * @param[in] testCaseName The name of the test case.
         */
        explicit TestCase(std::string testCaseName);

        /**
         * @brief Asserts that two strings are equal.
         * @param[in] a The first string.
         * @param[in] b The second string.
         */
        void assertIsEqual(const std::string& a, const std::string& b);

        /**
         * @brief Asserts that two strings are not equal.
         * @param[in] a The first string.
         * @param[in] b The second string.
         */
        void assertIsNotEqual(const std::string& a, const std::string& b);

        /**
         * @brief Asserts that two numeric values are equal.
         * @param[in] a The first object.
         * @param[in] b The second object.
         */
        template<concepts::Numeric ValueT>
        void assertIsEqual(ValueT a, ValueT b)
        {
            const std::string& conditionName =
                __internals::format::format("Value {0} == {1}", { std::to_string(a), std::to_string(b) });
            _assertCondition(a == b, conditionName);
        }

        /**
         * @brief Asserts that two numeric values are not equal.
         * @param[in] a The first object.
         * @param[in] b The second object.
         */
        template<concepts::Numeric ValueT>
        void assertIsNotEqual(ValueT a, ValueT b)
        {
            const std::string& conditionName =
                __internals::format::format("Value {0} != {1}", { std::to_string(a), std::to_string(b) });
            _assertCondition(a != b, conditionName);
        }

        /**
         * @brief Asserts that two objects with .present() method are equal.
         * @param[in] a The first object.
         * @param[in] b The second object.
         */
        template<concepts::Presentable ValueT>
        void assertIsEqual(ValueT a, ValueT b)
        {
            const std::string& conditionName =
                __internals::format::format("Object {0} == {1}", { a.present(), b.present() });
            _assertCondition(a == b, conditionName);
        }

        /**
         * @brief Asserts that two objects with .present() method are not equal.
         * @param[in] a The first object.
         * @param[in] b The second object.
         */
        template<concepts::Presentable ValueT>
        void assertIsNotEqual(ValueT a, ValueT b)
        {
            const std::string& conditionName =
                __internals::format::format("Object {0} != {1}", { a.present(), b.present() });
            _assertCondition(a != b, conditionName);
        }

        /**
         * @brief Asserts that a boolean value is true.
         * @param[in] value The boolean value to be checked.
         */
        void assertTrue(bool value);

        /**
         * @brief Asserts that a boolean value is false.
         * @param[in] value The boolean value to be checked.
         */
        void assertFalse(bool value);

        /**
         * @brief Prints a summary of the test case, including the number of errors encountered.
         */
        void summarize() const;
    };
} // namespace steppable::testing
