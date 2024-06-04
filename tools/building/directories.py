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
This module contains functions that are used to create directories, check whether a target is updated, and create the
output name of a target.
"""

import json
import logging
import sys
from pathlib import Path
from typing import List

from lib.constants import WINDOWS
from lib.paths import BIN_DIR, BUILD_DIR, LIB_DIR, OBJ_DIR, PROJECT, PROJECT_PATH
from tools.building.constants import EXECUTABLE, SHARED, STATIC

logger = logging.getLogger(__name__)


def create_dir(name: str, parent: Path) -> None:
    """
    Creates a directory if it does not exist. If the directory exists, it does nothing. However, it will exit the
    program immediately if the object with the specified name exists, but is not a directory.
    :param name: The name of the directory.
    :param parent: The parent directory.
    """
    if (parent / name).is_dir():
        logger.debug(f"Directory {name} already exists!")
        return

    if (parent / name).exists() and not (parent / name).is_dir():
        logger.fatal(
            f"Cannot create directory {name}. It exists but is not a directory."
        )
        sys.exit(1)

    (parent / name).mkdir(parents=True)
    logger.debug(f"Created directory {name}.")


def create_build_dirs() -> None:
    """
    Creates the build directories if they do not exist. This function must be called before compilation, to ensure that
    objects are placed in the correct directories.
    """
    create_dir(f"{PROJECT}.build", PROJECT_PATH)
    create_dir("obj.temp", BUILD_DIR)
    create_dir("bin", BUILD_DIR)
    create_dir("lib", BUILD_DIR)

    if not (BUILD_DIR / "status.json").is_file():
        with open(BUILD_DIR / "status.json", "w") as f:
            json.dump({}, f)

    logger.debug("Created build directories.")


def modification_date(path: Path) -> float:
    """
    Returns the modification time of a file.
    :param path: The path to the file.
    :return: The modification time of the file.
    """
    return path.stat().st_mtime


def is_updated(target: str, files: List[Path], target_type: int = STATIC) -> bool:
    """
    Checks whether a target is updated. The trick is done using modification timestamps. A target that is not updated
    would have a source newer than the object file.
    :param target: The target name.
    :param files: The source files.
    :return: True if the target is updated, False otherwise.
    """
    object_files_dir = OBJ_DIR / f"{target}.build"
    object_files = [object_files_dir / f"{file.name}.o" for file in files]

    artifact_file = Path()
    check_artifact = True
    if target_type == STATIC or target_type == SHARED:
        artifact_file = LIB_DIR / make_output_name(target, target_type)
    elif target_type == EXECUTABLE:
        artifact_file = BIN_DIR / make_output_name(target, target_type)
    elif target_type == -1:
        # We are compiling an object file
        check_artifact = False

    try:
        object_modification_time = [modification_date(file) for file in object_files]
        source_modification_time = [modification_date(file) for file in files]
        artifact_modification_time = modification_date(artifact_file)
    except FileNotFoundError:
        # Object file does not exist
        return False

    newest_source = max(source_modification_time)
    oldest_object = min(object_modification_time)
    if newest_source > oldest_object:
        return False

    if check_artifact and newest_source > artifact_modification_time:
        return False
    return True


def make_output_name(target: str, lib_type: int) -> str:
    """
    Returns the output name of the target, for example, libtarget.a, libtarget.so, or target.exe. It is used to name
    the compiled file.
    :param target: The target name.
    :param lib_type: The type of the object. 0 for static, 1 for shared, 2 for executable.
    :return: The output name of the target.
    """
    if not WINDOWS:
        if lib_type == STATIC:
            return f"lib{target}.a"
        elif lib_type == SHARED:
            return f"lib{target}.so"
        elif lib_type == EXECUTABLE:
            return target
        else:
            logger.fatal(f"Invalid library type {lib_type}.")
            sys.exit(1)
    else:
        if lib_type == STATIC:
            return f"{target}.lib"
        elif lib_type == SHARED:
            return f"{target}.dll"
        elif lib_type == EXECUTABLE:
            return f"{target}.exe"
        else:
            logger.fatal(f"Invalid library type {lib_type}.")
            sys.exit(1)
