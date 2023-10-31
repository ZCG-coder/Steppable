#pragma once

#include <array>
#include <cstdio>
#include <filesystem>
#include <memory>
#include <string>
#include <string_view>

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
    CommandResult exec(const std::string& command);
};

std::filesystem::path getExecutablePathName();

int invokeCommand(const std::string& name);
