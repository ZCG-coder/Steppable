#include "invokeCommand.hpp"

#include "output.hpp"
#include "util.hpp"

#include <algorithm>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#pragma region getExecutablePathName
#if defined(WINDOWS)
#include <libloaderapi.h>

std::filesystem::path getExecutablePathName()
{
    std::filesystem::path pathName;
    std::string out;
    char* pathName;
    GetModuleFileNameA(NULL, pathName, 256);
    out = std::string(pathName);
    pathName = out;
    return pathName;
}

#elif defined(LINUX)
std::filesystem::path getExecutablePathName() { return std::filesystem::canonical("/proc/self/exe"); }

#elif defined(MACOSX)
#include <mach-o/dyld.h>

std::filesystem::path getExecutablePathName()
{
    unsigned int bufferSize = 512;
    std::vector<char> buffer(bufferSize + 1);
    if (_NSGetExecutablePath(&buffer[0], &bufferSize))
    {
        buffer.resize(bufferSize);
        _NSGetExecutablePath(&buffer[0], &bufferSize);
    }

    return buffer.data();
}
#else
#error Not implemented yet
#endif
#pragma endregion

std::string random_string(size_t length)
{
    auto randchar = []() {
        const std::string& charset = "0123456789"
                                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                     "abcdefghijklmnopqrstuvwxyz";
        const auto max_index = (charset.length() - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

std::string Command::constructCommand(const std::string& commandName)
{
    tmpErr = std::filesystem::temp_directory_path() / random_string(10);
    tmpOut = std::filesystem::temp_directory_path() / random_string(10);
    std::stringstream ss;

    ss << commandName << ' ';
    ss << "2>" << tmpErr;
    ss << " 1>" << tmpOut;

    return ss.str();
}

CommandResult Command::exec(const std::string& command)
{
    int exitcode = 257; // Should be an invalid exit code. If you see this, it probably means something is wrong.
#ifdef WINDOWS
#define popen _popen
#define pclose _pclose
#define WEXITSTATUS
#endif

    std::string fullCommand = constructCommand(command);
    FILE* pipe = popen(fullCommand.c_str(), "r");
    if (pipe == nullptr)
        throw std::runtime_error("popen() failed!");
    int status = pclose(pipe); // This avoids an error on macOS, do not inline!
    status = WEXITSTATUS(status);

    std::fstream errFs;
    std::stringstream err;
    errFs.open(tmpErr, std::ios::in);
    err << errFs.rdbuf();
    errFs.close();

    std::fstream outFs;
    std::stringstream out;
    outFs.open(tmpOut, std::ios::in);
    out << outFs.rdbuf();
    outFs.close();

    return { out.str(), err.str(), status };
}

int invokeCommand(const std::string& name)
{
    int status = 257;
    auto commands = split(name, ' ');
    auto currentExeFile = getExecutablePathName();
    if (not std::filesystem::is_regular_file(currentExeFile.string()))
        error("Cannot get the executable directory");
    auto currentDirectory = currentExeFile.parent_path();

    Command command;
    CommandResult result = command.exec(currentDirectory / name);
    std::cout << result.output << std::endl;

    if (result.status != 0)
    {
        auto lines = split(result.err, '\n');
        error("{} {}", lines.size(), "errors have occured:");
        for (int i = 0; i < lines.size(); i++)
            error("{}: {}", i + 1, lines[i]);
    }

    return status;
}
