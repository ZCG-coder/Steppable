# Tree-sitter Grammar for Steppable Language

This directory contains a complete Tree-sitter grammar for the Steppable language that fixes the parsing issues mentioned in the original problem.

## Fixed Issues

1. **Assignment statements** - Now parse correctly: `mat1 = [1 2 3]`
2. **Function calls** - Properly recognized as function calls: `sum(mat1)`
3. **Matrix syntax** - Correctly handles row/column separation: `[1 2 3; 4 5 6]`
4. **Function definitions** - Parse without errors
5. **Statement separation** - Proper boundary handling with semicolons and newlines

## Usage

The main grammar file is `stp_grammar.js` which contains the Tree-sitter grammar definition.

To generate the parser:
```bash
tree-sitter generate
```

To test parsing:
```bash
tree-sitter parse <file.stp>
```

## Example Code That Parses Successfully

```steppable
mat1 = [1 2 3; 4 5 6];
mat2 = [1*2^3 3 4 5 8 9; 4 5 6 8 9 0];
sum(mat1);
mat1 = mat1 + mat2;
```

All of these statements now parse correctly without errors.