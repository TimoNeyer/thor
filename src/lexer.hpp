#pragma once
#include <fstream>
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
  LESS_EQ, DOUBLE_SLASH, //LINECOMMENT, 
  BLOCKCOMMENT, ARROW, PLUS_EQ, ASSIGN,
  MINUS_EQ, STAR_EQ, SLASH_EQ, DOUBLE_MINUS,
  DOUBLE_STAR, DOUBLE_PLUS, DOUBLE_AND,

  // Keywords.
  BEGIN, BREAK, CASE, CLASS, CONTINUE, DEFAULT, 
  DO, ELSE, ENUM, FALSE, FN, FOR, IF, IMPORT, INULL, 
  MODULE, RETURN, STR, STRUCT, SWITCH, THROW, 
  TRUE, VAR, WHILE, YIELD,

  // Literals.
  IDENTIFIER, FSTRING, NSTRING, 
  RSTRING, NUMBER, FLOAT,

  // native types
  REFERENCE, INT, BOOL, ARRAY, BYTES, 
  TUPLE, OBJECT, EXPRESSION, // class, function, enum, float

  // modifiers
  LONG, SHORT, SIGNED, UNSIGNED, VOID, GC, NOGC,

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
        TokenArray(TokenArray&& other);
        TokenArray(TokenArray & other);
        TokenArray & operator=(const TokenArray &other);
        bool push(Token token);
        size_t size();
        Token at(size_t index);
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
        TokenType isKeyword(std::string value);
    public:
        TokenArray container;
        Lexer(std::ifstream *file);
        void parse();
  //      ~Parser();
};

