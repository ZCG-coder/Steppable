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

"""
Add a copyright header to all files.
"""

import datetime
import re
from pathlib import Path

PROJECT_PATH = Path(__file__).parent.parent

COPYRIGHT_CPP = """\
/**************************************************************************************************
 * Copyright (c) 2023-{year} NWSOFT                                                                 *
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
 **************************************************************************************************/\
"""

REGEX_CPP = re.compile(
    r"""/\*+
 \* Copyright \(c\) 2023-(....) NWSOFT {65}\*
 \* {96}\*
 \* Permission is hereby granted, free of charge, to any person obtaining a copy {19}\*
 \* of this software and associated documentation files \(the "Software"\), to deal {18}\*
 \* in the Software without restriction, including without limitation the rights {19}\*
 \* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell {22}\*
 \* copies of the Software, and to permit persons to whom the Software is {26}\*
 \* furnished to do so, subject to the following conditions: {39}\*
 \* {96}\*
 \* The above copyright notice and this permission notice shall be included in all {17}\*
 \* copies or substantial portions of the Software\. {48}\*
 \* {96}\*
 \* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR {21}\*
 \* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, {23}\*
 \* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT\. IN NO EVENT SHALL THE {20}\*
 \* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER {25}\*
 \* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, {18}\*
 \* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE {18}\*
 \* SOFTWARE\. {86}\*
 \*+/
""",
    flags=re.MULTILINE,
)

COPYRIGHT_PY_CMAKE = """\
#####################################################################################################
#  Copyright (c) 2023-{year} NWSOFT                                                                   #
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
#####################################################################################################\
"""

REGEX_PY_CMAKE = re.compile(
    r"""#{101}
# {2}Copyright \(c\) 2023-(....) NWSOFT {67}#
# {99}#
# {2}Permission is hereby granted, free of charge, to any person obtaining a copy {21}#
# {2}of this software and associated documentation files \(the "Software"\), to deal {20}#
# {2}in the Software without restriction, including without limitation the rights {21}#
# {2}to use, copy, modify, merge, publish, distribute, sublicense, and/or sell {24}#
# {2}copies of the Software, and to permit persons to whom the Software is {28}#
# {2}furnished to do so, subject to the following conditions: {41}#
# {99}#
# {2}The above copyright notice and this permission notice shall be included in all {19}#
# {2}copies or substantial portions of the Software\. {50}#
# {99}#
# {2}THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  {22}#
# {2}IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, {25}#
# {2}FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT\. IN NO EVENT SHALL THE {22}#
# {2}AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER {27}#
# {2}LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, {20}#
# {2}OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE {20}#
# {2}SOFTWARE\. {88}#
#{101}
""",
    flags=re.MULTILINE,
)


def count_lines(text: str) -> int:
    """
    Count the number of lines in a string.
    :param text: The string to count the lines of.
    :return: The number of lines.
    """

    return len(text.splitlines())


def first_n_lines(text: str, n: int) -> str:
    """
    Get the first n lines of a string.
    :param text: The string to get the first n lines of.
    :param n: The number of lines to get.
    :return: The first n lines of the string.
    """

    lines = text.splitlines()
    return "\n".join(lines[0:n])


def process(file: Path) -> None:
    """
    Process the file, adding or updating the header if necessary.
    :param file: The file to process.
    """
    if (
        file.suffix in (".cpp", ".hpp")  # C++ Source / Header
        or file.name == "cpp.hint"  # C++ Hint file
    ):
        with open(file, "r") as f:
            contents = f.read()
            results = re.match(
                REGEX_CPP, first_n_lines(contents, count_lines(COPYRIGHT_CPP) + 1)
            )
            year = results.group(1) if results is not None else None
            if results is None:
                contents = (
                    COPYRIGHT_CPP.format(year=datetime.datetime.now().year)
                    + "\n\n"
                    + contents
                )
                print(f"Added header to {file}")
            elif year != str(datetime.datetime.now().year):
                header = COPYRIGHT_CPP.format(year=datetime.datetime.now().year)
                contents = contents.replace(results.group(0), header + "\n")
                print(f"Updated header in {file}")

        with open(file, "w") as f:
            f.write(contents)
    elif (
        file.suffix == ".py"
        or file.name == "CMakeLists.txt"
        or ".stp_" in file.suffix  # Steppable configuration files
    ):  # Python File or CMake file
        with open(file, "r") as f:
            contents = f.read()
            results = re.match(
                REGEX_PY_CMAKE,
                first_n_lines(contents, count_lines(COPYRIGHT_PY_CMAKE) + 1),
            )
            year = results.group(1) if results is not None else None
            if results is None:
                contents = (
                    COPYRIGHT_PY_CMAKE.format(year=datetime.datetime.now().year)
                    + "\n\n"
                    + contents
                )
                print(f"Added header to {file}")
            elif year != str(datetime.datetime.now().year):
                header = COPYRIGHT_PY_CMAKE.format(year=datetime.datetime.now().year)
                contents = contents.replace(results.group(0), header + "\n")
                print(f"Updated header in {file}")

        with open(file, "w") as f:
            f.write(contents)


def walk_into_directory(path: Path) -> None:
    """
    Walk into the directory and process all files.
    :param path: The directory to walk
    """

    for subpath in path.rglob("*"):
        if subpath.is_file():
            process(subpath)


if __name__ == "__main__":
    process(PROJECT_PATH / "CMakeLists.txt")
    process(PROJECT_PATH / "setup.py")
    process(PROJECT_PATH / "__init__.py")
    process(PROJECT_PATH / "cpp.hint")
    walk_into_directory(PROJECT_PATH / "include")
    walk_into_directory(PROJECT_PATH / "lib")
    walk_into_directory(PROJECT_PATH / "res")
    walk_into_directory(PROJECT_PATH / "src")
    walk_into_directory(PROJECT_PATH / "tests")
    walk_into_directory(PROJECT_PATH / "tools")
