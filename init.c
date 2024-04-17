#include "init.h"

const extern int num_keywords = 36;
const extern char * keywords[36] = {
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "float",
    "for",
    "if",
    "int",
    "long",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "while",

    "str",
    "import",
    "yield",
    "new"
};

const extern int num_attributes = 2;
const extern char * attributes[2] = {
    "gc",
    "heimdall"
};

const extern int num_operatores = 35;
const extern char * operators[35] = {
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

const extern int num_punctuators = 17;
const extern char * punctuators[17] = {
    ",",
    ";",
    ":",
    '"',
    "'",
    "!",
    "?",
    "(",
    ")",
    "[",
    "]",
    "{",
    "}",
    "#",
    "##",
    "//"

    "@"
};

int upper[2] = {65, 90};
int lower[2] = {97, 122};
int numbers[2] = {48, 57};
