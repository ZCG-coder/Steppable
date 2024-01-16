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

/**************************************************************************************************
 * @file symbols.hpp
 * @brief This file contains the definitions of various symbols used in the project.
 *
 * The symbols include mathematical operators, subscripts, and superscripts.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 **************************************************************************************************/

#pragma once

#include <array>
#include <string>

#define BECAUSE "\u2235"
#define THEREFORE "\u2234"

#define MULTIPLY "\u00D7"
#define DIVIDED_BY "\u00F7"

#define LARGE_DOT "\u25C9"

// Subscripts
#define SUB_0 "\u2080"
#define SUB_Z "\u1D69"
#define SUB_MAGIC_NUMBER 8272

extern const std::array<std::string_view, 10>& SUPERSCRIPTS;

/**
 * @brief Create a subscript string from a normal string.
 *
 * @param normal The normal string.
 * @return The subscript string.
 */
std::string makeSubscript(const std::string& normal);

/**
 * @brief Create a subscript string from a normal integer.
 *
 * @param normal The normal integer.
 * @return The subscript string.
 */
std::string makeSubscript(int normal);

// Superscripts
#define SUP_0 "\u2070"
#define SUP_Z "\u1DBB"
#define SUP_MAGIC_NUMBER 8304

/**
 * @brief Create a superscript string from a normal string.
 *
 * @param normal The normal string.
 * @return The superscript string.
 */
std::string makeSuperscript(const std::string& normal);

/**
 * @brief Create a superscript string from a normal character.
 *
 * @param normal The normal character.
 * @return The superscript string.
 */
std::string_view makeSuperscript(char normal);
