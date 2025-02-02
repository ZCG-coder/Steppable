#####################################################################################################
#  Copyright (c) 2023-2025 NWSOFT                                                                   #
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

# LICENSE NOTE:
# Modified from LLVM run-clang-tidy.py, originally under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception


"""
Parallel clang-tidy runner
==========================

Runs clang-tidy over all files in a compilation database. Requires clang-tidy
and clang-apply-replacements in $PATH.

Example invocations.
- Run clang-tidy on all files in the current working directory with a default
  set of checks and show warnings in the cpp files and all project headers.
    run-clang-tidy.py $PWD

- Fix all header guards.
    run-clang-tidy.py -fix -checks=-*,llvm-header-guard

- Fix all header guards included from clang-tidy and header guards
  for clang-tidy headers.
    run-clang-tidy.py -fix -checks=-*,llvm-header-guard extra/clang-tidy \
                      -header-filter=extra/clang-tidy

Compilation database setup:
http://clang.llvm.org/docs/HowToSetupToolingForLLVM.html
"""

import argparse
import glob
import json
import multiprocessing
import os
import queue
import re
import shutil
import subprocess
import sys
import tempfile
import threading
import traceback
from typing import List, Union

import yaml  # pyright: ignore


def strtobool(val: str) -> bool:
    """
    Convert a string representation of truth to a bool following LLVM's CLI argument parsing.
    :param val: The string to convert.
    :return: The bool value.
    :raises argparse.ArgumentTypeError: If the string is not a valid boolean.
    """

    val = val.lower()
    if val in ["", "true", "1"]:
        return True
    elif val in ["false", "0"]:
        return False

    # Return ArgumentTypeError so that argparse does not substitute its own error message
    raise argparse.ArgumentTypeError(
        "'{}' is invalid value for boolean argument! Try 0 or 1.".format(val)
    )


def find_compilation_database(path: str) -> str:
    """
    Adjusts the directory until a compilation database is found.
    :param path: The path close to the compilation database.
    :return: The absolute path to the compilation database.
    """
    result = os.path.realpath("./")
    while not os.path.isfile(os.path.join(result, path)):
        parent = os.path.dirname(result)
        if result == parent:
            print("Error: could not find compilation database.")
            sys.exit(1)
        result = parent
    return result


def make_absolute(f: str, directory: str) -> str:
    """
    Return an absolute path if f is not already an absolute path.
    :param f: The file path.
    :param directory: The directory path.
    :return: The absolute path.
    """
    if os.path.isabs(f):
        return f
    return os.path.normpath(os.path.join(directory, f))


def get_tidy_invocation(
    f: str,
    clang_tidy_binary: str,
    checks: str,
    tmpdir: Union[str, None],
    build_path: str,
    header_filter: str,
    allow_enabling_alpha_checkers: str,
    extra_arg: str,
    extra_arg_before: str,
    quiet: str,
    config_file_path: str,
    config: str,
    line_filter: str,
    use_color: str,
    plugins: str,
    warnings_as_errors: str,
) -> List[str]:
    """
    Gets a command line for clang-tidy.
    :param f: The file path.
    :param clang_tidy_binary: The clang-tidy binary path.
    :param checks: The checks to run.
    :param tmpdir: The temporary directory.
    :param build_path: The build path.
    :param header_filter: The header filter.
    :param allow_enabling_alpha_checkers: Whether to allow enabling alpha checkers.
    :param extra_arg: The extra arguments.
    :param extra_arg_before: The extra arguments before.
    :param quiet: Whether to run clang-tidy in quiet mode.
    :param config_file_path: The config file path.
    :param config: The config.
    :param line_filter: The line filter.
    :param use_color: Whether to use colors in diagnostics.
    :param plugins: The plugins to load.
    :param warnings_as_errors: Whether to upgrade warnings to errors.

    :return: The full command line.
    """

    start = [clang_tidy_binary]
    if allow_enabling_alpha_checkers:
        start.append("-allow-enabling-analyzer-alpha-checkers")
    if header_filter is not None:
        start.append("-header-filter=" + header_filter)
    if line_filter is not None:
        start.append("-line-filter=" + line_filter)
    if use_color is not None:
        if use_color:
            start.append("--use-color")
        else:
            start.append("--use-color=false")
    if checks:
        start.append("-checks=" + checks)
    if tmpdir is not None:
        start.append("-export-fixes")
        # Get a temporary file. We immediately close the handle so clang-tidy can
        # overwrite it.
        (handle, name) = tempfile.mkstemp(suffix=".yaml", dir=tmpdir)
        os.close(handle)
        start.append(name)
    for arg in extra_arg:
        start.append("-extra-arg=%s" % arg)
    for arg in extra_arg_before:
        start.append("-extra-arg-before=%s" % arg)
    start.append("-p=" + build_path)
    if quiet:
        start.append("-quiet")
    if config_file_path:
        start.append("--config-file=" + config_file_path)
    elif config:
        start.append("-config=" + config)
    for plugin in plugins:
        start.append("-load=" + plugin)
    if warnings_as_errors:
        start.append("--warnings-as-errors=" + warnings_as_errors)
    start.append(f)
    return start


