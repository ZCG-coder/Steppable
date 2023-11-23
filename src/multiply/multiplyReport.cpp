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

#include "multiplyReport.hpp"

#include "symbols.hpp"
#include "util.hpp"

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

std::string reportMultiply(const std::string& a,
                           const std::string& b,
                           const std::vector<int>& finalProdDigits,
                           const std::vector<int>& finalProdCarries,
                           const std::vector<std::vector<int>>& prodDigitsOut,
                           const std::vector<std::vector<int>>& carries,
                           int steps)
{
    std::stringstream ss;
    unsigned long outputWidth;

    if (steps == 2)
    {
        outputWidth = prodDigitsOut[0].size() * 3 - 2;
        ss << std::right << std::setw(outputWidth + 3) << makeWider(a) << std::endl;
        ss << MULTIPLY << std::right << std::setw(outputWidth + 2) << makeWider(b) << std::endl;
        ss << std::string(outputWidth + 6, '_') << std::endl;

        for (int indexProdDigits = 0; indexProdDigits < prodDigitsOut.size(); indexProdDigits++)
        {
            auto subVector = removeLeadingZeros(prodDigitsOut[indexProdDigits]);

            ss << std::string(indexProdDigits * 3 + 3, ' ');
            for (int c : carries[indexProdDigits])
                if (c != 0)
                    ss << makeSubscript(std::to_string(c)) << "  ";
                else
                    ss << "   ";
            ss << std::endl;

            ss << std::string(indexProdDigits * 3 + 3, ' ');
            for (int i : subVector)
                if (i >= 0)
                    ss << i << "  ";
                else
                    ss << "   ";
            ss << std::endl;
        }

        // Display the full result. If there is just one result, do not show them again.
        if (prodDigitsOut.size() != 1)
        {
            ss << std::endl;
            ss << std::string(outputWidth + 6, '_') << std::endl << "   ";
            for (int i : finalProdCarries)
                if (i)
                    ss << makeSubscript(i + '0') << "  ";
                else
                    ss << "   ";
            ss << std::endl << "   ";

            for (int i : finalProdDigits)
                ss << i << "  ";
        }
    }
    else if (steps == 1)
        ss << a << " " MULTIPLY " " << b << " = ";
    if (steps == 1 or steps == 0)
    {
        auto vector = removeLeadingZeros(finalProdDigits);
        for (int i : vector)
            if (i >= 0)
                ss << i;
    }

    return ss.str();
}
