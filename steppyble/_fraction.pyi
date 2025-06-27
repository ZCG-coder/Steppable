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

class Fraction:
    def __init__(self, top: str = "1", bottom: str = "1") -> None:
        """
        Initializes a Fraction.

        Parameters
        ----------
        top : str, optional
            Numerator of the fraction (default is "1").
        bottom : str, optional
            Denominator of the fraction (default is "1").
        """
        ...

    def __repr__(self) -> str:
        """
        Returns the string representation of the fraction.

        Returns
        -------
        str
            String representation of the fraction.
        """
        ...

    def __add__(self, rhs: steppyble.Fraction, /) -> steppyble.Fraction:
        """
        Adds another fraction to this fraction.

        Parameters
        ----------
        rhs : steppyble.Fraction
            The fraction to add.

        Returns
        -------
        steppyble.Fraction
            The sum of the two fractions.
        """
        ...

    def __iadd__(self, rhs: steppyble.Fraction, /) -> steppyble.Fraction:
        """
        Adds another fraction to this fraction in-place.

        Parameters
        ----------
        rhs : steppyble.Fraction
            The fraction to add.

        Returns
        -------
        steppyble.Fraction
            The sum of the two fractions (in-place).
        """
        ...

    def __sub__(self, rhs: steppyble.Fraction, /) -> steppyble.Fraction:
        """
        Subtracts another fraction from this fraction.

        Parameters
        ----------
        rhs : steppyble.Fraction
            The fraction to subtract.

        Returns
        -------
        steppyble.Fraction
            The difference of the two fractions.
        """
        ...

    def __isub__(self, rhs: steppyble.Fraction, /) -> steppyble.Fraction:
        """
        Subtracts another fraction from this fraction in-place.

        Parameters
        ----------
        rhs : steppyble.Fraction
            The fraction to subtract.

        Returns
        -------
        steppyble.Fraction
            The difference of the two fractions (in-place).
        """
        ...

    def __neg__(self, /) -> steppyble.Fraction:
        """
        Returns the negation of the fraction.

        Returns
        -------
        steppyble.Fraction
            The negated fraction.
        """
        ...

    def __pos__(self, /) -> steppyble.Fraction:
        """
        Returns a copy of the fraction (unary plus).

        Returns
        -------
        steppyble.Fraction
            A copy of the fraction.
        """
        ...

    def __mul__(self, rhs: steppyble.Fraction, /) -> steppyble.Fraction:
        """
        Multiplies this fraction by another fraction.

        Parameters
        ----------
        rhs : steppyble.Fraction
            The fraction to multiply with.

        Returns
        -------
        steppyble.Fraction
            The product of the two fractions.
        """
        ...

    def __imul__(self, rhs: steppyble.Fraction, /) -> steppyble.Fraction:
        """
        Multiplies this fraction by another fraction in-place.

        Parameters
        ----------
        rhs : steppyble.Fraction
            The fraction to multiply with.

        Returns
        -------
        steppyble.Fraction
            The product of the two fractions (in-place).
        """
        ...

    def __truediv__(self, rhs: steppyble.Fraction, /) -> steppyble.Fraction:
        """
        Divides this fraction by another fraction.

        Parameters
        ----------
        rhs : steppyble.Fraction
            The fraction to divide by.

        Returns
        -------
        steppyble.Fraction
            The quotient of the two fractions.
        """
        ...

    def __itruediv__(self, rhs: steppyble.Fraction, /) -> steppyble.Fraction:
        """
        Divides this fraction by another fraction in-place.

        Parameters
        ----------
        rhs : steppyble.Fraction
            The fraction to divide by.

        Returns
        -------
        steppyble.Fraction
            The quotient of the two fractions (in-place).
        """
        ...

    def __pow__(self, rhs: steppyble.Fraction, /) -> steppyble.Fraction:
        """
        Raises this fraction to the power of another fraction.

        Parameters
        ----------
        rhs : steppyble.Fraction
            The exponent.

        Returns
        -------
        steppyble.Fraction
            The result of exponentiation.
        """
        ...

    def __ipow__(self, rhs: steppyble.Fraction, /) -> steppyble.Fraction:
        """
        Raises this fraction to the power of another fraction in-place.

        Parameters
        ----------
        rhs : steppyble.Fraction
            The exponent.

        Returns
        -------
        steppyble.Fraction
            The result of exponentiation (in-place).
        """
        ...

    def __eq__(self, _: object, /) -> bool:
        """
        Checks if this fraction is equal to another object.

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
        Checks if this fraction is not equal to another object.

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

    def __ge__(self, rhs: steppyble.Fraction, /) -> bool:
        """
        Checks if this fraction is greater than or equal to another fraction.

        Parameters
        ----------
        rhs : steppyble.Fraction
            The fraction to compare with.

        Returns
        -------
        bool
            True if greater than or equal, False otherwise.
        """
        ...

    def __gt__(self, rhs: steppyble.Fraction, /) -> bool:
        """
        Checks if this fraction is greater than another fraction.

        Parameters
        ----------
        rhs : steppyble.Fraction
            The fraction to compare with.

        Returns
        -------
        bool
            True if greater, False otherwise.
        """
        ...

    def __le__(self, rhs: steppyble.Fraction, /) -> bool:
        """
        Checks if this fraction is less than or equal to another fraction.

        Parameters
        ----------
        rhs : steppyble.Fraction
            The fraction to compare with.

        Returns
        -------
        bool
            True if less than or equal, False otherwise.
        """
        ...

    def __lt__(self, rhs: steppyble.Fraction, /) -> bool:
        """
        Checks if this fraction is less than another fraction.

        Parameters
        ----------
        rhs : steppyble.Fraction
            The fraction to compare with.

        Returns
        -------
        bool
            True if less, False otherwise.
        """
        ...
