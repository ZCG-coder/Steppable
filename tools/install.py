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
Installs the Steppable settings and resources to the user home.
"""

from lib.paths import DEFAULT_CONFIG_DIR, CONFIG_DIR
import shutil


def copy_resources() -> None:
    """
    Copy the resources to the user home.
    """
    # Copy the resources
    if CONFIG_DIR.is_dir():
        # Only copy the files
        for file in DEFAULT_CONFIG_DIR.iterdir():
            if file.is_file():
                print(f"Copying FILE {file.name}")
                shutil.copy(file, CONFIG_DIR)
            else:
                print(f"Copying DIRECTORY {file.name}")
                shutil.copytree(file, CONFIG_DIR / file.name, dirs_exist_ok=True)
        return
    shutil.copytree(DEFAULT_CONFIG_DIR, CONFIG_DIR)


def install() -> None:
    """
    Install the Steppable settings and resources.
    """

    copy_resources()


if __name__ == "__main__":
    install()
