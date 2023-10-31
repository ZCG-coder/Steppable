#pragma once

#include <any>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

using Args = std::unordered_map<std::string_view, std::any>;
using PosArgs = std::vector<std::string_view>;

class ProgramArgs
{
private:
    Args args;

    std::vector<std::string_view> switchesNames; // Used for error messages and indexing

    // name: description
    std::unordered_map<std::string_view, std::string_view> switches;

    std::vector<std::string_view> posArgsNames; // Names are used for error messages only. They need not to be provided.

    int argc;

    std::vector<std::string_view> argv;

    std::string_view programName;

public:
    ProgramArgs(const int _argc, const char** argv);

    void parseArgs();

    void addSwitch(const std::string_view& name, const bool defaultValue, const std::string_view& description = "");

    void addPosArg(const std::string_view& name); // Positional arguments are always required and ordered

    std::string_view getPosArg(const int index);

    bool getSwitch(const std::string_view& name);

    void printUsage(const std::string_view& reason = "") const;
};
