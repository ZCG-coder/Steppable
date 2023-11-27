/**************************************************************************************************
 * Copyright (c) 2023 NWSOFT                                                                      *
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

#include "argParse.hpp"

#include "colors.hpp"
#include "output.hpp"
#include "util.hpp"

#include <iostream>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

void ProgramArgs::addSwitch(const std::string_view& name, const bool defaultValue, const std::string_view& description)
{
    switches.insert({ name, defaultValue });
    switchDescriptions.insert_or_assign(name, description);
}

void ProgramArgs::addKeywordArg(const std::string_view& name, int defaultValue, const std::string_view description)
{
    keywordArgs.insert({ name, defaultValue });
    keywordArgDescriptions.insert({ name, description });
}

void ProgramArgs::addPosArg(const char name, const std::string_view& description)
{
    posArgDescriptions.insert({ name, description });
}

void ProgramArgs::printUsage(const std::string_view& reason) const
{
    std::cout << "Usage: " << formats::bold << programName << reset << " ";

    if (not posArgDescriptions.empty())
        for (const auto& [posArg, _] : posArgDescriptions)
            std::cout << colors::brightGreen << '<' << posArg << '>' << " ";

    if (not switchDescriptions.empty())
        std::cout << colors::brightGreen << "[switches] " << reset;
    if (not keywordArgDescriptions.empty())
        std::cout << colors::brightGreen << "[keywordArguments] " << reset;
    std::cout << std::endl;

    if (not posArgDescriptions.empty())
    {
        std::cout << formats::bold << "Available positional arguments:" << reset << std::endl;
        for (const auto& [posArgName, posArgDescription] : posArgDescriptions)
        {
            std::cout << colors::brightGreen << formats::bold << '<' << posArgName << '>' << reset;
            std::cout << ": " << posArgDescription << std::endl;
        }
        std::cout << reset << std::endl;
    }

    if (not switchDescriptions.empty())
    {
        std::cout << formats::bold << "Available switches:" << reset << std::endl;
        for (const auto& [switchName, switchDescription] : switchDescriptions)
        {
            std::cout << colors::brightGreen << formats::bold << '[' << '-' << switchName << "] ";
            std::cout << '[' << '+' << switchName << "]" << reset << std::endl;
            std::cout << "  Enables/Disables " << switchDescription << std::endl;
        }
        std::cout << reset << std::endl;
    }

    if (not keywordArgDescriptions.empty())
    {
        std::cout << formats::bold << "Available keyword arguments:" << reset << std::endl;
        for (const auto& [keywordArgName, keywordArgDescription] : keywordArgDescriptions)
        {
            std::cout << colors::brightGreen << formats::bold << '[' << '-' << keywordArgName << ": <VALUE>]" << reset
                      << std::endl;
            std::cout << "  " << keywordArgDescription << reset << std::endl;
        }
        std::cout << reset;
    }

    if (not reason.empty())
    {
        std::cerr << std::endl;
        error(std::string(reason));
    }
    exit(-1);
}

std::string_view ProgramArgs::getPosArg(const int index)
{
    if (posArgs.size() <= index)
        printUsage("Missing positional argument: " + std::to_string(index));
    return posArgs[index];
}

int ProgramArgs::getKeywordArgument(const std::string_view& name)
{
    if (not keywordArgs.contains(name))
        printUsage("Missing switch: " + (std::string)name);
    return keywordArgs[name];
}

bool ProgramArgs::getSwitch(const std::string_view& name)
{
    if (not switches.contains(name))
        printUsage("Missing switch: " + (std::string)name);
    return switches[name];
}

ProgramArgs::ProgramArgs(const int _argc, const char** _argv)
{
    argc = _argc - 1;
    programName = _argv[0]; // Call this program whatever the user calls it
    PosArgs pos;

    // Copy the arguments into a vector
    for (int i = 0; i <= argc; i++)
        argv.emplace_back(_argv[i]);
    argv.erase(argv.begin());
}

void ProgramArgs::parseArgs()
{
    for (auto _arg : argv)
    {
        std::smatch match;
        std::string arg = static_cast<std::string>(_arg);
        if (std::regex_match(arg, match, keywordArgRegex))
        {
            std::string name = match[1];
            int value = std::stoi(match[2]);
            keywordArgs.insert_or_assign(name, value);
        }
        else if (std::regex_match(arg, match, switchRegex))
        {
            bool enabled = match[1] == "+";
            std::string name = match[2];
            switches.insert_or_assign(name, enabled);
        }
        else
        {
            if (not isNumber(_arg))
            {
                error("Invalid argument: %s", _arg);
                exit(-1);
            }
            posArgs.push_back(_arg);
        }
    }
}
