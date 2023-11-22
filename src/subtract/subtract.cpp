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

#include "argParse.hpp"
#include "fn/basicArithm.hpp"
#include "subtractReport.hpp"
#include "util.hpp"

#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

std::string subtract(const std::string_view& a, const std::string_view& b, const int steps)
{
    auto [aInteger, aDecimal, bInteger, bDecimal] = splitNumber(a, b);
    bool aIsDecimal = not isZeroString(aDecimal), bIsDecimal = not isZeroString(bDecimal);

    std::string aStr = aInteger + aDecimal, bStr = bInteger + bDecimal;
    std::reverse(aStr.begin(), aStr.end());
    std::reverse(bStr.begin(), bStr.end());

    std::vector<int> diffDigits(aStr.length(), 0);
    std::vector<int> borrows(aStr.length());
    std::copy(aStr.begin(), aStr.end(), borrows.begin());
    std::for_each(borrows.begin(), borrows.end(), [](int& c) { c -= '0'; });
    for (int index = 0; index < aStr.length(); index++)
    {
        int aDigit = borrows[index], bDigit = bStr[index] - '0';
        if (aStr[index] == ' ')
            aDigit = 0;
        if (bStr[index] == ' ')
            bDigit = 0;

        int diffDigit = aDigit - bDigit;
        diffDigits[index] = diffDigit;
        if (diffDigits[index] < 0)
        {
            diffDigits[index] += 10;
            borrows[index] += 10;
            diffDigits[index + 1]--;
            borrows[index + 1]--;
        }
    }

    // Add a decimal point
    if (aIsDecimal or bIsDecimal)
    {
        auto decimalPos = aDecimal.length();
        auto itSumDigits = diffDigits.begin();
        auto itCarries = borrows.begin();

        diffDigits.insert(itSumDigits + static_cast<long>(decimalPos), -1); // -1 indicating a decimal point
        borrows.insert(itCarries + static_cast<long>(decimalPos), -1); // Reserve the space
    }

    std::reverse(borrows.begin(), borrows.end());
    std::reverse(diffDigits.begin(), diffDigits.end());
    return reportSubtract(aInteger, aDecimal, bInteger, bDecimal, aIsDecimal, bIsDecimal, diffDigits, borrows, steps);
}

#ifndef NO_MAIN
int main(int _argc, const char* _argv[])
{
    UTF8CodePage _;
    ProgramArgs program(_argc, _argv);
    program.addPosArg('a', "");
    program.addPosArg('b', "");
    program.addKeywordArg("steps", 2, "steps while adding");
    program.addSwitch("profile", false, "profiling the program");
    program.parseArgs();

    int steps = program.getKeywordArgument("steps");
    bool profile = program.getSwitch("profile");
    const auto& aStr = program.getPosArg(0);
    const auto& bStr = program.getPosArg(1);

    if (profile)
    {
        TIC(Column Method Addition)
        std::cout << "Column Method Addition :\n" << subtract(aStr, bStr) << std::endl;
        TOC()
    }
    else
        std::cout << subtract(aStr, bStr, steps) << std::endl;
}
#endif
