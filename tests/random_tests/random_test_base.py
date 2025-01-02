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

import random
import subprocess
import time

from lib.printing import bold, green, red, reset


class RandomTest:
    """
    Gives a program a series of numbers, and test it against the numbers to see if it works.
    """

    def __init__(
        self,
        executable="",
        times: int = 100,
        expression: str = "{} / {}",
        rounding: bool = True,
    ):
        self.times = times
        if executable == "":
            raise RuntimeError("Executable cannot be empty")
        self.executable = executable
        self.failed = []
        self.expression = expression
        self.rounding = rounding

    def random_test(self):
        """Gives the executable a series of random numbers and tests them."""
        random.seed(time.time())
        top_limit = random.randint(100, int(1e100))

        for i in range(self.times):
            number1 = random.randint(1000, top_limit) / random.randint(1000, top_limit)
            number2 = random.randint(1000, top_limit) / random.randint(1000, top_limit)

            output = None
            if self.rounding:
                output = subprocess.check_output(
                    [
                        self.executable,
                        f"{number1:.20f}",
                        f"{number2:.20f}",
                        "-steps:0",
                        "-decimals:2",
                    ]
                )
            else:
                output = subprocess.check_output(
                    [self.executable, f"{number1:.20f}", f"{number2:.20f}", "-steps:0"]
                )

            output = float(output.decode("utf-8")[:-1])

            expression = self.expression.format(number1, number2)
            if self.rounding:
                python_output = round(eval(expression), 2)
            else:
                python_output = eval(expression)
            print(
                f"\033[K\033[A\rTest [{i + 1}/{self.times}|{(i + 1) / self.times * 100:2.1f}%] - ",
                end="",
            )

            diff = abs(python_output - output)
            try:
                quotient = python_output // output
            except ZeroDivisionError:
                quotient = 1  # Ignorable
            # Rounding errors, ignorable
            if diff > 1e-2 and self.rounding:
                self.failed.append((number1, number2, output, python_output))
                print(red() + f"INCORRECT RESULT for {expression}" + reset())
            elif abs(1 - quotient) > 1:
                self.failed.append((number1, number2, output, python_output))
                print(red() + f"PROBLEMATIC SCALE for {expression}" + reset())
            else:
                print(green() + f"PASSED" + reset())

        self.summary()

    def summary(self):
        print(bold() + "==== SUMMARY OF ALL TESTS ====" + reset())
        if len(self.failed) > 0:
            print(
                red()
                + bold()
                + f"Failed {len(self.failed)}/{self.times} tests"
                + reset()
            )
            for idx, (number1, number2, output, python_output) in enumerate(
                self.failed
            ):
                print(f"TEST {idx + 1}")
                print(f"  {self.expression.format(number1, number2)}")
                print(f"  - Python gives {python_output}")
                print(f"  - Steppable gives {output}")
            exit(1)
        print(green() + bold() + "ALL TESTS PASSED." + reset())
