# How to document the code

This guide shows how to document the code in the project. All of the code documentation should follow this guide.

## 1 What needs to be documented?

- All code files must have a file documentation. If there is a header file that defines some functions, document the
  functions **in the header file only**. If there are overloads, document **all of them**.
- All functions, classes, `enum`s, `constexpr`s and macros defined in the global scope needs to be documented.
- Variables defined inside functions need not to be documented, but methods and fields defined in `class`es, and members
  of `namespace`s must be documented.

## 2 Format of documentation

### 2.1 General

Take, for example, this piece of code to implement a absolute value function:

```cpp
template<typename NumberT>
constexpr inline NumberT abs(NumberT number)
{
    if (number < 0)
        return -number;
    return number;
}
```

This code can be documented as:

```cpp
/// INFN : abs
/// TMPL : NumberT - The type of the number.
/// OUT  : NumberT
/// IN   : NumberT number - The number to get the absolute value of.
/// DESC : Get the absolute value of a number.
template<typename NumberT>
constexpr inline NumberT abs(NumberT number);
```

Here, every line of the comments are in the following format:

```cpp
/// LABEL: Value...
```

Every label takes up 5 characters (if it is less than 5 characters, pad with spaces). The value can take up multiple
lines, however, every line that follows should be indented to the colon, like this:

```cpp
/// LABEL: Value 1...
///        Value 2 that is still a part of LABEL
```

### 2.2 Available labels

#### 2.2.1 Available labels for all functions, classes, `enum`s, `constexpr`s, `namespace`s and macros

Labels of names:

- `CLASS`: Defines the name of a `class`
- `NMSPC`: Defines the name of a `namespace`
- `CEXPR`: Defines the name of a `constexpr`
- `FMCRO`: Defines a function-like macro
- `MACRO`: Defines a macro
- `INFN`: Defines the name of an inline function. This must be used for inline functions.
- `FN`: Defines the name of a general function. Inline functions need not to use this label.

Attributes:

- `DESC`: Description of the object documented
- `NOTE`: Defines an optional note to show in the documentation. This shows after `DESC`
- `WARN`: Defines an optional warning to show in the documentation, for example, a depreciated warning.
           This shows after `NOTE`.

#### 2.2.2 Available labels for all functions and methods of classes

- `TMPL`: Defines a list of template types
- `OUT`: Defines the type of output
- `IN`: Defines a list of inputs and their types. For function-like macros, the types need not to be specified.

#### 2.2.3 Available labels for files

- `FILE`: Defines the name of the file
- `DESC`: Description of file
