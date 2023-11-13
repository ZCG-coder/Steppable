#include "testing.hpp"

#include "output.hpp"

#include <string_view>

TestCase::TestCase(const std::string_view& testCaseName) { this->testCaseName = testCaseName; }

void TestCase::assert(bool condition, const std::string_view& conditionName)
{
    if (condition)
    {
        info("{} PASSED", conditionName);
        return;
    }
    error("{}: Condition {} evaluates to false. FAILED", errorCount + 1, conditionName);
    errorCount++;
}

void TestCase::assertIsEqual(const std::string_view& a, const std::string_view& b)
{
    const std::string& conditionName = std::format("String {} == {}", a, b);
    assert(a == b, conditionName);
}

void TestCase::assertIsNotEqual(const std::string_view& a, const std::string_view& b)
{
    const std::string& conditionName = std::format("String {} != {}", a, b);
    assert(a != b, conditionName);
}

void TestCase::assertIsEqual(const int a, const int b)
{
    const std::string& conditionName = std::format("Integer {} == {}", a, b);
    assert(a == b, conditionName);
}

void TestCase::assertIsNotEqual(const int a, const int b)
{
    const std::string& conditionName = std::format("Integer {} != {}", a, b);
    assert(a != b, conditionName);
}

void TestCase::assertTrue(const bool value)
{
    const std::string& conditionName = std::format("{} is True", value);
    assert(value, conditionName);
}

void TestCase::assertFalse(const bool value)
{
    const std::string& conditionName = std::format("{} is False", value);
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
