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
Benchmarking script for Steppable executables.
"""

import argparse
import random
import subprocess
import time
from pathlib import Path
from typing import Callable, List, Tuple

from lib.paths import PROJECT_PATH

BUILD_PATH_DEFAULT = "build"

FUNCTIONS = {
    "abs": lambda x, _: abs(x),
    "add": lambda x, y: x + y,
    "comparison": lambda x, y: x > y,
    "division": lambda x, y: x / y,
    "multiply": lambda x, y: x * y,
    "subtract": lambda x, y: x - y,
    "root": lambda x, y: x ** (1 / y),
    "power": lambda x, y: x**y,
}


def _benchmark_function(
    function: Callable,
    input_1: int,
    input_2: int,
) -> float:
    """
    Benchmark a Python function.
    :param function: The function to benchmark.
    :param input_1: The first input.
    :param input_2: The second input.
    :return: The time taken to run the function.
    """

    start = time.time()
    try:
        function(input_1, input_2)
    except Exception as e:
        print(f"Error: {e}")
    end = time.time()
    return end - start


def _benchmark(
    cmd: str,
    input_str1: str,
    input_str2: str,
    *,
    verbose: bool = False,
    timeout: int = 10,
) -> float:
    """
    Benchmark a system executable.
    :param cmd: The executable to run.
    :param input_str1: The first input.
    :param input_str2: The second input.
    :param verbose: Whether to print the output.
    :param timeout: The timeout for the process.
    :return: The time taken to run the executable.
    """

    start = time.time()
    try:
        result = subprocess.run(
            [cmd, input_str1, input_str2],
            text=True,
            check=True,
            stderr=subprocess.PIPE,
            stdout=subprocess.PIPE,
            timeout=timeout,
        )
        if verbose:
            print(
                f"Finished with {result.returncode}\n{result.stdout}\n{result.stderr}"
            )
    except subprocess.CalledProcessError as e:
        print(
            f"Error: Non-zero exit code while running {cmd} on {input_str1}, {input_str2}: {e.output}"
        )
    except subprocess.TimeoutExpired:
        print(f"Warning: Timeout running {cmd} on {input_str1}, {input_str2}")
    end = time.time()
    return end - start


def benchmark(
    cmd: str, inputs: List[str], limit: int, verbose: bool = False, timeout: int = 10
) -> Tuple[List[float], List[float], bool]:
    """
    Benchmark a Steppable executable.
    :param cmd: The executable to run.
    :param inputs: The inputs to run the executable on.
    :param limit: The limit for the inputs.
    :param verbose: Whether to print the output.
    :param timeout: The timeout for the process.
    :return: The time taken to run the executable.
    """

    random_number = random.randint(0, limit)
    random_number_str = str(random_number)
    time_needed = []
    time_needed_system = []
    system_available = False
    for input_str in inputs:
        time_needed.append(
            _benchmark(
                cmd, input_str, random_number_str, verbose=verbose, timeout=timeout
            )
        )
        if (func := Path(cmd).stem) in FUNCTIONS:
            time_needed_system.append(
                _benchmark_function(FUNCTIONS[func], int(input_str), random_number)
            )
            system_available = True
        else:
            time_needed_system.append(0)

    return time_needed, time_needed_system, system_available


def main() -> None:
    """
    Main function for the benchmarking script.
    """

    parser = argparse.ArgumentParser(
        prog="benchmark.py",
        description="Performs benchmarks on Steppable executables",
        epilog="Copyright 2023-2024 NWSOFT, licensed under the MIT License.",
    )
    parser.add_argument(
        "-p", "--build_dir", type=str, default=BUILD_PATH_DEFAULT, required=False
    )
    parser.add_argument(
        "-e", "--executables", type=str, default="bin/*", required=False
    )
    parser.add_argument("-t", "--timeout", type=int, default=50, required=False)
    parser.add_argument("-l", "--limit", type=float, default=100, required=False)
    parser.add_argument("-v", "--verbose", action="store_true", required=False)
    parser.add_argument("-g", "--graph", action="store_true", required=False)
    args = parser.parse_args()

    LIMIT = int(args.limit)

    build_dir = Path(PROJECT_PATH / args.build_dir).resolve()
    if not build_dir.exists():
        print(f"Build directory {build_dir} does not exist.")
        return

    if args.executables:
        executables = sorted(list(build_dir.glob(args.executables)))
        if not executables:
            print(f"No executables found in {build_dir}")
            return
    else:
        executables = [
            build_dir / "bin" / "abs",
            build_dir / "bin" / "add",
            build_dir / "bin" / "comparison",
            build_dir / "bin" / "division",
            build_dir / "bin" / "multiply",
            build_dir / "bin" / "subtract",
        ]

    print(
        f"Started benchmarking on {' '.join([executable.stem for executable in executables])}"
    )

    for exe in executables:
        print(f"Running benchmarks on {exe}")
        inputs_system = [i for i in range(LIMIT)]
        inputs = [str(i) for i in inputs_system]
        time_result = benchmark(
            str(exe), inputs, LIMIT, verbose=args.verbose, timeout=args.timeout
        )
        times = time_result[0]
        times_system = time_result[1]
        if (not args.graph) and args.verbose:
            print(f"Times: {times}")
        if args.graph:
            img_path = PROJECT_PATH / "tools" / "figures" / f"benchmark_{exe.stem}.svg"
            print(f"Saving as {img_path}")

            import matplotlib.pyplot as plt

            plt.figure(figsize=(15, 5))
            plt.plot(range(LIMIT), times, label="Steppable")
            if time_result[2]:
                plt.plot(range(LIMIT), times_system, label="System")

            plt.legend()
            plt.xlabel("Input")
            plt.ylabel("Time (s)")
            plt.title(f"Benchmark for {exe.stem}")
            plt.savefig(img_path, format="svg")


if __name__ == "__main__":
    main()
