# The Steppable Project

[![Build Status](https://dev.azure.com/NWSOFT/Steppable/_apis/build/status%2FSteppable?branchName=main)](https://dev.azure.com/NWSOFT/Steppable/_build/latest?definitionId=3&branchName=main)

This project tries to make a Computer Algebra System (CAS) out of scratch, and without any external libraries.

## What is this?

This project attempts to make a CAS that solves problems like a human does. It even adds, subtracts, multiplies, and
divides using the column method. This is because we believe that a CAS should be able to solve problems step by step, so
that the user can understand how the problem is solved.

## What this is not?

This is not a CAS intended for high-performance computing. This is because the basic arithmetic operations are much more
time consuming than the plain old `+`, `-`, `*`, and `/` (around 10 times slower).

## Why another CAS?

Out of [this list](https://en.wikipedia.org/wiki/List_of_computer_algebra_systems), we could not find a CAS that is:

- Free and open source
- Solves step by step
- Runs even without internet connection

## How does it work?

We found that there is no simpler method of writing a step-by-step solver than imitating how a human solves it.
So we wrote a parser that converts the input into a tree, and then we wrote a calculator that solves the tree step by
step. Finally, the reporter shows the steps and results to the user in a human-readable format.

Currently, only the calculator and the reporter is implemented, with very limited functionality. Here is a list of what
we are planning to implement next (and in the near future):

- [ ] Parser
- [ ] Calculator and reporter (all the major functions)
  - [x] Comparison of integers and decimal
  - [x] Addition of integers and decimals
  - [x] Subtraction of integers and decimals
  - [x] Multiplication of integers and decimals
  - [ ] Division of integers and decimals
  - [ ] Addition of fractions
  - [ ] Subtraction of fractions
  - [ ] Multiplication of fractions
  - [ ] Simplification of fractions
  - [ ] Division of fractions
  - [ ] Conversion between fractions and decimals
  - [ ] Expansion of polynomials
  - [ ] Factoring of polynomials

The parser is the most difficult part of the project, so we will probably start with the calculator and reporter first.
When implemented, it will probably call the calculator(s) (which is/are compiled into executable format together with the
reporter) and then show the result to the user.

## How to get it running?

First, you will need:

- [CMake](https://cmake.org/) (version 3.8 or higher, latest version preferred) to generate the build files.
- A working C++ compiler (GCC and Clang are preferred) to generate the executable.
- A build system ([GNU Make](https://www.gnu.org/software/make/), [Ninja](https://ninja-build.org/), etc.), as long as
it gets along with CMake.
- [Git](https://git-scm.com/) (optional, but recommended) to download the project and commit changes.

Then, you can clone this repository by running the following command, or [download](https://github.com/ZCG-Coder) it
from GitHub (if you don't have Git installed):

```bash
# TODO: Publish this to GitHub
git clone ...
```

Then, you can build the project by running the following commands:

```bash
cd <path/to/this/repo>
mkdir build
cd build
cmake .. -G <your build system> # Replace <your build system> with your build system of choice. Default is Make.
```

Alternatively, you may generate a differently optimized build by replacing adding with one of the following options:

- `-DCMAKE_BUILD_TYPE=Debug` for a debug build (has debug symbols, no optimizations). This is perfect for running with a
debugger, such as [GDB](https://www.gnu.org/software/gdb/), [LLDB](https://lldb.llvm.org/), or your IDE.
- `-DCMAKE_BUILD_TYPE=Release` for a release build (no debug symbols, full optimizations). This is perfect for running
the program normally and redistributing it.
- `-DCMAKE_BUILD_TYPE=RelWithDebInfo` for a release build with debug symbols (has debug symbols, full optimizations).
- `-DCMAKE_BUILD_TYPE=MinSizeRel` for a release build with minimum size (no debug symbols, minimum executable size).

Finally, you can build the project by running the following command:

```bash
cmake --build .
```

The different calculators can be run by specifying the necessary arguments, and optionally, switches. For example:

```bash
# Add 4 and 5.677 via the column method
./add 4 5.677
# Output:
#       4              
# +     5  .  6  7  7  
#                     
# _____________________
#       9  .  6  7  7  

# Add 4 and 5.677, but do not show the steps
./add 4 5.677 -steps
# Output:
# 9.677
```

## How to contribute?

Welcome to our project! We are glad that you are interested in contributing to our project. Please make a
[pull request](https://github.com/ZCG-Coder/) in order to contribute to the project, and we will review it as soon as
possible.

The project is structured as follows:

```text
Steppable
├── CMakeLists.txt
├── README.md
├── Steppable.sublime-project
├── include
│   ├── argParse.hpp ─────────────────────────────────────────────┐
│   ├── colors.hpp <- Console colors                              │
│   └── util.hpp ─────────────────────────────────────────────────┼─┐
└── src                                                           │ │
    ├── CMakeLists.txt                                            │ │
    ├── [Calculator Name (camelCase is recommended)]              │ │
    │   ├── [Calculator Name (same as directory name)].cpp        │ │
    │   ├── [Calculator Name (same as directory name)]Report.cpp  │ │
    │   └── [Calculator Name (same as directory name)]Report.hpp  │ │
    ├── ...                                                       │ │
    ├── argParse.cpp <-───── [Function Definition] ───────────────┘ │
    └── util.cpp <-───────── [Function Definition] ─────────────────┘
```

### How to add a new feature

To add a new feature, `a`:

1. Add a directory called `src/a`, with at least three files:
    - `a.cpp` - The main file. The `main` function should be present, as it it the entry point of the executable.
    - `aReport.cpp` - The report file to show the results.
    - `aReport.hpp` - A header that contains optional definition.
    > Note: Only the above-mentioned three files will be added to CMake.
2. Make sure to document the code. Please follow [this](docs/DOCUMENTING.md) for documentation guidelines.
3. Add an entry to `src/CMakeLists.txt`

    ```cmake
    SET(COMPONENTS
        add
        ...
        a # Replace with yours
    )
    ```

4. Create a pull request.
