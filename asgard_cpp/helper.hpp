#pragma once
#include <iostream>
#include <vector>

#include "init.hpp"

#define CONTAINERBUFF 128 

typedef enum {
    KEYWORD,
    ATTRIBUTE,
    OPERATOR,
    PUNCTUATOR,
    IDENTIFIER,
    NUMBER
} Cathegorie;


typedef enum {
  // Single-character tokens.
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

  // One or two character tokens.
  BANG, BANG_EQ,
  EQUAL, EQUAL_EQ,
  GREATER, GREATER_EQ,
  LESS, LESS_EQ, DOUBLE_SLASH, 
  LINECOMMENT, BLOCKCOMMENT,
  ARROW, PLUS_EQ, MINUS_EQUAL,
  STAR_EQ, SLASH_EQ, DOUBLE_STAR,

  // Literals.
  IDENTIFIER, FSTRING, NSTRING, RSTRING, NUMBER, FLOAT,

  // Keywords.
  AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NONE, OR,
  RETURN, TRUE, VAR, WHILE,

  IEOF
}TokenType ;

class Token {
    public:
        std::string value;
        TokenType type;
        int line;
        int column;
        Token(std::string str, TokenType type, int ln, int clmn);
        Token(int vl, TokenType type, int line, int column);
        Token(double vl, TokenType type, int line, int column);
};

class TokenArray {
    std::vector <Token> container;
    public:
        std::vector <Token> container;
        TokenArray(int minsize);
        TokenArray();
        void push(Token token);
};

class Parser{
    std::ifstream stream;
    int line;
    int column;
    TokenArray container;
    bool stdcheck(char next);
    void parseNum();
    void parseIdent();
    void parse();
}

TokenType parse(char current);
char getClose(char start);
std::string isComment(std::string current);
