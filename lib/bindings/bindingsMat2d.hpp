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
#include <nanobind/make_iterator.h>
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
        nb::class_<Matrix>(mod, "Matrix")
            .def(nb::init<MatVec2D<Number>, size_t>(), "values"_a, "prec"_a = 5)
            .def(nb::init<MatVec2D<double>, size_t>(), "values"_a, "prec"_a = 5)
            .def("zeros", [](size_t rows, size_t cols) { return Matrix::zeros(rows, cols); })
            .def("diag", [](size_t rows_cols, const Number& fill = 1) { return Matrix::diag(rows_cols, fill); })
            .def("diag", [](size_t rows_cols, const double fill = 1) { return Matrix::diag(rows_cols, fill); })
            .def("ones", [](size_t rows, size_t cols) { return Matrix::ones(rows, cols); })
            .def("rref", &Matrix::rref)
            .def("ref", &Matrix::ref)
            .def("rank", &Matrix::rank)
            .def("det", &Matrix::det)
            .def("transpose", &Matrix::transpose)
            .def(nb::self + nb::self, nb::rv_policy::automatic_reference)
            .def(nb::self - nb::self, nb::rv_policy::automatic_reference)
            .def(nb::self += nb::self, nb::rv_policy::automatic_reference)
            .def(nb::self -= nb::self, nb::rv_policy::automatic_reference)
            .def(nb::self << nb::self, nb::rv_policy::automatic_reference)
            .def(nb::self >> nb::self, nb::rv_policy::automatic_reference)
            .def(nb::self <<= nb::self, nb::rv_policy::automatic_reference)
            .def(nb::self >>= nb::self, nb::rv_policy::automatic_reference)
            .def(nb::self * nb::self, nb::rv_policy::automatic_reference)
            .def(nb::self *= nb::self, nb::rv_policy::automatic_reference)
            .def("__neg__", [](Matrix& matrix) { return -matrix; })
            .def("__pos__", [](Matrix& matrix) { return +matrix; })
            .def("__repr__", [](Matrix& matrix) { return matrix.present(0); })
            .def("__getitem__",
                 [](Matrix& matrix, std::array<size_t, 2> ij) {
                     auto [i, j] = ij;
                     return matrix[{ .y = i, .x = j }];
                 })
            .def_prop_ro("rows", &Matrix::getRows, nb::rv_policy::copy)
            .def_prop_ro("cols", &Matrix::getCols, nb::rv_policy::copy)
            .def_prop_ro(
                "dims",
                [](Matrix& matrix) { return std::array<size_t, 2>{ matrix.getRows(), matrix.getCols() }; },
                nb::rv_policy::copy)
            .def(
                "__iter__",
                [](Matrix& self) {
                    return nb::make_iterator(nb::type<Matrix>(), "MatrixIterator", self.begin(), self.end());
                },
                nb::keep_alive<0, 1>()); // Important for lifetime management
        ;
    }
} // namespace steppable::__internals::bindings
