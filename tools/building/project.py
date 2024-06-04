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
This module contains the Project class, which is used to build the project. It is used to build executables, shared
libraries, and static libraries. The Project class is a parent class of the BuildSteppable class, which is used to build
the components of the project.
"""

import logging
import subprocess
import sys
from collections import OrderedDict
from functools import partial
from multiprocessing.dummy import Pool
from pathlib import Path
from typing import List, Tuple

from lib.constants import LINUX, MACOSX
from lib.paths import BIN_DIR, LIB_DIR, OBJ_DIR, PROJECT_PATH, SRC_DIR, TESTS_DIR
from lib.printing import blue, bold, erase_line, green, red, reset
from tools.building.compiler_detection import detect_cxx_compiler
from tools.building.constants import EXECUTABLE, SHARED, STATIC
from tools.building.directories import WINDOWS, create_dir, is_updated, make_output_name

logger = logging.getLogger(__name__)


class Project:
    """
    Manages executables, shared libraries, and static libraries. It also manages the build order of these objects.
    Typically, the build order follows your specified order, but if a static library needs to be linked by a target, the
    static library will be built first.
    """

    def __init__(self, name: str) -> None:
        """
        Initializes the Project object, and sets the name of the project.
        :param name: The name of the project.
        """

        self.name = name

        self.executables = OrderedDict()
        self.shares = OrderedDict()
        self.statics = OrderedDict()
        self.build_order = OrderedDict()

        self.compiler = detect_cxx_compiler()

        self.includes = []
        self.extra_options = {}
        self.lang_std = "c++2b"

        self.pre_build = lambda: None
        self.post_build = lambda: None

    def add_include(self, name: str) -> None:
        """
        Adds an include directory to the project. This is a project-wide option, and is applied to ALL targets.
        :param name: The name of the include directory.
        """
        self.includes.append(PROJECT_PATH / name)

    def add_extra_options(self, name: str, option: str) -> None:
        """
        Adds extra compiler and linker options to a specific target.
        :param name: The name of the target.
        :param option: The option(s) to add in the form of space-separated string.
        """
        self.extra_options[name] = option

    def add_executable(
        self, name: str, files: List[Path], with_statics: List[str] = []
    ) -> None:
        """
        Adds an executable target to the project. Executable targets are the final output of the project, and can be run
        directly from the command line.
        :param name: The name of the executable.
        :param files: A list of files that are part of the executable.
        :param with_statics: A list of static libraries that the executable depends on. They will be built first.
        """
        self.executables[name] = {"files": files, "statics": with_statics}

        for item in with_statics:
            if item not in self.statics:
                print(f"ERROR: {item} is not a valid static library.")
            self.build_order[item] = 0

        self.build_order[name] = 2

    def add_shared(
        self, name: str, files: List[Path], with_statics: List[str] = []
    ) -> None:
        """
        Adds a shared library target to the project. Shared libraries are dynamic libraries that can be linked to
        executables at runtime.
        :param name: The name of the shared library.
        :param files: A list of files that are part of the shared library.
        :param with_statics: A list of static libraries that the shared library depends on. They will be built first.
        """
        self.shares[name] = {"files": files, "statics": with_statics}

        for item in with_statics:
            if item not in self.statics:
                print(f"ERROR: {item} is not a valid static library.")
            self.build_order[item] = 0

        self.build_order[name] = 1

    def add_static(
        self, name: str, files: List[Path], with_statics: List[str] = []
    ) -> None:
        """
        Adds a static library target to the project. Static libraries are linked to executables at compile time.
        :param name: The name of the static library.
        :param files: A list of files that are part of the static library.
        :param with_statics: A list of static libraries that the static library depends on. They will be built first.
        """
        self.statics[name] = {"files": files, "statics": with_statics}

        for item in with_statics:
            if item not in self.statics:
                print(f"ERROR: {item} is not a valid static library.")
            self.build_order[item] = 0

        self.build_order[name] = 0

    @property
    def platform_definitions(self) -> str:
        """
        Gets suitable platform definitions for the project.
        :return: A string of platform definitions.
        """
        if WINDOWS:
            return "-DWINDOWS "
        if MACOSX:
            return "-DMACOSX "
        if LINUX:
            return "-DLINUX "
        return ""

    def build_objects(self) -> Tuple[List[str], List[Path]]:
        """
        Builds the object files for the project. This function will compile the source files into object files.
        :return: A tuple of commands and files.
        """
        all_file_objects = {**self.executables, **self.statics, **self.shares}
        commands = []
        all_files = []
        for item in self.build_order.keys():
            item_dir = OBJ_DIR / f"{item}.build"
            create_dir(f"{item}.build", OBJ_DIR)
            for file in all_file_objects[item]["files"]:
                if is_updated(item, [file], -1):
                    logger.debug(f"{item}: SKIPPED")
                    continue
                command = f"{self.compiler} -c -o{item_dir / file.name}.o -std={self.lang_std} {file} {self.platform_definitions}"
                for include in self.includes:
                    command += f"-I{include} "
                options = op if (op := self.extra_options.get(item)) else ""
                command += options + " "
                commands.append(command)
                all_files.append(file)

        return commands, all_files

    def link_objects(self) -> List[str]:
        """
        Links the object files into executables, shared libraries, and static libraries.
        :return: A list of commands.
        """
        commands = []
        for item in self.build_order.keys():
            command = ""
            if self.build_order[item] == STATIC:
                if is_updated(item, self.statics[item]["files"]):
                    logger.debug(f"{item}: SKIPPED")
                    continue

                output_file = LIB_DIR / make_output_name(item, STATIC)
                command += f"ar qc {output_file}"
                for file in self.statics[item]["files"]:
                    command += f" {OBJ_DIR}/{item}.build/{file.name}.o"

                command += f" && ranlib {output_file}"

            if self.build_order[item] == SHARED:
                if is_updated(item, self.shares[item]["files"]):
                    logger.debug(f"{item}: SKIPPED")
                    continue
                command += f"{self.compiler} -shared -fPIC -o {LIB_DIR / make_output_name(item, SHARED)} -L{LIB_DIR} "
                for static in self.shares[item]["statics"]:
                    command += f"-l{static} "

                for file in self.shares[item]["files"]:
                    command += f" {OBJ_DIR}/{item}.build/{file.name}.o "

            if self.build_order[item] == EXECUTABLE:
                if is_updated(item, self.executables[item]["files"]):
                    logger.debug(f"{item}: SKIPPED")
                    continue
                command += f"{self.compiler} -o {BIN_DIR / item} -L{LIB_DIR} "
                for static in self.executables[item]["statics"]:
                    command += f"-l{static} "
                for file in self.executables[item]["files"]:
                    command += f"{OBJ_DIR}/{item}.build/{file.name}.o "

            commands.append(command)

        return commands

    def build(self) -> None:
        """
        Performs the build process. This function will compile the source files into object files, and link the object
        files into executables, shared libraries, and static libraries. The build order is determined by the order in
        which the targets are added to the project.

        By default, this function will build the project in parallel. If you want to build the project sequentially, you
        can remove the Pool objects and use the subprocess.call function directly.

        Remember to call this function at the end of the build script.
        """
        total_commands = []

        objects = self.build_objects()
        compile_commands = objects[0]
        total_commands += compile_commands

        all_files = objects[1]
        link_commands = self.link_objects()
        total_commands += link_commands

        if not total_commands:
            print("Nothing to build.")
            return

        compile_pool = Pool()
        last_compile_index = 0
        for compile_index, exit_code in enumerate(
            compile_pool.imap(partial(subprocess.call, shell=True), compile_commands)
        ):
            percentage = (compile_index + 1) / len(total_commands) * 100
            print(
                (
                    f"{green()}{bold()}[{compile_index + 1}/{len(total_commands)}|{percentage:.0f}%]{reset()}"
                    f" Building {Path(all_files[compile_index]).name}.o{erase_line()}"
                )
            )
            if exit_code != 0:
                print(
                    (
                        f"{green()}{bold()}[{compile_index + 1}/{len(total_commands)}|{percentage:.0f}%]{reset()}"
                        f" {red()}Command Failed{reset()}"
                    )
                )
                sys.exit(exit_code)
            last_compile_index = compile_index

        link_pool = Pool()
        for link_index, exit_code in enumerate(
            link_pool.imap(partial(subprocess.call, shell=True), link_commands)
        ):
            percentage = (
                (link_index + last_compile_index + 2) / len(total_commands) * 100
            )
            print(
                (
                    f"{blue()}{bold()}[{link_index + last_compile_index + 2}/{len(total_commands)}|{percentage:.0f}%]"
                    f"{reset()} Linking {list(self.build_order.keys())[link_index]}{erase_line()}"
                )
            )
            if exit_code != 0:
                print(
                    (
                        f"{blue()}{bold()}[{link_index + last_compile_index + 2}/{len(total_commands)}|"
                        f"{percentage:.0f}%]{reset()}{red()} Command Failed{reset()}"
                    )
                )
                sys.exit(exit_code)


class BuildSteppable(Project):
    """
    A child class of the Project class. This class is used to build the components of the project. It is used to build
    the components of the project, such as the add, abs, subtract, etc.
    """

    def __init__(self, build_component_executables: bool = False) -> None:
        """
        Initializes the BuildSteppable object.
        :param build_component_executables: A boolean that determines whether to build the component executables.
        """

        super().__init__("Steppable")
        self.components = []
        self.calc_files = set()
        self.build_component_executables = build_component_executables
        self.add_extra_options("calc", "-DNO_MAIN")
        self.add_extra_options("base", "-DNO_MAIN")

        self.add_static(
            "util",
            [
                SRC_DIR / "argParse.cpp",
                SRC_DIR / "colors.cpp",
                SRC_DIR / "logging.cpp",
                SRC_DIR / "symbols.cpp",
                SRC_DIR / "rounding.cpp",
                SRC_DIR / "testing.cpp",
                SRC_DIR / "util.cpp",
            ],
        )
        self.add_static("calc", [], ["util"])
        self.add_static("base", [], ["util", "calc"])
        self.add_include("include")

    def add_component(self, group: str, name: str) -> None:
        """
        Adds a component to the project. Components are the building blocks of the project, and are linked together to
        build the final executables.
        """

        files = [
            SRC_DIR / name / f"{name}.cpp",
            SRC_DIR / name / f"{name}Report.cpp",
        ]
        if self.build_component_executables:
            self.add_executable(name, files, ["calc", "util"])

        # Add the test executable
        test_name = f"test{name[0].upper()}{name[1:]}"
        self.add_executable(
            test_name,
            [*files, TESTS_DIR / f"{test_name}.cpp"],
            ["base", "util", "calc"],
        )
        self.add_extra_options(test_name, "-DNO_MAIN")

        self.calc_files.update(files)
        self.add_static(group, list(self.calc_files), ["util"])
