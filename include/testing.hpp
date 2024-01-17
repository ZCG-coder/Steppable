/**************************************************************************************************
 * Copyright (c) 2024 NWSOFT                                                                      *
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

#include <string>
#include <string_view>

/// @brief This macro defines the main function and initializes the Utf8CodePage object, and prepares the error counter.
#define TEST_START()           \
    int main()                 \
    {                          \
        Utf8CodePage use_utf8; \
        int errors = 0;

/// @brief This macro defines a test section with the given name.
#define SECTION(...)                                                                            \
    {                                                                                           \
        const std::string& nameSection = #__VA_ARGS__;                                          \
        std::cout << colors::brightBlue << std::setw(80) << std::setfill('-') << reset << '\n'; \
        std::cout << colors::brightBlue << "[Testing: " << nameSection << ']' << reset << '\n'; \
        auto start = std::chrono::high_resolution_clock::now();                                 \
        auto _ = TestCase(nameSection);

/// @brief This macro ends a test section and prints the time taken to execute the section.
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
#define TEST_END()                                                                             \
    if (errors)                                                                                \
        error("TEST_END", (std::string) "Not all tests passed. There are %i errors.", errors); \
    else                                                                                       \
        info("All tests passed.");                                                             \
    std::cout << colors::brightBlue << std::setw(80) << std::setfill('=') << reset << '\n';    \
    if (errors)                                                                                \
        return 1;                                                                              \
    }

/**
 * @class TestCase
 * @brief Represents a test case for unit testing.
 */
class TestCase
{
private:
    /**
     * @brief Asserts a given condition and logs the condition name if it fails.
     * @param condition The condition to be checked.
     * @param conditionName The name of the condition.
     */
    void assert(bool condition, const std::string& conditionName);

    std::string_view testCaseName;

public:
    int errorCount = 0;

    /**
     * @brief Constructs a new TestCase object with the given name.
     * @param testCaseName The name of the test case.
     */
    TestCase(const std::string& testCaseName);

    /**
     * @brief Asserts that two strings are equal.
     * @param a The first string.
     * @param b The second string.
     */
    void assertIsEqual(const std::string& a, const std::string& b);

    /**
     * @brief Asserts that two strings are not equal.
     * @param a The first string.
     * @param b The second string.
     */
    void assertIsNotEqual(const std::string& a, const std::string& b);

    /**
     * @brief Asserts that two integers are equal.
     * @param a The first integer.
     * @param b The second integer.
     */
    void assertIsEqual(int a, int b);

    /**
     * @brief Asserts that two integers are not equal.
     * @param a The first integer.
     * @param b The second integer.
     */
    void assertIsNotEqual(int a, int b);

    /**
     * @brief Asserts that a boolean value is true.
     * @param value The boolean value to be checked.
     */
    void assertTrue(bool value);

    /**
     * @brief Asserts that a boolean value is false.
     * @param value The boolean value to be checked.
     */
    void assertFalse(bool value);

    /**
     * @brief Prints a summary of the test case, including the number of errors encountered.
     */
    void summarize() const;
};
