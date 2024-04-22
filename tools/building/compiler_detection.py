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
This module is used to detect the C++ compiler on the system, and return the path to it.
If possible, it will cache the compiler path in the build directory, so that it does not have to be detected again.
"""

import json
import logging
import re
import subprocess
from pathlib import Path

from building.paths import BUILD_DIR

GCC_VERSION_RE = re.compile(r"g\+\+ (\(.+?\))? (\d+\.\d+\.\d+)")
CLANG_VERSION_RE = re.compile(r"version (\d+\.\d+\.\d+)")

logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)


def get_identification(compiler_path: Path, compiler_type: int) -> str:
    """
    Returns a string that identifies the compiler. This is used to display the compiler in a more user-friendly way.

    :param compiler_path: The path to the compiler executable.
    :param compiler_type: The type of compiler. 0 for GCC, 1 for Clang, 2 for CL.EXE.
    :return: A string that identifies the compiler.
    """
    if compiler_type == 0:
        # GCC
        output = subprocess.check_output(
            [compiler_path, "--version"], stderr=subprocess.STDOUT
        ).decode("utf-8")
        matches = GCC_VERSION_RE.search(output)
        if matches:
            return f"GCC {matches.group(2)}"

    elif compiler_type == 1:
        # Clang
        output = subprocess.check_output(
            [compiler_path, "--version"], stderr=subprocess.STDOUT
        ).decode("utf-8")
        matches = CLANG_VERSION_RE.search(output)
        if matches:
            return f"Clang {matches.group(1)}"
    elif compiler_type == 2:
        # CL.EXE
        output = subprocess.check_output(
            [compiler_path, "/?"], stderr=subprocess.STDOUT
        ).decode("utf-8")
        return output.split("\n")[0]

    raise ValueError("Unknown compiler type.")


def register_compiler(path: Path) -> None:
    """
    Adds the compiler path to the status.json file in the build directory. This is used to cache the compiler path.
    """
    with open(BUILD_DIR / "status.json", "w") as f:
        json.dump({"compiler": str(path)}, f)


def detect_cxx_compiler() -> Path:
    """
    Find a suitable C++ compiler installed on the system. This function will first check the status.json file in the
    build directory to see if the compiler has already been detected. If not, it will search for the compiler on the
    system.

    The function prioritizes Clang over GCC, and GCC over CL.EXE.

    :return: The path to the compiler executable.
    :raises FileNotFoundError: If no compiler is found.
    """
    logger.info("DETECTING C++ COMPILER")
    with open(BUILD_DIR / "status.json", "r") as f:
        data = json.loads(f.read())
        if "compiler" in data.keys():
            logger.info(f"USING CACHED COMPILER: {data['compiler']}")
            return Path(data["compiler"])

    # Is it Clang?
    try:
        output = (
            subprocess.check_output(["which", "clang++"], stderr=subprocess.STDOUT)
            .decode("utf-8")
            .strip()
        )

        logger.info(f"FOUND COMPILER: {get_identification(Path(output), 1)}")
        path = Path(output)
        register_compiler(path)
        return path
    except (subprocess.CalledProcessError, FileNotFoundError):
        pass

    # Is it GCC?
    try:
        output = (
            subprocess.check_output(["which", "g++"], stderr=subprocess.STDOUT)
            .decode("utf-8")
            .strip()
        )

        logger.info(f"FOUND COMPILER: {get_identification(Path(output), 0)}")
        path = Path(output)
        register_compiler(path)
        return path
    except (subprocess.CalledProcessError, FileNotFoundError):
        pass

    # Is it CL.EXE?
    try:
        output = (
            subprocess.check_output(["where", "cl.exe"], stderr=subprocess.STDOUT)
            .decode("utf-8")
            .strip()
        )

        logger.info(f"FOUND COMPILER: {output}")
        path = Path(output)
        register_compiler(path)
        return path
    except (subprocess.CalledProcessError, FileNotFoundError):
        pass

    raise FileNotFoundError("No C++ compiler found.")
