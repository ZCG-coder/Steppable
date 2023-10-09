#include "argParse.hpp"

#include "colors.hpp"
#include "util.hpp"

#include <any>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

void ProgramArgs::addSwitch(const std::string& name, const bool defaultValue, const std::string& description)
{
    args.insert({ name, defaultValue });
    switchesNames.emplace_back(name);
    switches.insert_or_assign(name, description);
}

void ProgramArgs::addPosArg(const std::string& name)
{
    auto posArgs = std::any_cast<std::vector<std::string>>(args["_pos"]);
    posArgsNames.emplace_back(name);
    posArgs.emplace_back("");
}

void ProgramArgs::printUsage(const std::string& reason) const
{
    std::cout << "Usage: " << BOLD << programName << RESET << " ";
    for (const auto& posArg : posArgsNames)
        std::cout << BRIGHT_GREEN << '<' << posArg << '>' << " ";
    std::cout << "[switches]" << RESET << std::endl;
    std::cout << BOLD << "Available switches:" << RESET << std::endl;

    for (const auto& switchName : switchesNames)
    {
        std::cout << BRIGHT_GREEN << BOLD << '[' << '-' << switchName << "] ";
        std::cout << '[' << '+' << switchName << "]" << RESET << std::endl;
        std::cout << "  Enables/Disables " << switches.at(switchName) << std::endl;
    }

    if (not reason.empty())
        std::cerr << std::endl << RED BOLD << "Error: " RESET RED << reason << RESET << std::endl;

    exit(-1);
}

std::string ProgramArgs::getPosArg(const int index)
{
    if (not args.contains("_pos"))
        throw std::runtime_error("No positional arguments found. Argument map corrupted.");
    const auto& pos = std::any_cast<std::vector<std::string>>(args["_pos"]);
    if (not(pos.size() > index))
        printUsage("Missing positional argument: " + std::to_string(index));
    return std::any_cast<std::string>(pos[index]);
}

bool ProgramArgs::getSwitch(const std::string& name)
{
    if (not args.contains(name))
        printUsage("Missing keyword argument: " + name);
    return std::any_cast<bool>(args[name]);
}

ProgramArgs::ProgramArgs(const int _argc, const char** _argv)
{
    argc = _argc - 1;
    programName = _argv[0];
    std::vector<std::string> pos;

    // Copy the arguments into a vector
    for (int i = 0; i <= argc; i++)
        argv.emplace_back(_argv[i]);
    argv.erase(argv.begin());
    args.insert({ "_pos", pos });
}

void ProgramArgs::parseArgs()
{
    auto pos = std::any_cast<std::vector<std::string>>(args["_pos"]);
    for (std::string arg : argv)
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
                printUsage("Invalid number: " + arg);
            pos.push_back(arg);
        }
        }
    }

    args["_pos"] = pos;
}
