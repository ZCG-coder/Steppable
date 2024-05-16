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

from pathlib import Path
import time
from typing import List
import random
import subprocess
import argparse

ROOT_PATH = Path(__file__).parent.parent
BUILD_PATH_DEFAULT = "build"


def _benchmark(
    cmd: str,
    input_str1: str,
    input_str2: str,
    *,
    verbose: bool = False,
    timeout: int = 10,
) -> float:
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
) -> List[float]:
    random_number = str(random.randint(0, limit))
    time_needed = []
    for input_str in inputs:
        time_needed.append(
            _benchmark(cmd, input_str, random_number, verbose=verbose, timeout=timeout)
        )

    return time_needed


def main():
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
    parser.add_argument("-l", "--limit", type=float, default=1e5, required=False)
    parser.add_argument("-v", "--verbose", action="store_true", required=False)
    parser.add_argument("-g", "--graph", action="store_true", required=False)
    args = parser.parse_args()

    LIMIT = int(args.limit)

    build_dir = Path(ROOT_PATH / args.build_dir).resolve()
    if not build_dir.exists():
        print(f"Build directory {build_dir} does not exist.")
        return

    executables = sorted(list(build_dir.glob(args.executables)))
    if not executables:
        print(f"No executables found in {build_dir}")
        return

    for exe in executables:
        print(f"Running benchmarks on {exe}")
        inputs = [str(i) for i in range(LIMIT)]
        times = benchmark(
            str(exe), inputs, LIMIT, verbose=args.verbose, timeout=args.timeout
        )
        if (not args.graph) and args.verbose:
            print(f"Times: {times}")
        if args.graph:
            img_path = ROOT_PATH / "tools" / "figures" / f"benchmark_{exe.stem}.svg"
            print(f"Saving as {img_path}")

            import matplotlib.pyplot as plt

            plt.figure(figsize=(15, 5))
            plt.plot(range(LIMIT), times)
            plt.xlabel("Input")
            plt.ylabel("Time (s)")
            plt.title(f"Benchmark for {exe.stem}")
            plt.savefig(img_path, format="svg")


if __name__ == "__main__":
    main()
