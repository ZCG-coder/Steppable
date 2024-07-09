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
Translates all strings in a stp_strings file.

Process:
              |-> Yes ----------------+
              |                       |
+----------+  |-Index file exists?    |
| Read all |  |      +-------------+  |     +--------------------------+
| strings  | -+-> No | Write index |--+---> | Write translated strings |
| in file  |         | file        |        | to a new file            |
+----------+         +-------------+        +--------------------------+
"""
from pathlib import Path
import re
import sys
import uuid

from lib.getch import getch
from lib.printing import erase_line, print_error

ISO_639_REGEX = re.compile(r"^[a-z]{2}(-[A-Z]{2})?$")
LOCALIZED_HEADER = """\
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

# NOTE: This file is generated. Do not edit it manually. Any changes will be overwritten.
# STR_GUID: (key) / STRING {TYPE}: (string)
# eg: a491b7b2-1239-4acb-9045-0747d806b96f >> "Hello World!"
# Recommended syntax highlighting: Bash Script
"""


def ask_translation(string: str) -> str:
    """
    Asks the user to translate a string.
    """
    print(f'String      : "{string}"')
    translation = input("Translation : ")
    print(erase_line(2))

    return translation


def verify_language(language: str) -> None:
    """
    Verifies that the language code is a valid ISO 639-1 code. Eg. "en" or "en-US".
    Exits the program if the language code is invalid.
    """
    if not ISO_639_REGEX.match(language):
        print(f"ERROR: Invalid language code: {language}")
        exit(1)


def write_indexed_file(component: str, *, append: bool = False) -> None:
    """
    Writes the indexed entries to a file with the given path.
    Indexed entries are the strings with a GUID assigned to them.

    :param component: The name of the component to write the indexed file for.
    :param append: If True, appends the strings to the file. If False, overwrites the file.
    """
    path = Path(f"res/translations/{component}.stp_strings")
    mode = "a" if append else "w"

    print(f"Enter the strings in {component}, blank line to quit.")
    string = input("> ")
    guid = str(uuid.uuid4())
    strings = [f"{guid} >> {string}"]
    while string != "":
        string = input("> ")
        guid = str(uuid.uuid4())
        strings.append(f'{guid} >> "{string}"')

    strings.pop(-1)
    for idx, string in enumerate(strings):
        if string.endswith(" >> "):
            strings.pop(idx)

    with path.open(mode) as f:
        content = "\n".join(strings)
        if not append:
            content = LOCALIZED_HEADER.format(TYPE="ORIGINAL") + content
        else:
            content = "\n" + content
        f.write(content)


def add_translations(file: Path, language: str) -> None:
    verify_language(language)  # Check if the language code is valid
    print("INFO: Thank you for helping us translate the project!")
    print(f"INFO: TRANSLATING {file} TO {language}")

    if not file.is_file():
        write_indexed_file(file.stem, append=False)

    entries = []

    with file.open("r") as f:
        lines = f.readlines()
    for line in lines:
        line = line.strip()
        if not line:
            # Skip empty lines
            continue

        # Step 2: Check for invalid characters: \ " '
        if line.startswith("#"):
            continue  # Skip comments
        line_parts = line.split(" >> ")  # Split the UUID and the string

        # Step 1: Get the GUID and the string
        guid, line = line_parts
        line = line.replace('"', "")  # Remove quotes

        if (pos := line.find("\\")) != -1:
            print_error(line, pos, "Invalid character: \\")
            exit(1)
        if (pos := line.find('"')) != -1:
            print_error(line, pos, 'Invalid character: "')
            exit(1)
        if (pos := line.find("'")) != -1:
            print_error(line, pos, "Invalid character: '")
            exit(1)

        if not line:
            print_error(line, 0, "Empty string")
            exit(1)

        # Step 3: Ask for translations
        if language.startswith("en"):
            # Since strings in Steppable are in English, we don't need to translate them.
            translation = line
        else:
            translation = ask_translation(line)
        # Step 4: Make the translation entry
        entry = f'{guid} >> "{translation}"'
        entries.append(entry)

    # Step 5: Write the translations to a new file
    if not (lang_path := Path(f"res/translations/{language}")).is_dir():
        lang_path.mkdir(parents=True)
    output_file = Path(f"res/translations/{language}/{component}.stp_localized")
    with output_file.open("w") as f:
        f.write(LOCALIZED_HEADER.format(TYPE="TRANSLATED") + "\n".join(entries))
    print(f"INFO: Translations written to {output_file}. Done.")


if __name__ == "__main__":
    args = sys.argv
    if len(args) == 1:
        print("USAGE: python -m tools.translation <COMMAND> <args>")
        exit(1)

    if args[1] == "add_tr":
        component = args[2]
        language = args[3]
        file = Path(f"res/translations/{component}.stp_strings")
        add_translations(file, language)
    elif args[1] == "wr_idx":
        component = args[2]
        print("Do you want to append to the file? (Y/n) ", end="", flush=True)
        char = getch()
        print()
        append = char.lower() == "y" or char.strip() == ""
        write_indexed_file(component, append=append)
