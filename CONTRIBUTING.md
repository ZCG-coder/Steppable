# Contributing to Steppable

## Introduction

As Steppable is still a project with only basic features, we need more contributors to expand its features quickly.

## Ways to contribute

There are currently four ways to contribute to this repository, including:

- Adding new features and fixing bugs
- Adding documentation or usage examples
- Posting issues about bugs
- Suggesting improvements

### Adding new features and fixing bugs

If you would like to add a new feature, that is more than welcomed!
To add a new feature:

1. If you do not have the repository cloned, please run the following commands first:

   ```bash
   git clone https://github.com/ZCG-coder/Steppable
   git checkout -b new-branch-name
   ```

   **Warning:** Never work on the `main` branch!

2. Create a new directory under `src/`, suppose your feature is called `abc`
   ```
   Steppable/
   └── src/abc              [ Feature ]
   ```
3. Create the following files under the directory just created
   ```
   Steppable/
   ├── include/fn/
   │   └── calc.hpp [ Feature declaration ]
   ├── src/abc/
   │   ├── abcReport.hpp   [ Output declaration ]
   │   ├── abc.cpp         [ Feature definition ]
   │   ├── abcReport.cpp   [ Output definition ]
   │   └── README.md       [ OPTIONAL - describe the feature ]
   └── CMakeLists.txt      [ Build definition ]
   ```
4. Add the following in `abc.cpp`:

```diff
// abc.cpp
+ #include "fn/calc.hpp"
+ #include "abcReport.cpp"
+ #include <...> // Other include files

+ // Your code here
+ std::string abc(const string_view& in);
```

5. Add the following in `abcReport.cpp`

```diff
// abcReport.cpp
+ #include "abcReport.hpp"
+ #include <string>
+
+ std::string reportAbc()
+ {
+     return "";
+ }
```

6. Add the following in `abcReport.hpp`

```diff
// abcReport.hpp
+ #include <string>
+ std::string reportAbc();
```

7. Add the following in the `calc.hpp` file:

```diff
// calc.hpp
std::string division(...);
+ std::string abc(const std::string_view& in);
```

8. Modify the `CMakeLists.txt`

```diff
# CMakeLists.txt
# -snip-
- set(COMPONENTS add subtract multiply decimalConvert comparison power division)
+ set(COMPONENTS add subtract multiply decimalConvert comparison power division abc)
# -snip-
```

9. Make a pull request about your new feature

### Adding documentation

Currently, most of our functions are undocumented, making it hard for others to maintain. We are looking for contributors to add documentation to our functions, classes, etc.

To add some documentation comments:

1. Clone the repository if you have not.
   ```bash
   git clone https://github.com/ZCG-coder/Steppable.git
   git checkout -b new-branch-name
   ```
   **Warning:** Never work on the `main` branch!
2. Add documentation on namespaces, classes, class methods and functions.
   **Note:** The documentation should be written with Doxygen.
3. Create a pull request about your documentation updates

### Posting issues about bugs

If you have any issues with Steppable, you may post them on the [issues page](https://github.com/ZCG-Coder/Steppable/issues). Please also tag your issue with the `bug` tag.

Issues should include:

- A title that describes the issue. (Incorrect result, etc.)
- A description of the issue.
- Output from the program. (The more verbose the better, e.g., with the `-steps:2` option)
- Expected output

### Suggesting new features

The issues page can also be used to suggest new features. Please tag your issue with the `feature` tag to indicate that it is a feature request.

The feature request should include:

- Description of the new feature
- Why adding it is important (2-3 sentences about how beneficial it is to the users)

You do not necessarily need to implement the feature yourself.

## Contacts and inquiries

Should you have any inquiries, please contact Andy Zhang (`[andy at nwsoft dot tk]`).
