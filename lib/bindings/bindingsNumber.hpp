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

#include "steppable/number.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/string_view.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace steppable::__internals::bindings
{
    void bindingsNumber(nanobind::module_& mod)
    {
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
                 "roundingMode"_a = steppable::RoundingMode::USE_CURRENT_PREC)
            .def(nb::init<double, size_t, steppable::RoundingMode>(),
                 "value"_a = 0,
                 "prec"_a = 5,
                 "roundingMode"_a = steppable::RoundingMode::USE_CURRENT_PREC)
            .def(nb::self + nb::self, nb::rv_policy::automatic_reference)
            .def(nb::self += nb::self, nb::rv_policy::automatic_reference)
            .def(nb::self - nb::self, nb::rv_policy::automatic_reference)
            .def("__neg__", [](steppable::Number& number) { return -number; })
            .def("__pos__", [](steppable::Number& number) { return +number; })
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
    }
} // namespace steppable::__internals::bindings
