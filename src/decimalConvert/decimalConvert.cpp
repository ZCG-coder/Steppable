#include "fn/basicArithm.hpp"
#include "output.hpp"

#include <string>

std::string decimalConvert(const std::string& inputStr, const std::string& baseStr, int steps)
{
    std::string larger = compare(baseStr, "36");
    if (larger == "0")
    {
        error("The base is larger than 36, which means that it is impossible to represent the number.");
        return "";
    }

    std::string converted = "0";
    for (auto digit : inputStr)
    {
        auto decimalDigit = multiply(std::string(1, digit), baseStr);
        converted = add(converted, decimalDigit);
    }
    return converted;
}

#ifndef NO_MAIN
int main() {
    std::cout << decimalConvert("1", "2");
}
#endif
