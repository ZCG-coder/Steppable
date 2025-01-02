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

import sys
import os

from lib.constants import WINDOWS


def green() -> str:
    """
    Sets the terminal output color to green.

    :return: The escape sequence to set the terminal output color to green.
    """
    if WINDOWS:
        return ""
    if sys.stdout.isatty():
        return "\033[92m"
    return ""


def red() -> str:
    """
    Sets the terminal output color to red.

    :return: The escape sequence to set the terminal output color to red.
    """
    if WINDOWS:
        return ""
    if sys.stdout.isatty():
        return "\033[91m"
    return ""


def yellow() -> str:
    """
    Sets the terminal output color to yellow.

    :return: The escape sequence to set the terminal output color to yellow.
    """
    if WINDOWS:
        return ""
    if sys.stdout.isatty():
        return "\033[93m"
    return ""


def blue() -> str:
    """
    Sets the terminal output color to blue.

    :return: The escape sequence to set the terminal output color to blue.
    """
    if WINDOWS:
        return ""
    if sys.stdout.isatty():
        return "\033[94m"
    return ""


def erase_line(lines: int = 1) -> str:
    """
    Erases the specified number of lines in the terminal.

    :param lines: Number of lines to erase.
    :return: The escape sequence to erase the lines.
    """
    if WINDOWS:
        return ""
    if sys.stdout.isatty():
        return "\033[K\033[A\r"
    return ""


def reset() -> str:
    if WINDOWS:
        return ""
    if sys.stdout.isatty():
        return "\033[0m"
    return ""


def bold() -> str:
    if WINDOWS:
        return ""
    if sys.stdout.isatty():
        return "\033[1m"
    return ""


def print_error(line: str, pos: int, message: str) -> None:
    """
    Prints an error message with an arrow pointing to the position of the error.
    """
    print(f"ERROR: {message}")
    print(line)
    print(" " * pos + "^")


def print_progressbar(
    iteration: int,
    total: int,
    prefix: str = "",
    suffix: str = "",
    decimals: int = 1,
    length: int = 100,
    fill: str = "\u2588",
) -> None:
    """
    Call in a loop to create terminal progress bar.
    :param iteration: Current iteration.
    :param total: Total iterations.
    :param prefix: Prefix string.
    :param suffix: Suffix string.
    :param decimals: Positive number of decimals in percent complete.
    :param length: Character length of bar.
    :param fill: Bar fill character.
    """
    if not os.isatty(sys.stdout.fileno()):
        print(f"{prefix} {iteration}/{total} {suffix}")
        return
    percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))
    filled_length = int(length * iteration // total)
    bar = fill * filled_length + " " * (length - filled_length)
    print("\r%s |%s| %s%% %s" % (prefix, bar, percent, suffix), end="")
    # Print New Line on Complete
    if iteration == total:
        print()
