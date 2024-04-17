#include "init.h"

const int num_keywords = 33;
const std::string keywords[] = {
    "break",
    "case",
    "continue",
    "default",
    "do",
    "else",
    "for",
    "if",
    "return",
    "switch",
    "typedef",
    "while",

    "str"   // string
    "chr",  // char
    "flt",  // float
    "enm",  // enum
    "cls",  // class, maybe later
    "stc",  // struct
    "uni",  // union
    "vod",  // void
    "any",  // raw bytes
    "dbl",  // double

    "import",
    "yield",
    "var",
    "fn",
};

const  int num_attributes = 3;
const std::string attributes[] = {
    "gc",
    "heimdall",
    "const",
    "long",
    "short",
    "unsigned",
    "signed",
};

const int num_operatores = 35;
const std::string operators[] = {
    "+",
    "-",
    "*",
    "/",
    "%",
    "++",
    "--",
    "=",
    "+=",
    "-=",
    "*=",
    "/=",
    "%=",
    "==",
    "!=",
    ">",
    "<",
    ">=",
    "<=",
    "&&",
    "||",
    "!",
    "&",
    "|",
    "^",
    "~",
    "<<",
    ">>",
    "&=",
    "|=",
    "^=",
    "<<=",
    ">>=",
    "->",
    "."
};

const  int num_punctuators = 28;
const char punctuators[] = {
    ',',
    ';',
    ':',
    '\"',
    '\'',
    '!',
    '?',
    '(',
    ')',
    '[',
    ']',
    '{',
    '}',
    '#',
    '/',
    '*',
    '=',
    '+',
    '-',
    '%',
    '|',
    '&',
    '^',
    '`',
    '<',
    '>',
    '=',
    '~',

    '@'
};

const int num_line_delim = 3;
const char line_delim[3] = {
    ';',
    "{",
    "}"
}
