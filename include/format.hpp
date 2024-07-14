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
 * @file format.hpp
 * @brief This file contains the definition of the vFormat function template.
 *
 * The vFormat function template provides a convenient way to format strings using variable arguments.
 * It supports both C-style format strings and std::basic_string format strings.
 * The formatted string is returned as a std::basic_string object.
 *
 * Example usage:
 * @code
 * std::string formatted = vFormat("Hello, %s!", "world");
 * @endcode
 *
 * @author Andy Zhang
 * @date 27th November 2023
 */

#pragma once

#include <string>
#include <vector>

/**
 * @namespace steppable::__internals::format
 * @brief Contains string formatting utilities.
 */
namespace steppable::__internals::format
{
    std::string format(const std::string& format, const std::vector<std::string>& args);
} // namespace steppable::__internals::format
