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

#include "rootReport.hpp"

#include "symbols.hpp"

#include <sstream>
#include <string>

using namespace steppable::__internals::symbols;
using namespace steppable::prettyPrint::printers;

std::string reportRootPower(const std::string& _number,
                            const std::string& base,
                            const steppable::Fraction& fraction,
                            const std::string& rootResult,
                            const int steps)
{
    const auto& array = fraction.asArray();
    std::stringstream ss;

    if (steps == 2)
        ss << "The base " << base << " is a decimal. Therefore, we need to perform a power operation first." << '\n';
    if (steps >= 1)
    {
        ss << ppRoot(_number, base) << '\n';
        ss << "= " << ppRoot(ppSuperscript(_number, array[0]), array[1]) << "\n= ";
    }
    ss << rootResult;
    return ss.str();
}

std::string reportRoot()
{
    // Intentionally not implemented.
    return "";
}
