#pragma once
#include <fstream>
#include <iostream>
#include <vector>

#define CONTAINERBUFF 128

enum TokenType {
  Separators,

  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  LEFT_BRACKET,
  SEMICOLON,
  BLOCKCOMMENT,
  COMMA,
  HASHTAG,

  MODIFIERS,

  RIGHT_BRACKET,

  ENDSEPARATORS,

  AND,

  MATH,

  STAR,

  ENDMODIFIERS,

  MINUS,
  PLUS,
  SLASH,
  DOUBLE_SLASH,
  DOUBLE_STAR,

  ENDMATH,

  LOGIC,

  BANG,
  DOUBLE_AND,
  DOUBLE_PIPE,

  ENDLOGIC,

  COMPARE,

  GREATER,
  GREATER_EQ,
  LESS,
  LESS_EQ,
  BANG_EQ,
  EQUAL_EQ,

  ENDCOMPARE,

  ASSIGNMENT,

  EQUAL,
  MINUS_EQ,
  PLUS_EQ,
  STAR_EQ,
  DOUBLE_PLUS,
  DOUBLE_MINUS,
  ASSIGN,

  ENDASSIGNMENT,

  ACCESS,

  ARROW,
  DOT,
  DOUBLE_COLON,

  ENDACCESS,

  MISC,

  COLON,
  PIPE,
  DOUBLE_DOT,

  ENDMISC,

  TYPES,

  REFERENCE,
  INT,
  BOOL,
  ARRAY,
  BYTES,
  TUPLE,
  OBJECT,
  EXPRESSION,
  DOUBLE,

  KEYWORDS,

  CLASS,
  FN,
  ENUM,

  ENDTYPES,

  BEGIN,
  BREAK,
  CASE,
  CONTINUE,
  DEFAULT,
  DO,
  ELSE,
  FALSE,
  FOR,
  IF,
  IMPORT,
  INULL,
  MODULE,
  RETURN,
  STRUCT,
  SWITCH,
  THROW,
  TRUE,
  VAR,
  WHILE,
  YIELD,

  ENDKEYWORDS,

  TYPETYPE,

  LONG,
  SHORT,
  SIGNED,
  UNSIGNED,
  VOID,
  GC,
  NOGC,

  ENDTYPETYPE,

  LITERALS,

  IDENTIFIER,
  FSTRING,
  NSTRING,
  RSTRING,
  NUMBER,
  FLOAT,

  ENDLITERALS,

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
  std::vector<Token> values;
  TokenArray(int minsize);
  TokenArray();
  TokenArray(TokenArray &&other);
  TokenArray(TokenArray &other);
  TokenArray &operator=(const TokenArray &other);
  bool push(Token token);
  size_t size();
  Token at(size_t index);
};

class Lexer {
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
