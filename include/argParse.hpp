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

/**
 * @file argParse.hpp
 * @brief This file contains the declaration of the ProgramArgs class and related helper classes and functions.
 *
 * The ProgramArgs class provides a convenient way to parse command-line arguments and retrieve their values.
 * It supports switches, positional arguments, and keyword arguments.
 *
 * The class uses regular expressions to match and parse the command-line arguments.
 *
 * The file also includes the necessary headers and defines some types and constants used by the class.
 *
 * @author Andy Zhang
 * @date 9th October 2023
 */

#pragma once

#include <map>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * @namespace steppable::__internals::utils
 * @brief The namespace containing utility functions for the Steppable library.
 */
namespace steppable::__internals::utils
{
    /// @brief This is the type of the positional arguments. It is equivalent to a vector of string_views.
    using PosArgs = std::vector<std::string>;

    /// @brief This is the correct format of a keyword argument.
    // language=RegExp
    [[maybe_unused]] const std::regex KEYWORD_ARG_REGEX(R"(^-([a-zA-Z]*):(-?[0-9]+)$)"); // NOLINT(cert-err58-cpp)

    /// @brief This is the correct format of a switch.
    // language=RegExp
    [[maybe_unused]] const std::regex SWITCH_REGEX(R"(^([-+])([a-zA-Z]*)$)"); // NOLINT(cert-err58-cpp)

    /**
     * @class ProgramArgs
     * @brief This class is used by the program to parse command-line arguments.
     * The class uses regular expressions to match and parse the command-line arguments.
     * It supports switches, positional arguments, and keyword arguments.
     *
     * @note A note on the names used in this class:
     * @note - Switches are arguments that start with a '+' or '-' sign. They are optional and can be in any order.
     * @note  '+' switches are used to enable a feature, while '-' switches are used to disable a feature.
     * @note - Positional arguments are arguments that are not switches or keyword arguments. The names does not matter,
     * and they are
     * @note  required and ordered.
     * @note - Keyword arguments are arguments that start with a '-' sign and are followed by a name and a value. The
     * format
     * @note  is "-name:value". They are optional and can be in any order.
     */
    class ProgramArgs
    {
    private:
        /** @brief This map is used to store the information of all switches specified. Keys are switch names, and
         * values are whether the switch is enabled.
         */
        std::unordered_map<std::string, bool> switches;
        /// @brief This map is used to store the descriptions of all switches specified.
        std::map<std::string, std::string> switchDescriptions;

        /// @brief This vector is used to store the values of all positional arguments specified.
        std::vector<std::string> posArgs; // Names are used for error messages only.
        /// @brief This map is used to store the descriptions of all positional arguments specified.
        std::map<char, std::string> posArgDescriptions;
        /// @brief This map stores whether the positional arguments are required to be numbers.
        std::vector<bool> posArgIsNumber;

        /**
         * @brief This map is used to store the values of all keyword arguments specified. Keys are keyword argument
         * names and values are the values of the keyword arguments.
         */
        std::unordered_map<std::string, int> keywordArgs;
        /// @brief This map is used to store the descriptions of all keyword arguments specified.
        std::map<std::string, std::string> keywordArgDescriptions;

        /// @brief This stores the number of arguments passed to the program.
        int argc;

        /// @brief This stores the arguments passed to the program.
        std::vector<std::string> argv;

        /// @brief This stores the name of the program.
        std::string programName;

    public:
        /**
         * @brief The constructor of the ProgramArgs class, which copies the arguments passed to the program to the
         * class.
         * @param[in] _argc The number of arguments passed to the program.
         * @param[in] argv The arguments passed to the program.
         */
        ProgramArgs(int _argc, const char** argv);

        /**
         * @brief This function is used to parse the command-line arguments and store them in the appropriate class
         * members.
         * @note You may want to call this function after adding all the arguments to the class. Otherwise, the class
         * will not recognize the arguments specified after the call.
         */
        void parseArgs();

        /**
         * @brief This function is used to add a switch to the class.
         * @param[in] name The name of the switch.
         * @param[in] defaultValue The default value of the switch. True = enabled, False = disabled.
         * @param[in] description The description of the switch.
         */
        void addSwitch(const std::string& name, bool defaultValue, const std::string& description = "");

        /**
         * @brief This function is used to add a positional argument to the class.
         * @param[in] name The name of the positional argument. Only one character is allowed.
         * @param[in] description The description of the positional argument.
         * @param[in] requiresNumber Whether the positional argument requires to be a number.
         *
         * @note The name of the positional argument is used for error messages only. It does not affect the parsing of
         * @note the command-line arguments.
         */
        void addPosArg(char name,
                       const std::string& description = "",
                       bool requiresNumber = true); // Positional arguments are always required and ordered

        /**
         * @brief This function is used to add a keyword argument to the class.
         * @param[in] name The name of the keyword argument.
         * @param[in] defaultValue The default value of the keyword argument. The value is stored as an integer.
         * @param[in] description The description of the keyword argument.
         */
        void addKeywordArg(const std::string& name, int defaultValue, const std::string& description = "");

        /**
         * @brief This function is used to get the value of a positional argument.
         * @param[in] index The index of the positional argument.
         * @return The value of the positional argument.
         *
         * @note If the positional argument is not specified, the function will print an error message and exit the
         * program.
         */
        [[nodiscard]] std::string getPosArg(size_t index) const;

        /**
         * @brief This function is used to get the value of a keyword argument.
         * @param[in] name The name of the keyword argument.
         * @return The value of the keyword argument.
         *
         * @note If the keyword argument is not specified, the function will print an error message and exit the
         * program.
         */
        int getKeywordArgument(const std::string& name);

        /**
         * @brief This function is used to get the value of a switch.
         * @param[in] name The name of the switch.
         * @return The value of the switch.
         *
         * @note If the switch is not specified, the function will print an error message and exit the program.
         */
        bool getSwitch(const std::string& name);

        /**
         * @brief This function is used to print the possible command-line arguments. Usually called when the user
         * specifies the wrong arguments
         * @param[in] reason The reason for printing the usage. If specified, the reason will be printed after the
         * usage.
         *
         * @note The function will print the usage of the program and exit the program.
         */
        void printUsage(const std::string& reason = "") const;
    };
} // namespace steppable::__internals::utils
