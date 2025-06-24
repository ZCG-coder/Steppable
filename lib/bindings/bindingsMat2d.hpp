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

#include "steppable/mat2d.hpp"
#include "steppable/number.hpp"

#include <array>
#include <cstddef>
#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl/array.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/string_view.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace steppable::__internals::bindings
{
    void bindingsMatrix(nanobind::module_& mod)
    {
        nb::class_<steppable::Matrix>(mod, "Matrix")
            .def(nb::init<MatVec2D<Number>>(), "values"_a)
            .def(nb::init<MatVec2D<double>>(), "values"_a)
            .def("zeros", [](size_t cols, size_t rows) { return steppable::Matrix::zeros(cols, rows); })
            .def("ones", [](size_t cols, size_t rows) { return steppable::Matrix::ones(cols, rows); })
            .def("rref", &steppable::Matrix::rref)
            .def("ref", &steppable::Matrix::ref)
            .def("det", &steppable::Matrix::det)
            .def("transpose", &steppable::Matrix::transpose)
            .def(nb::self + nb::self, nb::rv_policy::automatic_reference)
            .def(nb::self - nb::self, nb::rv_policy::automatic_reference)
            .def(nb::self * nb::self, nb::rv_policy::automatic_reference)
            .def(nb::self *= nb::self, nb::rv_policy::automatic_reference)
            .def("__neg__", [](steppable::Matrix& matrix) { return -matrix; })
            .def("__pos__", [](steppable::Matrix& matrix) { return +matrix; })
            .def("__repr__", [](steppable::Matrix& matrix) { return matrix.present(0); })
            .def("__getitem__",
                 [](steppable::Matrix& matrix, std::array<size_t, 2> ij) {
                     auto [i, j] = ij;
                     return matrix[{ .y = i, .x = j }];
                 })
            .def_prop_ro("rows", &steppable::Matrix::getRows, nb::rv_policy::copy)
            .def_prop_ro("cols", &steppable::Matrix::getCols, nb::rv_policy::copy)
            .def_prop_ro(
                "dims",
                [](steppable::Matrix& matrix) { return std::array<size_t, 2>{ matrix.getRows(), matrix.getCols() }; },
                nb::rv_policy::copy);
    }
} // namespace steppable::__internals::bindings
