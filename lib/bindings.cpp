/**************************************************************************************************
 * Copyright (c) 2023-2024 NWSOFT                                                                 *
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

#include "fn/calc.hpp"
#include "fraction.hpp"
#include "number.hpp"

#include <Python.h>
#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/string_view.h>

namespace nb = nanobind;
using namespace steppable::__internals::arithmetic;
using namespace nb::literals;

NB_MODULE(steppyble, mod) // NOLINT
{
    auto internals = mod.def_submodule("_internals", "Internal functions.");

    nb::enum_<steppable::RoundingMode>(mod, "RoundingMode")
        .value("USE_MAXIMUM_PREC", steppable::RoundingMode::USE_MAXIMUM_PREC)
        .value("USE_MINIMUM_PREC", steppable::RoundingMode::USE_MINIMUM_PREC)
        .value("USE_CURRENT_PREC", steppable::RoundingMode::USE_CURRENT_PREC)
        .value("USE_OTHER_PREC", steppable::RoundingMode::USE_OTHER_PREC)
        .value("DISCARD_ALL_DECIMALS", steppable::RoundingMode::DISCARD_ALL_DECIMALS);

    nb::class_<steppable::Number>(mod, "Number")
        .def(nb::init<std::string, size_t, steppable::RoundingMode>(),
             "value"_a = "0",
             "prec"_a = 5,
             "roundingMode"_a = steppable::USE_CURRENT_PREC)
        .def(nb::self + nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self += nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self - nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self -= nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self * nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self *= nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self / nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self /= nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self % nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self %= nb::self, nb::rv_policy::automatic_reference)
        .def("__pow__", &steppable::Number::operator^)
        .def(nb::self == nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self != nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self < nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self > nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self <= nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self >= nb::self, nb::rv_policy::automatic_reference)
        .def("__repr__", &steppable::Number::present);

    nb::class_<steppable::Fraction>(mod, "Fraction")
        .def(nb::init<std::string, std::string>(), "top"_a = "1", "bottom"_a = "1")
        .def(nb::self + nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self += nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self - nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self -= nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self * nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self *= nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self / nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self /= nb::self, nb::rv_policy::automatic_reference)
        .def("__pow__", &steppable::Fraction::operator^)
        .def(nb::self == nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self != nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self < nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self > nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self <= nb::self, nb::rv_policy::automatic_reference)
        .def(nb::self >= nb::self, nb::rv_policy::automatic_reference)
        .def("__repr__", &steppable::Fraction::present);

    mod.doc() = "The Python bindings for Steppable.";

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
