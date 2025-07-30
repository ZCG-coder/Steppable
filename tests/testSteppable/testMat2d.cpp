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
SECTION(Matrix concatenation)
steppable::Matrix mat1({
    { 1, 2, 3, 4, 5 },
    { 2, 3, 4, 5, 6 },
    { 3, 4, 5, 6, 7 },
});
steppable::Matrix mat2({
    { 1, 2, 3, 4 },
    { 2, 3, 4, 5 },
    { 3, 4, 5, 6 },
});
steppable::Matrix mat3({ { 1, 2, 3, 4 } });
steppable::Matrix mat4({ { 1, 2, 3, 4, 5 } });

// Computed with MATLAB
// 1 | A = [
// 2 |     [1:5;2:6;3:7] [1:4;2:5;3:6]
// 3 |     1:4 1:5
// 4 | ]
_.assertIsEqual(steppable::Matrix({
                    { mat1, mat2 },
                    { mat3, mat4 },
                }),
                steppable::Matrix({
                    { 1, 2, 3, 4, 5, 1, 2, 3, 4 },
                    { 2, 3, 4, 5, 6, 2, 3, 4, 5 },
                    { 3, 4, 5, 6, 7, 3, 4, 5, 6 },
                    { 1, 2, 3, 4, 1, 2, 3, 4, 5 },
                }));
SECTION_END()

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

steppable::Matrix mat4({ { 1, 2, 3 } });
steppable::Matrix mat5({
    { 1 },
    { 2 },
    { 3 },
});
_.assertIsEqual(mat4.elemWiseMultiply(mat5),
                steppable::Matrix({
                    { 1, 2, 3 },
                    { 2, 4, 6 },
                    { 3, 6, 9 },
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

steppable::Matrix mat3({
    { 1, 7, 3 },
    { 7, 4, 5 },
    { 3, 5, 2 },
});
_.assertTrue(mat3.isSymmetric());
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

SECTION(Test matrix sum)
// Computed by MATLAB
// 1 | A = [1 2 3 4;5 6 7 8;9 1 2 3;4 7 9 5]
// 2 | sum(A, 1)
// > |
// > | ans =
// > |
// > | 19    16    21    20
// > |
// 3 | sum(A, 2)
// > |
// > | ans =
// > |
// > |     10
// > |     26
// > |     15
// > |     25
// > |
// 4 | sum(A, "all")
// > |
// > | ans =
// > |
// > |     76

steppable::Matrix mat({
    { 1, 2, 3, 4 },
    { 5, 6, 7, 8 },
    { 9, 1, 2, 3 },
    { 4, 7, 9, 5 },
});
_.assertIsEqual(mat.sum(), steppable::Number(76));
_.assertIsEqual(mat.sumDims(steppable::MatDims::COLS), steppable::Matrix({ { 19, 16, 21, 20 } }));
_.assertIsEqual(mat.sumDims(steppable::MatDims::ROWS), steppable::Matrix({ { 10 }, { 26 }, { 15 }, { 25 } }));

SECTION_END()

SECTION(Test matrix dot - product)
steppable::Matrix v1({ { 1, 2, 3 } });
steppable::Matrix v2({ { 4, 5, 6 } });
_.assertIsEqual(v1.dot(v2), steppable::Matrix({ { 32 } }));

steppable::Matrix mat1({ { 0, 0 }, { 0, 7 } });
steppable::Matrix mat2({ { 0, 0 }, { 0, 3 } });

_.assertIsEqual(mat1.dot(mat2, steppable::MatDims::ROWS), steppable::Matrix({ { 0, 21 } }).transpose());
_.assertIsEqual(mat1.dot(mat2, steppable::MatDims::COLS), steppable::Matrix({ { 0, 21 } }));

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
                        // 1 | c = [1 2 3 4];
                        // 2 | r = [1 5 6 7];
                        // 3 | toeplitz(c,r)
                        { 1, 5, 6, 7 },
                        { 2, 1, 5, 6 },
                        { 3, 2, 1, 5 },
                        { 4, 3, 2, 1 },
                    },
                    4),
                steppable::Matrix::toeplitz(steppable::Matrix({
                                                { 1, 2, 3, 4 },
                                            }),
                                            steppable::Matrix({
                                                { 1, 5, 6, 7 },
                                            }))
                    .roundOffValues(4));

_.assertIsEqual(steppable::Matrix(
                    {
                        // Computed with MATLAB
                        // 1 | c = [1 2 3 4];
                        // 2 | r = [4 5 6];
                        // 3 | toeplitz(c,r)
                        { 1, 5, 6 },
                        { 2, 1, 5 },
                        { 3, 2, 1 },
                        { 4, 3, 2 },
                    },
                    4),
                steppable::Matrix::toeplitz(steppable::Matrix({
                                                { 1, 2, 3, 4 },
                                            }),
                                            steppable::Matrix({
                                                { 4, 5, 6 },
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

_.assertIsEqual(steppable::Matrix(
                    {
                        // Computed with MATLAB
                        // 1 | A = vander(1:5)
                        { 1, 1, 1, 1, 1 },
                        { 16, 8, 4, 2, 1 },
                        { 81, 27, 9, 3, 1 },
                        { 256, 64, 16, 4, 1 },
                        { 625, 125, 25, 5, 1 },
                    },
                    4),
                steppable::Matrix::vandermonde(steppable::Matrix({
                                                   { 1, 2, 3, 4, 5 },
                                               }))
                    .roundOffValues(4));

// Property of Hadamard matrices
//      T
// H * H  = n * I
const auto& h1 = steppable::Matrix::hadamard(8);
_.assertIsEqual(h1* h1.transpose(), steppable::Matrix::diag(8, 1) * 8);

const auto& h2 = steppable::Matrix::hadamard(48);
_.assertIsEqual(h2* h2.transpose(), steppable::Matrix::diag(48, 1) * 48);

_.assertIsEqual(h1.trace(), steppable::Number(0));
_.assertIsEqual(h2.trace(), steppable::Number(0));
SECTION_END()
TEST_END()
