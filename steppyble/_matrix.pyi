#####################################################################################################
#  Copyright (c) 2023-2025 NWSOFT                                                                   #
#                                                                                                   #
#  Permission is hereby granted, free of charge, to any person obtaining a copy                     #
#  of this software and associated documentation files (the "Software"), to deal                    #
#  in the Software without restriction, including without limitation the rights                     #
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                        #
#  copies of the Software, and to permit persons to whom the Software is                            #
#  furnished to do so, subject to the following conditions:                                         #
#                                                                                                   #
#  The above copyright notice and this permission notice shall be included in all                   #
#  copies or substantial portions of the Software.                                                  #
#                                                                                                   #
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                       #
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                         #
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE                      #
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                           #
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,                    #
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE                    #
#  SOFTWARE.                                                                                        #
#####################################################################################################

import typing

import steppyble
import steppyble._types

class Matrix:
    """
    A Steppable matrix supporting arithmetic and matrix operations.

    Parameters
    ----------
    values : Sequence[Sequence[steppyble.Number]] or Sequence[Sequence[float]]
        The values of the matrix.
    prec : int, optional
        Precision of the values to be copied into the matrix (default is 5).

    Notes
    -----
    This class mimics Python's number behavior for matrices, supporting addition, subtraction, multiplication, and more.
    """

    @typing.overload
    def __init__(
        self,
        values: typing.Sequence[typing.Sequence[steppyble.Number]],
        prec: int = 5,
    ) -> None:
        """
        Constructs a matrix with specified dimensions and an optional fill value.

        Parameters
        ----------
        values
            The values of the matrix.
        prec
            Precision of the values to be copied into the matrix.
        """

        ...

    @typing.overload
    def __init__(
        self,
        values: typing.Sequence[typing.Sequence[float]],
        prec: int = 5,
    ) -> None:
        """
        Constructs a matrix with specified dimensions and an optional fill value.

        Parameters
        ----------
        values
            The values of the matrix.
        prec
            Precision of the values to be copied into the matrix.
        """
        ...

    def __repr__(self) -> str:
        """
        Represents the values in the matrix in text form.

        Returns
        -------
        str
            A string representing the matrix.
        """

        ...

    def __lshift__(self, matrix: steppyble.Matrix, /) -> steppyble.Matrix:
        """
        Joins a matrix to the right of the current matrix.

        Parameters
        ----------
        matrix
            The matrix to join.

        Return
        ------
        steppyble.Matrix
            The two matrices joined together.
        """

        ...

    def __ilshift__(self, matrix: steppyble.Matrix, /) -> steppyble.Matrix:
        """
        Joins a matrix to the right of the current matrix, assigning the result to the current one.

        Parameters
        ----------
        matrix
            The matrix to join.

        Return
        ------
        steppyble.Matrix
            The two matrices joined together.
        """

        ...

    def __rshift__(self, matrix: steppyble.Matrix, /) -> steppyble.Matrix:
        """
        Joins a matrix to the left of the current matrix.

        Parameters
        ----------
        matrix
            The matrix to join.

        Return
        ------
        steppyble.Matrix
            The two matrices joined together.
        """

        ...

    def __irshift__(self, matrix: steppyble.Matrix, /) -> steppyble.Matrix:
        """
        Joins a matrix to the left of the current matrix, assigning the result to the current one.

        Parameters
        ----------
        matrix
            The matrix to join.

        Return
        ------
        steppyble.Matrix
            The two matrices joined together.
        """
        ...

    def __add__(self, matrix: steppyble.Matrix, /) -> steppyble.Matrix:
        """
        Adds another matrix to the current one.

        Parameters
        ----------
        matrix
            The other matrix.

        Returns
        -------
        steppyble.Matrix
            A new matrix where all elements are added together correspondingly.
        """
        ...

    def __iadd__(self, matrix: steppyble.Matrix, /) -> steppyble.Matrix:
        """
        Adds another matrix to the current one, assigning the result to the current one.

        Parameters
        ----------
        matrix
            The other matrix.

        Returns
        -------
        steppyble.Matrix
            A new matrix where all elements are added together correspondingly.
        """
        ...

    def __sub__(self, matrix: steppyble.Matrix, /) -> steppyble.Matrix:
        """
        Subtracts another matrix from the current one.

        Parameters
        ----------
        matrix : steppyble.Matrix
            The other matrix.

        Returns
        -------
        steppyble.Matrix
            A new matrix where all elements are subtracted correspondingly.
        """
        ...

    def __neg__(self, /) -> steppyble.Matrix:
        """
        Returns the negation of the matrix (element-wise negation).

        Returns
        -------
        steppyble.Matrix
            A new matrix with all elements negated.
        """
        ...

    def __pos__(self, /) -> steppyble.Matrix:
        """
        Returns a copy of the matrix (unary plus).

        Returns
        -------
        steppyble.Matrix
            A copy of the matrix.
        """
        ...

    def __isub__(self, matrix: steppyble.Matrix, /) -> steppyble.Matrix:
        """
        Subtracts another matrix from the current one, assigning the result to the current one.

        Parameters
        ----------
        matrix : steppyble.Matrix
            The other matrix.

        Returns
        -------
        steppyble.Matrix
            The updated matrix after subtraction.
        """
        ...

    @typing.overload
    def __mul__(self, matrix: steppyble.Matrix, /) -> steppyble.Matrix:
        """
        Multiplies the current matrix by another matrix (matrix multiplication).

        Parameters
        ----------
        matrix : steppyble.Matrix
            The matrix to multiply with.

        Returns
        -------
        steppyble.Matrix
            The matrix product.
        """
        ...

    @typing.overload
    def __mul__(self, _: steppyble.Number, /) -> steppyble.Matrix:
        """
        Multiplies the current matrix by a scalar.

        Parameters
        ----------
        _ : steppyble.Number
            The scalar to multiply with.

        Returns
        -------
        steppyble.Matrix
            The scaled matrix.
        """
        ...

    @typing.overload
    def __imul__(self, _: steppyble.Number, /) -> steppyble.Matrix:
        """
        Multiplies the current matrix by a scalar in-place.

        Parameters
        ----------
        _ : steppyble.Number
            The scalar to multiply with.

        Returns
        -------
        steppyble.Matrix
            The scaled matrix (in-place).
        """
        ...

    @typing.overload
    def __imul__(self, matrix: steppyble.Matrix, /) -> steppyble.Matrix:
        """
        Multiplies the current matrix by another matrix in-place (matrix multiplication).

        Parameters
        ----------
        matrix : steppyble.Matrix
            The matrix to multiply with.

        Returns
        -------
        steppyble.Matrix
            The matrix product (in-place).
        """
        ...

    def __pow__(self, _: steppyble.Number, /) -> steppyble.Matrix:
        """
        Raises the matrix to a given power.

        Parameters
        ----------
        _ : steppyble.Number
            The exponent.

        Returns
        -------
        steppyble.Matrix
            The matrix raised to the given power.
        """
        ...

    def __ipow__(self, _: steppyble.Number, /) -> steppyble.Matrix:
        """
        Raises the matrix to a given power in-place.

        Parameters
        ----------
        _ : steppyble.Number
            The exponent.

        Returns
        -------
        steppyble.Matrix
            The matrix raised to the given power (in-place).
        """
        ...

    def __eq__(self, _: object, /) -> bool:
        """
        Checks if two matrices are equal.

        Parameters
        ----------
        _ : object
            The object to compare with.

        Returns
        -------
        bool
            True if the matrices are equal, False otherwise.
        """
        ...

    def __ne__(self, _: object, /) -> bool:
        """
        Checks if two matrices are not equal.

        Parameters
        ----------
        _ : object
            The object to compare with.

        Returns
        -------
        bool
            True if the matrices are not equal, False otherwise.
        """
        ...

    @staticmethod
    def zeros(rows: int, cols: int) -> steppyble.Matrix:
        """
        Returns a matrix filled with zeros.

        Parameters
        ----------
        rows : int
            Number of rows.
        cols : int
            Number of columns.

        Returns
        -------
        steppyble.Matrix
            A matrix of shape (rows, cols) filled with zeros.
        """
        ...

    @typing.overload
    @staticmethod
    def diag(
        rows_cols: int, fill: steppyble.Number = steppyble.Number("1")
    ) -> steppyble.Matrix:
        """
        Returns a diagonal matrix with a specified fill value (steppyble.Number).

        Parameters
        ----------
        rows_cols : int
            Number of rows and columns (matrix is square).
        fill : steppyble.Number, optional
            Value to fill the diagonal (default is steppyble.Number("1")).

        Returns
        -------
        steppyble.Matrix
            A diagonal matrix.
        """
        ...

    @typing.overload
    @staticmethod
    def diag(rows_cols: int, fill: float = 1) -> steppyble.Matrix:
        """
        Returns a diagonal matrix with a specified fill value (float).

        Parameters
        ----------
        rows_cols : int
            Number of rows and columns (matrix is square).
        fill : float, optional
            Value to fill the diagonal (default is 1).

        Returns
        -------
        steppyble.Matrix
            A diagonal matrix.
        """
        ...

    @staticmethod
    def ones(rows: int, cols: int) -> steppyble.Matrix:
        """
        Returns a matrix filled with ones.

        Parameters
        ----------
        rows : int
            Number of rows.
        cols : int
            Number of columns.

        Returns
        -------
        steppyble.Matrix
            A matrix of shape (rows, cols) filled with ones.
        """
        ...

    def rref(self) -> steppyble.Matrix:
        """
        Returns the reduced row echelon form (RREF) of the matrix.

        Returns
        -------
        steppyble.Matrix
            The RREF of the matrix.
        """
        ...

    def ref(self) -> steppyble.Matrix:
        """
        Returns the row echelon form (REF) of the matrix.

        Returns
        -------
        steppyble.Matrix
            The REF of the matrix.
        """
        ...

    def rank(self) -> steppyble.Number:
        """
        Returns the rank of the matrix.

        Returns
        -------
        steppyble.Number
            The rank of the matrix.
        """
        ...

    def det(self) -> steppyble.Matrix:
        """
        Returns the determinant of the matrix.

        Returns
        -------
        steppyble.Matrix
            The determinant of the matrix.
        """
        ...

    def transpose(self) -> steppyble.Matrix:
        """
        Returns the transpose of the matrix.

        Returns
        -------
        steppyble.Matrix
            The transposed matrix.
        """
        ...

    def __getitem__(self, indices: typing.Tuple[int]) -> steppyble.Matrix:
        """
        Returns a submatrix or element at the specified indices.

        Parameters
        ----------
        indices : Tuple[int]
            Indices to access.

        Returns
        -------
        steppyble.Matrix
            The submatrix or element at the given indices.
        """
        ...

    def rows(self) -> int:
        """
        Returns the number of rows of the matrix.

        Returns
        -------
        int
            The number of rows.
        """
        ...

    def cols(self) -> int:
        """
        Returns the number of columns of the matrix.

        Returns
        -------
        int
            The number of columns.
        """
        ...

    def dims(self) -> typing.Tuple[int, int]:
        """
        Returns the dimensions of the matrix.

        Returns
        -------
        typing.Tuple[int, int]
            The dimensions of the matrix as a tuple (rows, cols).
        """
        ...

    def __iter__(self) -> steppyble._types.MatrixIterator:
        """
        Returns an iterator over the matrix rows.

        Returns
        -------
        steppyble.Matrix
            An iterator over the matrix rows.
        """
        ...
