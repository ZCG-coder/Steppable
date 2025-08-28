// Tree-sitter grammar for Steppable language
module.exports = grammar({
  name: 'steppable',

  extras: $ => [
    /\s+/,        // whitespace  
    /\/\/[^\n]*/  // line comments - simplified
  ],

  conflicts: $ => [
    [$.call_expression, $.expression],
    [$.return_statement]
  ],

  rules: {
    // Root rule - a program consists of statements
    source_file: $ => repeat(choice(
      seq($.statement, optional(choice(';', '\n'))),
      '\n'
    )),

    // Statements 
    statement: $ => choice(
      $.assignment_statement,
      $.expression_statement,
      $.function_definition,
      $.return_statement
    ),

    // Expression statements are just expressions
    expression_statement: $ => $.expression,

    // Assignment statements: identifier = expression  
    assignment_statement: $ => seq(
      $.identifier,
      '=',
      $.expression
    ),

    // Return statements
    return_statement: $ => seq(
      'return',
      optional($.expression)
    ),

    // Function definitions (basic structure)
    function_definition: $ => seq(
      'function',
      $.identifier,
      '(',
      optional($.parameter_list),
      ')',
      $.block
    ),

    parameter_list: $ => sep1($.identifier, ','),

    block: $ => seq(
      '{',
      repeat(choice($.statement, '\n')),
      '}'
    ),

    // Expressions
    expression: $ => choice(
      $.binary_expression,
      $.unary_expression,
      $.call_expression,
      $.matrix_literal,
      $.identifier,
      $.number,
      $.parenthesized_expression
    ),

    // Binary expressions with precedence
    binary_expression: $ => choice(
      prec.left(1, seq($.expression, '+', $.expression)),
      prec.left(1, seq($.expression, '-', $.expression)),
      prec.left(2, seq($.expression, '*', $.expression)),
      prec.left(2, seq($.expression, '/', $.expression)),
      prec.left(2, seq($.expression, '%', $.expression)),
      prec.right(3, seq($.expression, '^', $.expression))
    ),

    // Unary expressions
    unary_expression: $ => choice(
      prec(4, seq('-', $.expression)),
      prec(4, seq('+', $.expression))
    ),

    // Function calls: identifier(arguments)
    call_expression: $ => prec.dynamic(1, seq(
      $.identifier,
      '(',
      optional($.argument_list),
      ')'
    )),

    argument_list: $ => sep1($.expression, ','),

    // Matrix literals: [row1; row2; row3] where rows are space-separated
    matrix_literal: $ => seq(
      '[',
      optional($.matrix_content),
      ']'
    ),

    matrix_content: $ => sep1($.matrix_row, ';'),

    matrix_row: $ => repeat1($.expression),

    // Parenthesized expressions
    parenthesized_expression: $ => seq(
      '(',
      $.expression,
      ')'
    ),

    // Basic tokens
    identifier: $ => /[a-zA-Z_][a-zA-Z0-9_]*/,
    
    number: $ => {
      const decimal = /[0-9]+/;
      const float = /[0-9]*\.[0-9]+/;
      const scientific = /[0-9]*\.?[0-9]+[eE][+-]?[0-9]+/;
      
      return token(choice(
        scientific,
        float, 
        decimal
      ));
    }
  }
});

// Helper function for comma-separated lists
function sep1(rule, separator) {
  return seq(rule, repeat(seq(separator, rule)));
}