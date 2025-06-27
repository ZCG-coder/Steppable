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

#include "fn/calc.hpp"

#include <Python.h>
#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/string_view.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace steppable::__internals::bindings
{
    void bindingsCalc(nb::module_& mod)
    {
        using namespace steppable::__internals::calc;

        auto internals = mod.def_submodule("_internals", "Internal functions.");
        internals.def("abs",
                      &steppable::__internals::calc::abs,
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
            [](const std::string& a, const std::string& b, const int steps, const int decimals) {
                return multiply(a, b, steps, decimals);
            },
            "a"_a,
            "b"_a,
            "steps"_a = 2,
            "decimals"_a = 8,
            "Internal function that multiplies two numbers.");
        internals.def(
            "divide",
            [](const std::string& a, const std::string& b, const int steps, const int decimals) {
                return divide(a, b, steps, decimals);
            },
            "a"_a,
            "b"_a,
            "steps"_a = 2,
            "decimals"_a = 5,
            "Internal function that divides two numbers.");
        internals.def("divide_with_quotient",
                      &divideWithQuotient,
                      "Internal function that divides two numbers, but separating the quotient and remainder.");
        internals.def("power",
                      &power,
                      "a"_a,
                      "raiseTo"_a,
                      "steps"_a = 2,
                      "decimals"_a = 8,
                      "Internal function raises a number to a power.");
    }
} // namespace steppable::__internals::bindings
