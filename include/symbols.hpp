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
 * @file symbols.hpp
 * @brief This file contains the definitions of various symbols used in the project.
 *
 * The symbols include mathematical operators, subscripts, and superscripts.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 */

#pragma once

#include <array>
#include <string>

namespace steppable::__internals::symbols
{
/// @brief The because symbol (3 dots in a triangle, Unicode U+2235)
#define BECAUSE "\u2235"
/// @brief The therefore symbol (3 dots in a triangle, Unicode U+2234)
#define THEREFORE "\u2234"

/// @brief The multiply symbol (Unicode U+00D7)
#define MULTIPLY "\u00D7"
/// @brief The divide symbol (Unicode U+00F7)
#define DIVIDED_BY "\u00F7"

#define SURD "\u221A"
#define COMBINE_MACRON "\u0305"

/// @brief The large dot symbol (Unicode U+25C9)
#define LARGE_DOT "\u25C9"
#define ABOVE_DOT "\u02D9"

// Subscripts
/**
 * @brief The subscript 0 (Unicode U+2080)
 * @note This is used to check if a subscript is converted correctly, do not use this in the program.
 */
#define SUB_0 "\u2080"
/**
 * @brief The subscript z (Unicode U+2098)
 * @note This is used to check if a subscript is converted correctly, do not use this in the program.
 */
#define SUB_Z "\u1D69"
/**
 * @brief The subscript magic number (8272)
 * @note This is used to check if a subscript is converted correctly, do not use this in the program.
 */
#define SUB_MAGIC_NUMBER 8272

    /// @brief A list of subscript characters.
    extern const std::array<std::string_view, 10>& SUPERSCRIPTS;

    /**
     * @brief Create a subscript string from a normal string.
     *
     * @param[in] normal The normal string.
     * @return The subscript string.
     */
    std::string makeSubscript(const std::string& normal);

    /**
     * @brief Create a subscript string from a normal integer.
     *
     * @param[in] normal The normal integer.
     * @return The subscript string.
     */
    std::string makeSubscript(int normal);

// Superscripts
/**
 * @brief The superscript 0 (Unicode U+2070)
 * @note This is used to check if a superscript is converted correctly, do not use this in the program.
 */
#define SUP_0 "\u2070"
/**
 * @brief The superscript z (Unicode U+1DBB)
 * @note This is used to check if a superscript is converted correctly, do not use this in the program.
 */
#define SUP_Z "\u1DBB"
/**
 * @brief The superscript magic number (8304)
 * @note This is used to check if a superscript is converted correctly, do not use this in the program.
 */
#define SUP_MAGIC_NUMBER 8304

    /**
     * @brief Create a superscript string from a normal string.
     *
     * @param[in] normal The normal string.
     * @return The superscript string.
     */
    std::string makeSuperscript(const std::string& normal);

    /**
     * @brief Create a superscript string from a normal character.
     *
     * @param[in] normal The normal character.
     * @return The superscript string.
     */
    std::string_view makeSuperscript(char normal);

    /**
     * @brief Makes a surd expression from a radicand.
     *
     * @param radicand The radicand.
     * @return The surd expression.
     */
    std::string makeSurd(const std::string& radicand);
} // namespace steppable::__internals::symbols
