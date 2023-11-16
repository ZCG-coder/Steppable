/*
 * @Author: Andy Zhang
 * @Date:   2023-11-14 21:52:17
 * @Last Modified by:   Andy Zhang
 * @Last Modified time: 2023-11-15 22:38:27
 */

#include "powerReport.hpp"

#include "fn/basicArithm.hpp"
#include "symbols.hpp"

#include <sstream>

std::string reportPower(const std::string_view _number, const std::string_view& raiseTo, const int steps)
{
    std::stringstream ss;
    auto numberOrig = static_cast<std::string>(_number), number = static_cast<std::string>("1");

    loop(raiseTo, [&](const auto& i) {
        number = multiply(number, numberOrig, 0);
        const auto& currentPower = add(i, "1", 0);
        if (steps == 2)
        {
            ss << BECAUSE " " << multiply(number, numberOrig, 1) << std::endl;
            ss << THEREFORE " " << numberOrig << makeSuperscript(currentPower) << " = " << number << std::endl;
        }
    });

    if (steps == 1)
        ss << numberOrig << makeSuperscript(static_cast<std::string>(raiseTo)) << " = " << number;
    else if (steps == 0)
        ss << number;

    return ss.str();
}
