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

#include "steppable/fraction.hpp"

#include <Python.h>
#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/string_view.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace steppable::__internals::bindings
{
    void bindingsFraction(nb::module_& mod)
    {
        nb::class_<steppable::Fraction>(mod, "Fraction")
            .def(nb::init<std::string, std::string>(), "top"_a = "1", "bottom"_a = "1")
            .def(nb::self + nb::self, nb::rv_policy::automatic_reference)
            .def(nb::self += nb::self, nb::rv_policy::automatic_reference)
            .def(nb::self - nb::self, nb::rv_policy::automatic_reference)
            .def("__neg__", [](steppable::Fraction& fraction) { return -fraction; })
            .def("__pos__", [](steppable::Fraction& fraction) { return +fraction; })
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
    }
} // namespace steppable::__internals::bindings
