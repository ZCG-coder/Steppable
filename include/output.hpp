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
 * @file output.hpp
 * @brief This file contains functions for displaying error, warning, and info messages.
 *
 * The functions in this file provide a convenient way to display formatted error, warning, and info messages to the
 *console. The error function displays an error message in red color, the warning function displays a warning message in
 *yellow color, and the info function displays an info message in bright green color. These functions also write the
 *messages to a log file.
 *
 * Example usage:
 *
 * @code
 * error("main.cpp", "Invalid input: {}", input);
 * warning("main.cpp", "Unused variable: {}", variable);
 * info("main.cpp", "Program started successfully");
 * @endcode
 *
 * @author Andy Zhang
 * @date 25th October 2023
 */

#pragma once

#include "colors.hpp"
#include "format.hpp"
#include "logging.hpp"
#include "symbols.hpp"

#include <iostream>
#include <string>

namespace steppable::output
{
    using namespace steppable::__internals;
    using namespace steppable::__internals::utils;
    using namespace steppable::__internals::symbols;

    /**
     * @brief Prints an error message.
     *
     * This function prints an error message with the given name and message.
     * Additional arguments can be provided to format the message using the
     * `std::basic_string<T>` format syntax.
     *
     * The message is printed in red color, and is also written to the log file.
     * It is intended to tell the user that something is going wrong and cannot be handled.
     *
     * @tparam T The character type of the message.
     * @tparam Args The types of the additional arguments.
     * @param[in] name The name of the error.
     * @param[in] msg The error message.
     * @param[in] args Additional arguments for formatting the message.
     */
    template<typename T, typename... Args>
    void error(const std::string& name, std::basic_string<T> msg, Args... args)
    {
        auto formattedMsg = format::vFormat(std::string(msg), args...);
        std::cerr << colors::red << formats::bold << LARGE_DOT << " Error: " << reset << colors::red;
        std::cerr << formattedMsg << reset << '\n';

        // Write to the log file
        auto logger = logging::Logger(name, "steppable.log");
        logger.error(formattedMsg);
    }

    /**
     * @brief Prints an error message.
     *
     * This function prints an error message with the given name and message.
     * Additional arguments can be provided to format the message using the
     * `std::basic_string<T>` format syntax.
     *
     * The message is printed in red color, and is also written to the log file.
     * It is intended to tell the user that something is going wrong and cannot be handled.
     *
     * @tparam CharT The character type of the message.
     * @param[in] name The name of the error.
     * @param[in] msg The error message.
     */
    template<typename CharT>
    void error(const std::string& name, std::basic_string<CharT> msg)
    {
        std::cerr << colors::red << formats::bold << LARGE_DOT << " Error: " << reset << colors::red;
        std::cerr << msg << reset << '\n';

        // Write to the log file
        auto logger = logging::Logger(name, "steppable.log");
        logger.error(msg);
    }

    /**
     * @brief Prints a warning message.
     *
     * This function prints an error message with the given name and message.
     * Additional arguments can be provided to format the message using the
     * `std::basic_string<T>` format syntax.
     *
     * The message is printed in yellow color, and is also written to the log file.
     * It is intended to tell the user that something is going wrong but can be handled.
     *
     * @tparam T The character type of the message.
     * @tparam Args The types of the additional arguments.
     * @param[in] msg The error message.
     * @param[in] args Additional arguments for formatting the message.
     */
    template<typename T, typename... Args>
    [[maybe_unused]] void warning(T msg, Args... args)
    {
        std::cout << colors::yellow << formats::bold << LARGE_DOT << " Warning: " << reset << colors::yellow;
        std::cout << format::vFormat(msg, args...) << reset << '\n';
    }

    /**
     * @brief Prints an info message.
     *
     * This function prints an info message with the given name and message.
     * Additional arguments can be provided to format the message using the
     * `std::basic_string<T>` format syntax.
     *
     * The message is printed in bright green color.
     * It is intended to tell the user that something is going right, or to provide some information.
     *
     * @tparam T The character type of the message.
     * @tparam Args The types of the additional arguments.
     * @param[in] msg The info message.
     * @param[in] args Additional arguments for formatting the message.
     */
    template<typename T, typename... Args>
    void info(T msg, Args... args)
    {
        std::cout << colors::brightGreen << formats::bold << LARGE_DOT << " Info: " << reset << colors::brightGreen;
        std::cout << format::vFormat(msg, args...) << reset << '\n';
    }
} // namespace steppable::output
