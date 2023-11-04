#include <string_view>
#define TEST_START() \
    int main()       \
    {
#define SECTION(...)                                                                                         \
    {                                                                                                        \
        const char* nameSection = #__VA_ARGS__;                                                              \
        std::cout << colors::brightBlue << std::setw(80) << std::setfill('-') << '\0' << reset << std::endl; \
        std::cout << colors::brightBlue << "[Testing: " << nameSection << ']' << reset << std::endl;         \
        auto start = std::chrono::high_resolution_clock::now();                                              \
        auto testCase = TestCase(static_cast<std::string>(nameSection));

#define SECTION_END()                                                                                            \
    auto end = std::chrono::high_resolution_clock::now();                                                        \
    auto duration =                                                                                              \
        std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start) \
            .count();                                                                                            \
    testCase.summarize();                                                                                        \
    std::cout << colors::brightBlue << '[' << nameSection << " took " << duration << "(microseconds) to finish]" \
              << reset << std::endl;                                                                             \
    std::cout << colors::brightBlue << std::setw(80) << std::setfill('-') << '\0';                               \
    std::cout << reset << std::endl;                                                                             \
    }
#define TEST_END() }

class TestCase
{
private:
    void assert(bool condition, const std::string_view& conditionName);

    std::string_view testCaseName;

    int errorCount = 0;

public:
    TestCase(const std::string_view& testCaseName);

    void assertIsEqual(const std::string_view& a, const std::string_view& b);

    void assertIsNotEqual(const std::string_view& a, const std::string_view& b);

    void summarize();
};