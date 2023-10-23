#include "multiplyReport.hpp"

#include "symbols.hpp"

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

std::string reportMultiply(const std::string& a,
                           const std::string& b,
                           const std::vector<int>& finalProdDigits,
                           const std::vector<int>& finalProdCarries,
                           const std::vector<std::vector<int>>& prodDigitsOut,
                           const std::vector<std::vector<int>>& carries)
{
    std::stringstream ss;

    const int outputWidth = prodDigitsOut[0].size() * 3 - 2;
    ss << std::right << std::setw(outputWidth) << makeWider(a) << std::endl;
    ss << MULTIPLY << std::right << std::setw(outputWidth - 1) << makeWider(b) << std::endl;
    ss << std::string(outputWidth + 2, '_') << std::endl;

    for (int indexProdDigits = 0; indexProdDigits < prodDigitsOut.size(); indexProdDigits++)
    {
        auto subVector = prodDigitsOut[indexProdDigits];

        ss << std::string(indexProdDigits * 3, ' ');
        for (int c : carries[indexProdDigits])
            if (c != 0)
                ss << makeSubscript(std::to_string(c)) << "  ";
            else
                ss << "   ";
        ss << std::endl;

        ss << std::string(indexProdDigits * 3, ' ');
        for (int i : subVector)
            ss << i << "  ";
        ss << std::endl;
    }

    // Display the full result. If there is just one result, do not show them again.
    if (prodDigitsOut.size() != 1)
    {
        ss << std::string(outputWidth + 2, '_') << std::endl;
        for (int i : finalProdCarries)
            if (i)
                ss << makeSubscript(i + '0') << "  ";
            else
                ss << "   ";
        ss << std::endl;

        for (int i : finalProdDigits)
            ss << i << "  ";
    }

    return ss.str();
}
