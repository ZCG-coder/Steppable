/**************************************************************************************************
 * Copyright (c) 2023-2024 NWSOFT                                                                 *
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
#include "platform.hpp"
#include "util.hpp"

#include <iostream>
#include <ranges>
#include <regex>
#include <string>
#include <vector>

using namespace std::literals;

namespace steppable::__internals::utils
{
    void ProgramArgs::addSwitch(const std::string& name, const bool defaultValue, const std::string& description)
    {
        switches.insert({ name, defaultValue });
        switchDescriptions.insert_or_assign(name, description);
    }

    void ProgramArgs::addKeywordArg(const std::string& name, int defaultValue, const std::string& description)
    {
        keywordArgs.insert({ name, defaultValue });
        keywordArgDescriptions.insert({ name, description });
    }

    void ProgramArgs::addPosArg(const char name, const std::string& description, const bool requiresNumber)
    {
        posArgDescriptions.insert({ name, description });
        posArgIsNumber.push_back(requiresNumber);
    }

    void ProgramArgs::printUsage(const std::string& reason) const
    {
        std::cout << "Usage: " << formats::bold << programName << reset << " ";

        if (not posArgDescriptions.empty())
            for (const auto& posArg : posArgDescriptions | std::views::keys)
                std::cout << colors::brightGreen << '<' << posArg << '>' << " ";

        if (not switchDescriptions.empty())
            std::cout << colors::brightGreen << "[switches] " << reset;
        if (not keywordArgDescriptions.empty())
            std::cout << colors::brightGreen << "[keywordArguments] " << reset;
        std::cout << '\n';

        if (not posArgDescriptions.empty())
        {
            std::cout << formats::bold << "Available positional arguments:" << reset << '\n';
            for (const auto& [posArgName, posArgDescription] : posArgDescriptions)
            {
                std::cout << colors::brightGreen << formats::bold << '<' << posArgName << '>' << reset;
                if (posArgIsNumber[std::distance(posArgDescriptions.begin(), posArgDescriptions.find(posArgName))])
                    std::cout << " (*)";

                std::cout << ": " << posArgDescription << '\n';
            }
            std::cout << reset << '\n';
        }

        if (not switchDescriptions.empty())
        {
            std::cout << formats::bold << "Available switches:" << reset << '\n';
            for (const auto& [switchName, switchDescription] : switchDescriptions)
            {
                std::cout << colors::brightGreen << formats::bold << '[' << '-' << switchName << "] ";
                std::cout << '[' << '+' << switchName << "]" << reset << '\n';
                std::cout << "  Enables/Disables " << switchDescription << '\n';
            }
            std::cout << reset << '\n';
        }

        if (not keywordArgDescriptions.empty())
        {
            std::cout << formats::bold << "Available keyword arguments:" << reset << '\n';
            for (const auto& [keywordArgName, keywordArgDescription] : keywordArgDescriptions)
            {
                std::cout << colors::brightGreen << formats::bold << '[' << '-' << keywordArgName << ": <VALUE>]"
                          << reset << '\n';
                std::cout << "  " << keywordArgDescription << reset << '\n';
            }
            std::cout << reset;
        }

        if (not reason.empty())
        {
            std::cerr << '\n';
            output::error("ProgramArgs::printUsage"s, "{0}"s, { reason });
        }

        // Print the footnote only if there are positional arguments that require a number
        if (std::ranges::any_of(posArgIsNumber, [](const bool isNumber) { return isNumber; }))
            std::cout << "(*) Requires a number\n";
        programSafeExit(-1);
    }

    std::string ProgramArgs::getPosArg(const size_t index) const
    {
        if (posArgs.size() <= index)
            printUsage("Missing positional argument: " + std::to_string(index));
        return posArgs[index];
    }

    int ProgramArgs::getKeywordArgument(const std::string& name)
    {
        if (not keywordArgs.contains(name))
            printUsage("Missing switch: " + static_cast<std::string>(name));
        return keywordArgs[name];
    }

    bool ProgramArgs::getSwitch(const std::string& name)
    {
        if (not switches.contains(name))
            printUsage("Missing switch: " + static_cast<std::string>(name));
        return switches[name];
    }

    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    ProgramArgs::ProgramArgs(const int _argc, const char** _argv) : argc(_argc - 1), programName(_argv[0])
    {
        // Call this program whatever the user calls it
        PosArgs pos;

        // Copy the arguments into a vector
        for (int i = 0; i <= argc; i++)
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            argv.emplace_back(_argv[i]);
        argv.erase(argv.begin());
    }

    void ProgramArgs::parseArgs()
    {
        for (const auto& _arg : argv)
        {
            auto arg = static_cast<std::string>(_arg);
            if (std::smatch match; std::regex_match(arg, match, KEYWORD_ARG_REGEX))
            {
                std::string name = match[1];
                int value = std::stoi(match[2]);
                keywordArgs.insert_or_assign(name, value);
            }
            else if (std::regex_match(arg, match, SWITCH_REGEX))
            {
                bool enabled = match[1] == "+";
                std::string name = match[2];

                switches.insert_or_assign(name, enabled);
            }
            else
            {
                if (not numUtils::isNumber(_arg) and posArgIsNumber[posArgs.size()])
                {
                    output::error("ProgramArgs::parseArgs"s, "Invalid argument: {0}"s, { _arg });
                    programSafeExit(-1);
                }
                posArgs.push_back(_arg);
            }
        }
    }
} // namespace steppable::__internals::utils
