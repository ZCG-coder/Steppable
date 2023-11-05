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

#pragma region getExecutablePathName
#if defined(WINDOWS)
    #include <Windows.h>

std::filesystem::path getExecutablePathName()
{
    char buffer[MAX_PATH];

    // Get the path of the current executable module
    DWORD length = GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    if (length == 0)
    {
        std::cerr << "Failed to get the module filename." << std::endl;
        return "NUL";
    }
    return buffer;
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

std::filesystem::path getExecutablesPath()
{
    auto currentExeFile = getExecutablePathName();
    if (not std::filesystem::is_regular_file(currentExeFile.string()))
        error(static_cast<std::string>("Cannot get the executable directory"));
    auto executablesPath = currentExeFile.parent_path().parent_path();
    return executablesPath / "bin";
}

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

#ifdef WINDOWS
    ss << "powershell -c "; // Makes sure it uses PowerShell, so that redirection works correctly
#endif
    ss << commandName << " -steps:0 "; // Disable steps
    ss << "2>" << tmpErr;
    ss << " 1>" << tmpOut;

    return ss.str();
}

CommandResult Command::exec(const std::filesystem::path& command)
{
    int exitcode = 257; // Should be an invalid exit code. If you see this, it probably means something is wrong.
#ifdef WINDOWS
    #define popen _popen
    #define pclose _pclose
    #define WEXITSTATUS
#endif

    std::string fullCommand = constructCommand(command.string());
    FILE* pipe = popen(fullCommand.c_str(), "r");
    if (pipe == nullptr)
        throw std::runtime_error("popen() failed!");
    int status = pclose(pipe); // This avoids an error on macOS, do not inline!
    status = WEXITSTATUS(status);

    std::fstream errFs, outFs;
    std::string err, out;

    errFs.open(tmpErr, std::ios::in);
    outFs.open(tmpOut, std::ios::in);
    errFs >> err;
    outFs >> out;
    errFs.close();
    outFs.close();

    out.erase(std::remove(out.begin(), out.end(), '\n'), out.cend());
    err.erase(std::remove(err.begin(), err.end(), '\n'), err.cend());

    return { out, err, status };
}

CommandResult invokeCommand(const std::string& commands)
{
    auto currentDirectory = getExecutablesPath();

    Command command;
    CommandResult result = command.exec(currentDirectory / commands);

    if (result.status != 0 or not result.err.empty())
    {
        auto lines = split(result.err, '\n');
        error("{} {}", lines.size(), "errors have occurred:");
        for (int i = 0; i < lines.size(); i++)
            error("{}: {}", i + 1, lines[i]);
    }
    return result;
}

CommandResult invokeCommand(const std::vector<std::string>& commands)
{
    std::string fullCommand;
    for (auto& item : commands)
        fullCommand += item + " ";
    return invokeCommand(fullCommand);
}