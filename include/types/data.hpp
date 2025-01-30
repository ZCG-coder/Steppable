#pragma once

#include <string>

#include "util.hpp"

using namespace std::literals;
using namespace steppable::__internals::utils;

namespace steppable
{
    template<typename BaseT, StringLiteral BaseTName>
    class Data
    {
        BaseT value;

    public:
        std::string getDataType() { return BaseTName.value; }

        Data(const BaseT object) : value(object) {} // NOLINT(*-explicit-constructor)
        Data() : value() {}

        Data& operator=(const BaseT& object)
        {
            value = object;
            return *this;
        }
    };

    enum class _Weekday : std::uint8_t
    {
        Sunday = 0,
        Monday = 1,
        Tuesday = 2,
        Wednesday = 3,
        Thursday = 4,
        Friday = 5,
        Saturday = 6,
    };

    using Weekday = Data<_Weekday, StringLiteral{"Weekday"}>;
} // namespace steppable