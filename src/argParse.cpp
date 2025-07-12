/**************************************************************************************************
 * Copyright (c) 2023-2025 NWSOFT                                                                 *
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
#include "getString.hpp"
#include "output.hpp"
#include "platform.hpp"
#include "util.hpp"

#include <iostream>
#include <ranges>
#include <regex>
#include <string>
#include <vector>

using namespace std::literals;
using namespace steppable::localization;

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
        // Usage: <programName> <switches> <keywordArgs>
        std::cout << $("steppable::argParse", "91408f1e-6627-41e5-9707-d8a660c2b86b") << formats::bold << programName
                  << reset << " ";

        if (not posArgDescriptions.empty())
            for (const auto& posArg : posArgDescriptions | std::views::keys)
                std::cout << colors::brightGreen << '<' << posArg << '>' << " ";

        if (not switchDescriptions.empty())
            // Siwtches
            std::cout << colors::brightGreen << $("steppable::argParse", "38f61169-17f1-4a49-870b-814745cdf4c6")
                      << reset;
        if (not keywordArgDescriptions.empty())
            // Keyword arguments
            std::cout << colors::brightGreen << $("steppable::argParse", "4f332974-1fd1-43eb-bbbc-8d32071ed735")
                      << reset;
        std::cout << '\n';

        if (not posArgDescriptions.empty())
        {
            // Available positional arguments
            std::cout << formats::bold << $("steppable::argParse", "5d482eea-c4e4-4c4d-89f0-6b33fcc9618c") << reset
                      << '\n';
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
            // Available switches
            std::cout << formats::bold << $("steppable::argParse", "10b1c33b-070f-4dfb-be12-a1a4349e76bc") << reset
                      << '\n';
            for (const auto& [switchName, switchDescription] : switchDescriptions)
            {
                std::cout << colors::brightGreen << formats::bold << '[' << '-' << switchName << "] ";
                std::cout << '[' << '+' << switchName << "]" << reset << '\n';

                // Enables/Disables {0}.
                std::cout << $("steppable::argParse", "227375c6-6ec8-479e-ad39-59f975272c6b", { switchDescription })
                          << '\n';
            }
            std::cout << reset << '\n';
        }

        if (not keywordArgDescriptions.empty())
        {
            // Available keyword arguments
            std::cout << formats::bold << $("steppable::argParse", "be2d8c84-0dfc-4f52-b450-e34d1cf20c91") << reset
                      << '\n';
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
            // Requires number
            std::cout << $("steppable::argParse", "fd67fddb-ca42-4a79-b852-c0bc71aa9969") << "\n";
        programSafeExit(-1);
    }

    std::string ProgramArgs::getPosArg(const size_t index) const
    {
        if (posArgs.size() <= index)
            // Invalid positional argument
            printUsage($("steppable::argParse", "b782de55-513d-4eda-b068-98d2d6210603") + std::to_string(index));
        return posArgs[index];
    }

    int ProgramArgs::getKeywordArgument(const std::string& name)
    {
        if (not keywordArgs.contains(name))
            // Invalid keyword argument
            printUsage($("steppable::argParse", "aa26a7f2-0949-454e-b987-42b40348e104") + name);
        return keywordArgs[name];
    }

    bool ProgramArgs::getSwitch(const std::string& name)
    {
        if (not switches.contains(name))
            // Invalid switch
            printUsage($("steppable::argParse", "2b854b9f-da27-483e-a016-0eb0d26eb9e9") + name);
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
                    // Positional argument is not a number.
                    output::error("ProgramArgs::parseArgs"s,
                                  $("steppable::argParse", "34782921-b560-4706-a2c9-d5c326af2cff", { _arg }));
                    programSafeExit(-1);
                }
                posArgs.push_back(_arg);
            }
        }
    }
} // namespace steppable::__internals::utils
