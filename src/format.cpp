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

#include "format.hpp"

#include <stdexcept>
#include <string>
#include <vector>

namespace steppable::__internals::format
{

    std::string format(const std::string& format, const std::vector<std::string>& args)
    {
        // Format string
        // Original format:
        // {0} -> args[0]
        // {1} -> args[1]
        // ...
        // {n} -> args[n]

        std::string result = format;
        std::string index;
        bool inBrackets = false;
        for (char i : format)
        {
            switch (i)
            {
            // Start replacing!
            case '{':
            {
                inBrackets = true;
                index = i;
                break;
            }

            // End replacing
            case '}':
            {
                inBrackets = false;
                size_t argIndex = std::stoull(index.substr(1));
                if (argIndex >= args.size())
                    throw std::out_of_range("Argument index out of range.");

                // +1 for the closing bracket
                result.replace(result.find(index), index.size() + 1, args.at(argIndex));
                break;
            }

            default:
            {
                if (inBrackets)
                    index += i;
                break;
            }
            }
        }

        return result;
    }
} // namespace steppable::__internals::format
