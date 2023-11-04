#pragma once

#include <any>
#include <map>
#include <regex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

using PosArgs = std::vector<std::string_view>;

// language=RegExp
[[maybe_unused]] static const std::regex keywordArgRegex(R"(^-([a-zA-Z]*):([0-9]*?)$)",
                                                         std::regex_constants::ECMAScript);

// language=RegExp
[[maybe_unused]] static const std::regex switchRegex(R"(^([-+])([a-zA-Z0-9]*)$)", std::regex_constants::ECMAScript);

class ProgramArgs
{
private:
    std::unordered_map<std::string_view, bool> switches;
    std::map<std::string_view, std::string_view> switchDescriptions;

    std::vector<std::string_view> posArgs; // Names are used for error messages only.
    std::map<char, std::string_view> posArgDescriptions;

    std::unordered_map<std::string_view, int> keywordArgs;
    std::map<std::string_view, std::string_view> keywordArgDescriptions;

    int argc;

    std::vector<std::string_view> argv;

    std::string_view programName;

public:
    ProgramArgs(int _argc, const char** argv);

    void parseArgs();

    void addSwitch(const std::string_view& name, bool defaultValue, const std::string_view& description = "");

    void addPosArg(char name,
                   const std::string_view& description = ""); // Positional arguments are always required and ordered

    void addKeywordArg(const std::string_view& name, int defaultValue, std::string_view description = "");

    std::string_view getPosArg(int index);

    int getKeywordArgument(const std::string_view& name);

    bool getSwitch(const std::string_view& name);

    void printUsage(const std::string_view& reason = "") const;
};
