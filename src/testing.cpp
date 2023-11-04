#include "testing.hpp"

#include "output.hpp"

#include <string_view>

TestCase::TestCase(const std::string_view& testCaseName) { this->testCaseName = testCaseName; }

void TestCase::assert(bool condition, const std::string_view& conditionName)
{
    if (condition)
    {
        info("in {}: {} PASSED", testCaseName, conditionName);
        return;
    }
    error("{} in {}: condition {} evaluates to false", errorCount + 1, testCaseName, conditionName);
    errorCount++;
}

void TestCase::assertIsEqual(const std::string_view& a, const std::string_view& b)
{
    const std::string& conditionName = std::format("{} == {}", a, b);
    assert(a == b, conditionName);
}

void TestCase::assertIsNotEqual(const std::string_view& a, const std::string_view& b)
{
    const std::string& conditionName = std::format("{} != {}", a, b);
    assert(a != b, conditionName);
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