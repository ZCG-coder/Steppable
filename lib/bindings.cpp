#include "fn/basicArithm.hpp"

#include <Python.h>
#include <nanobind/nanobind.h>

NB_MODULE(bindings, mod)
{
    mod.doc() = "Python bindings for the Steppable library."; // optional module docstring

    mod.def("abs",
            &steppable::__internals::arithmetic::add,
            "Internal function that takes the absolute value of a number.");
    mod.def("add", &steppable::__internals::arithmetic::add, "Internal function that adds two numbers.");
    mod.def("subtract", &steppable::__internals::arithmetic::subtract, "Internal function that subtracts two numbers.");
    mod.def("multiply", &steppable::__internals::arithmetic::multiply, "Internal function that multiplys two numbers.");
    mod.def("divide", &steppable::__internals::arithmetic::divide, "Internal function that divides two numbers.");
    mod.def("divideWithQuotient",
            &steppable::__internals::arithmetic::divideWithQuotient,
            "Internal function that divides two numbers, but separating the quotient and remainder.");
    mod.def("power", &steppable::__internals::arithmetic::power, "Internal function that raises a number to a power.");
}
