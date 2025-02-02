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
    """A Steppable number, which performs exactly like a Python number, allowing add, subtract, multiply..."""

    def __init__(
        self,
        value: str = "0",
        prec: int = 5,
        roundingMode: steppyble.RoundingMode = steppyble.RoundingMode.USE_CURRENT_PREC,
    ) -> None:
        ...

    def __repr__(self) -> str:
        ...

    def __add__(self, _: steppyble.Number, /) -> steppyble.Number:
        ...

    def __iadd__(self, _: steppyble.Number, /) -> steppyble.Number:
        ...

    def __sub__(self, _: steppyble.Number, /) -> steppyble.Number:
        ...

    def __isub__(self, _: steppyble.Number, /) -> steppyble.Number:
        ...

    def __mul__(self, _: steppyble.Number, /) -> steppyble.Number:
        ...

    def __imul__(self, _: steppyble.Number, /) -> steppyble.Number:
        ...

    def __truediv__(self, _: steppyble.Number, /) -> steppyble.Number:
        ...

    def __itruediv__(self, _: steppyble.Number, /) -> steppyble.Number:
        ...

    def __pow__(self, _: steppyble.Number, /) -> steppyble.Number:
        ...

    def __ipow__(self, _: steppyble.Number, /) -> steppyble.Number:
        ...

    def __eq__(self, _: object, /) -> bool:
        ...

    def __ne__(self, _: object, /) -> bool:
        ...

    def __ge__(self, _: steppyble.Number, /) -> bool:
        ...

    def __gt__(self, _: steppyble.Number, /) -> bool:
        ...

    def __le__(self, _: steppyble.Number, /) -> bool:
        ...

    def __lt__(self, _: steppyble.Number, /) -> bool:
        ...
