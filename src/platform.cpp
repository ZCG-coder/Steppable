/**************************************************************************************************
 * Copyright (c) 2023-2026 NWSOFT                                                                 *
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

#include "platform.hpp"

#include "output.hpp"

#ifdef LINUX
    #include <cstring>
#endif
#include <string>

#ifdef WINDOWS
    #include <shlobj.h>
    #include <windows.h>
#else
    #include <pwd.h>
    #include <sys/types.h>
    #include <unistd.h>
#endif

#include <filesystem>
#include <stdexcept>
#include <vector>

#if defined(WINDOWS)
    #include <windows.h>
#elif defined(MACOSX)
    #include <limits.h>
    #include <mach-o/dyld.h>
    #include <stdlib.h>
#else
    #include <limits.h>
    #include <stdlib.h>
    #include <unistd.h>
#endif

using namespace std::literals;

namespace steppable::utils
{
    std::filesystem::path getHomeDirectory()
    {
        std::filesystem::path homeDir;

#ifdef WINDOWS
        char homePath[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PROFILE, NULL, 0, homePath)))
            homeDir = homePath;
        else
            output::error("platform::getHomeDirectory"s, "Error: Unable to get the home directory."s);
#else
        const std::filesystem::path& homeEnv = std::getenv("HOME"); // NOLINT(concurrency-mt-unsafe)

        if (std::filesystem::is_directory(homeEnv))
            homeDir = homeEnv;
        else
        {
            std::array<char, 4096> buffer{};
            std::array<char, 4096> errBuffer{};
            const char* homeEnv = nullptr;
            int error = 0;
            struct passwd pw{};
            struct passwd* result = nullptr;

            uid_t userId = getuid();
            error = getpwuid_r(userId, &pw, buffer.data(), sizeof(buffer), &result);

            if (result != nullptr)
                homeDir = pw.pw_dir;
            else if (error != 0)
            {
                strerror_r(error, errBuffer.data(), errBuffer.size());
                output::error("platform::getHomeDirectory"s,
                              "Error occurred while getting the home directory: {0}"s,
                              { buffer.data() });
            }
            else
                output::error("platform::getHomeDirectory"s, "Error: Unable to get the home directory."s);
        }
#endif

        return homeDir;
    }

    std::filesystem::path getResDirectory()
    {
        // When we have a full application, we can allow users to change the configuration directory.
        // However, now, we will use the default configuration directory for the platform.
        std::filesystem::path confDir = getHomeDirectory();

#ifndef WINDOWS
        confDir /= ".config";
        confDir /= "steppable";
#else
        confDir /= "AppData";
        confDir /= "Roaming";
        confDir /= "Steppable";
#endif
        // If the directory does not exist, create it.
        if (not std::filesystem::is_directory(confDir))
            std::filesystem::create_directories(confDir);
        return confDir;
    }

    std::filesystem::path getBinDir()
    {
        namespace fs = std::filesystem;

#if defined(WINDOWS)
        // GetModuleFileNameW returns the full path to the executable (UTF-16).
        std::vector<wchar_t> buf;
        buf.resize(MAX_PATH);
        DWORD len = 0;
        for (;;)
        {
            len = GetModuleFileNameW(nullptr, buf.data(), static_cast<DWORD>(buf.size()));
            if (len == 0)
                throw std::system_error(GetLastError(), std::system_category(), "GetModuleFileNameW failed");
            if (len < buf.size())
                break; // success and fit in buffer
            // Buffer was too small, enlarge and retry
            buf.resize(buf.size() * 2);
        }
        // Construct filesystem path from wide string (works on Windows)
        fs::path exePath = fs::path(std::wstring(buf.data(), buf.data() + len));
        return exePath.parent_path().string();

#elif defined(MACOSX)
        // _NSGetExecutablePath gives a path that may be relative; realpath resolves it to an absolute path.
        uint32_t size = 0;
        // First call to get required buffer size
        _NSGetExecutablePath(nullptr, &size); // sets size
        std::vector<char> buf;
        buf.resize(size);
        if (_NSGetExecutablePath(buf.data(), &size) != 0)
            throw std::runtime_error("_NSGetExecutablePath failed");

        char resolved[PATH_MAX];
        if (realpath(buf.data(), resolved) == nullptr)
        {
            fs::path exePath = fs::path(std::string(buf.data()));
            return exePath.parent_path().string();
        }
        fs::path exePath = fs::path(std::string(resolved));
        return exePath.parent_path().string();

#elif defined(LINUX)
        // readlink on /proc/self/exe returns the executable path
        std::vector<char> buf;
        buf.resize(PATH_MAX);
        ssize_t len = 0;
        for (;;)
        {
            len = readlink("/proc/self/exe", buf.data(), buf.size());
            if (len == -1)
                throw std::system_error(errno, std::system_category(), "readlink(/proc/self/exe) failed");
            if (static_cast<size_t>(len) < buf.size())
            {
                buf[static_cast<size_t>(len)] = '\0';
                break;
            }
            // Buffer too small, enlarge and retry
            buf.resize(buf.size() * 2);
        }
        fs::path exePath = fs::path(std::string(buf.data()));
        // Optionally resolve symlinks / canonicalize; uncomment if you want canonical path:
        // exePath = fs::canonical(exePath);
        return exePath.parent_path().string();

#endif
    }

} // namespace steppable::utils
