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
 * @file platform.hpp
 * @brief This file contains platform-specific functions
 * As the name suggests, this file contains functions that are specific to a certain platform.
 * For example, the programSafeExit function uses std::quick_exit on Windows and exit on macOS,
 * because std::quick_exit is not implemented on macOS.
 *
 * @author Andy Zhang
 * @date 13th January 2024
 */

#pragma once

#include "output.hpp"

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>
#ifdef WINDOWS
    #include <shlobj.h>
    #include <windows.h>
#else
    #include <pwd.h>
    #include <sys/types.h>
    #include <unistd.h>
#endif

using namespace std::literals;

/**
 * @namespace steppable::__internals::utils
 * @brief Namespace for internal functions
 * @note This namespace should not be used by other programs outside of the Steppable core.
 */
namespace steppable::__internals::utils
{
    /**
     * @brief Exit the program safely
     *
     * This function exits the program safely with the given status code.
     * On Windows, it uses std::quick_exit, and on macOS, it uses exit,
     * because std::quick_exit is not implemented on macOS.
     *
     * @param[in] status The status code to exit with
     */
    inline void programSafeExit(const int status)
    {
#ifdef MACOSX
        exit(status); // NOLINT(concurrency-mt-unsafe)
#else
        std::quick_exit(status);
#endif
    }

    inline std::tm localtime_xp(std::time_t* timer)
    {
        std::tm bt{};
#if defined(__unix__)
        localtime_r(timer, &bt);
#elif defined(WINDOWS)
        localtime_s(&bt, timer);
#else
        static std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);
        bt = *std::localtime(timer); // NOLINT(concurrency-mt-unsafe)
#endif
        return bt;
    }

    inline std::string getHomeDirectory()
    {
        std::string homeDir;

#ifdef _WIN32
        char homePath[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PROFILE, NULL, 0, homePath)))
            homeDir = homePath;
        else
            output::error("platform::getHomeDirectory"s, "Error: Unable to get the home directory."s);
#else
        const char* homeEnv = std::getenv("HOME"); // NOLINT(concurrency-mt-unsafe)

        if (homeEnv != nullptr)
            homeDir = homeEnv;
        else
        {
            std::array<char, 4096> buffer{};
            std::array<char, 4096> errBuffer{};
            const char* homeEnv = nullptr;
            int error = 0;
            struct passwd pw
            {
            };
            struct passwd* result = nullptr;

            uid_t userId = getuid();
            error = getpwuid_r(userId, &pw, buffer.data(), sizeof(buffer), &result);

            if (result != nullptr)
                homeDir = pw.pw_dir;
            else if (error != 0)
            {
                strerror_r(error, errBuffer.data(), errBuffer.size());
                output::error("platform::getHomeDirectory"s,
                              "Error occurred while getting the home directory: "s + buffer.data());
            }
            else
                output::error("platform::getHomeDirectory"s, "Error: Unable to get the home directory."s);
        }
#endif

        return homeDir;
    }

} // namespace steppable::__internals::utils
