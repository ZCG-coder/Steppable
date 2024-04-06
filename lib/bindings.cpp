#include "fn/basicArithm.hpp"

#include <Python.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/string_view.h>

namespace nb = nanobind;
using namespace steppable::__internals::arithmetic;
using namespace nb::literals;

NB_MODULE(bindings, mod)
{
    auto internals = mod.def_submodule("_internals", "Internal functions.");

    internals.def("abs",
                  &steppable::__internals::arithmetic::abs,
                  "a"_a,
                  "steps"_a = 2,
                  "Internal function that takes the absolute value of a number.");
    internals.def(
        "add",
        [](const std::string& a, const std::string& b, const int steps) { return add(a, b, steps); },
        "a"_a,
        "b"_a,
        "steps"_a = 2,
        "Internal function that adds two numbers.");
    internals.def(
        "subtract",
        [](const std::string& a, const std::string& b, const int steps) { return subtract(a, b, steps); },
        "a"_a,
        "b"_a,
        "steps"_a = 2,
        "Internal function that subtracts two numbers.");
    internals.def(
        "multiply",
        [](const std::string& a, const std::string& b, const int steps) { return multiply(a, b, steps); },
        "a"_a,
        "b"_a,
        "steps"_a = 2,
        "Internal function that multiplies two numbers.");
    internals.def(
        "divide",
        [](const std::string& a, const std::string& b, const int steps, const int decimals) {
            return divide(a, b, steps);
        },
        "a"_a,
        "b"_a,
        "steps"_a = 2,
        "decimals"_a = 5,
        "Internal function that divides two numbers.");
    internals.def("divideWithQuotient",
                  &divideWithQuotient,
                  "Internal function that divides two numbers, but separating the quotient and remainder.");
    internals.def("power", &power, "a"_a, "raiseTo"_a, "steps"_a = 2, "Internal function raises a number to a power.");
}
