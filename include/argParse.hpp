#pragma once

#include <any>
#include <unordered_map>
#include <string>
#include <vector>

using Args = std::unordered_map<std::string, std::any>;

class ProgramArgs
{
private:
    Args args;

    std::vector<std::string> switchesNames; // Used for error messages and indexing

    // name: description
    std::unordered_map<std::string, std::string> switches;

    std::vector<std::string> posArgsNames; // Names are used for error messages only. They need not to be provided.

    int argc;

    std::vector<std::string> argv;

    std::string programName;

public:
    ProgramArgs(const int _argc, const char** argv);

    void parseArgs();

    void addSwitch(const std::string& name, const bool defaultValue, const std::string& description = "");

    void addPosArg(const std::string& name); // Positional arguments are always required and ordered

    std::string getPosArg(const int index);

    bool getSwitch(const std::string& name);

    void printUsage(const std::string& reason = "") const;
};
