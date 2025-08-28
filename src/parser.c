#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 169
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 44
#define ALIAS_COUNT 0
#define TOKEN_COUNT 21
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 6
#define PRODUCTION_ID_COUNT 1

enum {
  anon_sym_SEMI = 1,
  anon_sym_LF = 2,
  anon_sym_EQ = 3,
  anon_sym_return = 4,
  anon_sym_function = 5,
  anon_sym_LPAREN = 6,
  anon_sym_RPAREN = 7,
  anon_sym_COMMA = 8,
  anon_sym_LBRACE = 9,
  anon_sym_RBRACE = 10,
  anon_sym_PLUS = 11,
  anon_sym_DASH = 12,
  anon_sym_STAR = 13,
  anon_sym_SLASH = 14,
  anon_sym_PERCENT = 15,
  anon_sym_CARET = 16,
  anon_sym_LBRACK = 17,
  anon_sym_RBRACK = 18,
  sym_identifier = 19,
  sym_number = 20,
  sym_source_file = 21,
  sym_statement = 22,
  sym_expression_statement = 23,
  sym_assignment_statement = 24,
  sym_return_statement = 25,
  sym_function_definition = 26,
  sym_parameter_list = 27,
  sym_block = 28,
  sym_expression = 29,
  sym_binary_expression = 30,
  sym_unary_expression = 31,
  sym_call_expression = 32,
  sym_argument_list = 33,
  sym_matrix_literal = 34,
  sym_matrix_content = 35,
  sym_matrix_row = 36,
  sym_parenthesized_expression = 37,
  aux_sym_source_file_repeat1 = 38,
  aux_sym_parameter_list_repeat1 = 39,
  aux_sym_block_repeat1 = 40,
  aux_sym_argument_list_repeat1 = 41,
  aux_sym_matrix_content_repeat1 = 42,
  aux_sym_matrix_row_repeat1 = 43,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_SEMI] = ";",
  [anon_sym_LF] = "\n",
  [anon_sym_EQ] = "=",
  [anon_sym_return] = "return",
  [anon_sym_function] = "function",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_COMMA] = ",",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_PLUS] = "+",
  [anon_sym_DASH] = "-",
  [anon_sym_STAR] = "*",
  [anon_sym_SLASH] = "/",
  [anon_sym_PERCENT] = "%",
  [anon_sym_CARET] = "^",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [sym_identifier] = "identifier",
  [sym_number] = "number",
  [sym_source_file] = "source_file",
  [sym_statement] = "statement",
  [sym_expression_statement] = "expression_statement",
  [sym_assignment_statement] = "assignment_statement",
  [sym_return_statement] = "return_statement",
  [sym_function_definition] = "function_definition",
  [sym_parameter_list] = "parameter_list",
  [sym_block] = "block",
  [sym_expression] = "expression",
  [sym_binary_expression] = "binary_expression",
  [sym_unary_expression] = "unary_expression",
  [sym_call_expression] = "call_expression",
  [sym_argument_list] = "argument_list",
  [sym_matrix_literal] = "matrix_literal",
  [sym_matrix_content] = "matrix_content",
  [sym_matrix_row] = "matrix_row",
  [sym_parenthesized_expression] = "parenthesized_expression",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_parameter_list_repeat1] = "parameter_list_repeat1",
  [aux_sym_block_repeat1] = "block_repeat1",
  [aux_sym_argument_list_repeat1] = "argument_list_repeat1",
  [aux_sym_matrix_content_repeat1] = "matrix_content_repeat1",
  [aux_sym_matrix_row_repeat1] = "matrix_row_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_LF] = anon_sym_LF,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_return] = anon_sym_return,
  [anon_sym_function] = anon_sym_function,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_PLUS] = anon_sym_PLUS,
  [anon_sym_DASH] = anon_sym_DASH,
  [anon_sym_STAR] = anon_sym_STAR,
  [anon_sym_SLASH] = anon_sym_SLASH,
  [anon_sym_PERCENT] = anon_sym_PERCENT,
  [anon_sym_CARET] = anon_sym_CARET,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [sym_identifier] = sym_identifier,
  [sym_number] = sym_number,
  [sym_source_file] = sym_source_file,
  [sym_statement] = sym_statement,
  [sym_expression_statement] = sym_expression_statement,
  [sym_assignment_statement] = sym_assignment_statement,
  [sym_return_statement] = sym_return_statement,
  [sym_function_definition] = sym_function_definition,
  [sym_parameter_list] = sym_parameter_list,
  [sym_block] = sym_block,
  [sym_expression] = sym_expression,
  [sym_binary_expression] = sym_binary_expression,
  [sym_unary_expression] = sym_unary_expression,
  [sym_call_expression] = sym_call_expression,
  [sym_argument_list] = sym_argument_list,
  [sym_matrix_literal] = sym_matrix_literal,
  [sym_matrix_content] = sym_matrix_content,
  [sym_matrix_row] = sym_matrix_row,
  [sym_parenthesized_expression] = sym_parenthesized_expression,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_parameter_list_repeat1] = aux_sym_parameter_list_repeat1,
  [aux_sym_block_repeat1] = aux_sym_block_repeat1,
  [aux_sym_argument_list_repeat1] = aux_sym_argument_list_repeat1,
  [aux_sym_matrix_content_repeat1] = aux_sym_matrix_content_repeat1,
  [aux_sym_matrix_row_repeat1] = aux_sym_matrix_row_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LF] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_return] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_function] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PLUS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_STAR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SLASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PERCENT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_CARET] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_expression_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_assignment_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_return_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_function_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_parameter_list] = {
    .visible = true,
    .named = true,
  },
  [sym_block] = {
    .visible = true,
    .named = true,
  },
  [sym_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_binary_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_unary_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_call_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_argument_list] = {
    .visible = true,
    .named = true,
  },
  [sym_matrix_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_matrix_content] = {
    .visible = true,
    .named = true,
  },
  [sym_matrix_row] = {
    .visible = true,
    .named = true,
  },
  [sym_parenthesized_expression] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_parameter_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_block_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_argument_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_matrix_content_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_matrix_row_repeat1] = {
    .visible = false,
    .named = false,
  },
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 5,
  [7] = 7,
  [8] = 3,
  [9] = 9,
  [10] = 10,
  [11] = 10,
  [12] = 10,
  [13] = 13,
  [14] = 10,
  [15] = 9,
  [16] = 10,
  [17] = 17,
  [18] = 18,
  [19] = 13,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 33,
  [35] = 35,
  [36] = 24,
  [37] = 29,
  [38] = 21,
  [39] = 17,
  [40] = 35,
  [41] = 18,
  [42] = 25,
  [43] = 30,
  [44] = 32,
  [45] = 22,
  [46] = 46,
  [47] = 35,
  [48] = 26,
  [49] = 27,
  [50] = 35,
  [51] = 28,
  [52] = 31,
  [53] = 35,
  [54] = 54,
  [55] = 28,
  [56] = 56,
  [57] = 33,
  [58] = 32,
  [59] = 59,
  [60] = 54,
  [61] = 61,
  [62] = 54,
  [63] = 63,
  [64] = 22,
  [65] = 54,
  [66] = 66,
  [67] = 18,
  [68] = 68,
  [69] = 68,
  [70] = 59,
  [71] = 59,
  [72] = 63,
  [73] = 63,
  [74] = 66,
  [75] = 75,
  [76] = 66,
  [77] = 63,
  [78] = 59,
  [79] = 66,
  [80] = 68,
  [81] = 75,
  [82] = 68,
  [83] = 68,
  [84] = 59,
  [85] = 63,
  [86] = 66,
  [87] = 31,
  [88] = 54,
  [89] = 27,
  [90] = 26,
  [91] = 24,
  [92] = 29,
  [93] = 17,
  [94] = 94,
  [95] = 95,
  [96] = 96,
  [97] = 97,
  [98] = 98,
  [99] = 99,
  [100] = 97,
  [101] = 98,
  [102] = 102,
  [103] = 95,
  [104] = 96,
  [105] = 94,
  [106] = 29,
  [107] = 107,
  [108] = 28,
  [109] = 24,
  [110] = 110,
  [111] = 17,
  [112] = 32,
  [113] = 33,
  [114] = 22,
  [115] = 26,
  [116] = 27,
  [117] = 18,
  [118] = 31,
  [119] = 29,
  [120] = 26,
  [121] = 22,
  [122] = 33,
  [123] = 32,
  [124] = 18,
  [125] = 17,
  [126] = 27,
  [127] = 127,
  [128] = 127,
  [129] = 24,
  [130] = 127,
  [131] = 28,
  [132] = 127,
  [133] = 31,
  [134] = 127,
  [135] = 135,
  [136] = 136,
  [137] = 137,
  [138] = 138,
  [139] = 139,
  [140] = 140,
  [141] = 139,
  [142] = 142,
  [143] = 143,
  [144] = 144,
  [145] = 145,
  [146] = 146,
  [147] = 145,
  [148] = 148,
  [149] = 149,
  [150] = 146,
  [151] = 151,
  [152] = 151,
  [153] = 153,
  [154] = 153,
  [155] = 151,
  [156] = 153,
  [157] = 157,
  [158] = 151,
  [159] = 153,
  [160] = 153,
  [161] = 151,
  [162] = 162,
  [163] = 157,
  [164] = 164,
  [165] = 165,
  [166] = 166,
  [167] = 162,
  [168] = 165,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(60);
      if (lookahead == '\n') ADVANCE(65);
      if (lookahead == '%') ADVANCE(114);
      if (lookahead == '(') ADVANCE(76);
      if (lookahead == ')') ADVANCE(85);
      if (lookahead == '*') ADVANCE(112);
      if (lookahead == '+') ADVANCE(96);
      if (lookahead == ',') ADVANCE(90);
      if (lookahead == '-') ADVANCE(104);
      if (lookahead == '.') ADVANCE(50);
      if (lookahead == '/') ADVANCE(113);
      if (lookahead == ';') ADVANCE(61);
      if (lookahead == '=') ADVANCE(67);
      if (lookahead == '[') ADVANCE(116);
      if (lookahead == ']') ADVANCE(124);
      if (lookahead == '^') ADVANCE(115);
      if (lookahead == 'f') ADVANCE(190);
      if (lookahead == 'r') ADVANCE(181);
      if (lookahead == '{') ADVANCE(92);
      if (lookahead == '}') ADVANCE(94);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(201);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 1:
      if (lookahead == '\n') ADVANCE(65);
      if (lookahead == '%') ADVANCE(114);
      if (lookahead == '(') ADVANCE(76);
      if (lookahead == '*') ADVANCE(112);
      if (lookahead == '+') ADVANCE(96);
      if (lookahead == '-') ADVANCE(104);
      if (lookahead == '.') ADVANCE(50);
      if (lookahead == '/') ADVANCE(113);
      if (lookahead == '=') ADVANCE(67);
      if (lookahead == '[') ADVANCE(116);
      if (lookahead == '^') ADVANCE(115);
      if (lookahead == 'f') ADVANCE(190);
      if (lookahead == 'r') ADVANCE(181);
      if (lookahead == '}') ADVANCE(94);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(1)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(201);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 2:
      if (lookahead == '\n') ADVANCE(65);
      if (lookahead == '%') ADVANCE(114);
      if (lookahead == '(') ADVANCE(76);
      if (lookahead == '*') ADVANCE(112);
      if (lookahead == '+') ADVANCE(96);
      if (lookahead == '-') ADVANCE(104);
      if (lookahead == '.') ADVANCE(50);
      if (lookahead == '/') ADVANCE(113);
      if (lookahead == '[') ADVANCE(116);
      if (lookahead == '^') ADVANCE(115);
      if (lookahead == 'f') ADVANCE(190);
      if (lookahead == 'r') ADVANCE(181);
      if (lookahead == '}') ADVANCE(94);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(2)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(201);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 3:
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(76);
      if (lookahead == '+') ADVANCE(96);
      if (lookahead == '-') ADVANCE(104);
      if (lookahead == '.') ADVANCE(50);
      if (lookahead == '/') SKIP(32)
      if (lookahead == '[') ADVANCE(116);
      if (lookahead == 'f') ADVANCE(190);
      if (lookahead == 'r') ADVANCE(181);
      if (lookahead == '}') ADVANCE(94);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(3)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(201);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 4:
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '/') SKIP(4)
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'r') ADVANCE(131);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(4)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(194);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      if (lookahead != 0) SKIP(4)
      END_STATE();
    case 5:
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '/') SKIP(5)
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == '}') ADVANCE(95);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(5)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(195);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      if (lookahead != 0) SKIP(5)
      END_STATE();
    case 6:
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == '/') SKIP(6)
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'r') ADVANCE(159);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(6)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(196);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      if (lookahead != 0) SKIP(6)
      END_STATE();
    case 7:
      if (lookahead == '\n') SKIP(25)
      if (lookahead == '(') ADVANCE(80);
      if (lookahead == '+') ADVANCE(100);
      if (lookahead == '-') ADVANCE(108);
      if (lookahead == '.') ADVANCE(7);
      if (lookahead == '/') SKIP(7)
      if (lookahead == '[') ADVANCE(120);
      if (lookahead == ']') ADVANCE(125);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(7)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(197);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(172);
      if (lookahead != 0) SKIP(7)
      END_STATE();
    case 8:
      if (lookahead == '\n') SKIP(26)
      if (lookahead == '(') ADVANCE(81);
      if (lookahead == '+') ADVANCE(101);
      if (lookahead == '-') ADVANCE(109);
      if (lookahead == '.') ADVANCE(8);
      if (lookahead == '/') SKIP(8)
      if (lookahead == ';') ADVANCE(63);
      if (lookahead == '[') ADVANCE(121);
      if (lookahead == ']') ADVANCE(126);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(8)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(198);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      if (lookahead != 0) SKIP(8)
      END_STATE();
    case 9:
      if (lookahead == '\n') SKIP(24)
      if (lookahead == '(') ADVANCE(82);
      if (lookahead == ')') ADVANCE(86);
      if (lookahead == '+') ADVANCE(102);
      if (lookahead == '-') ADVANCE(110);
      if (lookahead == '.') ADVANCE(9);
      if (lookahead == '/') SKIP(9)
      if (lookahead == '[') ADVANCE(122);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(9)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(199);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(176);
      if (lookahead != 0) SKIP(9)
      END_STATE();
    case 10:
      if (lookahead == '\n') SKIP(27)
      if (lookahead == '(') ADVANCE(83);
      if (lookahead == '+') ADVANCE(103);
      if (lookahead == '-') ADVANCE(111);
      if (lookahead == '.') ADVANCE(10);
      if (lookahead == '/') SKIP(10)
      if (lookahead == '[') ADVANCE(123);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(10)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(200);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(178);
      if (lookahead != 0) SKIP(10)
      END_STATE();
    case 11:
      if (lookahead == '\n') SKIP(29)
      if (lookahead == ')') ADVANCE(87);
      if (lookahead == ',') ADVANCE(91);
      if (lookahead == '/') SKIP(11)
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(11)
      if (lookahead != 0) SKIP(11)
      END_STATE();
    case 12:
      if (lookahead == '\n') SKIP(45)
      if (lookahead == '/') SKIP(12)
      if (lookahead == ';') ADVANCE(64);
      if (lookahead == ']') ADVANCE(127);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(12)
      if (lookahead != 0) SKIP(12)
      END_STATE();
    case 13:
      if (lookahead == '\n') SKIP(30)
      if (lookahead == ')') ADVANCE(88);
      if (lookahead == '/') SKIP(13)
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(13)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      if (lookahead != 0) SKIP(13)
      END_STATE();
    case 14:
      if (lookahead == '\n') SKIP(46)
      if (lookahead == '/') SKIP(14)
      if (lookahead == '{') ADVANCE(93);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(14)
      if (lookahead != 0) SKIP(14)
      END_STATE();
    case 15:
      if (lookahead == '\n') SKIP(47)
      if (lookahead == '/') SKIP(15)
      if (lookahead == ']') ADVANCE(128);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(15)
      if (lookahead != 0) SKIP(15)
      END_STATE();
    case 16:
      if (lookahead == '\n') SKIP(31)
      if (lookahead == ')') ADVANCE(89);
      if (lookahead == '/') SKIP(16)
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(16)
      if (lookahead != 0) SKIP(16)
      END_STATE();
    case 17:
      if (lookahead == '\n') SKIP(28)
      if (lookahead == '(') ADVANCE(84);
      if (lookahead == '/') SKIP(17)
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(17)
      if (lookahead != 0) SKIP(17)
      END_STATE();
    case 18:
      if (lookahead == '\n') SKIP(48)
      if (lookahead == '/') SKIP(18)
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(18)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(192);
      if (lookahead != 0) SKIP(18)
      END_STATE();
    case 19:
      if (lookahead == '%') ADVANCE(114);
      if (lookahead == '(') ADVANCE(76);
      if (lookahead == ')') ADVANCE(85);
      if (lookahead == '*') ADVANCE(112);
      if (lookahead == '+') ADVANCE(96);
      if (lookahead == ',') ADVANCE(90);
      if (lookahead == '-') ADVANCE(104);
      if (lookahead == '/') ADVANCE(113);
      if (lookahead == '^') ADVANCE(115);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(19)
      END_STATE();
    case 20:
      if (lookahead == '%') ADVANCE(114);
      if (lookahead == '(') ADVANCE(76);
      if (lookahead == ')') ADVANCE(85);
      if (lookahead == '*') ADVANCE(112);
      if (lookahead == '+') ADVANCE(96);
      if (lookahead == '-') ADVANCE(104);
      if (lookahead == '/') ADVANCE(113);
      if (lookahead == '^') ADVANCE(115);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(20)
      END_STATE();
    case 21:
      if (lookahead == '%') ADVANCE(114);
      if (lookahead == '(') ADVANCE(76);
      if (lookahead == '*') ADVANCE(112);
      if (lookahead == '+') ADVANCE(96);
      if (lookahead == '-') ADVANCE(104);
      if (lookahead == '.') ADVANCE(50);
      if (lookahead == '/') ADVANCE(113);
      if (lookahead == ';') ADVANCE(61);
      if (lookahead == '[') ADVANCE(116);
      if (lookahead == ']') ADVANCE(124);
      if (lookahead == '^') ADVANCE(115);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(21)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(201);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 22:
      if (lookahead == '%') ADVANCE(114);
      if (lookahead == ')') ADVANCE(85);
      if (lookahead == '*') ADVANCE(112);
      if (lookahead == '+') ADVANCE(96);
      if (lookahead == ',') ADVANCE(90);
      if (lookahead == '-') ADVANCE(104);
      if (lookahead == '/') ADVANCE(113);
      if (lookahead == '^') ADVANCE(115);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(22)
      END_STATE();
    case 23:
      if (lookahead == '%') ADVANCE(114);
      if (lookahead == ')') ADVANCE(85);
      if (lookahead == '*') ADVANCE(112);
      if (lookahead == '+') ADVANCE(96);
      if (lookahead == '-') ADVANCE(104);
      if (lookahead == '/') ADVANCE(113);
      if (lookahead == '^') ADVANCE(115);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(23)
      END_STATE();
    case 24:
      if (lookahead == '(') ADVANCE(76);
      if (lookahead == ')') ADVANCE(85);
      if (lookahead == '+') ADVANCE(96);
      if (lookahead == '-') ADVANCE(104);
      if (lookahead == '.') ADVANCE(50);
      if (lookahead == '/') SKIP(35)
      if (lookahead == '[') ADVANCE(116);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(24)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(201);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 25:
      if (lookahead == '(') ADVANCE(76);
      if (lookahead == '+') ADVANCE(96);
      if (lookahead == '-') ADVANCE(104);
      if (lookahead == '.') ADVANCE(50);
      if (lookahead == '/') SKIP(33)
      if (lookahead == '[') ADVANCE(116);
      if (lookahead == ']') ADVANCE(124);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(25)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(201);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 26:
      if (lookahead == '(') ADVANCE(76);
      if (lookahead == '+') ADVANCE(96);
      if (lookahead == '-') ADVANCE(104);
      if (lookahead == '.') ADVANCE(50);
      if (lookahead == '/') SKIP(34)
      if (lookahead == ';') ADVANCE(61);
      if (lookahead == '[') ADVANCE(116);
      if (lookahead == ']') ADVANCE(124);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(26)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(201);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 27:
      if (lookahead == '(') ADVANCE(76);
      if (lookahead == '+') ADVANCE(96);
      if (lookahead == '-') ADVANCE(104);
      if (lookahead == '.') ADVANCE(50);
      if (lookahead == '/') SKIP(36)
      if (lookahead == '[') ADVANCE(116);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(27)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(201);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 28:
      if (lookahead == '(') ADVANCE(76);
      if (lookahead == '/') SKIP(43)
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(28)
      END_STATE();
    case 29:
      if (lookahead == ')') ADVANCE(85);
      if (lookahead == ',') ADVANCE(90);
      if (lookahead == '/') SKIP(37)
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(29)
      END_STATE();
    case 30:
      if (lookahead == ')') ADVANCE(85);
      if (lookahead == '/') SKIP(39)
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(30)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 31:
      if (lookahead == ')') ADVANCE(85);
      if (lookahead == '/') SKIP(42)
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(31)
      END_STATE();
    case 32:
      if (lookahead == '/') SKIP(5)
      END_STATE();
    case 33:
      if (lookahead == '/') SKIP(7)
      END_STATE();
    case 34:
      if (lookahead == '/') SKIP(8)
      END_STATE();
    case 35:
      if (lookahead == '/') SKIP(9)
      END_STATE();
    case 36:
      if (lookahead == '/') SKIP(10)
      END_STATE();
    case 37:
      if (lookahead == '/') SKIP(11)
      END_STATE();
    case 38:
      if (lookahead == '/') SKIP(12)
      END_STATE();
    case 39:
      if (lookahead == '/') SKIP(13)
      END_STATE();
    case 40:
      if (lookahead == '/') SKIP(14)
      END_STATE();
    case 41:
      if (lookahead == '/') SKIP(15)
      END_STATE();
    case 42:
      if (lookahead == '/') SKIP(16)
      END_STATE();
    case 43:
      if (lookahead == '/') SKIP(17)
      END_STATE();
    case 44:
      if (lookahead == '/') SKIP(18)
      END_STATE();
    case 45:
      if (lookahead == '/') SKIP(38)
      if (lookahead == ';') ADVANCE(61);
      if (lookahead == ']') ADVANCE(124);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(45)
      END_STATE();
    case 46:
      if (lookahead == '/') SKIP(40)
      if (lookahead == '{') ADVANCE(92);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(46)
      END_STATE();
    case 47:
      if (lookahead == '/') SKIP(41)
      if (lookahead == ']') ADVANCE(124);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(47)
      END_STATE();
    case 48:
      if (lookahead == '/') SKIP(44)
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(48)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 49:
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(51);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(203);
      END_STATE();
    case 50:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(202);
      END_STATE();
    case 51:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(203);
      END_STATE();
    case 52:
      if (eof) ADVANCE(60);
      if (lookahead == '\n') ADVANCE(65);
      if (lookahead == '%') ADVANCE(114);
      if (lookahead == '(') ADVANCE(76);
      if (lookahead == '*') ADVANCE(112);
      if (lookahead == '+') ADVANCE(96);
      if (lookahead == '-') ADVANCE(104);
      if (lookahead == '.') ADVANCE(50);
      if (lookahead == '/') ADVANCE(113);
      if (lookahead == ';') ADVANCE(61);
      if (lookahead == '=') ADVANCE(67);
      if (lookahead == '[') ADVANCE(116);
      if (lookahead == '^') ADVANCE(115);
      if (lookahead == 'f') ADVANCE(190);
      if (lookahead == 'r') ADVANCE(181);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(52)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(201);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 53:
      if (eof) ADVANCE(60);
      if (lookahead == '\n') ADVANCE(65);
      if (lookahead == '%') ADVANCE(114);
      if (lookahead == '(') ADVANCE(76);
      if (lookahead == '*') ADVANCE(112);
      if (lookahead == '+') ADVANCE(96);
      if (lookahead == '-') ADVANCE(104);
      if (lookahead == '.') ADVANCE(50);
      if (lookahead == '/') ADVANCE(113);
      if (lookahead == ';') ADVANCE(61);
      if (lookahead == '[') ADVANCE(116);
      if (lookahead == '^') ADVANCE(115);
      if (lookahead == 'f') ADVANCE(190);
      if (lookahead == 'r') ADVANCE(181);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(53)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(201);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 54:
      if (eof) ADVANCE(60);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(76);
      if (lookahead == '+') ADVANCE(96);
      if (lookahead == '-') ADVANCE(104);
      if (lookahead == '.') ADVANCE(50);
      if (lookahead == '/') SKIP(58)
      if (lookahead == '[') ADVANCE(116);
      if (lookahead == 'f') ADVANCE(190);
      if (lookahead == 'r') ADVANCE(181);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(54)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(201);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 55:
      if (eof) ADVANCE(60);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(76);
      if (lookahead == '+') ADVANCE(96);
      if (lookahead == '-') ADVANCE(104);
      if (lookahead == '.') ADVANCE(50);
      if (lookahead == '/') SKIP(59)
      if (lookahead == ';') ADVANCE(61);
      if (lookahead == '[') ADVANCE(116);
      if (lookahead == 'f') ADVANCE(190);
      if (lookahead == 'r') ADVANCE(181);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(55)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(201);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 56:
      if (eof) ADVANCE(60);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '/') SKIP(56)
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'r') ADVANCE(131);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(56)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(194);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      if (lookahead != 0) SKIP(56)
      END_STATE();
    case 57:
      if (eof) ADVANCE(60);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == '/') SKIP(57)
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'r') ADVANCE(159);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(57)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(196);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      if (lookahead != 0) SKIP(57)
      END_STATE();
    case 58:
      if (eof) ADVANCE(60);
      if (lookahead == '/') SKIP(56)
      END_STATE();
    case 59:
      if (eof) ADVANCE(60);
      if (lookahead == '/') SKIP(57)
      END_STATE();
    case 60:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(anon_sym_SEMI);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'r') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(196);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(anon_sym_SEMI);
      if (lookahead == '(') ADVANCE(81);
      if (lookahead == '+') ADVANCE(101);
      if (lookahead == '-') ADVANCE(109);
      if (lookahead == '.') ADVANCE(8);
      if (lookahead == ';') ADVANCE(63);
      if (lookahead == '[') ADVANCE(121);
      if (lookahead == ']') ADVANCE(126);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(198);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(anon_sym_SEMI);
      if (lookahead == ';') ADVANCE(64);
      if (lookahead == ']') ADVANCE(127);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(anon_sym_LF);
      if (lookahead == '\n') ADVANCE(65);
      if (lookahead == '/') ADVANCE(113);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(anon_sym_LF);
      if (lookahead == '\n') ADVANCE(66);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(anon_sym_return);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'r') ADVANCE(131);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(140);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(anon_sym_return);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == '}') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(154);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(anon_sym_return);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'r') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(168);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(anon_sym_return);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(anon_sym_function);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'r') ADVANCE(131);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(140);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(anon_sym_function);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == '}') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(154);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(anon_sym_function);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'r') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(168);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(anon_sym_function);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'r') ADVANCE(131);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(194);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == '}') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(195);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'r') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(196);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      if (lookahead == '(') ADVANCE(80);
      if (lookahead == '+') ADVANCE(100);
      if (lookahead == '-') ADVANCE(108);
      if (lookahead == '.') ADVANCE(7);
      if (lookahead == '[') ADVANCE(120);
      if (lookahead == ']') ADVANCE(125);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(197);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(172);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      if (lookahead == '(') ADVANCE(81);
      if (lookahead == '+') ADVANCE(101);
      if (lookahead == '-') ADVANCE(109);
      if (lookahead == '.') ADVANCE(8);
      if (lookahead == ';') ADVANCE(63);
      if (lookahead == '[') ADVANCE(121);
      if (lookahead == ']') ADVANCE(126);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(198);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      if (lookahead == '(') ADVANCE(82);
      if (lookahead == ')') ADVANCE(86);
      if (lookahead == '+') ADVANCE(102);
      if (lookahead == '-') ADVANCE(110);
      if (lookahead == '.') ADVANCE(9);
      if (lookahead == '[') ADVANCE(122);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(199);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(176);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      if (lookahead == '(') ADVANCE(83);
      if (lookahead == '+') ADVANCE(103);
      if (lookahead == '-') ADVANCE(111);
      if (lookahead == '.') ADVANCE(10);
      if (lookahead == '[') ADVANCE(123);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(200);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(178);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      if (lookahead == '(') ADVANCE(84);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      if (lookahead == '(') ADVANCE(82);
      if (lookahead == ')') ADVANCE(86);
      if (lookahead == '+') ADVANCE(102);
      if (lookahead == '-') ADVANCE(110);
      if (lookahead == '.') ADVANCE(9);
      if (lookahead == '[') ADVANCE(122);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(199);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(176);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      if (lookahead == ')') ADVANCE(87);
      if (lookahead == ',') ADVANCE(91);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      if (lookahead == ')') ADVANCE(88);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      if (lookahead == ')') ADVANCE(89);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(anon_sym_COMMA);
      if (lookahead == ')') ADVANCE(87);
      if (lookahead == ',') ADVANCE(91);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      if (lookahead == '{') ADVANCE(93);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == '}') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(195);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(anon_sym_PLUS);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(anon_sym_PLUS);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'r') ADVANCE(131);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(194);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(anon_sym_PLUS);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == '}') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(195);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(anon_sym_PLUS);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'r') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(196);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(anon_sym_PLUS);
      if (lookahead == '(') ADVANCE(80);
      if (lookahead == '+') ADVANCE(100);
      if (lookahead == '-') ADVANCE(108);
      if (lookahead == '.') ADVANCE(7);
      if (lookahead == '[') ADVANCE(120);
      if (lookahead == ']') ADVANCE(125);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(197);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(172);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(anon_sym_PLUS);
      if (lookahead == '(') ADVANCE(81);
      if (lookahead == '+') ADVANCE(101);
      if (lookahead == '-') ADVANCE(109);
      if (lookahead == '.') ADVANCE(8);
      if (lookahead == ';') ADVANCE(63);
      if (lookahead == '[') ADVANCE(121);
      if (lookahead == ']') ADVANCE(126);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(198);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(anon_sym_PLUS);
      if (lookahead == '(') ADVANCE(82);
      if (lookahead == ')') ADVANCE(86);
      if (lookahead == '+') ADVANCE(102);
      if (lookahead == '-') ADVANCE(110);
      if (lookahead == '.') ADVANCE(9);
      if (lookahead == '[') ADVANCE(122);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(199);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(176);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(anon_sym_PLUS);
      if (lookahead == '(') ADVANCE(83);
      if (lookahead == '+') ADVANCE(103);
      if (lookahead == '-') ADVANCE(111);
      if (lookahead == '.') ADVANCE(10);
      if (lookahead == '[') ADVANCE(123);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(200);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(178);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(anon_sym_DASH);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'r') ADVANCE(131);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(194);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(anon_sym_DASH);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == '}') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(195);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(anon_sym_DASH);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'r') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(196);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(anon_sym_DASH);
      if (lookahead == '(') ADVANCE(80);
      if (lookahead == '+') ADVANCE(100);
      if (lookahead == '-') ADVANCE(108);
      if (lookahead == '.') ADVANCE(7);
      if (lookahead == '[') ADVANCE(120);
      if (lookahead == ']') ADVANCE(125);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(197);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(172);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(anon_sym_DASH);
      if (lookahead == '(') ADVANCE(81);
      if (lookahead == '+') ADVANCE(101);
      if (lookahead == '-') ADVANCE(109);
      if (lookahead == '.') ADVANCE(8);
      if (lookahead == ';') ADVANCE(63);
      if (lookahead == '[') ADVANCE(121);
      if (lookahead == ']') ADVANCE(126);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(198);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(anon_sym_DASH);
      if (lookahead == '(') ADVANCE(82);
      if (lookahead == ')') ADVANCE(86);
      if (lookahead == '+') ADVANCE(102);
      if (lookahead == '-') ADVANCE(110);
      if (lookahead == '.') ADVANCE(9);
      if (lookahead == '[') ADVANCE(122);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(199);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(176);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(anon_sym_DASH);
      if (lookahead == '(') ADVANCE(83);
      if (lookahead == '+') ADVANCE(103);
      if (lookahead == '-') ADVANCE(111);
      if (lookahead == '.') ADVANCE(10);
      if (lookahead == '[') ADVANCE(123);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(200);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(178);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(anon_sym_STAR);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(anon_sym_SLASH);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(anon_sym_PERCENT);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(anon_sym_CARET);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'r') ADVANCE(131);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(194);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == '}') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(195);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'r') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(196);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      if (lookahead == '(') ADVANCE(80);
      if (lookahead == '+') ADVANCE(100);
      if (lookahead == '-') ADVANCE(108);
      if (lookahead == '.') ADVANCE(7);
      if (lookahead == '[') ADVANCE(120);
      if (lookahead == ']') ADVANCE(125);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(197);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(172);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      if (lookahead == '(') ADVANCE(81);
      if (lookahead == '+') ADVANCE(101);
      if (lookahead == '-') ADVANCE(109);
      if (lookahead == '.') ADVANCE(8);
      if (lookahead == ';') ADVANCE(63);
      if (lookahead == '[') ADVANCE(121);
      if (lookahead == ']') ADVANCE(126);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(198);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      if (lookahead == '(') ADVANCE(82);
      if (lookahead == ')') ADVANCE(86);
      if (lookahead == '+') ADVANCE(102);
      if (lookahead == '-') ADVANCE(110);
      if (lookahead == '.') ADVANCE(9);
      if (lookahead == '[') ADVANCE(122);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(199);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(176);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      if (lookahead == '(') ADVANCE(83);
      if (lookahead == '+') ADVANCE(103);
      if (lookahead == '-') ADVANCE(111);
      if (lookahead == '.') ADVANCE(10);
      if (lookahead == '[') ADVANCE(123);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(200);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(178);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      if (lookahead == '(') ADVANCE(80);
      if (lookahead == '+') ADVANCE(100);
      if (lookahead == '-') ADVANCE(108);
      if (lookahead == '.') ADVANCE(7);
      if (lookahead == '[') ADVANCE(120);
      if (lookahead == ']') ADVANCE(125);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(197);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(172);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      if (lookahead == '(') ADVANCE(81);
      if (lookahead == '+') ADVANCE(101);
      if (lookahead == '-') ADVANCE(109);
      if (lookahead == '.') ADVANCE(8);
      if (lookahead == ';') ADVANCE(63);
      if (lookahead == '[') ADVANCE(121);
      if (lookahead == ']') ADVANCE(126);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(198);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      if (lookahead == ';') ADVANCE(64);
      if (lookahead == ']') ADVANCE(127);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      if (lookahead == ']') ADVANCE(128);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'c') ADVANCE(136);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'r') ADVANCE(131);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(140);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'e') ADVANCE(137);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'n') ADVANCE(68);
      if (lookahead == 'r') ADVANCE(131);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(140);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'e') ADVANCE(137);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'r') ADVANCE(131);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(140);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'i') ADVANCE(135);
      if (lookahead == 'r') ADVANCE(131);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(140);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'n') ADVANCE(129);
      if (lookahead == 'r') ADVANCE(131);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(140);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'n') ADVANCE(72);
      if (lookahead == 'r') ADVANCE(131);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(140);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'o') ADVANCE(134);
      if (lookahead == 'r') ADVANCE(131);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(140);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'r') ADVANCE(131);
      if (lookahead == 't') ADVANCE(132);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(140);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'r') ADVANCE(131);
      if (lookahead == 't') ADVANCE(139);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(140);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'r') ADVANCE(131);
      if (lookahead == 'u') ADVANCE(133);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(140);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'r') ADVANCE(131);
      if (lookahead == 'u') ADVANCE(142);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(140);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'r') ADVANCE(131);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(141);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(140);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 141:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'r') ADVANCE(131);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(140);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 142:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'r') ADVANCE(130);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(140);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 143:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'c') ADVANCE(150);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == '}') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(154);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 144:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'e') ADVANCE(151);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'n') ADVANCE(69);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == '}') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(154);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'e') ADVANCE(151);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == '}') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(154);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'i') ADVANCE(149);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == '}') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(154);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'n') ADVANCE(143);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == '}') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(154);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 148:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'n') ADVANCE(73);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == '}') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(154);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 149:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'o') ADVANCE(148);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == '}') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(154);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 150:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == 't') ADVANCE(146);
      if (lookahead == '}') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(154);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 151:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == 't') ADVANCE(153);
      if (lookahead == '}') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(154);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 152:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == 'u') ADVANCE(147);
      if (lookahead == '}') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(154);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 153:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == 'u') ADVANCE(156);
      if (lookahead == '}') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(154);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 154:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == '}') ADVANCE(95);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(155);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(154);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == '}') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(154);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 156:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'r') ADVANCE(144);
      if (lookahead == '}') ADVANCE(95);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(154);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 157:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'c') ADVANCE(164);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'r') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(168);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 158:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'e') ADVANCE(165);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'n') ADVANCE(70);
      if (lookahead == 'r') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(168);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 159:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'e') ADVANCE(165);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'r') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(168);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 160:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'i') ADVANCE(163);
      if (lookahead == 'r') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(168);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 161:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'n') ADVANCE(157);
      if (lookahead == 'r') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(168);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 162:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'n') ADVANCE(74);
      if (lookahead == 'r') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(168);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 163:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'o') ADVANCE(162);
      if (lookahead == 'r') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(168);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 164:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'r') ADVANCE(159);
      if (lookahead == 't') ADVANCE(160);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(168);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 165:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'r') ADVANCE(159);
      if (lookahead == 't') ADVANCE(167);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(168);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 166:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'r') ADVANCE(159);
      if (lookahead == 'u') ADVANCE(161);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(168);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 167:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'r') ADVANCE(159);
      if (lookahead == 'u') ADVANCE(170);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(168);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 168:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'r') ADVANCE(159);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(169);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(168);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 169:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'r') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(168);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 170:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'r') ADVANCE(158);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(168);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 171:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '(') ADVANCE(80);
      if (lookahead == '+') ADVANCE(100);
      if (lookahead == '-') ADVANCE(108);
      if (lookahead == '.') ADVANCE(7);
      if (lookahead == '[') ADVANCE(120);
      if (lookahead == ']') ADVANCE(125);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(172);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(171);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(172);
      END_STATE();
    case 172:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '(') ADVANCE(80);
      if (lookahead == '+') ADVANCE(100);
      if (lookahead == '-') ADVANCE(108);
      if (lookahead == '.') ADVANCE(7);
      if (lookahead == '[') ADVANCE(120);
      if (lookahead == ']') ADVANCE(125);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(171);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(172);
      END_STATE();
    case 173:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '(') ADVANCE(81);
      if (lookahead == '+') ADVANCE(101);
      if (lookahead == '-') ADVANCE(109);
      if (lookahead == '.') ADVANCE(8);
      if (lookahead == ';') ADVANCE(63);
      if (lookahead == '[') ADVANCE(121);
      if (lookahead == ']') ADVANCE(126);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(174);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(173);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 174:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '(') ADVANCE(81);
      if (lookahead == '+') ADVANCE(101);
      if (lookahead == '-') ADVANCE(109);
      if (lookahead == '.') ADVANCE(8);
      if (lookahead == ';') ADVANCE(63);
      if (lookahead == '[') ADVANCE(121);
      if (lookahead == ']') ADVANCE(126);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(173);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 175:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '(') ADVANCE(82);
      if (lookahead == ')') ADVANCE(86);
      if (lookahead == '+') ADVANCE(102);
      if (lookahead == '-') ADVANCE(110);
      if (lookahead == '.') ADVANCE(9);
      if (lookahead == '[') ADVANCE(122);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(176);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(175);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(176);
      END_STATE();
    case 176:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '(') ADVANCE(82);
      if (lookahead == ')') ADVANCE(86);
      if (lookahead == '+') ADVANCE(102);
      if (lookahead == '-') ADVANCE(110);
      if (lookahead == '.') ADVANCE(9);
      if (lookahead == '[') ADVANCE(122);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(175);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(176);
      END_STATE();
    case 177:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '(') ADVANCE(83);
      if (lookahead == '+') ADVANCE(103);
      if (lookahead == '-') ADVANCE(111);
      if (lookahead == '.') ADVANCE(10);
      if (lookahead == '[') ADVANCE(123);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(178);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(177);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(178);
      END_STATE();
    case 178:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '(') ADVANCE(83);
      if (lookahead == '+') ADVANCE(103);
      if (lookahead == '-') ADVANCE(111);
      if (lookahead == '.') ADVANCE(10);
      if (lookahead == '[') ADVANCE(123);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(177);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(178);
      END_STATE();
    case 179:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ')') ADVANCE(88);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(179);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(179);
      END_STATE();
    case 180:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(188);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 181:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(189);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 182:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(186);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 183:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(180);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 184:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(71);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 185:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(75);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 186:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(185);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 187:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(184);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 188:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(182);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 189:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(191);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 190:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(183);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 191:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(187);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 192:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(192);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(192);
      END_STATE();
    case 193:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(193);
      END_STATE();
    case 194:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(77);
      if (lookahead == '+') ADVANCE(97);
      if (lookahead == '-') ADVANCE(105);
      if (lookahead == '.') ADVANCE(4);
      if (lookahead == '[') ADVANCE(117);
      if (lookahead == 'f') ADVANCE(138);
      if (lookahead == 'r') ADVANCE(131);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(141);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(194);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(141);
      END_STATE();
    case 195:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(78);
      if (lookahead == '+') ADVANCE(98);
      if (lookahead == '-') ADVANCE(106);
      if (lookahead == '.') ADVANCE(5);
      if (lookahead == '[') ADVANCE(118);
      if (lookahead == 'f') ADVANCE(152);
      if (lookahead == 'r') ADVANCE(145);
      if (lookahead == '}') ADVANCE(95);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(155);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(195);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(155);
      END_STATE();
    case 196:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '\n') ADVANCE(66);
      if (lookahead == '(') ADVANCE(79);
      if (lookahead == '+') ADVANCE(99);
      if (lookahead == '-') ADVANCE(107);
      if (lookahead == '.') ADVANCE(6);
      if (lookahead == ';') ADVANCE(62);
      if (lookahead == '[') ADVANCE(119);
      if (lookahead == 'f') ADVANCE(166);
      if (lookahead == 'r') ADVANCE(159);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(169);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(196);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(169);
      END_STATE();
    case 197:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '(') ADVANCE(80);
      if (lookahead == '+') ADVANCE(100);
      if (lookahead == '-') ADVANCE(108);
      if (lookahead == '.') ADVANCE(7);
      if (lookahead == '[') ADVANCE(120);
      if (lookahead == ']') ADVANCE(125);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(172);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(197);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(172);
      END_STATE();
    case 198:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '(') ADVANCE(81);
      if (lookahead == '+') ADVANCE(101);
      if (lookahead == '-') ADVANCE(109);
      if (lookahead == '.') ADVANCE(8);
      if (lookahead == ';') ADVANCE(63);
      if (lookahead == '[') ADVANCE(121);
      if (lookahead == ']') ADVANCE(126);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(174);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(198);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 199:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '(') ADVANCE(82);
      if (lookahead == ')') ADVANCE(86);
      if (lookahead == '+') ADVANCE(102);
      if (lookahead == '-') ADVANCE(110);
      if (lookahead == '.') ADVANCE(9);
      if (lookahead == '[') ADVANCE(122);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(176);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(199);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(176);
      END_STATE();
    case 200:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '(') ADVANCE(83);
      if (lookahead == '+') ADVANCE(103);
      if (lookahead == '-') ADVANCE(111);
      if (lookahead == '.') ADVANCE(10);
      if (lookahead == '[') ADVANCE(123);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(178);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(200);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(178);
      END_STATE();
    case 201:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(50);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(49);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(201);
      END_STATE();
    case 202:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(49);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(202);
      END_STATE();
    case 203:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(203);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 54},
  [2] = {.lex_state = 3},
  [3] = {.lex_state = 3},
  [4] = {.lex_state = 54},
  [5] = {.lex_state = 3},
  [6] = {.lex_state = 3},
  [7] = {.lex_state = 54},
  [8] = {.lex_state = 3},
  [9] = {.lex_state = 55},
  [10] = {.lex_state = 25},
  [11] = {.lex_state = 25},
  [12] = {.lex_state = 25},
  [13] = {.lex_state = 52},
  [14] = {.lex_state = 25},
  [15] = {.lex_state = 3},
  [16] = {.lex_state = 25},
  [17] = {.lex_state = 53},
  [18] = {.lex_state = 53},
  [19] = {.lex_state = 1},
  [20] = {.lex_state = 26},
  [21] = {.lex_state = 53},
  [22] = {.lex_state = 53},
  [23] = {.lex_state = 26},
  [24] = {.lex_state = 53},
  [25] = {.lex_state = 53},
  [26] = {.lex_state = 53},
  [27] = {.lex_state = 53},
  [28] = {.lex_state = 53},
  [29] = {.lex_state = 53},
  [30] = {.lex_state = 53},
  [31] = {.lex_state = 53},
  [32] = {.lex_state = 53},
  [33] = {.lex_state = 53},
  [34] = {.lex_state = 2},
  [35] = {.lex_state = 24},
  [36] = {.lex_state = 2},
  [37] = {.lex_state = 2},
  [38] = {.lex_state = 2},
  [39] = {.lex_state = 2},
  [40] = {.lex_state = 24},
  [41] = {.lex_state = 2},
  [42] = {.lex_state = 2},
  [43] = {.lex_state = 2},
  [44] = {.lex_state = 2},
  [45] = {.lex_state = 2},
  [46] = {.lex_state = 27},
  [47] = {.lex_state = 24},
  [48] = {.lex_state = 2},
  [49] = {.lex_state = 2},
  [50] = {.lex_state = 24},
  [51] = {.lex_state = 2},
  [52] = {.lex_state = 2},
  [53] = {.lex_state = 24},
  [54] = {.lex_state = 27},
  [55] = {.lex_state = 21},
  [56] = {.lex_state = 27},
  [57] = {.lex_state = 21},
  [58] = {.lex_state = 21},
  [59] = {.lex_state = 27},
  [60] = {.lex_state = 27},
  [61] = {.lex_state = 21},
  [62] = {.lex_state = 27},
  [63] = {.lex_state = 27},
  [64] = {.lex_state = 21},
  [65] = {.lex_state = 27},
  [66] = {.lex_state = 27},
  [67] = {.lex_state = 21},
  [68] = {.lex_state = 27},
  [69] = {.lex_state = 27},
  [70] = {.lex_state = 27},
  [71] = {.lex_state = 27},
  [72] = {.lex_state = 27},
  [73] = {.lex_state = 27},
  [74] = {.lex_state = 27},
  [75] = {.lex_state = 27},
  [76] = {.lex_state = 27},
  [77] = {.lex_state = 27},
  [78] = {.lex_state = 27},
  [79] = {.lex_state = 27},
  [80] = {.lex_state = 27},
  [81] = {.lex_state = 27},
  [82] = {.lex_state = 27},
  [83] = {.lex_state = 27},
  [84] = {.lex_state = 27},
  [85] = {.lex_state = 27},
  [86] = {.lex_state = 27},
  [87] = {.lex_state = 21},
  [88] = {.lex_state = 27},
  [89] = {.lex_state = 21},
  [90] = {.lex_state = 21},
  [91] = {.lex_state = 21},
  [92] = {.lex_state = 21},
  [93] = {.lex_state = 21},
  [94] = {.lex_state = 55},
  [95] = {.lex_state = 55},
  [96] = {.lex_state = 55},
  [97] = {.lex_state = 55},
  [98] = {.lex_state = 55},
  [99] = {.lex_state = 55},
  [100] = {.lex_state = 3},
  [101] = {.lex_state = 3},
  [102] = {.lex_state = 54},
  [103] = {.lex_state = 3},
  [104] = {.lex_state = 3},
  [105] = {.lex_state = 3},
  [106] = {.lex_state = 19},
  [107] = {.lex_state = 22},
  [108] = {.lex_state = 22},
  [109] = {.lex_state = 22},
  [110] = {.lex_state = 22},
  [111] = {.lex_state = 22},
  [112] = {.lex_state = 22},
  [113] = {.lex_state = 22},
  [114] = {.lex_state = 22},
  [115] = {.lex_state = 22},
  [116] = {.lex_state = 22},
  [117] = {.lex_state = 22},
  [118] = {.lex_state = 22},
  [119] = {.lex_state = 20},
  [120] = {.lex_state = 23},
  [121] = {.lex_state = 23},
  [122] = {.lex_state = 23},
  [123] = {.lex_state = 23},
  [124] = {.lex_state = 23},
  [125] = {.lex_state = 23},
  [126] = {.lex_state = 23},
  [127] = {.lex_state = 23},
  [128] = {.lex_state = 23},
  [129] = {.lex_state = 23},
  [130] = {.lex_state = 23},
  [131] = {.lex_state = 23},
  [132] = {.lex_state = 23},
  [133] = {.lex_state = 23},
  [134] = {.lex_state = 23},
  [135] = {.lex_state = 29},
  [136] = {.lex_state = 29},
  [137] = {.lex_state = 45},
  [138] = {.lex_state = 29},
  [139] = {.lex_state = 30},
  [140] = {.lex_state = 29},
  [141] = {.lex_state = 30},
  [142] = {.lex_state = 45},
  [143] = {.lex_state = 29},
  [144] = {.lex_state = 45},
  [145] = {.lex_state = 46},
  [146] = {.lex_state = 46},
  [147] = {.lex_state = 46},
  [148] = {.lex_state = 29},
  [149] = {.lex_state = 45},
  [150] = {.lex_state = 46},
  [151] = {.lex_state = 47},
  [152] = {.lex_state = 47},
  [153] = {.lex_state = 31},
  [154] = {.lex_state = 31},
  [155] = {.lex_state = 47},
  [156] = {.lex_state = 31},
  [157] = {.lex_state = 31},
  [158] = {.lex_state = 47},
  [159] = {.lex_state = 31},
  [160] = {.lex_state = 31},
  [161] = {.lex_state = 47},
  [162] = {.lex_state = 28},
  [163] = {.lex_state = 31},
  [164] = {.lex_state = 0},
  [165] = {.lex_state = 48},
  [166] = {.lex_state = 48},
  [167] = {.lex_state = 28},
  [168] = {.lex_state = 48},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_LF] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_return] = ACTIONS(1),
    [anon_sym_function] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_PLUS] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_STAR] = ACTIONS(1),
    [anon_sym_SLASH] = ACTIONS(1),
    [anon_sym_PERCENT] = ACTIONS(1),
    [anon_sym_CARET] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [sym_number] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(164),
    [sym_statement] = STATE(99),
    [sym_expression_statement] = STATE(97),
    [sym_assignment_statement] = STATE(97),
    [sym_return_statement] = STATE(97),
    [sym_function_definition] = STATE(97),
    [sym_expression] = STATE(30),
    [sym_binary_expression] = STATE(24),
    [sym_unary_expression] = STATE(24),
    [sym_call_expression] = STATE(24),
    [sym_matrix_literal] = STATE(24),
    [sym_parenthesized_expression] = STATE(24),
    [aux_sym_source_file_repeat1] = STATE(7),
    [ts_builtin_sym_end] = ACTIONS(3),
    [anon_sym_LF] = ACTIONS(5),
    [anon_sym_return] = ACTIONS(7),
    [anon_sym_function] = ACTIONS(9),
    [anon_sym_LPAREN] = ACTIONS(11),
    [anon_sym_PLUS] = ACTIONS(13),
    [anon_sym_DASH] = ACTIONS(13),
    [anon_sym_LBRACK] = ACTIONS(15),
    [sym_identifier] = ACTIONS(17),
    [sym_number] = ACTIONS(19),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 13,
    ACTIONS(21), 1,
      anon_sym_LF,
    ACTIONS(24), 1,
      anon_sym_return,
    ACTIONS(27), 1,
      anon_sym_function,
    ACTIONS(30), 1,
      anon_sym_LPAREN,
    ACTIONS(33), 1,
      anon_sym_RBRACE,
    ACTIONS(38), 1,
      anon_sym_LBRACK,
    ACTIONS(41), 1,
      sym_identifier,
    ACTIONS(44), 1,
      sym_number,
    STATE(43), 1,
      sym_expression,
    ACTIONS(35), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(2), 2,
      sym_statement,
      aux_sym_block_repeat1,
    STATE(100), 4,
      sym_expression_statement,
      sym_assignment_statement,
      sym_return_statement,
      sym_function_definition,
    STATE(36), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [49] = 13,
    ACTIONS(47), 1,
      anon_sym_LF,
    ACTIONS(49), 1,
      anon_sym_return,
    ACTIONS(51), 1,
      anon_sym_function,
    ACTIONS(53), 1,
      anon_sym_LPAREN,
    ACTIONS(55), 1,
      anon_sym_RBRACE,
    ACTIONS(59), 1,
      anon_sym_LBRACK,
    ACTIONS(61), 1,
      sym_identifier,
    ACTIONS(63), 1,
      sym_number,
    STATE(43), 1,
      sym_expression,
    ACTIONS(57), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(5), 2,
      sym_statement,
      aux_sym_block_repeat1,
    STATE(100), 4,
      sym_expression_statement,
      sym_assignment_statement,
      sym_return_statement,
      sym_function_definition,
    STATE(36), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [98] = 14,
    ACTIONS(65), 1,
      ts_builtin_sym_end,
    ACTIONS(67), 1,
      anon_sym_LF,
    ACTIONS(70), 1,
      anon_sym_return,
    ACTIONS(73), 1,
      anon_sym_function,
    ACTIONS(76), 1,
      anon_sym_LPAREN,
    ACTIONS(82), 1,
      anon_sym_LBRACK,
    ACTIONS(85), 1,
      sym_identifier,
    ACTIONS(88), 1,
      sym_number,
    STATE(4), 1,
      aux_sym_source_file_repeat1,
    STATE(30), 1,
      sym_expression,
    STATE(99), 1,
      sym_statement,
    ACTIONS(79), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(97), 4,
      sym_expression_statement,
      sym_assignment_statement,
      sym_return_statement,
      sym_function_definition,
    STATE(24), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [149] = 13,
    ACTIONS(49), 1,
      anon_sym_return,
    ACTIONS(51), 1,
      anon_sym_function,
    ACTIONS(53), 1,
      anon_sym_LPAREN,
    ACTIONS(59), 1,
      anon_sym_LBRACK,
    ACTIONS(61), 1,
      sym_identifier,
    ACTIONS(63), 1,
      sym_number,
    ACTIONS(91), 1,
      anon_sym_LF,
    ACTIONS(93), 1,
      anon_sym_RBRACE,
    STATE(43), 1,
      sym_expression,
    ACTIONS(57), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(2), 2,
      sym_statement,
      aux_sym_block_repeat1,
    STATE(100), 4,
      sym_expression_statement,
      sym_assignment_statement,
      sym_return_statement,
      sym_function_definition,
    STATE(36), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [198] = 13,
    ACTIONS(49), 1,
      anon_sym_return,
    ACTIONS(51), 1,
      anon_sym_function,
    ACTIONS(53), 1,
      anon_sym_LPAREN,
    ACTIONS(59), 1,
      anon_sym_LBRACK,
    ACTIONS(61), 1,
      sym_identifier,
    ACTIONS(63), 1,
      sym_number,
    ACTIONS(91), 1,
      anon_sym_LF,
    ACTIONS(95), 1,
      anon_sym_RBRACE,
    STATE(43), 1,
      sym_expression,
    ACTIONS(57), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(2), 2,
      sym_statement,
      aux_sym_block_repeat1,
    STATE(100), 4,
      sym_expression_statement,
      sym_assignment_statement,
      sym_return_statement,
      sym_function_definition,
    STATE(36), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [247] = 14,
    ACTIONS(7), 1,
      anon_sym_return,
    ACTIONS(9), 1,
      anon_sym_function,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(15), 1,
      anon_sym_LBRACK,
    ACTIONS(17), 1,
      sym_identifier,
    ACTIONS(19), 1,
      sym_number,
    ACTIONS(97), 1,
      ts_builtin_sym_end,
    ACTIONS(99), 1,
      anon_sym_LF,
    STATE(4), 1,
      aux_sym_source_file_repeat1,
    STATE(30), 1,
      sym_expression,
    STATE(99), 1,
      sym_statement,
    ACTIONS(13), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(97), 4,
      sym_expression_statement,
      sym_assignment_statement,
      sym_return_statement,
      sym_function_definition,
    STATE(24), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [298] = 13,
    ACTIONS(49), 1,
      anon_sym_return,
    ACTIONS(51), 1,
      anon_sym_function,
    ACTIONS(53), 1,
      anon_sym_LPAREN,
    ACTIONS(59), 1,
      anon_sym_LBRACK,
    ACTIONS(61), 1,
      sym_identifier,
    ACTIONS(63), 1,
      sym_number,
    ACTIONS(101), 1,
      anon_sym_LF,
    ACTIONS(103), 1,
      anon_sym_RBRACE,
    STATE(43), 1,
      sym_expression,
    ACTIONS(57), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(6), 2,
      sym_statement,
      aux_sym_block_repeat1,
    STATE(100), 4,
      sym_expression_statement,
      sym_assignment_statement,
      sym_return_statement,
      sym_function_definition,
    STATE(36), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [347] = 9,
    ACTIONS(105), 1,
      ts_builtin_sym_end,
    ACTIONS(109), 1,
      anon_sym_LPAREN,
    ACTIONS(115), 1,
      anon_sym_LBRACK,
    ACTIONS(118), 1,
      sym_identifier,
    ACTIONS(121), 1,
      sym_number,
    STATE(25), 1,
      sym_expression,
    ACTIONS(112), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(107), 4,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
    STATE(24), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [383] = 11,
    ACTIONS(124), 1,
      anon_sym_LPAREN,
    ACTIONS(128), 1,
      anon_sym_LBRACK,
    ACTIONS(130), 1,
      anon_sym_RBRACK,
    ACTIONS(132), 1,
      sym_identifier,
    ACTIONS(134), 1,
      sym_number,
    STATE(23), 1,
      aux_sym_matrix_row_repeat1,
    STATE(61), 1,
      sym_expression,
    STATE(137), 1,
      sym_matrix_row,
    STATE(151), 1,
      sym_matrix_content,
    ACTIONS(126), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(91), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [422] = 11,
    ACTIONS(124), 1,
      anon_sym_LPAREN,
    ACTIONS(128), 1,
      anon_sym_LBRACK,
    ACTIONS(132), 1,
      sym_identifier,
    ACTIONS(134), 1,
      sym_number,
    ACTIONS(136), 1,
      anon_sym_RBRACK,
    STATE(23), 1,
      aux_sym_matrix_row_repeat1,
    STATE(61), 1,
      sym_expression,
    STATE(137), 1,
      sym_matrix_row,
    STATE(161), 1,
      sym_matrix_content,
    ACTIONS(126), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(91), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [461] = 11,
    ACTIONS(124), 1,
      anon_sym_LPAREN,
    ACTIONS(128), 1,
      anon_sym_LBRACK,
    ACTIONS(132), 1,
      sym_identifier,
    ACTIONS(134), 1,
      sym_number,
    ACTIONS(138), 1,
      anon_sym_RBRACK,
    STATE(23), 1,
      aux_sym_matrix_row_repeat1,
    STATE(61), 1,
      sym_expression,
    STATE(137), 1,
      sym_matrix_row,
    STATE(155), 1,
      sym_matrix_content,
    ACTIONS(126), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(91), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [500] = 4,
    ACTIONS(140), 1,
      ts_builtin_sym_end,
    ACTIONS(144), 1,
      anon_sym_EQ,
    ACTIONS(146), 1,
      anon_sym_LPAREN,
    ACTIONS(142), 13,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [525] = 11,
    ACTIONS(124), 1,
      anon_sym_LPAREN,
    ACTIONS(128), 1,
      anon_sym_LBRACK,
    ACTIONS(132), 1,
      sym_identifier,
    ACTIONS(134), 1,
      sym_number,
    ACTIONS(149), 1,
      anon_sym_RBRACK,
    STATE(23), 1,
      aux_sym_matrix_row_repeat1,
    STATE(61), 1,
      sym_expression,
    STATE(137), 1,
      sym_matrix_row,
    STATE(152), 1,
      sym_matrix_content,
    ACTIONS(126), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(91), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [564] = 8,
    ACTIONS(151), 1,
      anon_sym_LPAREN,
    ACTIONS(157), 1,
      anon_sym_LBRACK,
    ACTIONS(160), 1,
      sym_identifier,
    ACTIONS(163), 1,
      sym_number,
    STATE(42), 1,
      sym_expression,
    ACTIONS(154), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(107), 4,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_RBRACE,
    STATE(36), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [597] = 11,
    ACTIONS(124), 1,
      anon_sym_LPAREN,
    ACTIONS(128), 1,
      anon_sym_LBRACK,
    ACTIONS(132), 1,
      sym_identifier,
    ACTIONS(134), 1,
      sym_number,
    ACTIONS(166), 1,
      anon_sym_RBRACK,
    STATE(23), 1,
      aux_sym_matrix_row_repeat1,
    STATE(61), 1,
      sym_expression,
    STATE(137), 1,
      sym_matrix_row,
    STATE(158), 1,
      sym_matrix_content,
    ACTIONS(126), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(91), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [636] = 2,
    ACTIONS(168), 1,
      ts_builtin_sym_end,
    ACTIONS(170), 14,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [656] = 2,
    ACTIONS(172), 1,
      ts_builtin_sym_end,
    ACTIONS(174), 14,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [676] = 3,
    ACTIONS(176), 1,
      anon_sym_EQ,
    ACTIONS(178), 1,
      anon_sym_LPAREN,
    ACTIONS(142), 13,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [698] = 9,
    ACTIONS(183), 1,
      anon_sym_LPAREN,
    ACTIONS(189), 1,
      anon_sym_LBRACK,
    ACTIONS(192), 1,
      sym_identifier,
    ACTIONS(195), 1,
      sym_number,
    STATE(20), 1,
      aux_sym_matrix_row_repeat1,
    STATE(61), 1,
      sym_expression,
    ACTIONS(181), 2,
      anon_sym_SEMI,
      anon_sym_RBRACK,
    ACTIONS(186), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(91), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [732] = 5,
    ACTIONS(198), 1,
      ts_builtin_sym_end,
    ACTIONS(206), 1,
      anon_sym_CARET,
    ACTIONS(202), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(204), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
    ACTIONS(200), 8,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [758] = 2,
    ACTIONS(208), 1,
      ts_builtin_sym_end,
    ACTIONS(210), 14,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [778] = 9,
    ACTIONS(124), 1,
      anon_sym_LPAREN,
    ACTIONS(128), 1,
      anon_sym_LBRACK,
    ACTIONS(132), 1,
      sym_identifier,
    ACTIONS(134), 1,
      sym_number,
    STATE(20), 1,
      aux_sym_matrix_row_repeat1,
    STATE(61), 1,
      sym_expression,
    ACTIONS(126), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(212), 2,
      anon_sym_SEMI,
      anon_sym_RBRACK,
    STATE(91), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [812] = 2,
    ACTIONS(140), 1,
      ts_builtin_sym_end,
    ACTIONS(142), 14,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [832] = 5,
    ACTIONS(206), 1,
      anon_sym_CARET,
    ACTIONS(214), 1,
      ts_builtin_sym_end,
    ACTIONS(202), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(204), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
    ACTIONS(216), 8,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [858] = 4,
    ACTIONS(206), 1,
      anon_sym_CARET,
    ACTIONS(218), 1,
      ts_builtin_sym_end,
    ACTIONS(204), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
    ACTIONS(220), 10,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [882] = 3,
    ACTIONS(206), 1,
      anon_sym_CARET,
    ACTIONS(218), 1,
      ts_builtin_sym_end,
    ACTIONS(220), 13,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [904] = 3,
    ACTIONS(206), 1,
      anon_sym_CARET,
    ACTIONS(218), 1,
      ts_builtin_sym_end,
    ACTIONS(220), 13,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [926] = 3,
    ACTIONS(140), 1,
      ts_builtin_sym_end,
    ACTIONS(146), 1,
      anon_sym_LPAREN,
    ACTIONS(142), 13,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [948] = 5,
    ACTIONS(206), 1,
      anon_sym_CARET,
    ACTIONS(222), 1,
      ts_builtin_sym_end,
    ACTIONS(202), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(204), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
    ACTIONS(224), 8,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [974] = 2,
    ACTIONS(226), 1,
      ts_builtin_sym_end,
    ACTIONS(228), 14,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [994] = 2,
    ACTIONS(230), 1,
      ts_builtin_sym_end,
    ACTIONS(232), 14,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [1014] = 2,
    ACTIONS(234), 1,
      ts_builtin_sym_end,
    ACTIONS(236), 14,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [1034] = 1,
    ACTIONS(236), 14,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [1051] = 9,
    ACTIONS(238), 1,
      anon_sym_LPAREN,
    ACTIONS(240), 1,
      anon_sym_RPAREN,
    ACTIONS(244), 1,
      anon_sym_LBRACK,
    ACTIONS(246), 1,
      sym_identifier,
    ACTIONS(248), 1,
      sym_number,
    STATE(107), 1,
      sym_expression,
    STATE(153), 1,
      sym_argument_list,
    ACTIONS(242), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(109), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [1084] = 1,
    ACTIONS(142), 14,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [1101] = 2,
    ACTIONS(178), 1,
      anon_sym_LPAREN,
    ACTIONS(142), 13,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [1120] = 4,
    ACTIONS(254), 1,
      anon_sym_CARET,
    ACTIONS(250), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(252), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
    ACTIONS(200), 8,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [1143] = 1,
    ACTIONS(170), 14,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [1160] = 9,
    ACTIONS(238), 1,
      anon_sym_LPAREN,
    ACTIONS(244), 1,
      anon_sym_LBRACK,
    ACTIONS(246), 1,
      sym_identifier,
    ACTIONS(248), 1,
      sym_number,
    ACTIONS(256), 1,
      anon_sym_RPAREN,
    STATE(107), 1,
      sym_expression,
    STATE(156), 1,
      sym_argument_list,
    ACTIONS(242), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(109), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [1193] = 1,
    ACTIONS(174), 14,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [1210] = 4,
    ACTIONS(254), 1,
      anon_sym_CARET,
    ACTIONS(250), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(252), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
    ACTIONS(216), 8,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [1233] = 4,
    ACTIONS(254), 1,
      anon_sym_CARET,
    ACTIONS(250), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(252), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
    ACTIONS(224), 8,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_RBRACE,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [1256] = 1,
    ACTIONS(232), 14,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [1273] = 1,
    ACTIONS(210), 14,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [1290] = 9,
    ACTIONS(124), 1,
      anon_sym_LPAREN,
    ACTIONS(128), 1,
      anon_sym_LBRACK,
    ACTIONS(132), 1,
      sym_identifier,
    ACTIONS(134), 1,
      sym_number,
    STATE(23), 1,
      aux_sym_matrix_row_repeat1,
    STATE(61), 1,
      sym_expression,
    STATE(149), 1,
      sym_matrix_row,
    ACTIONS(126), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(91), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [1323] = 9,
    ACTIONS(238), 1,
      anon_sym_LPAREN,
    ACTIONS(244), 1,
      anon_sym_LBRACK,
    ACTIONS(246), 1,
      sym_identifier,
    ACTIONS(248), 1,
      sym_number,
    ACTIONS(258), 1,
      anon_sym_RPAREN,
    STATE(107), 1,
      sym_expression,
    STATE(160), 1,
      sym_argument_list,
    ACTIONS(242), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(109), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [1356] = 3,
    ACTIONS(254), 1,
      anon_sym_CARET,
    ACTIONS(252), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
    ACTIONS(220), 10,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [1377] = 2,
    ACTIONS(254), 1,
      anon_sym_CARET,
    ACTIONS(220), 13,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [1396] = 9,
    ACTIONS(238), 1,
      anon_sym_LPAREN,
    ACTIONS(244), 1,
      anon_sym_LBRACK,
    ACTIONS(246), 1,
      sym_identifier,
    ACTIONS(248), 1,
      sym_number,
    ACTIONS(260), 1,
      anon_sym_RPAREN,
    STATE(107), 1,
      sym_expression,
    STATE(154), 1,
      sym_argument_list,
    ACTIONS(242), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(109), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [1429] = 2,
    ACTIONS(254), 1,
      anon_sym_CARET,
    ACTIONS(220), 13,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [1448] = 1,
    ACTIONS(228), 14,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [1465] = 9,
    ACTIONS(238), 1,
      anon_sym_LPAREN,
    ACTIONS(244), 1,
      anon_sym_LBRACK,
    ACTIONS(246), 1,
      sym_identifier,
    ACTIONS(248), 1,
      sym_number,
    ACTIONS(262), 1,
      anon_sym_RPAREN,
    STATE(107), 1,
      sym_expression,
    STATE(159), 1,
      sym_argument_list,
    ACTIONS(242), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(109), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [1498] = 7,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(15), 1,
      anon_sym_LBRACK,
    ACTIONS(19), 1,
      sym_number,
    ACTIONS(264), 1,
      sym_identifier,
    STATE(17), 1,
      sym_expression,
    ACTIONS(13), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(24), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [1525] = 2,
    ACTIONS(266), 1,
      anon_sym_CARET,
    ACTIONS(220), 11,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      sym_identifier,
      sym_number,
  [1542] = 7,
    ACTIONS(238), 1,
      anon_sym_LPAREN,
    ACTIONS(244), 1,
      anon_sym_LBRACK,
    ACTIONS(246), 1,
      sym_identifier,
    ACTIONS(248), 1,
      sym_number,
    STATE(110), 1,
      sym_expression,
    ACTIONS(242), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(109), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [1569] = 1,
    ACTIONS(236), 12,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      sym_identifier,
      sym_number,
  [1584] = 1,
    ACTIONS(232), 12,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      sym_identifier,
      sym_number,
  [1599] = 7,
    ACTIONS(124), 1,
      anon_sym_LPAREN,
    ACTIONS(128), 1,
      anon_sym_LBRACK,
    ACTIONS(132), 1,
      sym_identifier,
    ACTIONS(134), 1,
      sym_number,
    STATE(55), 1,
      sym_expression,
    ACTIONS(126), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(91), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [1626] = 7,
    ACTIONS(268), 1,
      anon_sym_LPAREN,
    ACTIONS(272), 1,
      anon_sym_LBRACK,
    ACTIONS(274), 1,
      sym_identifier,
    ACTIONS(276), 1,
      sym_number,
    STATE(125), 1,
      sym_expression,
    ACTIONS(270), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(129), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [1653] = 4,
    ACTIONS(266), 1,
      anon_sym_CARET,
    ACTIONS(280), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(282), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
    ACTIONS(278), 6,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      sym_identifier,
      sym_number,
  [1674] = 7,
    ACTIONS(238), 1,
      anon_sym_LPAREN,
    ACTIONS(244), 1,
      anon_sym_LBRACK,
    ACTIONS(246), 1,
      sym_identifier,
    ACTIONS(248), 1,
      sym_number,
    STATE(111), 1,
      sym_expression,
    ACTIONS(242), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(109), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [1701] = 7,
    ACTIONS(124), 1,
      anon_sym_LPAREN,
    ACTIONS(128), 1,
      anon_sym_LBRACK,
    ACTIONS(132), 1,
      sym_identifier,
    ACTIONS(134), 1,
      sym_number,
    STATE(89), 1,
      sym_expression,
    ACTIONS(126), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(91), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [1728] = 1,
    ACTIONS(210), 12,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      sym_identifier,
      sym_number,
  [1743] = 7,
    ACTIONS(53), 1,
      anon_sym_LPAREN,
    ACTIONS(59), 1,
      anon_sym_LBRACK,
    ACTIONS(63), 1,
      sym_number,
    ACTIONS(284), 1,
      sym_identifier,
    STATE(39), 1,
      sym_expression,
    ACTIONS(57), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(36), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [1770] = 7,
    ACTIONS(124), 1,
      anon_sym_LPAREN,
    ACTIONS(128), 1,
      anon_sym_LBRACK,
    ACTIONS(132), 1,
      sym_identifier,
    ACTIONS(134), 1,
      sym_number,
    STATE(90), 1,
      sym_expression,
    ACTIONS(126), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(91), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [1797] = 1,
    ACTIONS(174), 12,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      sym_identifier,
      sym_number,
  [1812] = 7,
    ACTIONS(268), 1,
      anon_sym_LPAREN,
    ACTIONS(272), 1,
      anon_sym_LBRACK,
    ACTIONS(274), 1,
      sym_identifier,
    ACTIONS(276), 1,
      sym_number,
    STATE(128), 1,
      sym_expression,
    ACTIONS(270), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(129), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [1839] = 7,
    ACTIONS(268), 1,
      anon_sym_LPAREN,
    ACTIONS(272), 1,
      anon_sym_LBRACK,
    ACTIONS(274), 1,
      sym_identifier,
    ACTIONS(276), 1,
      sym_number,
    STATE(134), 1,
      sym_expression,
    ACTIONS(270), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(129), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [1866] = 7,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(15), 1,
      anon_sym_LBRACK,
    ACTIONS(19), 1,
      sym_number,
    ACTIONS(264), 1,
      sym_identifier,
    STATE(28), 1,
      sym_expression,
    ACTIONS(13), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(24), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [1893] = 7,
    ACTIONS(53), 1,
      anon_sym_LPAREN,
    ACTIONS(59), 1,
      anon_sym_LBRACK,
    ACTIONS(63), 1,
      sym_number,
    ACTIONS(284), 1,
      sym_identifier,
    STATE(51), 1,
      sym_expression,
    ACTIONS(57), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(36), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [1920] = 7,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(15), 1,
      anon_sym_LBRACK,
    ACTIONS(19), 1,
      sym_number,
    ACTIONS(264), 1,
      sym_identifier,
    STATE(27), 1,
      sym_expression,
    ACTIONS(13), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(24), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [1947] = 7,
    ACTIONS(53), 1,
      anon_sym_LPAREN,
    ACTIONS(59), 1,
      anon_sym_LBRACK,
    ACTIONS(63), 1,
      sym_number,
    ACTIONS(284), 1,
      sym_identifier,
    STATE(49), 1,
      sym_expression,
    ACTIONS(57), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(36), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [1974] = 7,
    ACTIONS(53), 1,
      anon_sym_LPAREN,
    ACTIONS(59), 1,
      anon_sym_LBRACK,
    ACTIONS(63), 1,
      sym_number,
    ACTIONS(284), 1,
      sym_identifier,
    STATE(48), 1,
      sym_expression,
    ACTIONS(57), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(36), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [2001] = 7,
    ACTIONS(53), 1,
      anon_sym_LPAREN,
    ACTIONS(59), 1,
      anon_sym_LBRACK,
    ACTIONS(63), 1,
      sym_number,
    ACTIONS(284), 1,
      sym_identifier,
    STATE(38), 1,
      sym_expression,
    ACTIONS(57), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(36), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [2028] = 7,
    ACTIONS(268), 1,
      anon_sym_LPAREN,
    ACTIONS(272), 1,
      anon_sym_LBRACK,
    ACTIONS(274), 1,
      sym_identifier,
    ACTIONS(276), 1,
      sym_number,
    STATE(120), 1,
      sym_expression,
    ACTIONS(270), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(129), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [2055] = 7,
    ACTIONS(268), 1,
      anon_sym_LPAREN,
    ACTIONS(272), 1,
      anon_sym_LBRACK,
    ACTIONS(274), 1,
      sym_identifier,
    ACTIONS(276), 1,
      sym_number,
    STATE(126), 1,
      sym_expression,
    ACTIONS(270), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(129), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [2082] = 7,
    ACTIONS(268), 1,
      anon_sym_LPAREN,
    ACTIONS(272), 1,
      anon_sym_LBRACK,
    ACTIONS(274), 1,
      sym_identifier,
    ACTIONS(276), 1,
      sym_number,
    STATE(131), 1,
      sym_expression,
    ACTIONS(270), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(129), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [2109] = 7,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(15), 1,
      anon_sym_LBRACK,
    ACTIONS(19), 1,
      sym_number,
    ACTIONS(264), 1,
      sym_identifier,
    STATE(26), 1,
      sym_expression,
    ACTIONS(13), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(24), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [2136] = 7,
    ACTIONS(268), 1,
      anon_sym_LPAREN,
    ACTIONS(272), 1,
      anon_sym_LBRACK,
    ACTIONS(274), 1,
      sym_identifier,
    ACTIONS(276), 1,
      sym_number,
    STATE(127), 1,
      sym_expression,
    ACTIONS(270), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(129), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [2163] = 7,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(15), 1,
      anon_sym_LBRACK,
    ACTIONS(19), 1,
      sym_number,
    ACTIONS(264), 1,
      sym_identifier,
    STATE(21), 1,
      sym_expression,
    ACTIONS(13), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(24), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [2190] = 7,
    ACTIONS(268), 1,
      anon_sym_LPAREN,
    ACTIONS(272), 1,
      anon_sym_LBRACK,
    ACTIONS(274), 1,
      sym_identifier,
    ACTIONS(276), 1,
      sym_number,
    STATE(132), 1,
      sym_expression,
    ACTIONS(270), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(129), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [2217] = 7,
    ACTIONS(268), 1,
      anon_sym_LPAREN,
    ACTIONS(272), 1,
      anon_sym_LBRACK,
    ACTIONS(274), 1,
      sym_identifier,
    ACTIONS(276), 1,
      sym_number,
    STATE(130), 1,
      sym_expression,
    ACTIONS(270), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(129), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [2244] = 7,
    ACTIONS(238), 1,
      anon_sym_LPAREN,
    ACTIONS(244), 1,
      anon_sym_LBRACK,
    ACTIONS(246), 1,
      sym_identifier,
    ACTIONS(248), 1,
      sym_number,
    STATE(108), 1,
      sym_expression,
    ACTIONS(242), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(109), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [2271] = 7,
    ACTIONS(238), 1,
      anon_sym_LPAREN,
    ACTIONS(244), 1,
      anon_sym_LBRACK,
    ACTIONS(246), 1,
      sym_identifier,
    ACTIONS(248), 1,
      sym_number,
    STATE(116), 1,
      sym_expression,
    ACTIONS(242), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(109), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [2298] = 7,
    ACTIONS(238), 1,
      anon_sym_LPAREN,
    ACTIONS(244), 1,
      anon_sym_LBRACK,
    ACTIONS(246), 1,
      sym_identifier,
    ACTIONS(248), 1,
      sym_number,
    STATE(115), 1,
      sym_expression,
    ACTIONS(242), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(109), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [2325] = 1,
    ACTIONS(228), 12,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      sym_identifier,
      sym_number,
  [2340] = 7,
    ACTIONS(124), 1,
      anon_sym_LPAREN,
    ACTIONS(128), 1,
      anon_sym_LBRACK,
    ACTIONS(132), 1,
      sym_identifier,
    ACTIONS(134), 1,
      sym_number,
    STATE(93), 1,
      sym_expression,
    ACTIONS(126), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    STATE(91), 5,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_matrix_literal,
      sym_parenthesized_expression,
  [2367] = 2,
    ACTIONS(266), 1,
      anon_sym_CARET,
    ACTIONS(220), 11,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      sym_identifier,
      sym_number,
  [2384] = 3,
    ACTIONS(266), 1,
      anon_sym_CARET,
    ACTIONS(282), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
    ACTIONS(220), 8,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      sym_identifier,
      sym_number,
  [2403] = 1,
    ACTIONS(142), 12,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      sym_identifier,
      sym_number,
  [2418] = 2,
    ACTIONS(286), 1,
      anon_sym_LPAREN,
    ACTIONS(142), 11,
      anon_sym_SEMI,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      sym_identifier,
      sym_number,
  [2435] = 1,
    ACTIONS(170), 12,
      anon_sym_SEMI,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
      sym_identifier,
      sym_number,
  [2450] = 2,
    ACTIONS(289), 1,
      ts_builtin_sym_end,
    ACTIONS(291), 10,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [2466] = 2,
    ACTIONS(293), 1,
      ts_builtin_sym_end,
    ACTIONS(295), 10,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [2482] = 2,
    ACTIONS(297), 1,
      ts_builtin_sym_end,
    ACTIONS(299), 10,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [2498] = 2,
    ACTIONS(301), 1,
      ts_builtin_sym_end,
    ACTIONS(303), 10,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [2514] = 2,
    ACTIONS(305), 1,
      ts_builtin_sym_end,
    ACTIONS(307), 10,
      anon_sym_SEMI,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [2530] = 4,
    ACTIONS(309), 1,
      ts_builtin_sym_end,
    ACTIONS(311), 1,
      anon_sym_SEMI,
    ACTIONS(313), 1,
      anon_sym_LF,
    ACTIONS(316), 8,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [2550] = 1,
    ACTIONS(303), 10,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [2563] = 1,
    ACTIONS(307), 10,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [2576] = 2,
    ACTIONS(65), 1,
      ts_builtin_sym_end,
    ACTIONS(318), 9,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [2591] = 1,
    ACTIONS(295), 10,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [2604] = 1,
    ACTIONS(299), 10,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [2617] = 1,
    ACTIONS(291), 10,
      anon_sym_LF,
      anon_sym_return,
      anon_sym_function,
      anon_sym_LPAREN,
      anon_sym_RBRACE,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_LBRACK,
      sym_identifier,
      sym_number,
  [2630] = 2,
    ACTIONS(320), 1,
      anon_sym_LPAREN,
    ACTIONS(142), 8,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
  [2644] = 6,
    ACTIONS(322), 1,
      anon_sym_RPAREN,
    ACTIONS(324), 1,
      anon_sym_COMMA,
    ACTIONS(330), 1,
      anon_sym_CARET,
    STATE(140), 1,
      aux_sym_argument_list_repeat1,
    ACTIONS(326), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(328), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [2666] = 2,
    ACTIONS(330), 1,
      anon_sym_CARET,
    ACTIONS(220), 7,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [2679] = 1,
    ACTIONS(142), 8,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
  [2690] = 4,
    ACTIONS(330), 1,
      anon_sym_CARET,
    ACTIONS(326), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(332), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
    ACTIONS(328), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [2707] = 1,
    ACTIONS(170), 8,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
  [2718] = 1,
    ACTIONS(232), 8,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
  [2729] = 1,
    ACTIONS(236), 8,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
  [2740] = 1,
    ACTIONS(210), 8,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
  [2751] = 3,
    ACTIONS(330), 1,
      anon_sym_CARET,
    ACTIONS(328), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
    ACTIONS(220), 4,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_PLUS,
      anon_sym_DASH,
  [2766] = 2,
    ACTIONS(330), 1,
      anon_sym_CARET,
    ACTIONS(220), 7,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [2779] = 1,
    ACTIONS(174), 8,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
  [2790] = 1,
    ACTIONS(228), 8,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
  [2801] = 2,
    ACTIONS(334), 1,
      anon_sym_LPAREN,
    ACTIONS(142), 7,
      anon_sym_RPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
  [2814] = 3,
    ACTIONS(338), 1,
      anon_sym_CARET,
    ACTIONS(220), 3,
      anon_sym_RPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(336), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [2828] = 1,
    ACTIONS(210), 7,
      anon_sym_RPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
  [2838] = 1,
    ACTIONS(236), 7,
      anon_sym_RPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
  [2848] = 1,
    ACTIONS(232), 7,
      anon_sym_RPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
  [2858] = 1,
    ACTIONS(174), 7,
      anon_sym_RPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
  [2868] = 1,
    ACTIONS(170), 7,
      anon_sym_RPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
  [2878] = 2,
    ACTIONS(338), 1,
      anon_sym_CARET,
    ACTIONS(220), 6,
      anon_sym_RPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [2890] = 4,
    ACTIONS(338), 1,
      anon_sym_CARET,
    ACTIONS(340), 1,
      anon_sym_RPAREN,
    ACTIONS(342), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(336), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [2906] = 4,
    ACTIONS(338), 1,
      anon_sym_CARET,
    ACTIONS(344), 1,
      anon_sym_RPAREN,
    ACTIONS(342), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(336), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [2922] = 1,
    ACTIONS(142), 7,
      anon_sym_RPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
  [2932] = 4,
    ACTIONS(338), 1,
      anon_sym_CARET,
    ACTIONS(346), 1,
      anon_sym_RPAREN,
    ACTIONS(342), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(336), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [2948] = 2,
    ACTIONS(338), 1,
      anon_sym_CARET,
    ACTIONS(220), 6,
      anon_sym_RPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [2960] = 4,
    ACTIONS(338), 1,
      anon_sym_CARET,
    ACTIONS(348), 1,
      anon_sym_RPAREN,
    ACTIONS(342), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(336), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [2976] = 1,
    ACTIONS(228), 7,
      anon_sym_RPAREN,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_CARET,
  [2986] = 4,
    ACTIONS(338), 1,
      anon_sym_CARET,
    ACTIONS(350), 1,
      anon_sym_RPAREN,
    ACTIONS(342), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(336), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [3002] = 3,
    ACTIONS(352), 1,
      anon_sym_RPAREN,
    ACTIONS(354), 1,
      anon_sym_COMMA,
    STATE(138), 1,
      aux_sym_parameter_list_repeat1,
  [3012] = 3,
    ACTIONS(332), 1,
      anon_sym_RPAREN,
    ACTIONS(356), 1,
      anon_sym_COMMA,
    STATE(136), 1,
      aux_sym_argument_list_repeat1,
  [3022] = 3,
    ACTIONS(359), 1,
      anon_sym_SEMI,
    ACTIONS(361), 1,
      anon_sym_RBRACK,
    STATE(142), 1,
      aux_sym_matrix_content_repeat1,
  [3032] = 3,
    ACTIONS(354), 1,
      anon_sym_COMMA,
    ACTIONS(363), 1,
      anon_sym_RPAREN,
    STATE(143), 1,
      aux_sym_parameter_list_repeat1,
  [3042] = 3,
    ACTIONS(365), 1,
      anon_sym_RPAREN,
    ACTIONS(367), 1,
      sym_identifier,
    STATE(157), 1,
      sym_parameter_list,
  [3052] = 3,
    ACTIONS(324), 1,
      anon_sym_COMMA,
    ACTIONS(369), 1,
      anon_sym_RPAREN,
    STATE(136), 1,
      aux_sym_argument_list_repeat1,
  [3062] = 3,
    ACTIONS(367), 1,
      sym_identifier,
    ACTIONS(371), 1,
      anon_sym_RPAREN,
    STATE(163), 1,
      sym_parameter_list,
  [3072] = 3,
    ACTIONS(359), 1,
      anon_sym_SEMI,
    ACTIONS(373), 1,
      anon_sym_RBRACK,
    STATE(144), 1,
      aux_sym_matrix_content_repeat1,
  [3082] = 3,
    ACTIONS(375), 1,
      anon_sym_RPAREN,
    ACTIONS(377), 1,
      anon_sym_COMMA,
    STATE(143), 1,
      aux_sym_parameter_list_repeat1,
  [3092] = 3,
    ACTIONS(380), 1,
      anon_sym_SEMI,
    ACTIONS(383), 1,
      anon_sym_RBRACK,
    STATE(144), 1,
      aux_sym_matrix_content_repeat1,
  [3102] = 2,
    ACTIONS(385), 1,
      anon_sym_LBRACE,
    STATE(95), 1,
      sym_block,
  [3109] = 2,
    ACTIONS(387), 1,
      anon_sym_LBRACE,
    STATE(101), 1,
      sym_block,
  [3116] = 2,
    ACTIONS(387), 1,
      anon_sym_LBRACE,
    STATE(103), 1,
      sym_block,
  [3123] = 1,
    ACTIONS(375), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [3128] = 1,
    ACTIONS(383), 2,
      anon_sym_SEMI,
      anon_sym_RBRACK,
  [3133] = 2,
    ACTIONS(385), 1,
      anon_sym_LBRACE,
    STATE(98), 1,
      sym_block,
  [3140] = 1,
    ACTIONS(389), 1,
      anon_sym_RBRACK,
  [3144] = 1,
    ACTIONS(391), 1,
      anon_sym_RBRACK,
  [3148] = 1,
    ACTIONS(393), 1,
      anon_sym_RPAREN,
  [3152] = 1,
    ACTIONS(395), 1,
      anon_sym_RPAREN,
  [3156] = 1,
    ACTIONS(397), 1,
      anon_sym_RBRACK,
  [3160] = 1,
    ACTIONS(399), 1,
      anon_sym_RPAREN,
  [3164] = 1,
    ACTIONS(401), 1,
      anon_sym_RPAREN,
  [3168] = 1,
    ACTIONS(403), 1,
      anon_sym_RBRACK,
  [3172] = 1,
    ACTIONS(405), 1,
      anon_sym_RPAREN,
  [3176] = 1,
    ACTIONS(407), 1,
      anon_sym_RPAREN,
  [3180] = 1,
    ACTIONS(409), 1,
      anon_sym_RBRACK,
  [3184] = 1,
    ACTIONS(411), 1,
      anon_sym_LPAREN,
  [3188] = 1,
    ACTIONS(413), 1,
      anon_sym_RPAREN,
  [3192] = 1,
    ACTIONS(415), 1,
      ts_builtin_sym_end,
  [3196] = 1,
    ACTIONS(417), 1,
      sym_identifier,
  [3200] = 1,
    ACTIONS(419), 1,
      sym_identifier,
  [3204] = 1,
    ACTIONS(421), 1,
      anon_sym_LPAREN,
  [3208] = 1,
    ACTIONS(423), 1,
      sym_identifier,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 49,
  [SMALL_STATE(4)] = 98,
  [SMALL_STATE(5)] = 149,
  [SMALL_STATE(6)] = 198,
  [SMALL_STATE(7)] = 247,
  [SMALL_STATE(8)] = 298,
  [SMALL_STATE(9)] = 347,
  [SMALL_STATE(10)] = 383,
  [SMALL_STATE(11)] = 422,
  [SMALL_STATE(12)] = 461,
  [SMALL_STATE(13)] = 500,
  [SMALL_STATE(14)] = 525,
  [SMALL_STATE(15)] = 564,
  [SMALL_STATE(16)] = 597,
  [SMALL_STATE(17)] = 636,
  [SMALL_STATE(18)] = 656,
  [SMALL_STATE(19)] = 676,
  [SMALL_STATE(20)] = 698,
  [SMALL_STATE(21)] = 732,
  [SMALL_STATE(22)] = 758,
  [SMALL_STATE(23)] = 778,
  [SMALL_STATE(24)] = 812,
  [SMALL_STATE(25)] = 832,
  [SMALL_STATE(26)] = 858,
  [SMALL_STATE(27)] = 882,
  [SMALL_STATE(28)] = 904,
  [SMALL_STATE(29)] = 926,
  [SMALL_STATE(30)] = 948,
  [SMALL_STATE(31)] = 974,
  [SMALL_STATE(32)] = 994,
  [SMALL_STATE(33)] = 1014,
  [SMALL_STATE(34)] = 1034,
  [SMALL_STATE(35)] = 1051,
  [SMALL_STATE(36)] = 1084,
  [SMALL_STATE(37)] = 1101,
  [SMALL_STATE(38)] = 1120,
  [SMALL_STATE(39)] = 1143,
  [SMALL_STATE(40)] = 1160,
  [SMALL_STATE(41)] = 1193,
  [SMALL_STATE(42)] = 1210,
  [SMALL_STATE(43)] = 1233,
  [SMALL_STATE(44)] = 1256,
  [SMALL_STATE(45)] = 1273,
  [SMALL_STATE(46)] = 1290,
  [SMALL_STATE(47)] = 1323,
  [SMALL_STATE(48)] = 1356,
  [SMALL_STATE(49)] = 1377,
  [SMALL_STATE(50)] = 1396,
  [SMALL_STATE(51)] = 1429,
  [SMALL_STATE(52)] = 1448,
  [SMALL_STATE(53)] = 1465,
  [SMALL_STATE(54)] = 1498,
  [SMALL_STATE(55)] = 1525,
  [SMALL_STATE(56)] = 1542,
  [SMALL_STATE(57)] = 1569,
  [SMALL_STATE(58)] = 1584,
  [SMALL_STATE(59)] = 1599,
  [SMALL_STATE(60)] = 1626,
  [SMALL_STATE(61)] = 1653,
  [SMALL_STATE(62)] = 1674,
  [SMALL_STATE(63)] = 1701,
  [SMALL_STATE(64)] = 1728,
  [SMALL_STATE(65)] = 1743,
  [SMALL_STATE(66)] = 1770,
  [SMALL_STATE(67)] = 1797,
  [SMALL_STATE(68)] = 1812,
  [SMALL_STATE(69)] = 1839,
  [SMALL_STATE(70)] = 1866,
  [SMALL_STATE(71)] = 1893,
  [SMALL_STATE(72)] = 1920,
  [SMALL_STATE(73)] = 1947,
  [SMALL_STATE(74)] = 1974,
  [SMALL_STATE(75)] = 2001,
  [SMALL_STATE(76)] = 2028,
  [SMALL_STATE(77)] = 2055,
  [SMALL_STATE(78)] = 2082,
  [SMALL_STATE(79)] = 2109,
  [SMALL_STATE(80)] = 2136,
  [SMALL_STATE(81)] = 2163,
  [SMALL_STATE(82)] = 2190,
  [SMALL_STATE(83)] = 2217,
  [SMALL_STATE(84)] = 2244,
  [SMALL_STATE(85)] = 2271,
  [SMALL_STATE(86)] = 2298,
  [SMALL_STATE(87)] = 2325,
  [SMALL_STATE(88)] = 2340,
  [SMALL_STATE(89)] = 2367,
  [SMALL_STATE(90)] = 2384,
  [SMALL_STATE(91)] = 2403,
  [SMALL_STATE(92)] = 2418,
  [SMALL_STATE(93)] = 2435,
  [SMALL_STATE(94)] = 2450,
  [SMALL_STATE(95)] = 2466,
  [SMALL_STATE(96)] = 2482,
  [SMALL_STATE(97)] = 2498,
  [SMALL_STATE(98)] = 2514,
  [SMALL_STATE(99)] = 2530,
  [SMALL_STATE(100)] = 2550,
  [SMALL_STATE(101)] = 2563,
  [SMALL_STATE(102)] = 2576,
  [SMALL_STATE(103)] = 2591,
  [SMALL_STATE(104)] = 2604,
  [SMALL_STATE(105)] = 2617,
  [SMALL_STATE(106)] = 2630,
  [SMALL_STATE(107)] = 2644,
  [SMALL_STATE(108)] = 2666,
  [SMALL_STATE(109)] = 2679,
  [SMALL_STATE(110)] = 2690,
  [SMALL_STATE(111)] = 2707,
  [SMALL_STATE(112)] = 2718,
  [SMALL_STATE(113)] = 2729,
  [SMALL_STATE(114)] = 2740,
  [SMALL_STATE(115)] = 2751,
  [SMALL_STATE(116)] = 2766,
  [SMALL_STATE(117)] = 2779,
  [SMALL_STATE(118)] = 2790,
  [SMALL_STATE(119)] = 2801,
  [SMALL_STATE(120)] = 2814,
  [SMALL_STATE(121)] = 2828,
  [SMALL_STATE(122)] = 2838,
  [SMALL_STATE(123)] = 2848,
  [SMALL_STATE(124)] = 2858,
  [SMALL_STATE(125)] = 2868,
  [SMALL_STATE(126)] = 2878,
  [SMALL_STATE(127)] = 2890,
  [SMALL_STATE(128)] = 2906,
  [SMALL_STATE(129)] = 2922,
  [SMALL_STATE(130)] = 2932,
  [SMALL_STATE(131)] = 2948,
  [SMALL_STATE(132)] = 2960,
  [SMALL_STATE(133)] = 2976,
  [SMALL_STATE(134)] = 2986,
  [SMALL_STATE(135)] = 3002,
  [SMALL_STATE(136)] = 3012,
  [SMALL_STATE(137)] = 3022,
  [SMALL_STATE(138)] = 3032,
  [SMALL_STATE(139)] = 3042,
  [SMALL_STATE(140)] = 3052,
  [SMALL_STATE(141)] = 3062,
  [SMALL_STATE(142)] = 3072,
  [SMALL_STATE(143)] = 3082,
  [SMALL_STATE(144)] = 3092,
  [SMALL_STATE(145)] = 3102,
  [SMALL_STATE(146)] = 3109,
  [SMALL_STATE(147)] = 3116,
  [SMALL_STATE(148)] = 3123,
  [SMALL_STATE(149)] = 3128,
  [SMALL_STATE(150)] = 3133,
  [SMALL_STATE(151)] = 3140,
  [SMALL_STATE(152)] = 3144,
  [SMALL_STATE(153)] = 3148,
  [SMALL_STATE(154)] = 3152,
  [SMALL_STATE(155)] = 3156,
  [SMALL_STATE(156)] = 3160,
  [SMALL_STATE(157)] = 3164,
  [SMALL_STATE(158)] = 3168,
  [SMALL_STATE(159)] = 3172,
  [SMALL_STATE(160)] = 3176,
  [SMALL_STATE(161)] = 3180,
  [SMALL_STATE(162)] = 3184,
  [SMALL_STATE(163)] = 3188,
  [SMALL_STATE(164)] = 3192,
  [SMALL_STATE(165)] = 3196,
  [SMALL_STATE(166)] = 3200,
  [SMALL_STATE(167)] = 3204,
  [SMALL_STATE(168)] = 3208,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [5] = {.entry = {.count = 1, .reusable = false}}, SHIFT(7),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(165),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(68),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(54),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(12),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(13),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(24),
  [21] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_repeat1, 2), SHIFT_REPEAT(2),
  [24] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_repeat1, 2), SHIFT_REPEAT(15),
  [27] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_repeat1, 2), SHIFT_REPEAT(168),
  [30] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_repeat1, 2), SHIFT_REPEAT(83),
  [33] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_block_repeat1, 2),
  [35] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_repeat1, 2), SHIFT_REPEAT(65),
  [38] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_repeat1, 2), SHIFT_REPEAT(16),
  [41] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_repeat1, 2), SHIFT_REPEAT(19),
  [44] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_repeat1, 2), SHIFT_REPEAT(36),
  [47] = {.entry = {.count = 1, .reusable = false}}, SHIFT(5),
  [49] = {.entry = {.count = 1, .reusable = false}}, SHIFT(15),
  [51] = {.entry = {.count = 1, .reusable = false}}, SHIFT(168),
  [53] = {.entry = {.count = 1, .reusable = false}}, SHIFT(83),
  [55] = {.entry = {.count = 1, .reusable = false}}, SHIFT(104),
  [57] = {.entry = {.count = 1, .reusable = false}}, SHIFT(65),
  [59] = {.entry = {.count = 1, .reusable = false}}, SHIFT(16),
  [61] = {.entry = {.count = 1, .reusable = false}}, SHIFT(19),
  [63] = {.entry = {.count = 1, .reusable = false}}, SHIFT(36),
  [65] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [67] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(4),
  [70] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(9),
  [73] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(165),
  [76] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(68),
  [79] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(54),
  [82] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(12),
  [85] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(13),
  [88] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(24),
  [91] = {.entry = {.count = 1, .reusable = false}}, SHIFT(2),
  [93] = {.entry = {.count = 1, .reusable = false}}, SHIFT(105),
  [95] = {.entry = {.count = 1, .reusable = false}}, SHIFT(94),
  [97] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [99] = {.entry = {.count = 1, .reusable = false}}, SHIFT(4),
  [101] = {.entry = {.count = 1, .reusable = false}}, SHIFT(6),
  [103] = {.entry = {.count = 1, .reusable = false}}, SHIFT(96),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_return_statement, 1),
  [107] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_return_statement, 1),
  [109] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_return_statement, 1), SHIFT(68),
  [112] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_return_statement, 1), SHIFT(54),
  [115] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_return_statement, 1), SHIFT(12),
  [118] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_return_statement, 1), SHIFT(29),
  [121] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_return_statement, 1), SHIFT(24),
  [124] = {.entry = {.count = 1, .reusable = false}}, SHIFT(80),
  [126] = {.entry = {.count = 1, .reusable = false}}, SHIFT(88),
  [128] = {.entry = {.count = 1, .reusable = false}}, SHIFT(11),
  [130] = {.entry = {.count = 1, .reusable = false}}, SHIFT(117),
  [132] = {.entry = {.count = 1, .reusable = false}}, SHIFT(92),
  [134] = {.entry = {.count = 1, .reusable = false}}, SHIFT(91),
  [136] = {.entry = {.count = 1, .reusable = false}}, SHIFT(67),
  [138] = {.entry = {.count = 1, .reusable = false}}, SHIFT(18),
  [140] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 1),
  [142] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_expression, 1),
  [144] = {.entry = {.count = 1, .reusable = false}}, SHIFT(81),
  [146] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_expression, 1), SHIFT(40),
  [149] = {.entry = {.count = 1, .reusable = false}}, SHIFT(124),
  [151] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_return_statement, 1), SHIFT(83),
  [154] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_return_statement, 1), SHIFT(65),
  [157] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_return_statement, 1), SHIFT(16),
  [160] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_return_statement, 1), SHIFT(37),
  [163] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_return_statement, 1), SHIFT(36),
  [166] = {.entry = {.count = 1, .reusable = false}}, SHIFT(41),
  [168] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unary_expression, 2),
  [170] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_unary_expression, 2),
  [172] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_matrix_literal, 2),
  [174] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_matrix_literal, 2),
  [176] = {.entry = {.count = 1, .reusable = false}}, SHIFT(75),
  [178] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_expression, 1), SHIFT(47),
  [181] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_matrix_row_repeat1, 2),
  [183] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_matrix_row_repeat1, 2), SHIFT_REPEAT(80),
  [186] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_matrix_row_repeat1, 2), SHIFT_REPEAT(88),
  [189] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_matrix_row_repeat1, 2), SHIFT_REPEAT(11),
  [192] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_matrix_row_repeat1, 2), SHIFT_REPEAT(92),
  [195] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_matrix_row_repeat1, 2), SHIFT_REPEAT(91),
  [198] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_assignment_statement, 3),
  [200] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_assignment_statement, 3),
  [202] = {.entry = {.count = 1, .reusable = false}}, SHIFT(79),
  [204] = {.entry = {.count = 1, .reusable = false}}, SHIFT(72),
  [206] = {.entry = {.count = 1, .reusable = false}}, SHIFT(70),
  [208] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call_expression, 3, .dynamic_precedence = 1),
  [210] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_call_expression, 3, .dynamic_precedence = 1),
  [212] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_matrix_row, 1),
  [214] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_return_statement, 2),
  [216] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_return_statement, 2),
  [218] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_expression, 3),
  [220] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_binary_expression, 3),
  [222] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression_statement, 1),
  [224] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_expression_statement, 1),
  [226] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call_expression, 4, .dynamic_precedence = 1),
  [228] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_call_expression, 4, .dynamic_precedence = 1),
  [230] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parenthesized_expression, 3),
  [232] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parenthesized_expression, 3),
  [234] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_matrix_literal, 3),
  [236] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_matrix_literal, 3),
  [238] = {.entry = {.count = 1, .reusable = false}}, SHIFT(82),
  [240] = {.entry = {.count = 1, .reusable = false}}, SHIFT(121),
  [242] = {.entry = {.count = 1, .reusable = false}}, SHIFT(62),
  [244] = {.entry = {.count = 1, .reusable = false}}, SHIFT(10),
  [246] = {.entry = {.count = 1, .reusable = false}}, SHIFT(106),
  [248] = {.entry = {.count = 1, .reusable = false}}, SHIFT(109),
  [250] = {.entry = {.count = 1, .reusable = false}}, SHIFT(74),
  [252] = {.entry = {.count = 1, .reusable = false}}, SHIFT(73),
  [254] = {.entry = {.count = 1, .reusable = false}}, SHIFT(71),
  [256] = {.entry = {.count = 1, .reusable = false}}, SHIFT(22),
  [258] = {.entry = {.count = 1, .reusable = false}}, SHIFT(45),
  [260] = {.entry = {.count = 1, .reusable = false}}, SHIFT(114),
  [262] = {.entry = {.count = 1, .reusable = false}}, SHIFT(64),
  [264] = {.entry = {.count = 1, .reusable = false}}, SHIFT(29),
  [266] = {.entry = {.count = 1, .reusable = false}}, SHIFT(59),
  [268] = {.entry = {.count = 1, .reusable = false}}, SHIFT(69),
  [270] = {.entry = {.count = 1, .reusable = false}}, SHIFT(60),
  [272] = {.entry = {.count = 1, .reusable = false}}, SHIFT(14),
  [274] = {.entry = {.count = 1, .reusable = false}}, SHIFT(119),
  [276] = {.entry = {.count = 1, .reusable = false}}, SHIFT(129),
  [278] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_matrix_row_repeat1, 1),
  [280] = {.entry = {.count = 1, .reusable = false}}, SHIFT(66),
  [282] = {.entry = {.count = 1, .reusable = false}}, SHIFT(63),
  [284] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [286] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_expression, 1), SHIFT(53),
  [289] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block, 3),
  [291] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block, 3),
  [293] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_definition, 6),
  [295] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_function_definition, 6),
  [297] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block, 2),
  [299] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block, 2),
  [301] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_statement, 1),
  [303] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_statement, 1),
  [305] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_definition, 5),
  [307] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_function_definition, 5),
  [309] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 1),
  [311] = {.entry = {.count = 1, .reusable = false}}, SHIFT(102),
  [313] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 1), SHIFT_REPEAT(102),
  [316] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 1),
  [318] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [320] = {.entry = {.count = 1, .reusable = false}}, SHIFT(50),
  [322] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_argument_list, 1),
  [324] = {.entry = {.count = 1, .reusable = false}}, SHIFT(56),
  [326] = {.entry = {.count = 1, .reusable = false}}, SHIFT(86),
  [328] = {.entry = {.count = 1, .reusable = false}}, SHIFT(85),
  [330] = {.entry = {.count = 1, .reusable = false}}, SHIFT(84),
  [332] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_argument_list_repeat1, 2),
  [334] = {.entry = {.count = 1, .reusable = false}}, SHIFT(35),
  [336] = {.entry = {.count = 1, .reusable = false}}, SHIFT(77),
  [338] = {.entry = {.count = 1, .reusable = false}}, SHIFT(78),
  [340] = {.entry = {.count = 1, .reusable = false}}, SHIFT(58),
  [342] = {.entry = {.count = 1, .reusable = false}}, SHIFT(76),
  [344] = {.entry = {.count = 1, .reusable = false}}, SHIFT(32),
  [346] = {.entry = {.count = 1, .reusable = false}}, SHIFT(44),
  [348] = {.entry = {.count = 1, .reusable = false}}, SHIFT(112),
  [350] = {.entry = {.count = 1, .reusable = false}}, SHIFT(123),
  [352] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parameter_list, 1),
  [354] = {.entry = {.count = 1, .reusable = false}}, SHIFT(166),
  [356] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_argument_list_repeat1, 2), SHIFT_REPEAT(56),
  [359] = {.entry = {.count = 1, .reusable = false}}, SHIFT(46),
  [361] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_matrix_content, 1),
  [363] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parameter_list, 2),
  [365] = {.entry = {.count = 1, .reusable = false}}, SHIFT(150),
  [367] = {.entry = {.count = 1, .reusable = false}}, SHIFT(135),
  [369] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_argument_list, 2),
  [371] = {.entry = {.count = 1, .reusable = false}}, SHIFT(146),
  [373] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_matrix_content, 2),
  [375] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_parameter_list_repeat1, 2),
  [377] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_parameter_list_repeat1, 2), SHIFT_REPEAT(166),
  [380] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_matrix_content_repeat1, 2), SHIFT_REPEAT(46),
  [383] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_matrix_content_repeat1, 2),
  [385] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [387] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [389] = {.entry = {.count = 1, .reusable = true}}, SHIFT(113),
  [391] = {.entry = {.count = 1, .reusable = true}}, SHIFT(122),
  [393] = {.entry = {.count = 1, .reusable = true}}, SHIFT(133),
  [395] = {.entry = {.count = 1, .reusable = true}}, SHIFT(118),
  [397] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [399] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [401] = {.entry = {.count = 1, .reusable = true}}, SHIFT(145),
  [403] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [405] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [407] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [409] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [411] = {.entry = {.count = 1, .reusable = true}}, SHIFT(139),
  [413] = {.entry = {.count = 1, .reusable = true}}, SHIFT(147),
  [415] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [417] = {.entry = {.count = 1, .reusable = true}}, SHIFT(162),
  [419] = {.entry = {.count = 1, .reusable = true}}, SHIFT(148),
  [421] = {.entry = {.count = 1, .reusable = true}}, SHIFT(141),
  [423] = {.entry = {.count = 1, .reusable = true}}, SHIFT(167),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_steppable(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
