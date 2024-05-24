#include "parser.hpp"
#include "errors.hpp"

Node::Node() {
  this->value = Token();
  this->subtree = std::vector<Node *>();
  this->parent = nullptr;
}

Node::Node(Token token, const Node *parent) {
  this->subtree = std::vector<Node *>();
  this->value = token;
  this->parent = parent;
}

Node::Node(Node &other, Node *parent) {
  this->subtree = other.subtree;
  this->value = other.value;
}

void Node::push_node(Node *node) { this->subtree.push_back(node); }

Node::~Node() {
  for (Node *ptr : this->subtree) {
    if (!ptr->subtree.empty())
      delete ptr;
  }
}

Parser::Parser() {
  this->head = new Node();
  this->preProc = TokenArray();
  this->backtrack = std::stack<const Node *>();
  this->backtrack.push(this->head);
}

void Parser::testExpression(TokenArray *value, size_t *index, TokenType delim) {
  Node *exp = new Node(value->at(*index), this->backtrack.top());
  exp->value.value = "";
  TokenArray buffer(4);
  TokenType next;
  size_t cindex = *index;
  for (int i = 0; i < MAXEXP && value->at((*index)++).type != delim; i++) {
    next = value->at(*index + 1).type;
    if (delim != SEMICOLON && value->at(*index + i).type == DOUBLE_PIPE) {
      this->testExpression(value, &cindex, DOUBLE_PIPE);
      this->testExpression(value, &cindex, delim);
    }
    switch (value->at(*index).type) {
    case MINUS:
      if (next != INT  || next != FLOAT)
        throw BaseException(value->at(*index),
                            "Can not convert non int or float to minus", *index);
    case IDENTIFIER:
      if (next > MATH && next < ENDACCESS || next == LEFT_PAREN || next == SEMICOLON) {
        // parse Exp
      } else {
        std::cout << next << std::endl;
        throw BaseException(value->at(*index), "Wrong Expression", *index);
      }
      break;
    case LEFT_PAREN:
      this->testExpression(value, index, RIGHT_PAREN);
      break;
    case DOUBLE_PLUS:
    case DOUBLE_MINUS:
      break;
    default:
      break;
    }
  }
}

void Parser::getPreprocess(TokenArray *lexerout) {
  TokenArray PreProc(8);
  int i = 1;
  if (lexerout->values.front().type == HASHTAG) {
    for (; lexerout->values.at(i).type != HASHTAG &&
            lexerout->values.at(i + 1).type != BEGIN && i < MAXPREPROC;
         i++) {
      PreProc.push(lexerout->values.at(i));
    }
    lexerout->values = std::vector<Token>(lexerout->values.begin() + i,
                                          lexerout->values.end());
  }
  if (PreProc.values.size() == 0) {
    throw BaseException(
        lexerout->at(0),
        "missing directives, add module name and start program with #begin", -1);
  }
  PreProc.values.shrink_to_fit();
  this->preProc = PreProc;
}

void Parser::parseFn(TokenArray *value, size_t *index) {
  if (value->size() <= *index + 7)
    throw BaseException(value->at(*index), "function definition invalid", *index);
  if (value->at(++*index).type != LESS ||
      value->at(++*index).type < IDENTIFIER ||
      value->at(++*index).type != GREATER) {
    throw BaseException(value->at(*index - 3),
                        "function signature has no type", *index);
  }
  Node *fn = new Node(value->at(*index), this->backtrack.top());
  this->backtrack.push(fn);
  Node *type = new Node(value->at(++*index), fn);
  Node *name = new Node(value->at((++*index)), fn);
  *index += 2;
  Node *params = new Node(value->at(*index), fn);
  // Place to implement const
  for (int i = 0; i < MAXARGS && i + *index < value->size() &&
                  value->at(++*index).type != RIGHT_PAREN;
       i++) {
    Node *arg = new Node(value->at(*index), params);
    params->push_node(arg);
  }
}

void Parser::parseIf(TokenArray *value, size_t *index) {
  Node *iif = new Node(value->at((*index)++), this->backtrack.top());
  Node *exp = new Node(value->at(*index), iif);
  this->backtrack.push(exp);
//  this->testExpression(value, index, RIGHT_PAREN);
  this->backtrack.pop();
  this->backtrack.push(iif);
}

void Parser::parse(TokenArray *lexerout) {
  this->getPreprocess(lexerout);
  size_t *i = new size_t;
  for (*i = 0; *i < lexerout->size(); (*i)++) {
    switch (lexerout->at(*i).type) {
    case CLASS:

      break;
    case DO:

      break;
    case ENUM:

      break;
    case IF:
      this->parseIf(lexerout, i);
      break;
    case IMPORT:

      break;
    case FN:
      this->parseFn(lexerout, i);
      break;
    case FOR:

      break;
    case STRUCT:

      break;
    case SWITCH:

      break;
    case THROW:

      break;
    case WHILE:

      break;
    case RIGHT_BRACE:
      if (this->backtrack.size() == 0)
        throw BaseException(lexerout->at(*i),
                            "call stack ambiguous, probably missing { or }", *i);
      this->backtrack.pop();
      break;
    default:
      //this->testExpression(lexerout, i, SEMICOLON);
      break;
    }
  }
}