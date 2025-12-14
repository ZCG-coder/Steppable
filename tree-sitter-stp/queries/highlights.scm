; keywords
("fn") @keyword
("ret") @keyword
("sym") @keyword
("break") @keyword
("cont") @keyword
("exit") @keyword
("if") @keyword
("elseif") @keyword
("else") @keyword
("while") @keyword
("for") @keyword
("in") @keyword
("import") @keyword

; delimeters
(";") @punctuation.delimiter
("[") @punctuation.delimiter
("]") @punctuation.delimiter
("{") @punctuation.delimiter
("}") @punctuation.delimiter
("(") @punctuation.delimiter
(")") @punctuation.delimiter

; operators
("...") @operator
("%") @operator
(binary_operator_left0) @operator
(binary_operator_left1) @operator
(binary_operator_left2) @operator
(binary_operator_right) @operator
(unary_expression
    unary_op: _ @operator
)
(suffix_expression
    operator: _ @operator
)

; comment
(comment) @comment

; assignment
(assignment
    name: (identifier) @variable)

; function params
(fn_keyword_arg
    argument_name: (param_name) @variable.parameter
)
(fn_pos_arg
    argument_name: (param_name) @variable.parameter
)

; function call
(function_call
    fn_name: (identifier) @function
)

; function definition
(function_definition
    fn_name: (function_name) @function
)

; strings
(escape_sequence) @string.escape
(unicode_escape) @string.escape
(octal_escape) @string.escape
(string_char) @string
(string ("\"")) @punctuation.delimiter

; number
(number) @number

; identifiers
(identifier_or_member_access) @variable
