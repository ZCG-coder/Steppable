#pragma once

#include <array>
#include <cstdio>
#include <filesystem>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

using CommandResult = struct
{
    std::string output;

    std::string err;

    int status;
};

class Command
{
private:
    std::filesystem::path tmpOut;

    std::filesystem::path tmpErr;

    std::string constructCommand(const std::string& commandName);

public:
    /**
     * Execute system command and get STDOUT result.
     * Like system() but gives back exit status and stdout.
     * @param command system command to execute
     * @return CommandResult containing STDOUT (not stderr) output & exitstatus
     * of command. Empty if command failed (or has no output). If you want stderr,
     * use shell redirection (2&>1).
     */
    CommandResult exec(const std::filesystem::path& command);
};

std::filesystem::path getExecutablePathName();

std::filesystem::path getExecutablesPath();

CommandResult invokeCommand(const std::string& commands);

CommandResult invokeCommand(const std::vector<std::string>& commands);