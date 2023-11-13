#pragma once

#include <string_view>

#define TEST_START()           \
    int main()                 \
    {                          \
        UTF8CodePage use_utf8; \
        int errors = 0;
#define SECTION(...)                                                                                 \
    {                                                                                                \
        const std::string& nameSection = #__VA_ARGS__;                                               \
        std::cout << colors::brightBlue << std::setw(80) << std::setfill('-') << reset << std::endl; \
        std::cout << colors::brightBlue << "[Testing: " << nameSection << ']' << reset << std::endl; \
        auto start = std::chrono::high_resolution_clock::now();                                      \
        auto _ = TestCase(nameSection);

#define SECTION_END()                                                                                            \
    auto end = std::chrono::high_resolution_clock::now();                                                        \
    auto duration =                                                                                              \
        std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start) \
            .count();                                                                                            \
    _.summarize();                                                                                               \
    std::cout << colors::brightBlue << '[' << nameSection << " took " << duration << "(microseconds) to finish]" \
              << reset << std::endl;                                                                             \
    std::cout << reset << std::endl;                                                                             \
    errors += _.errorCount;                                                                                      \
    }
#define TEST_END()                                                                               \
    if (errors)                                                                                  \
        error("Not all tests passed. There are {} errors.", errors);                             \
    else                                                                                         \
        info("All tests passed.");                                                               \
    std::cout << colors::brightBlue << std::setw(80) << std::setfill('=') << reset << std::endl; \
    if (errors)                                                                                  \
        return 1;                                                                                \
    }

class TestCase
{
private:
    void assert(bool condition, const std::string_view& conditionName);

    std::string_view testCaseName;

public:
    int errorCount = 0;

    TestCase(const std::string_view& testCaseName);

    void assertIsEqual(const std::string_view& a, const std::string_view& b);

    void assertIsNotEqual(const std::string_view& a, const std::string_view& b);

    void assertIsEqual(const int a, const int b);

    void assertIsNotEqual(const int a, const int b);

    void assertTrue(bool value);

    void assertFalse(bool value);

    void summarize();
};
