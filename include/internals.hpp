#pragma once

namespace internals
{
    struct setw
    {
        unsigned long n;
        setw(unsigned long n) : n(n) {}

        friend std::ostream& operator<<(std::ostream& os, const setw& cs)
        {
            std::string spaces(cs.n, ' ');
            return os << spaces;
        }
    };
} // namespace internals