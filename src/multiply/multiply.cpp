#include "argParse.hpp"
#include "multiplyReport.hpp"
#include "symbols.hpp"
#include "util.hpp"

#include <algorithm>
#include <ios>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

std::string multiply(const std::string_view& a, const std::string_view& b, const int steps)
{
    const auto& [aInteger, aDecimal, bInteger, bDecimal] = splitNumber(a, b, false);
    std::string aStr = aInteger + aDecimal, bStr = bInteger + bDecimal;
    std::vector<std::vector<int>> prodDigits, carries;

    for (int indexB = 0; indexB < bStr.length(); indexB++)
    {
        int bDigit = bStr[indexB] - '0';
        if (bDigit == 0)
            continue;
        std::vector<int> currentProdDigits(aStr.length() + bStr.length() + 1, 0),
            currentCarries(aStr.length() + bStr.length() + 1, 0);
        for (auto indexA = aStr.length() - 1; indexA != -1; indexA--)
        {
            int aDigit = aStr[indexA] - '0';
            int prodDigit = bDigit * aDigit + currentCarries[indexA + 1];
            currentCarries[indexA] = prodDigit / 10;
            if (currentCarries[indexA] > 10)
            {
                currentCarries[indexA + 1]++;
                currentCarries[indexA] /= 10;
            }
            prodDigit %= 10;
            currentProdDigits[indexA + 1] = prodDigit; // Move back 1 to make room for carry
        }
        currentProdDigits[0] = currentCarries[0]; // The digit at index 0 is the carry, but was never added in the loop
        prodDigits.push_back(currentProdDigits);
        carries.push_back(currentCarries);
    }

    // Copy the original prodDigits to this new variable, because we'll be modifying prodDigits for output formatting.
    auto prodDigitsOut(prodDigits);
    for (int index = 0; index < prodDigits.size(); index++)
    {
        prodDigits[index].resize(prodDigits[index].size() - index - 1);
        prodDigitsOut[index].resize(prodDigitsOut[index].size() - index - 1);
        prodDigits[index].insert(prodDigits[index].begin(), index, 0);
    }

    // Add the vectors digit-wise together
    std::vector<int> finalProdDigits(prodDigits[0].size(), 0), finalProdCarries(prodDigits[0].size(), 0);
    for (auto indexDigit = finalProdDigits.size() - 1; indexDigit != -1; indexDigit--)
    {
        int sum = finalProdCarries[indexDigit];
        for (auto& prodDigitVector : prodDigits)
            sum += prodDigitVector[indexDigit];
        if (indexDigit != 0)
        {
            finalProdCarries[indexDigit - 1] = sum / 10;
            finalProdDigits[indexDigit - 1] += sum / 10;
        }
        else
        {
            finalProdCarries[indexDigit] = sum / 10;
            finalProdDigits[indexDigit] += sum / 10;
        }
        sum %= 10;
        finalProdDigits[indexDigit] = sum;
    }

    return reportMultiply(aStr, bStr, finalProdDigits, finalProdCarries, prodDigitsOut, carries, steps);
}

int main(const int _argc, const char* _argv[])
{
    UTF8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', "Number 1");
    program.addPosArg('b', "Number 2");
    program.addKeywordArg("steps", 2, "Amount of steps while multiplying");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    int steps = program.getKeywordArgument("steps");
    bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(Column Method Multiplication)
        std::cout << "Column Method Multiplication :\n" << multiply(aStr, bStr, steps) << std::endl;
        TOC()
    }
    else
        std::cout << multiply(aStr, bStr, steps) << std::endl;
}
