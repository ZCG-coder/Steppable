#include "fn/basicArithm.hpp"
#include "output.hpp"

#include <string>

std::string decimalConvert(const std::string& inputStr, const std::string& baseStr, int steps)
{
    std::string larger = invokeCommand({ "compare ", baseStr, "36" }).output;
    if (larger == "0")
    {
        error("The base is larger than 36, which means that it is impossible to represent the number.");
        return "";
    }

    std::string converted = "0";
    for (auto digit : inputStr)
    {
        auto decimalDigit = invokeCommand({"multiply", std::string(1, digit), baseStr}).output;
        converted = invokeCommand({"add", converted, decimalDigit}).output;
    }
    return converted;
}

int main() {
    std::cout << decimalConvert("1", "2");
}
