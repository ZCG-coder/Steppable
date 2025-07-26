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

#include "steppable/mat2d.hpp"
#include "steppable/number.hpp"
#include "testing.hpp"
#include "util.hpp"

#include <iomanip>
#include <iostream>

TEST_START()
SECTION(Matrix multiplication)
steppable::Matrix mat1({
    { 1, 0, 1 },
    { 2, 1, 1 },
    { 0, 1, 1 },
    { 1, 1, 2 },
});
steppable::Matrix mat2({
    { 1, 2, 1 },
    { 2, 3, 1 },
    { 4, 2, 2 },
});
auto mat3 = mat1 * mat2;

_.assertIsEqual(mat3,
                steppable::Matrix({
                    { 5, 4, 3 },
                    { 8, 9, 5 },
                    { 6, 5, 3 },
                    { 11, 9, 6 },
                }));
SECTION_END()

SECTION(Transpose)
steppable::Matrix mat2({
    { 1, 2, 1 },
    { 2, 3, 1 },
    { 4, 2, 2 },
});
// Two transposes results in the same matrix
//        T
// (  T )
// ( A  )   = A
_.assertIsEqual(mat2.transpose().transpose(), mat2);
_.assertIsNotEqual(mat2.transpose(), mat2);
SECTION_END()

SECTION(Determinant)
steppable::Matrix mat2({
    { 6, 90 },
    { 4892, 892 },
});
_.assertIsEqual(mat2.det(), steppable::Number(-434928));
SECTION_END()

SECTION(Matrix slicing)
steppable::Matrix matrix({
    { 5, 4, 3 },
    { 8, 9, 5 },
    { 6, 5, 3 },
    { 11, 9, 6 },
});
matrix = matrix[{ .y1 = 1, .x1 = 0, .y2 = 1, .x2 = 2 }];
_.assertIsEqual(matrix, steppable::Matrix({ { 8, 9, 5 } }));
SECTION_END()

SECTION(Matrix joining)
steppable::Matrix matrix1({
    { 5, 4, 3 },
    { 8, 9, 5 },
    { 6, 5, 3 },
});
steppable::Matrix matrix2({
    { 11, 9, 6 },
    { 8, 9, 5 },
    { 6, 5, 3 },
});
steppable::Matrix matrix3 = matrix1 << matrix2;
steppable::Matrix matrix4 = matrix1 >> matrix2;

_.assertIsEqual(matrix3,
                steppable::Matrix({
                    { 5, 4, 3, 11, 9, 6 },
                    { 8, 9, 5, 8, 9, 5 },
                    { 6, 5, 3, 6, 5, 3 },
                }));

_.assertIsEqual(matrix4,
                steppable::Matrix({
                    { 11, 9, 6, 5, 4, 3 },
                    { 8, 9, 5, 8, 9, 5 },
                    { 6, 5, 3, 6, 5, 3 },
                }));
SECTION_END()

SECTION(Matrix Rank)
using namespace steppable::literals;

steppable::Matrix matrix1({
    { 1, 2, 1 },
    { -2, -3, 1 },
    { 3, 5, 0 },
});
_.assertIsEqual(matrix1.rank(), 2_n);
SECTION_END()

SECTION(Matrix inverse)
steppable::Matrix matrix1({
    { -1, 1.5 },
    { 1, -1 },
});
_.assertIsEqual((matrix1 ^ -1),
                steppable::Matrix({ {
                                        2.0000000000,
                                        3.0000000000,
                                    },
                                    {
                                        2.0000000000,
                                        2.0000000000,
                                    } }));

steppable::Matrix matrix2(
    {
        { 69, 420, 475 },
        { 589, 4795, 33 },
        { 52, 47.5, 20.2 },
    },
    6);
auto test = (matrix2 ^ -1 ^ -1).roundOffValues(1);
_.assertIsEqual(test, matrix2);
SECTION_END()

SECTION(Test special matrices)
_.assertIsEqual(steppable::Matrix(
                    {
                        // Computed with MATLAB
                        // 1 | hilb(4)
                        { 1.0000, 0.5000, 0.3333, 0.2500 },
                        { 0.5000, 0.3333, 0.2500, 0.2000 },
                        { 0.3333, 0.2500, 0.2000, 0.1667 },
                        { 0.2500, 0.2000, 0.1667, 0.1429 },
                    },
                    4),
                steppable::Matrix::hilbert(4).roundOffValues(4));

_.assertIsEqual(steppable::Matrix(
                    {
                        // Computed with MATLAB
                        // 1 | hankel([1 2 5], [5 6 9 10])
                        { 1, 2, 5, 6 },
                        { 2, 5, 6, 9 },
                        { 5, 6, 9, 10 },
                    },
                    4),
                steppable::Matrix::hankel(steppable::Matrix({
                                              { 1, 2, 5 },
                                          }),
                                          steppable::Matrix({
                                              { 3, 6, 9, 10 },
                                          }))
                    .roundOffValues(4));

_.assertIsEqual(steppable::Matrix(
                    {
                        // Computed with MATLAB
                        // 1 | hankel([1 2 5], [5 10])
                        { 1, 2 },
                        { 2, 5 },
                        { 5, 10 },
                    },
                    4),
                steppable::Matrix::hankel(steppable::Matrix({
                                              { 1, 2, 5 },
                                          }),
                                          steppable::Matrix({
                                              { 5, 10 },
                                          }))
                    .roundOffValues(4));
SECTION_END()
TEST_END()
