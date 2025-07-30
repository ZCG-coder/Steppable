/**************************************************************************************************
 * Copyright (c) 2023-2025 NWSOFT                                                                 *
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

#include "steppable/parameter.hpp"

namespace steppable::__internals::parameter
{
    void ParameterMap::checkParameterOrder(const std::vector<std::string>& names)
    {
        if (names.size() != values.size())
        {
            output::error("ParameterMap::checkParameterOrder"s, "Incorrect name vector size."s);
            utils::programSafeExit(1);
        }

        for (size_t i = 0; i < values.size(); i++)
            if (names[i] != values[i].name)
            {
                output::error("ParameterMap::checkParameterOrder"s,
                              "Name {0} mismatch. Expect {1}"s,
                              { values[i].name, names[i] });
                utils::programSafeExit(1);
            }
    }

    void ParameterMap::checkParameterNameUnordered(const std::vector<std::string>& names)
    {
        if (names.size() != values.size())
        {
            output::error("ParameterMap::checkParameterNameUnordered"s, "Incorrect name vector size."s);
            utils::programSafeExit(1);
        }
        for (const auto& obj : values)
            if (std::ranges::find(names, obj.name) == names.end())
            {
                output::error("ParameterMap::checkParameterNameUnordered"s, "Name {0} not found."s, { obj.name });
                utils::programSafeExit(1);
            }
    }
} // namespace steppable::__internals::parameter
