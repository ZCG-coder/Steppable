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

#pragma once

#include <string>
#include <string_view>

#define TEST_START()           \
    int main()                 \
    {                          \
        Utf8CodePage use_utf8; \
        int errors = 0;
#define SECTION(...)                                                                                 \
    {                                                                                                \
        const std::string& nameSection = #__VA_ARGS__;                                               \
        std::cout << colors::brightBlue << std::setw(80) << std::setfill('-') << reset << '\n'; \
        std::cout << colors::brightBlue << "[Testing: " << nameSection << ']' << reset << '\n'; \
        auto start = std::chrono::high_resolution_clock::now();                                      \
        auto _ = TestCase(nameSection);

#define SECTION_END()                                                                                            \
    auto end = std::chrono::high_resolution_clock::now();                                                        \
    auto duration =                                                                                              \
        std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start) \
            .count();                                                                                            \
    _.summarize();                                                                                               \
    std::cout << colors::brightBlue << '[' << nameSection << " took " << duration << "(microseconds) to finish]" \
              << reset << '\n';                                                                             \
    std::cout << reset << '\n';                                                                             \
    errors += _.errorCount;                                                                                      \
    }
#define TEST_END()                                                                               \
    if (errors)                                                                                  \
        error("Not all tests passed. There are %i errors.", errors);                             \
    else                                                                                         \
        info("All tests passed.");                                                               \
    std::cout << colors::brightBlue << std::setw(80) << std::setfill('=') << reset << '\n'; \
    if (errors)                                                                                  \
        return 1;                                                                                \
    }

class TestCase
{
private:
    void assert(bool condition, const std::string& conditionName);

    std::string_view testCaseName;

public:
    int errorCount = 0;

    TestCase(const std::string& testCaseName);

    void assertIsEqual(const std::string& a, const std::string& b);

    void assertIsNotEqual(const std::string& a, const std::string& b);

    void assertIsEqual(int a, int b);

    void assertIsNotEqual(int a, int b);

    void assertTrue(bool value);

    void assertFalse(bool value);

    void summarize() const;
};
