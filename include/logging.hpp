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

/**
 * @file logging.hpp
 * @brief This file contains the declaration of the Logger class.
 * The Logger class provides logging functionality, including logging messages at different levels, such as error,
 * warning, info, and debug. It writes the log messages to a specified log file.
 *
 * Example usage:
 * @code
 * auto logger = logging::Logger("main", "steppable.log");
 * logger.error("Invalid input: " + input);
 */

#pragma once

#include <fstream>
#include <string>

namespace logging
{
    /**
     * @enum Level
     * @brief Enumeration of logging levels.
     *
     * The Level enum represents different levels of logging, including ERROR, WARNING, INFO, and DBG.
     */
    enum Level
    {
        ERROR = 3,
        WARNING = 2,
        INFO = 1,
        DBG = 0
    };

    /**
     * @class Logger
     * @brief The Logger class provides logging functionality.
     *
     * The Logger class allows logging messages at different levels, such as error, warning, info, and debug.
     * It writes the log messages to a specified log file.
     */
    class Logger
    {
    public:
        /**
         * @brief Constructs a Logger object.
         * @param name The name of the logger.
         * @param filename The name of the log file.
         * @param level The logging level (default: Level::INFO).
         */
#if DEBUG
        Logger(const std::string& name, const std::string& filename, const Level level = Level::DBG);
#else
        Logger(const std::string& name, const std::string& filename, const Level level = Level::INFO);
#endif

        /**
         * @brief Destroys the Logger object.
         */
        ~Logger();

        /**
         * @brief Logs an error message.
         * @param message The error message to be logged.
         */
        void error(const std::string& message);

        /**
         * @brief Logs an error message with additional arguments.
         * @param message The error message to be logged.
         * @param args The additional arguments.
         */
        template<typename... Args>
        void error(const std::string& message, Args&&... args)
        {
            auto formattedMsg = vFormat(message, args...);
            error(formattedMsg);
        }

        /**
         * @brief Logs a warning message.
         * @param message The warning message to be logged.
         */
        void warning(const std::string& message);

        /**
         * @brief Logs a warning message with additional arguments.
         * @param message The warning message to be logged.
         * @param args The additional arguments.
         */
        template<typename... Args>
        void warning(const std::string& message, Args&&... args)
        {
            auto formattedMsg = vFormat(message, args...);
            warning(formattedMsg);
        }

        /**
         * @brief Logs an info message.
         * @param message The info message to be logged.
         */
        void info(const std::string& message);

        /**
         * @brief Logs a debug message.
         * @param message The debug message to be logged.
         */
        void debug(const std::string& message);

        /**
         * @brief Logs a debug message with additional arguments.
         * @param message The debug message to be logged.
         * @param args The additional arguments.
         */
        template<typename... Args>
        void debug(const std::string& message, Args&&... args)
        {
            auto formattedMsg = vFormat(message, args...);
            debug(formattedMsg);
        }

    private:
        std::ofstream file; /**< The log file stream. */
        Level level = Level::INFO; /**< The logging level. */
        std::string name; /**< The name of the logger. */

        /**
         * @brief Logs a message.
         * @param message The message to be logged.
         */
        void log(const std::string& message);
    };
} // namespace logging
