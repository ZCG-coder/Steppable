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

import steppyble

class Number:
    """A Steppable number, which performs exactly like a Python number, allowing add, subtract, multiply, etc."""

    def __init__(
        self,
        value: str = "0",
        prec: int = 5,
        roundingMode: steppyble.RoundingMode = steppyble.RoundingMode.USE_CURRENT_PREC,
    ) -> None:
        """
        Initializes a Steppable number.

        Parameters
        ----------
        value : str, optional
            The value to initialize the number with (default is "0").
        prec : int, optional
            Precision of the number (default is 5).
        roundingMode : steppyble.RoundingMode, optional
            Rounding mode to use (default is steppyble.RoundingMode.USE_CURRENT_PREC).
        """
        ...

    def __repr__(self) -> str:
        """
        Returns the string representation of the number.

        Returns
        -------
        str
            String representation of the number.
        """
        ...

    def __add__(self, rhs: steppyble.Number, /) -> steppyble.Number:
        """
        Adds another number to this number.

        Parameters
        ----------
        rhs : steppyble.Number
            The number to add.

        Returns
        -------
        steppyble.Number
            The sum of the two numbers.
        """
        ...

    def __iadd__(self, rhs: steppyble.Number, /) -> steppyble.Number:
        """
        Adds another number to this number in-place.

        Parameters
        ----------
        rhs : steppyble.Number
            The number to add.

        Returns
        -------
        steppyble.Number
            The sum of the two numbers (in-place).
        """
        ...

    def __sub__(self, rhs: steppyble.Number, /) -> steppyble.Number:
        """
        Subtracts another number from this number.

        Parameters
        ----------
        rhs : steppyble.Number
            The number to subtract.

        Returns
        -------
        steppyble.Number
            The difference of the two numbers.
        """
        ...

    def __neg__(self, /) -> steppyble.Number:
        """
        Returns the negation of the number.

        Returns
        -------
        steppyble.Number
            The negated number.
        """
        ...

    def __pos__(self, /) -> steppyble.Number:
        """
        Returns a copy of the number (unary plus).

        Returns
        -------
        steppyble.Number
            A copy of the number.
        """
        ...

    def __isub__(self, rhs: steppyble.Number, /) -> steppyble.Number:
        """
        Subtracts another number from this number in-place.

        Parameters
        ----------
        rhs : steppyble.Number
            The number to subtract.

        Returns
        -------
        steppyble.Number
            The difference of the two numbers (in-place).
        """
        ...

    def __mul__(self, rhs: steppyble.Number, /) -> steppyble.Number:
        """
        Multiplies this number by another number.

        Parameters
        ----------
        rhs : steppyble.Number
            The number to multiply with.

        Returns
        -------
        steppyble.Number
            The product of the two numbers.
        """
        ...

    def __imul__(self, rhs: steppyble.Number, /) -> steppyble.Number:
        """
        Multiplies this number by another number in-place.

        Parameters
        ----------
        rhs : steppyble.Number
            The number to multiply with.

        Returns
        -------
        steppyble.Number
            The product of the two numbers (in-place).
        """
        ...

    def __truediv__(self, rhs: steppyble.Number, /) -> steppyble.Number:
        """
        Divides this number by another number.

        Parameters
        ----------
        rhs : steppyble.Number
            The number to divide by.

        Returns
        -------
        steppyble.Number
            The quotient of the two numbers.
        """
        ...

    def __itruediv__(self, rhs: steppyble.Number, /) -> steppyble.Number:
        """
        Divides this number by another number in-place.

        Parameters
        ----------
        rhs : steppyble.Number
            The number to divide by.

        Returns
        -------
        steppyble.Number
            The quotient of the two numbers (in-place).
        """
        ...

    def __pow__(self, rhs: steppyble.Number, /) -> steppyble.Number:
        """
        Raises this number to the power of another number.

        Parameters
        ----------
        rhs : steppyble.Number
            The exponent.

        Returns
        -------
        steppyble.Number
            The result of exponentiation.
        """
        ...

    def __ipow__(self, rhs: steppyble.Number, /) -> steppyble.Number:
        """
        Raises this number to the power of another number in-place.

        Parameters
        ----------
        rhs : steppyble.Number
            The exponent.

        Returns
        -------
        steppyble.Number
            The result of exponentiation (in-place).
        """
        ...

    def __eq__(self, _: object, /) -> bool:
        """
        Checks if this number is equal to another object.

        Parameters
        ----------
        _ : object
            The object to compare with.

        Returns
        -------
        bool
            True if equal, False otherwise.
        """
        ...

    def __ne__(self, _: object, /) -> bool:
        """
        Checks if this number is not equal to another object.

        Parameters
        ----------
        _ : object
            The object to compare with.

        Returns
        -------
        bool
            True if not equal, False otherwise.
        """
        ...

    def __ge__(self, rhs: steppyble.Number, /) -> bool:
        """
        Checks if this number is greater than or equal to another number.

        Parameters
        ----------
        rhs : steppyble.Number
            The number to compare with.

        Returns
        -------
        bool
            True if greater than or equal, False otherwise.
        """
        ...

    def __gt__(self, rhs: steppyble.Number, /) -> bool:
        """
        Checks if this number is greater than another number.

        Parameters
        ----------
        rhs : steppyble.Number
            The number to compare with.

        Returns
        -------
        bool
            True if greater, False otherwise.
        """
        ...

    def __le__(self, rhs: steppyble.Number, /) -> bool:
        """
        Checks if this number is less than or equal to another number.

        Parameters
        ----------
        rhs : steppyble.Number
            The number to compare with.

        Returns
        -------
        bool
            True if less than or equal, False otherwise.
        """
        ...

    def __lt__(self, rhs: steppyble.Number, /) -> bool:
        """
        Checks if this number is less than another number.

        Parameters
        ----------
        rhs : steppyble.Number
            The number to compare with.

        Returns
        -------
        bool
            True if less, False otherwise.
        """
        ...
