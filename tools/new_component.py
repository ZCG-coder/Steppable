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

import datetime
import sys
from pathlib import Path

from lib.paths import PROJECT_PATH, SRC_DIR, TESTS_DIR


class _Getch:
    """Gets a single character from standard input.  Does not echo to the
    screen."""

    def __init__(self):
        if not hasattr(sys.stdin, "fileno"):
            self.impl = input
            return
        try:
            self.impl = _GetchWindows()
        except ImportError:
            self.impl = _GetchUnix()

    def __call__(self):
        return self.impl()


class _GetchUnix:
    def __init__(self):
        import tty  # pyright: ignore

    def __call__(self) -> str:
        import termios
        import tty

        fd = sys.stdin.fileno()
        error = False
        try:
            old_settings = termios.tcgetattr(fd)
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
            error = False
        except termios.error:
            ch = input()
            error = True
        finally:
            if not error:
                termios.tcsetattr(
                    fd, termios.TCSADRAIN, old_settings  # pyright: ignore
                )
        return ch


class _GetchWindows:
    def __init__(self):
        import msvcrt  # pyright: ignore

    def __call__(self) -> str:
        import msvcrt

        return msvcrt.getch()  # pyright: ignore


getch = _Getch()

WELCOME_STRING = """\
WELCOME TO STEPPABLE!
=====================
Thank you for contributing to this project! This program is a guided wizard that creates a new component in Steppable.
Please select your option by pressing on the corresponding letter:

A - Add a new component
H - Help on new components, e.g., naming conventions etc. (**RECOMMENDED** for new contributors)
Q - Exit the program.
"""

HELP = [
    """\
HELP ON CONTRIBUTING
====================
Thank you for contributing to this project! This part documents how you may contribute to the project.

1. Naming Conventions for components
------------------------------------
Due to the problems of CMake with handling spaces, the names of components cannot include a space. Also, it cannot be a
restricted character in any operating system, for example, * " / \\ < > : | ? on Windows. The names should be in the
camelCase format.

Be descriptive with the name, and try to include similar functions in a single component. For example, instead of using
sin, cos, and tan in a single component, it is much better to combine them in a single component named "trigonometry".
""",
    """\
2. C++ Code Standard
--------------------
In this project, there are several things to bear in mind while developing.

For easier typing, camelCase naming is applied on all non-constant variables, functions and namespaces. Classes, enums,
structs need to apply the UpperCamelCase naming convention. The code should be formatted using the clang-format utility,
which is provided with LLVM, before the changed are committed.

The output should be constructed in the report file, instead of the main file. The latter is responsible for performing
calculations, while the report file is responsible for creating the output that can be shown to the user.

Examples:
+----------------------------------------------------------+-----------------------------------------------------------+
| BAD                                                      | GOOD                                                      |
+----------------------------------------------------------+-----------------------------------------------------------+
| #include<string>                                         | #include <string> // Formatting issues                    |
| std::string Func(std::string A, std::string B)           | std::string func(std::string A, std::string B)            |
|                                                          | // Naming issues                                          |
| {                                                        | {                                                         |
|     return "A + B" + " is " + A + B;                     |     return reportFunc(A, B); // The output should be      |
|                                                          |                              // constructed in the report |
|                                                          |                              // function.                 |
| }                                                        | }                                                         |
+----------------------------------------------------------+-----------------------------------------------------------+
""",
    """\
3. Questions?
-------------
Steppable has a discussion forum on GitHub, https://github.com/ZCG-coder/Steppable/discussions/categories/q-a. You may
raise any concers on contributing, using and more there.
""",
]

BRACE = "{"
END_BRACE = "}"
PATCH_COMMENT = "# NEW_COMPONENT: PATCH"


def show_help() -> None:
    for idx, part in enumerate(HELP):
        print(part)
        if idx != (len(HELP) - 1):
            print(f"Part {idx + 1}/{len(HELP)} | [Q]uit | [ANY KEY] next")
            char = getch().upper()
            if char == "Q":
                return
            elif char == "\n":
                continue
        else:
            print("END | [ANY KEY] exit")
            char = getch()


