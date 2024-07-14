/**************************************************************************************************
 * Copyright (c) 2023-2024 NWSOFT                                                                 *
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

/**
 * @file baseConvertReport.cpp
 * @brief This file contains the implementation of the reportBaseConvert function, which reports the converted number to
 * the user.
 * @warning Still work-in-progress.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 */

#include "baseConvertReport.hpp"

#include "getString.hpp"
#include "symbols.hpp"

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

using namespace std::string_literals;
using namespace steppable::__internals::symbols;
using namespace steppable::localization;

std::string reportBaseConvertStep(const std::string& _number,
                                  const std::string& _base,
                                  const std::string& _quotient,
                                  const std::string& _remainder)
{
    std::stringstream ss;
    ss << _number << " " << DIVIDED_BY << " " << _base << " = " << _quotient << " ... " << _remainder;
    return ss.str();
}

std::string reportBaseConvert(const std::string& _number,
                              const std::string& _base,
                              const std::vector<std::string>& _result,
                              const int steps)
{
    std::stringstream ss;

    if (steps == 2)
        ss << THEREFORE << $("baseConvert", "8a0b5c6d-b1a8-49b4-99fd-b1710744f4bf", { _number, _base });
    else if (steps == 1)
        ss << _number << steppable::__internals::symbols::makeSubscript("10") << " = ";
    // Output the result in reverse order
    auto result = _result;
    std::reverse(result.begin(), result.end());
    for (const auto& item : result)
        ss << item;
    if (steps == 1)
        ss << steppable::__internals::symbols::makeSubscript(_base);
    return ss.str();
}
