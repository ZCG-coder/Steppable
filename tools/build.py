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
This script is used to build the project in case CMake is not available. No dependencies are required.
"""

import logging

from lib.paths import BUILD_DIR
from tools.building.directories import create_build_dirs
from tools.building.project import BuildSteppable

logger = logging.getLogger(__name__)


def build() -> None:
    """
    This function builds the project. You can add components to the project by calling the add_component method, but do
    not forget to call the build method at the end of the function.

    Do not call this function directly. Instead, run the this script from the root directory of the project.
    """
    a = BuildSteppable(build_component_executables=False)
    a.add_component("calc", "add")
    a.add_component("calc", "abs")
    a.add_component("calc", "subtract")
    a.add_component("calc", "multiply")
    a.add_component("calc", "comparison")
    a.add_component("calc", "division")
    a.add_component("calc", "power")

    a.add_component("base", "decimalConvert")
    a.add_component("base", "baseConvert")
    a.build()


if __name__ == "__main__":
    create_build_dirs()
    logging.basicConfig(
        filename=BUILD_DIR / "status.log",
        filemode="w",
        level=logging.INFO,
        format="%(asctime)s - %(module)s->%(funcName)s[%(levelname)s] %(message)s",
    )

    build()