def validate_name(name: str) -> bool:
    if (
        "*" in name
        or '"' in name
        or "/" in name
        or "\\" in name
        or "<" in name
        or ">" in name
        or ":" in name
        or "|" in name
        or "?" in name
        or " " in name
    ):
        return False
    return True


def make_dir(name: str, date: str, author: str) -> None:
    path: Path = SRC_DIR / name

    if not path.is_dir():
        path.mkdir(exist_ok=False)
    else:
        print(
            "COMPONENT EXISTS. Maybe you want to add your code to that component, or choose another name."
        )
        return

    with open(path / f"{name}.cpp", "w") as f:
        f.write(
            f"""\
/**************************************************************************************************
 * Copyright (c) 2023-2024 NWSOFT                                                                 *
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

/**
 * @file {name}.cpp
 * @brief Desciption
 *
 * @author {author}
 * @date {date}
 */

#include "{name}Report.hpp"
#include <string>

std::string {name}(/* Arguments... */)
{BRACE}
    // Your code here...
{END_BRACE}
"""
        )
    print(f"- Added {name}.cpp")

    with open(path / f"{name}Report.cpp", "w") as f:
        f.write(
            f"""\
/**************************************************************************************************
 * Copyright (c) 2023-2024 NWSOFT                                                                 *
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

/**
 * @file {name}Report.cpp
 * @brief Desciption
 *
 * @author {author}
 * @date {date}
 */

#include "{name}Report.hpp"
#include <string>

std::string report{name.capitalize()}()
{BRACE}
    // Your code here...
{END_BRACE}
"""
        )
    print(f"- Added {name}Report.cpp")

    with open(path / f"{name}Report.hpp", "w") as f:
        f.write(
            f"""\
/**************************************************************************************************
 * Copyright (c) 2023-2024 NWSOFT                                                                 *
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

/**
 * @file {name}Report.hpp
 * @brief Desciption
 *
 * @author {author}
 * @date {date}
 */

#include <string>

std::string report{name.capitalize()}();
"""
        )
    print(f"- Added {name}Report.hpp")

    with open(TESTS_DIR / f"test{name.capitalize()}.cpp", "w") as f:
        f.write(
            """\
/**************************************************************************************************
 * Copyright (c) 2023-2024 NWSOFT                                                                 *
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

#include "colors.hpp"
#include "output.hpp"
#include "testing.hpp"
#include "util.hpp"

#include <iomanip>
#include <iostream>

TEST_START()
TEST_END()
"""
        )
    print(f"- Added test{name.capitalize()}.cpp")

    patch_cmakelists(name)


def patch_cmakelists(name: str) -> None:
    with open(PROJECT_PATH / "CMakeLists.txt") as f:
        contents = f.read()

    pos = contents.find(PATCH_COMMENT)
    contents = contents[: pos - 2] + f" {name}" + contents[pos - 2 :]
    with open(PROJECT_PATH / "CMakeLists.txt", "w") as f:
        f.write(contents)
        print(f"- Added {name} to CMakeLists.txt.")


def ordinal(n: int) -> str:
    """
    Get the ordinal numeral for a given number n.
    """
    return f"{n:d}{'tsnrhtdd'[(n // 10 % 10 != 1) * (n % 10 < 4) * n % 10::4]}"


today = datetime.date.today()
today_ordinal = ordinal(today.day)
today_string = today.strftime(f"{today_ordinal} %B %Y")


def main():
    print(WELCOME_STRING)
    selection = getch().upper()

    if selection == "H":
        return show_help()
    elif selection == "A":
        name = input("Name of your component: ")
        author = input("Your name: ")
        if not validate_name(name):
            print(f"INVALID NAME: {name}")
            return
        make_dir(name, today_string, author)


if __name__ == "__main__":
    main()