def merge_replacement_files(tmpdir: str, mergefile: str) -> None:
    """
    Merge all replacement files in a directory into a single file
    with the same format.
    :param tmpdir: The temporary directory.
    :param mergefile: The file to merge into.
    """
    # The fixes suggested by clang-tidy >= 4.0.0 are given under
    # the top level key 'Diagnostics' in the output yaml files
    mergekey = "Diagnostics"
    merged = []
    for replacefile in glob.iglob(os.path.join(tmpdir, "*.yaml")):
        content = yaml.safe_load(open(replacefile, "r"))
        if not content:
            continue  # Skip empty files.
        merged.extend(content.get(mergekey, []))

    if merged:
        # MainSourceFile: The key is required by the definition inside
        # include/clang/Tooling/ReplacementsYaml.h, but the value
        # is actually never used inside clang-apply-replacements,
        # so we set it to '' here.
        output = {"MainSourceFile": "", mergekey: merged}
        with open(mergefile, "w") as out:
            yaml.safe_dump(output, out)
    else:
        # Empty the file:
        open(mergefile, "w").close()


def find_binary(arg: str, name: str, build_path: str) -> str:
    """
    Get the path for a binary or exit
    :param arg: The binary path.
    :param name: The binary name.
    :param build_path: The build path.
    :return: The binary path.
    :raises SystemExit: If the binary is not found.
    """
    if arg:
        if shutil.which(arg):
            return arg
        else:
            raise SystemExit(
                "error: passed binary '{}' was not found or is not executable".format(
                    arg
                )
            )

    built_path = os.path.join(build_path, "bin", name)
    binary = shutil.which(name) or shutil.which(built_path)
    if binary:
        return binary
    else:
        raise SystemExit(
            "error: failed to find {} in $PATH or at {}".format(name, built_path)
        )


def apply_fixes(
    args: argparse.Namespace, clang_apply_replacements_binary: str, tmpdir: str
) -> None:
    """
    Calls clang-apply-fixes on a given directory.
    :param args: The command line arguments.
    :param clang_apply_replacements_binary: The clang-apply-replacements binary path.
    :param tmpdir: The temporary directory.
    """
    invocation = [clang_apply_replacements_binary]
    invocation.append("-ignore-insert-conflict")
    if args.format:
        invocation.append("-format")
    if args.style:
        invocation.append("-style=" + args.style)
    invocation.append(tmpdir)
    subprocess.call(invocation)


def run_tidy(
    args: argparse.Namespace,
    clang_tidy_binary: str,
    tmpdir: str,
    build_path: str,
    queue: queue.Queue,
    lock: threading.Lock,
    failed_files: List[str],
) -> None:
    """
    Takes filenames out of queue and runs clang-tidy on them.
    :param args: The command line arguments.
    :param clang_tidy_binary: The clang-tidy binary path.
    :param tmpdir: The temporary directory.
    :param build_path: The build path.
    :param queue: The queue of files to process.
    :param lock: The threading lock.
    :param failed_files: The list of failed files.
    """
    while True:
        name = queue.get()
        invocation = get_tidy_invocation(
            name,
            clang_tidy_binary,
            args.checks,
            tmpdir,
            build_path,
            args.header_filter,
            args.allow_enabling_alpha_checkers,
            args.extra_arg,
            args.extra_arg_before,
            args.quiet,
            args.config_file,
            args.config,
            args.line_filter,
            args.use_color,
            args.plugins,
            args.warnings_as_errors,
        )

        proc = subprocess.Popen(
            invocation, stdout=subprocess.PIPE, stderr=subprocess.PIPE
        )
        output, err = proc.communicate()
        if proc.returncode != 0:
            if proc.returncode < 0:
                msg = "%s: terminated by signal %d\n" % (name, -proc.returncode)
                err += msg.encode("utf-8")
            failed_files.append(name)
        with lock:
            sys.stdout.write(output.decode("utf-8"))
            if len(err) > 0:
                sys.stdout.flush()
                sys.stderr.write(err.decode("utf-8"))
        queue.task_done()


