#include "argParse.hpp"

#include "colors.hpp"
#include "output.hpp"
#include "util.hpp"

#include <any>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

void ProgramArgs::addSwitch(const std::string_view& name, const bool defaultValue, const std::string_view& description)
{
    args.insert({ name, defaultValue });
    switchesNames.emplace_back(name);
    switches.insert_or_assign(name, description);
}

void ProgramArgs::addPosArg(const std::string_view& name)
{
    auto posArgs = std::any_cast<PosArgs>(args["_pos"]);
    posArgsNames.emplace_back(name);
    posArgs.emplace_back("");
}

void ProgramArgs::printUsage(const std::string_view& reason) const
{
    std::cout << "Usage: " << formats::bold << programName << reset << " ";
    for (const auto& posArg : posArgsNames)
        std::cout << colors::brightGreen << '<' << posArg << '>' << " ";
    std::cout << "[switches]" << reset << std::endl;
    std::cout << formats::bold << "Available switches:" << reset << std::endl;

    for (const auto& switchName : switchesNames)
    {
        std::cout << colors::brightGreen << formats::bold << '[' << '-' << switchName << "] ";
        std::cout << '[' << '+' << switchName << "]" << reset << std::endl;
        std::cout << "  Enables/Disables " << switches.at(switchName) << std::endl;
    }

    if (not reason.empty())
    {
        std::cerr << std::endl;
        error(reason);
    }
    exit(-1);
}

std::string_view ProgramArgs::getPosArg(const int index)
{
    if (not args.contains("_pos"))
        throw std::runtime_error("No positional arguments found. Argument map corrupted.");
    const auto& pos = std::any_cast<PosArgs>(args["_pos"]);
    if (not(pos.size() > index))
        printUsage("Missing positional argument: " + std::to_string(index));
    return std::any_cast<std::string_view>(pos[index]);
}

bool ProgramArgs::getSwitch(const std::string_view& name)
{
    if (not args.contains(name))
        printUsage("Missing keyword argument: " + (std::string)name);
    return std::any_cast<bool>(args[name]);
}

ProgramArgs::ProgramArgs(const int _argc, const char** _argv)
{
    argc = _argc - 1;
    programName = _argv[0];
    PosArgs pos;

    // Copy the arguments into a vector
    for (int i = 0; i <= argc; i++)
        argv.emplace_back(_argv[i]);
    argv.erase(argv.begin());
    args.insert({ "_pos", pos });
}

void ProgramArgs::parseArgs()
{
    auto pos = std::any_cast<PosArgs>(args["_pos"]);
    for (std::string_view arg : argv)
    {
        switch (arg[0])
        {
        case '-':
        {
            std::string name;
            std::copy(arg.begin() + 1, arg.end(), std::back_inserter(name));
            if (not std::count(switchesNames.begin(), switchesNames.end(), name))
                printUsage("Invalid option: " + name);

            args.insert_or_assign(name, false);
            break;
        }
        case '+':
        {
            std::string name;
            std::copy(arg.begin() + 1, arg.end(), std::back_inserter(name));
            if (not std::count(switchesNames.begin(), switchesNames.end(), name))
                printUsage("Invalid option: " + name);

            args.insert_or_assign(name, true);
            break;
        }
        default:
        {
            // Treat as positional argument, must be number
            // Report error if it is not a number
            if (not isNumber(arg))
                printUsage("Invalid number: " + (std::string) arg);
            pos.push_back(arg);
        }
        }
    }

    args["_pos"] = pos;
}
