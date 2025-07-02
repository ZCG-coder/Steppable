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

#pragma once

#include "output.hpp"
#include "platform.hpp"

#include <algorithm>
#include <any>
#include <string>
#include <utility>
#include <vector>

using namespace std::literals;

/**
 * @namespace steppable::__internals::parameter
 * @brief Contains the parameter utilities to allow named parameters to be passed into functions.
 */
namespace steppable::__internals::parameter
{
    /**
     * @struct ValuedParameter
     * @brief A parameter with a name and value.
     */
    struct ValuedParameter
    {
        std::string name; ///< The name of the parameter.
        std::any value; ///< The value of the parameter.
    };

    /// @brief A type containing all the parameters of a function, in calling order.
    using ValueMap = std::vector<ValuedParameter>;

    /**
     * @struct Parameter
     * @brief Stores the name of a parameter
     */
    struct Parameter // NOLINT(cppcoreguidelines-special-member-functions)
    {
        std::string name; ///< The name of the parameter.

        /**
         * @brief Shorthand function to facilitate setting values of parameters.
         *
         * @param value The value to set for the parameter.
         * @return A `ValuedParameter` object representing the current parameter.
         */
        template<typename T>
        ValuedParameter operator=(T value) // NOLINT(cppcoreguidelines-c-copy-assignment-signature)
        {
            return { .name = name, .value = std::move(value) };
        }

        Parameter& operator=(const Parameter&) = delete;

        /**
         * @brief Initializes a new `Parameter` object.
         *
         * @param name The name of the parameter.
         */
        explicit Parameter(std::string name) : name(std::move(name)) {}
    };

    /**
     * @struct ParameterMap
     * @brief An object containing all parameters and their values passed into a function.
     */
    struct ParameterMap
    {
        ValueMap values; ///< All `ValuedParameter` objects passed to a function.

        /**
         * @brief Initializes a new `ParameterMap` object.
         *
         * @param values All `ValuedParameter` objects passed to a function.
         */
        ParameterMap(ValueMap values) : values(std::move(values)) {}

        /**
         * @brief Checks the presence of all the arguments, in the order which they should be specified. Prints an error
         * message and exits the program if one of the parameter names is not specified according to the order, or the
         * size of the name vector is not the same as the number of parameters passed into the function.
         *
         * @param names The names to check.
         */
        void checkParameterOrder(const std::vector<std::string>& names);

        /**
         * @brief Checks the presence of all the arguments, no matter which order they are specified. Prints an error
         * message and exits the program if one of the parameter names specified is not found, or the size of the name
         * vector is not the same as the number of parameters passed into the function.
         *
         * @param names The names to check.
         */
        void checkParameterNameUnordered(const std::vector<std::string>& names);

        /**
         * @brief Gets an item from the current parameter map.
         *
         * @param name The name of the parameter.
         * @return A value from the parameter list.
         */
        template<typename ValueT>
        ValueT getItem(const std::string& name)
        {
            ValuedParameter value;
            for (const auto& obj : values)
                if (obj.name == name)
                    value = obj;
            if (value.name == "")
            {
                output::error("ParameterMap::getItem"s, "Name {0} not found."s, { name });
                utils::programSafeExit(1);
            }
            return std::any_cast<ValueT>(value.value);
        }

        /**
         * @brief Gets an item from the current parameter map. Returns the fallback the matching parameter if not found.
         *
         * @param name The name of the parameter.
         * @param fallback If no matching parameter is specified, returns the fallback.
         * @return A value from the parameter list or the fallback.
         */
        template<typename ValueT>
        ValueT getItem(const std::string& name, const ValueT& fallback)
        {
            ValuedParameter value;
            for (const auto& obj : values)
                if (obj.name == name)
                    value = obj;
            if (value.name == "")
                return fallback;
            return std::any_cast<ValueT>(value.value);
        }
    };

    /**
     * @brief Convert a literal to a parameter, using a shorthand notation.
     *
     * @param name The name of the parameter, expressed as a simple string literal.
     * @return A `Parameter` object to set the value of the parameter.
     */
    inline Parameter operator""_p(const char* name, size_t /*unused*/) { return Parameter(name); }

    /**
     * @brief Process parameters passed into a function.
     * @details Takes in all arguments from a variadic function, and processes them as parameters.
     *
     * @param params The parameters passed into a function.
     * @return An instance of `ParameterMap` containing a list of the parameters.
     */
    template<typename... Params>
    ParameterMap processParams(Params... params)
    {
        return { std::vector{ params... } };
    }
} // namespace steppable::__internals::parameter

/// @brief Get a parameter from a parameter list.
#define PARAM_GET(map, type, name)                    \
    type name;                                        \
    do                                                \
    {                                                 \
        (name) = (map).template getItem<type>(#name); \
    } while (0)

/// @brief Get a parameter from a parameter list. If not found, return the fallback.
#define PARAM_GET_FALLBACK(map, type, name, fallback)           \
    type name;                                                  \
    do                                                          \
    {                                                           \
        (name) = (map).template getItem<type>(#name, fallback); \
    } while (0)
