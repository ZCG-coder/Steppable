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

#include "rounding.hpp"

#include "fn/basicArithm.hpp"
#include "util.hpp"

#include <string>

namespace steppable::__internals::numUtils
{
    std::string roundOff(const std::string& _number)
    {
        auto number = _number;
        if (number.empty())
            return "0";
        if (number.find('.') == std::string::npos)
            return number;
        auto splitNumberResult = splitNumber(number, "0", false, false, true).splitNumberArray;
        auto integer = splitNumberResult[0], decimal = splitNumberResult[1];

        if (arithmetic::compare(decimal, "5", 0) != "1")
            return integer + "." + decimal;
        return arithmetic::add(integer, "1", 0) + "." + decimal;
    }
} // namespace steppable::__internals::numUtils