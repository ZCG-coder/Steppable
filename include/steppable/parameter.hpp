#pragma once

#include <algorithm>
#include <any>
#include <iostream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>

using namespace std::literals;

namespace steppable::__internals::parameter
{
    using ValueMap = std::unordered_map<std::string, std::any>;
    using TypeMap = std::unordered_map<std::string, std::type_info*>;

    struct ValuedParameter
    {
        std::string name;
        std::any value;
    };

    struct Parameter
    {
        std::string name;

        ValuedParameter operator=(std::any value) { return { name, value }; }

        Parameter& operator=(const Parameter&) = delete;

        explicit Parameter(const std::string& name) : name(name) {}
    };

    struct ParameterMap
    {
        ValueMap values;

        ParameterMap(ValueMap values) : values(values) {}

        void checkParameterOrder(const std::vector<std::string>& names)
        {
            if (names.size() != values.size())
                throw std::runtime_error("Error");

            auto it = values.begin();
            for (size_t i = 0; i < values.size(); i++)
            {
                std::advance(it, i);
                if (names[i] != it->first)
                    throw std::runtime_error("Error");
            }
        }

        void checkParameterNameUnordered(const std::vector<std::string>& names)
        {
            if (names.size() != values.size())
                throw std::runtime_error("Error");
            for (const auto& pair : values)
                if (std::find(names.begin(), names.end(), pair.first) == names.end())
                    throw std::runtime_error("Error");
        }

        void checkParameterTypes() {}

        template<typename... Rest>
        void checkParameterTypes(const std::string& name, const std::type_info* info, const Rest... rest)
        {
            static_assert((sizeof...(rest) % 2) == 0, "Arguments must come in pairs (std::string, std::type_info*)");

            if (values.find(name) == values.end())
                throw std::runtime_error("Parameter name not found");

            const auto& value = values[name];
            if (value.type() != *info)
                throw std::runtime_error("Parameter type is wrong");
            checkParameterTypes(rest...);
        }

        template<typename ValueT>
        ValueT getItem(const std::string& name)
        {
            checkParameterTypes(name, &typeid(ValueT));
            return std::any_cast<ValueT>(values.at(name));
        }

        template<typename ValueT>
        ValueT getItem(const std::string& name, ValueT fallback)
        {
            // Value not found
            if (values.find(name) == values.end())
                return fallback;

            // checkParameterTypes(name, &typeid(ValueT));
            return std::any_cast<ValueT>(values.at(name));
        }
    };

    Parameter operator""_p(const char* name, size_t) { return Parameter(name); }

    template<typename... Params>
    ParameterMap processParams(Params... params)
    {
        ValueMap values;
        const std::vector<ValuedParameter> vec = { params... };

        for (const auto& elem : vec)
            values[elem.name] = elem.value;
        return { values };
    }
} // namespace steppable::__internals::parameter

#define PARAM_GET(map, type, name)       \
    type(name);                          \
    do                                   \
    {                                    \
        name = map.getItem<type>(#name); \
    } while (0)

#define PARAM_GET_FALLBACK(map, type, name, fallback) \
    type(name);                                       \
    do                                                \
    {                                                 \
        name = map.getItem<type>(#name, fallback);    \
    } while (0)
