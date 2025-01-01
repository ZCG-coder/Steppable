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

/**
 * @file colors.hpp
 * @brief This file contains functions and macros for manipulating text colors and formats in the terminal.
 *
 * The functions and macros in this file allow users to change the text color, background color, and format of text
 * displayed in the terminal. It provides a set of predefined colors and formats, as well as the ability to define
 * custom colors using RGB values.
 *
 * The file also includes a function to check if the output stream is a terminal, and a function to reset the text
 * color and format to the default values.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 */

#pragma once

#include <ostream>

/**
 * @brief An ANSI Escape Sequence to set a custom RGB color code for the text.
 * @param[in] r The red component of the color.
 * @param[in] g The green component of the color.
 * @param[in] b The blue component of the color.
 * @warning The color code should be from 0 to 255. No error checking is performed.
 */
// RGB Text Colors (8-bit)
#define RGB_TEXT(r, g, b) "\x1b[38;2;" #r ";" #g ";" #b "m"

/**
 * @brief An ANSI Escape Sequence to set a custom RGB color code for the background.
 * @param[in] r The red component of the color.
 * @param[in] g The green component of the color.
 * @param[in] b The blue component of the color.
 * @warning The color code should be from 0 to 255. No error checking is performed.
 */
// RGB Background Colors (8-bit)
#define RGB_BG(r, g, b) "\x1b[48;2;" #r ";" #g ";" #b "m"

namespace steppable::__internals::utils
{
    /**
     * @brief Check if the output stream is a terminal.
     *
     * This function checks if the given output stream is associated with a terminal.
     *
     * @param[in] stream The output stream to check.
     * @return true if the output stream is a terminal, false otherwise.
     */
    bool isTerminal(const std::ostream& stream);

    /**
     * @brief Reset the text color and format to the default values.
     *
     * This function resets the text color and format to the default values.
     *
     * @param[in] stream The output stream to reset.
     * @return The modified output stream.
     */
    std::ostream& reset(std::ostream& stream);

    /**
     * @namespace steppable::__internals::utils::colors
     * @brief A namespace containing functions to set the text color in an output stream.
     */
    namespace colors
    {
        /**
         * @brief Set the text color to black.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& black(std::ostream& stream);

        /**
         * @brief Set the text color to red.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& red(std::ostream& stream);

        /**
         * @brief Set the text color to green.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& green(std::ostream& stream);

        /**
         * @brief Set the text color to yellow.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& yellow(std::ostream& stream);

        /**
         * @brief Set the text color to blue.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& blue(std::ostream& stream);

        /**
         * @brief Set the text color to magenta.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& magenta(std::ostream& stream);

        /**
         * @brief Set the text color to cyan.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& cyan(std::ostream& stream);

        /**
         * @brief Set the text color to white.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& white(std::ostream& stream);

        /**
         * @brief Set the text color to bright black.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& brightBlack(std::ostream& stream);

        /**
         * @brief Set the text color to bright red.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& brightRed(std::ostream& stream);

        /**
         * @brief Set the text color to bright green.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& brightGreen(std::ostream& stream);

        /**
         * @brief Set the text color to bright yellow.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& brightYellow(std::ostream& stream);

        /**
         * @brief Set the text color to bright blue.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& brightBlue(std::ostream& stream);

        /**
         * @brief Set the text color to bright magenta.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& brightMagenta(std::ostream& stream);

        /**
         * @brief Set the text color to bright cyan.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& brightCyan(std::ostream& stream);

        /**
         * @brief Set the text color to bright white.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& brightWhite(std::ostream& stream);
    } // namespace colors

    /**
     * @namespace steppable::__internals::utils::colorsBg
     * @brief A namespace containing functions to set the background color in an output stream.
     */
    namespace colorsBg
    {
        /**
         * @brief Set the background color to bright black.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& brightBlack(std::ostream& stream);

        /**
         * @brief Set the background color to bright red.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& brightRed(std::ostream& stream);

        /**
         * @brief Set the background color to bright green.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& brightGreen(std::ostream& stream);

        /**
         * @brief Set the background color to bright yellow.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& brightYellow(std::ostream& stream);

        /**
         * @brief Set the background color to bright blue.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& brightBlue(std::ostream& stream);

        /**
         * @brief Set the background color to bright cyan.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& brightCyan(std::ostream& stream);

        /**
         * @brief Set the background color to bright white.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& brightWhite(std::ostream& stream);
    } // namespace colorsBg

    /**
     * @namespace steppable::__internals::utils::formats
     * @brief A namespace containing functions to set the text format in an output stream.
     */
    namespace formats
    {
        /**
         * @brief Set the text format to bold.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& bold(std::ostream& stream);

        /**
         * @brief Set the text format to dim.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& dim(std::ostream& stream);

        /**
         * @brief Set the text format to underline.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& underline(std::ostream& stream);

        /**
         * @brief Set the text format to blink.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& blink(std::ostream& stream);

        /**
         * @brief Set the text format to reverse.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& reverse(std::ostream& stream);

        /**
         * @brief Set the text format to hidden.
         *
         * @param[in] stream The output stream to modify.
         * @return The modified output stream.
         */
        std::ostream& hidden(std::ostream& stream);
    } // namespace formats
} // namespace steppable::__internals::utils
