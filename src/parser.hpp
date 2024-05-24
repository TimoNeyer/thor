#pragma once

#include <exception>
#include <stack>
#include <unordered_map>
#include <format>

#include "lexer.hpp"

// define max lengths
#define MAXFILESIZE 10000000
#define STDMAXS 128

#define MAXPREPROC STDMAXS
#define MAXTYPELEN STDMAXS
#define MAXARGS STDMAXS
#define MAXEXP MAXTYPELEN * 4

#define BLOCKBUFFER 4

enum BlockType { LEAF, PARAMETERS, STATEMENT, PREPROCESS };

struct Node {
  Token value;
  const Node *parent;
  std::vector<Node *> subtree;
  Node();
  Node(Token token, const Node *parent);
  Node(Node &other, Node *parent);
  void push_node(Node *node);
  ~Node();
};

/*
possible contents of variable:
- reference
- int
- float
- bool
- array
- string -> f,n,r
- enum
- function
- bytes
- tuple
- objectptr -> function or class
*/

class Parser {
  std::unordered_map<std::string, TokenType> SymbolTable;
  const Node *head;
  TokenArray preProc;

  void testExpression(TokenArray *value, size_t * index, TokenType delim);
  void getPreprocess(TokenArray *value);
  void parseClass(TokenArray *value, size_t * index);
  void parseDo(TokenArray *value, size_t index);
  void parseEnum(TokenArray *value, size_t index);
  void parseIf(TokenArray *value, size_t *index);
  void parseImport(TokenArray *value);
  void parseFn(TokenArray *value, size_t *index);
  void parseFor(TokenArray *value);
  void parseStruct(TokenArray *value);
  void parseSwitch(TokenArray *value);
  void parseThrow(TokenArray *value);
  void parseWhile(TokenArray *value);

public:
  // std::queue <Node> current;
  // Node * current;
  std::stack<const Node *> backtrack;

  void parse(TokenArray *value);
  Parser();
};

