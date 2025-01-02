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

#include "logging.hpp"

#include "platform.hpp"

#include <chrono>
#include <fstream>
#include <iomanip>

namespace steppable::__internals::logging
{
#if DEBUG
    Logger::Logger(const std::string& name, const std::string& filename, const Level level) : level(level), name(name)
#else
    Logger::Logger(const std::string& name, const std::string& filename, const Level level) : level(level), name(name)
#endif
    {
        file.open(filename);
        info(name + " logger started");
    }

    Logger::~Logger() { file.close(); }

    void Logger::log(const std::string& message)
    {
        auto const now = std::chrono::system_clock::now();
        auto now_time = std::chrono::system_clock::to_time_t(now);
        auto localTime = utils::localtime_xp(&now_time);
        auto timestamp = std::put_time(&localTime, "%F %T %Z");
        file << '[' << timestamp << "] " << message << '\n';
    }

    void Logger::error(const std::string& message)
    {
        if (level <= Level::ERR)
            log(name + " - ERROR: " + message);
    }

    void Logger::warning(const std::string& message)
    {
        if (level <= Level::WARNING)
            log(name + " - WARNING: " + message);
    }

    void Logger::info(const std::string& message)
    {
        if (level <= Level::INFO)
            log(name + " - INFO: " + message);
    }

    void Logger::debug(const std::string& message)
    {
        if (level <= Level::DBG)
            log(name + " - DEBUG: " + message);
    }
} // namespace steppable::__internals::logging
