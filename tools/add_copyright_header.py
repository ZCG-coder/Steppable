#####################################################################################################
#  Copyright (c) 2023 NWSOFT                                                                        #
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

from pathlib import Path

PROJECT_PATH = Path(__file__).parent.parent

COPYRIGHT_CPP = """\
/**************************************************************************************************
 * Copyright (c) 2023 NWSOFT                                                                      *
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

COPYRIGHT_PY_CMAKE = """\
#####################################################################################################
#  Copyright (c) 2023 NWSOFT                                                                        #
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


def count_lines(text: str) -> int:
    return len(text.splitlines())


def first_n_lines(text: str, n: int) -> str:
    lines = text.splitlines()
    return "\n".join(lines[0:n])


def process(file: Path):
    if file.suffix in [".cpp", ".hpp"] or file.name == "cpp.hint":  # C++ Source / Header
        with open(file, "r") as f:
            contents = f.read()
            if first_n_lines(contents, count_lines(COPYRIGHT_CPP)) != COPYRIGHT_CPP:
                contents = COPYRIGHT_CPP + "\n\n" + contents
                print(f"Added header to {file}")

        with open(file, "w") as f:
            f.write(contents)
    elif file.suffix == ".py" or file.name == "CMakeLists.txt":  # Python File or CMake file
        with open(file, "r") as f:
            contents = f.read()
            if first_n_lines(contents, count_lines(COPYRIGHT_CPP)) != COPYRIGHT_PY_CMAKE:
                contents = COPYRIGHT_PY_CMAKE + "\n\n" + contents
                print(f"Added header to {file}")

        with open(file, "w") as f:
            f.write(contents)


def walk_into_directory(path: Path):
    for subpath in path.rglob("*"):
        if subpath.is_file():
            print(f"Processing {subpath}")
            process(subpath)

    print("DONE!")


if __name__ == '__main__':
    process(PROJECT_PATH / "CMakeLists.txt")
    process(PROJECT_PATH / "cpp.hint")
    walk_into_directory(PROJECT_PATH / "src")
    walk_into_directory(PROJECT_PATH / "include")
    walk_into_directory(PROJECT_PATH / "tests")
    walk_into_directory(PROJECT_PATH / "tools")
