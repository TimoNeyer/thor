#pragma once
#include <iostream>
#include <vector>

#define CONTAINERBUFF 128 

enum TokenType {
  // Single-character tokens.
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, 
  RIGHT_BRACE, COMMA, DOT, MINUS, PLUS, 
  SEMICOLON, SLASH, STAR, AT, PIPE,

  // One or two character tokens.
  BANG, BANG_EQ, EQUAL, EQUAL_EQ,
  GREATER, GREATER_EQ, LESS, 
  LESS_EQ, DOUBLE_SLASH, LINECOMMENT, 
  BLOCKCOMMENT, ARROW, PLUS_EQ, 
  MINUS_EQUAL, STAR_EQ, SLASH_EQ, 
  DOUBLE_STAR, DOUBLE_PLUS,

  // Literals.
  IDENTIFIER, FSTRING, NSTRING, 
  RSTRING, NUMBER, FLOAT,

  // Keywords.
  AND, CLASS, ELSE, FALSE, 
  FUN, FOR, IF, NONE, OR,
  RETURN, TRUE, VAR, WHILE,

  IEOF
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
        std::vector <Token> container;
        TokenArray(int minsize);
        TokenArray();
        void push(Token token);
        ~TokenArray();
};

class Parser{
    private:
        std::ifstream stream;
        int line;
        int column;
        TokenArray container;
        void parseNum();
        bool stdcheck(char next);
        void parseIdent();
        char get_next(std::streampos return_addr);
        void isComment(std::string current);   
        char getClose(char start);
    public:
        Parser(std::ifstream file);
        void parse();
        ~Parser();
};

