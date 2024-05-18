#####################################################################################################
#  Copyright (c) 2023-2024 NWSOFT                                                                   #
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

from lib.constants import WINDOWS


def green() -> str:
    if WINDOWS:
        return ""
    if sys.stdout.isatty():
        return "\033[92m"
    return ""


def red() -> str:
    if WINDOWS:
        return ""
    if sys.stdout.isatty():
        return "\033[91m"
    return ""


def yellow() -> str:
    if WINDOWS:
        return ""
    if sys.stdout.isatty():
        return "\033[93m"
    return ""


def blue() -> str:
    if WINDOWS:
        return ""
    if sys.stdout.isatty():
        return "\033[94m"
    return ""


def erase_line() -> str:
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
