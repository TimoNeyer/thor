#pragma once
#include <iostream>
#include <vector>

#define CONTAINERBUFF 128 

enum TokenType {
  // Single-character tokens.
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, 
  RIGHT_BRACE, COMMA, DOT, MINUS, PLUS, COLON, 
  SEMICOLON, SLASH, STAR, AT, PIPE, HASHTAG,

  // One or two character tokens.
  BANG, BANG_EQ, EQUAL, EQUAL_EQ, DOUBLE_COLON,
  GREATER, GREATER_EQ, LESS, DOUBLE_DOT,
  LESS_EQ, DOUBLE_SLASH, LINECOMMENT, 
  BLOCKCOMMENT, ARROW, PLUS_EQ, ASSIGN,
  MINUS_EQ, STAR_EQ, SLASH_EQ, DOUBLE_MINUS,
  DOUBLE_STAR, DOUBLE_PLUS, DOUBLE_AND,

  // Literals.
  IDENTIFIER, FSTRING, NSTRING, 
  RSTRING, NUMBER, FLOAT,

  // Keywords.
  AND, CLASS, ELSE, FALSE, 
  FUN, FOR, IF, NONE, OR,
  RETURN, TRUE, VAR, WHILE,

  EMPTY
};

class Token {
    public:
        std::string value;
        TokenType type;
        int line;
        int column;
        Token();
        Token(std::string str, TokenType type, int ln, int clmn);
        Token(int vl, TokenType type, int ln, int clmn);
        Token(double vl, TokenType type, int ln, int clmn);
        Token(char vl, TokenType type, int ln, int clmn);

};

class TokenArray {
    public:
        std::vector <Token> values;
        TokenArray(int minsize);
        TokenArray();
        bool push(Token token);
 //       ~TokenArray();
};

class Lexer{
    private:
        std::ifstream stream;
        int line;
        int column;
        void parseNum(char value);
        bool stdcheck(char next);
        void parseIdent(char value);
        char get_next();
        bool isComment(std::string current);   
        char getClose(char start);
        void parseString(char start);
    public:
        TokenArray container;
        Lexer(std::ifstream *file);
        void parse();
  //      ~Parser();
};

