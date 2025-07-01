#pragma once

#include <algorithm>
#include <any>
#include <iostream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std::literals;

namespace steppable::__internals::parameter
{
    struct ValuedParameter
    {
        std::string name;
        std::any value;
    };

    using ValueMap = std::vector<ValuedParameter>;

    struct Parameter
    {
        std::string name;

        template<typename T>
        ValuedParameter operator=(T value) // NOLINT(cppcoreguidelines-c-copy-assignment-signature)
        {
            return { .name = name, .value = std::move(value) };
        }

        Parameter& operator=(const Parameter&) = delete;

        explicit Parameter(std::string name) : name(std::move(name)) {}
    };

    struct ParameterMap
    {
        ValueMap values;

        ParameterMap(ValueMap values) : values(std::move(values)) {}

        void checkParameterOrder(const std::vector<std::string>& names)
        {
            if (names.size() != values.size())
                throw std::runtime_error("Error");

            for (size_t i = 0; i < values.size(); i++)
                if (names[i] != values[i].name)
                    throw std::runtime_error("Error");
        }

        void checkParameterNameUnordered(const std::vector<std::string>& names)
        {
            if (names.size() != values.size())
                throw std::runtime_error("Error");
            for (const auto& obj : values)
                if (std::ranges::find(names, obj.name) == names.end())
                    throw std::runtime_error("Error");
        }

        template<typename ValueT>
        ValueT getItem(const std::string& name)
        {
            ValuedParameter value;
            for (const auto& obj : values)
                if (obj.name == name)
                    value = obj;
            if (value.name == "")
                throw std::invalid_argument("Name not found");
            return std::any_cast<ValueT>(value.value);
        }

        template<typename ValueT>
        ValueT getItem(const std::string& name, ValueT fallback)
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

    Parameter operator""_p(const char* name, size_t /*unused*/) { return Parameter(name); }

    template<typename... Params>
    ParameterMap processParams(Params... params)
    {
        return { std::vector{ params... } };
    }
} // namespace steppable::__internals::parameter

#define PARAM_GET(map, type, name)                    \
    type name;                                        \
    do                                                \
    {                                                 \
        (name) = (map).template getItem<type>(#name); \
    } while (0)

#define PARAM_GET_FALLBACK(map, type, name, fallback)           \
    type name;                                                  \
    do                                                          \
    {                                                           \
        (name) = (map).template getItem<type>(#name, fallback); \
    } while (0)