def main() -> None:
    """
    The main function.
    """
    parser = argparse.ArgumentParser(
        description=(
            "Runs clang-tidy over all files in a compilation database. Requires clang-tidy and clang-apply-replacements"
            " in $PATH or in your build directory."
        )
    )
    parser.add_argument(
        "-allow-enabling-alpha-checkers",
        action="store_true",
        help="allow alpha checkers from clang-analyzer.",
    )
    parser.add_argument(
        "-clang-tidy-binary", metavar="PATH", help="path to clang-tidy binary"
    )
    parser.add_argument(
        "-clang-apply-replacements-binary",
        metavar="PATH",
        help="path to clang-apply-replacements binary",
    )
    parser.add_argument(
        "-checks",
        default=None,
        help="checks filter, when not specified, use clang-tidy default",
    )
    config_group = parser.add_mutually_exclusive_group()
    config_group.add_argument(
        "-config",
        default=None,
        help=(
            "Specifies a configuration in YAML/JSON format: "
            "  -config=\"{Checks: '*', "
            '                       CheckOptions: {x: y}}" '
            "When the value is empty, clang-tidy will "
            "attempt to find a file named .clang-tidy for "
            "each source file in its parent directories."
        ),
    )
    config_group.add_argument(
        "-config-file",
        default=None,
        help=(
            "Specify the path of .clang-tidy or custom config "
            "file: e.g. -config-file=/some/path/myTidyConfigFile. "
            "This option internally works exactly the same way as "
            "-config option after reading specified config file. "
            "Use either -config-file or -config, not both."
        ),
    )
    parser.add_argument(
        "-header-filter",
        default=None,
        help=(
            "regular expression matching the names of the "
            "headers to output diagnostics from. Diagnostics from "
            "the main file of each translation unit are always "
            "displayed."
        ),
    )
    parser.add_argument(
        "-source-filter",
        default=None,
        help=(
            "Regular expression matching the names of the source files that will be excluded from compilation database "
            "to output diagnostics from."
        ),
    )
    parser.add_argument(
        "-line-filter",
        default=None,
        help="List of files with line ranges to filter the warnings.",
    )
    if yaml:
        parser.add_argument(
            "-export-fixes",
            metavar="file_or_directory",
            dest="export_fixes",
            help=(
                "A directory or a yaml file to store suggested fixes in, "
                "which can be applied with clang-apply-replacements. If the "
                "parameter is a directory, the fixes of each compilation unit are "
                "stored in individual yaml files in the directory."
            ),
        )
    else:
        parser.add_argument(
            "-export-fixes",
            metavar="directory",
            dest="export_fixes",
            help=(
                "A directory to store suggested fixes in, which can be applied "
                "with clang-apply-replacements. The fixes of each compilation unit are "
                "stored in individual yaml files in the directory."
            ),
        )
    parser.add_argument(
        "-j",
        type=int,
        default=0,
        help="number of tidy instances to be run in parallel.",
    )
    parser.add_argument(
        "files", nargs="*", default=[".*"], help="files to be processed (regex on path)"
    )
    parser.add_argument("-fix", action="store_true", help="apply fix-its")
    parser.add_argument(
        "-format", action="store_true", help="Reformat code after applying fixes"
    )
    parser.add_argument(
        "-style",
        default="file",
        help="The style of reformat code after applying fixes",
    )
    parser.add_argument(
        "-use-color",
        type=strtobool,
        nargs="?",
        const=True,
        help=(
            "Use colors in diagnostics, overriding clang-tidy's"
            " default behavior. This option overrides the 'UseColor"
            "' option in .clang-tidy file, if any."
        ),
    )
    parser.add_argument(
        "-p", dest="build_path", help="Path used to read a compile command database."
    )
    parser.add_argument(
        "-extra-arg",
        dest="extra_arg",
        action="append",
        default=[],
        help="Additional argument to append to the compiler command line.",
    )
    parser.add_argument(
        "-extra-arg-before",
        dest="extra_arg_before",
        action="append",
        default=[],
        help="Additional argument to prepend to the compiler command line.",
    )
    parser.add_argument(
        "-quiet", action="store_true", help="Run clang-tidy in quiet mode"
    )
    parser.add_argument(
        "-load",
        dest="plugins",
        action="append",
        default=[],
        help="Load the specified plugin in clang-tidy.",
    )
    parser.add_argument(
        "-warnings-as-errors",
        default=None,
        help="Upgrades warnings to errors. Same format as '-checks'",
    )
    args = parser.parse_args()

    db_path = "compile_commands.json"

    if args.build_path is not None:
        build_path = args.build_path
    else:
        # Find our database
        build_path = find_compilation_database(db_path)

    clang_tidy_binary = find_binary(args.clang_tidy_binary, "clang-tidy", build_path)

    if args.fix:
        clang_apply_replacements_binary = find_binary(
            args.clang_apply_replacements_binary, "clang-apply-replacements", build_path
        )

    combine_fixes = False
    export_fixes_dir = ""
    delete_fixes_dir = False
    if args.export_fixes is not None:
        # if a directory is given, create it if it does not exist
        if args.export_fixes.endswith(os.path.sep) and not os.path.isdir(
            args.export_fixes
        ):
            os.makedirs(args.export_fixes)

        if not os.path.isdir(args.export_fixes):
            if not yaml:
                raise RuntimeError(
                    "Cannot combine fixes in one yaml file. Either install PyYAML or specify an output directory."
                )

            combine_fixes = True

        if os.path.isdir(args.export_fixes):
            export_fixes_dir = args.export_fixes

    if export_fixes_dir is None and (args.fix or combine_fixes):
        export_fixes_dir = tempfile.mkdtemp()
        delete_fixes_dir = True

    try:
        invocation = get_tidy_invocation(
            "",
            clang_tidy_binary,
            args.checks,
            None,
            build_path,
            args.header_filter,
            args.allow_enabling_alpha_checkers,
            args.extra_arg,
            args.extra_arg_before,
            args.quiet,
            args.config_file,
            args.config,
            args.line_filter,
            args.use_color,
            args.plugins,
            args.warnings_as_errors,
        )
        invocation.append("-list-checks")
        invocation.append("-header-filter=.*")
        invocation.append("-")
        if args.quiet:
            # Even with -quiet we still want to check if we can call clang-tidy.
            with open(os.devnull, "w") as dev_null:
                subprocess.check_call(invocation, stdout=dev_null)
        else:
            subprocess.check_call(invocation)
    except:
        print("Unable to run clang-tidy.", file=sys.stderr)
        sys.exit(1)

    # Load the database and extract all files.
    database = json.load(open(os.path.join(build_path, db_path)))
    files = set(
        [make_absolute(entry["file"], entry["directory"]) for entry in database]
    )

    # Filter out source files from compilation database.
    if args.source_filter:
        try:
            source_filter_re = re.compile(args.source_filter)
        except:
            print(
                "Error: unable to compile regex from arg -source-filter:",
                file=sys.stderr,
            )
            traceback.print_exc()
            sys.exit(1)
        files = {f for f in files if not source_filter_re.match(f)}

    max_task = args.j
    if max_task == 0:
        max_task = multiprocessing.cpu_count()

    # Build up a big regexy filter from all command line arguments.
    file_name_re = re.compile("|".join(args.files))

    return_code = 0
    try:
        # Spin up a bunch of tidy-launching threads.
        task_queue = queue.Queue(max_task)
        # List of files with a non-zero return code.
        failed_files = []
        lock = threading.Lock()
        for _ in range(max_task):
            t = threading.Thread(
                target=run_tidy,
                args=(
                    args,
                    clang_tidy_binary,
                    export_fixes_dir,
                    build_path,
                    task_queue,
                    lock,
                    failed_files,
                ),
            )
            t.daemon = True
            t.start()

        # Fill the queue with files.
        for name in files:
            if file_name_re.search(name):
                task_queue.put(name)

        # Wait for all threads to be done.
        task_queue.join()
        if len(failed_files):
            return_code = 1

    except KeyboardInterrupt:
        # This is a sad hack. Unfortunately subprocess goes
        # bonkers with ctrl-c and we start forking merrily.
        print("\nCtrl-C detected, goodbye.")
        if delete_fixes_dir:
            shutil.rmtree(export_fixes_dir)
        os.kill(0, 9)

    if combine_fixes:
        print("Writing fixes to " + args.export_fixes + " ...")
        try:
            merge_replacement_files(export_fixes_dir, args.export_fixes)
        except:
            print("Error exporting fixes.\n", file=sys.stderr)
            traceback.print_exc()
            return_code = 1

    if args.fix:
        print("Applying fixes ...")
        try:
            apply_fixes(args, clang_apply_replacements_binary, export_fixes_dir)  # type: ignore
        except:
            print("Error applying fixes.\n", file=sys.stderr)
            traceback.print_exc()
            return_code = 1

    if delete_fixes_dir:
        shutil.rmtree(export_fixes_dir)
    sys.exit(return_code)


if __name__ == "__main__":
    main()
