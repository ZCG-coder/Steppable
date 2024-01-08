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

#pragma once

#include <map>
#include <regex>
#include <string_view>
#include <unordered_map>
#include <vector>

using PosArgs = std::vector<std::string_view>;

// language=RegExp
[[maybe_unused]] static const std::regex KEYWORD_ARG_REGEX(R"(^-([a-zA-Z]*):(-?[0-9]+)$)");

// language=RegExp
[[maybe_unused]] static const std::regex SWITCH_REGEX(R"(^([-+])([a-zA-Z]*)$)");

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

    [[nodiscard]] std::string_view getPosArg(size_t index) const;

    int getKeywordArgument(const std::string_view& name);

    bool getSwitch(const std::string_view& name);

    [[noreturn]] void printUsage(const std::string_view& reason = "") const;
};
