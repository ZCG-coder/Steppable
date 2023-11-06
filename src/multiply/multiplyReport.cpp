#include "multiplyReport.hpp"

#include "symbols.hpp"

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
                if (i > 0)
                    ss << i << "  ";
                else
                    ss << "   ";
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
            else
                ss << ' ';
    }

    return ss.str();
}
