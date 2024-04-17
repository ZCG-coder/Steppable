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
PATCH_COMPILE_COMMANDS.PY - Removes NO_MAIN definitions in compile_commands.json

This file contains the patch method, which patches the compile_commands.json file.
The compile_commands.json file is used by various LSP servers to try compiling the project,
and generate an AST tree for analyzing.

However, since this project also builds a library, calc,
we have to disable all the main() functions by the NO_MAIN macro.
This causes the LSP to spot out more warnings as usual, as the main function would get ignored.
This file removes the NO_MAIN definition to fix this issue.
"""

import json
import re
from pathlib import Path

PROJECT_PATH = Path(__file__).parent.parent
NO_MAIN_PATTERN = re.compile(r"\s-DNO_MAIN\s")
I_SYS_ROOT_PATTERN = re.compile(
    r"\s/Library/Developer/CommandLineTools/SDKs/MacOSX\d\d\.\d\.sdk\s"
)


def get_compile_commands() -> Path:
    """
    Gets the path to compile_commands.json.
    :returns: The commands file.
    :raises RuntimeError: if the build directory cannot be found.
    """

    if (
        compile_commands_file := PROJECT_PATH / "build" / "compile_commands.json"
    ).is_file:
        return compile_commands_file
    elif (
        compile_commands_file := PROJECT_PATH
        / "cmake-build-debug"
        / "compile_commands.json"
    ).is_file:
        return compile_commands_file
    elif (
        compile_commands_file := PROJECT_PATH
        / "cmake-build-release"
        / "compile_commands.json"
    ).is_file:
        return compile_commands_file

    raise RuntimeError("Cannot get the CMake build directory")


def patch():
    """Remove the NO_MAIN definition in compile_commands.json"""

    file = get_compile_commands()
    with open(file) as f:
        objs = json.load(f)

    modified_objs = []
    for obj in objs:
        command: str = obj["command"]
        command = re.sub(NO_MAIN_PATTERN, " ", command)
        command = re.sub(
            I_SYS_ROOT_PATTERN,
            " /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk ",
            command,
        )
        obj["command"] = command
        modified_objs.append(obj)

    with open(file, "w") as f:
        json.dump(modified_objs, f, indent=4)


if __name__ == "__main__":
    patch()
