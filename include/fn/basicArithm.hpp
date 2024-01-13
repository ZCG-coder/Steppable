/**************************************************************************************************
 * Copyright (c) 2024 NWSOFT                                                                      *
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

#pragma once

#include "output.hpp"

#include <exception>
#include <string>
#include <string_view>

std::string abs(const std::string_view& _number, const int steps);
std::string add(const std::string_view& a, const std::string_view& b, int steps = 2, bool negative = false);
std::string compare(const std::string_view& a, const std::string_view& b, int steps = 2);
std::string decimalConvert(const std::string_view& _inputString, const std::string_view& baseString, int steps = 2);
std::string divide(const std::string_view& number, const std::string_view& divisor, int steps = 2, int decimals = 5);
std::string multiply(const std::string_view& a, const std::string_view& b, int steps = 2);
std::string power(std::string_view _number, const std::string_view& raiseTo, int steps = 2);
std::string subtract(const std::string_view& a,
                     const std::string_view& b,
                     int steps = 2,
                     bool noMinus = false,
                     bool negative = false);

template<typename Pred>
void loop(const std::string_view& times, Pred predicate)
{
    std::string current = "0";
    auto result = compare(current, times, 0);

    while (result == "0")
    {
        try
        {
            predicate(current);
        }
        catch (std::exception e)
        {
            error("Exception occurred in predicate.");
            error("Exception message: %s", e.what());
        }
        current = add(current, "1", 0);
        result = compare(current, times, 0);
    }
}
