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

import subprocess
from typing import List


def get_commits() -> List[str]:
    """
    Get the commits between the main and develop branches.
    :return: A list of commits.
    """

    # git log main..develop --pretty="%B" --reverse
    try:
        output = subprocess.check_output(
            ["git", "log", "main..develop", "--pretty=%B#", "--reverse"],
            universal_newlines=True,
        )
    except subprocess.CalledProcessError as e:
        print(f"ERROR: {e}")
        return []
    except FileNotFoundError:
        print(f"ERROR: Git not found on the system.")
        return []

    # Do some processing, ie. split the output into a list of commits
    lines = output.split("\n#")
    commits = [line.strip() for line in lines if line.strip()]

    return commits


def process_changelog() -> None:
    """
    Generate a changelog from the commits between the main and develop branches.
    """

    print("INFO: Generating changelog")
    commits = get_commits()

    for commit in commits:
        lines = commit.split("\n")
        print(f"- **{lines[0]}**")
        lines.pop(0)

        for line in lines:
            print(f"  {line}")


if __name__ == "__main__":
    process_changelog()
