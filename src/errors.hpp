#include <exception>
#include <string>
#include <format>

#include "lexer.hpp"

class BaseException : std::exception {
  std::string msg;
  Token * last_seen;
  Token * block;

public:
  BaseException(Token backtracked, const char * message);
  virtual const char * what() const throw(); 
};

class SyntaxError : BaseException {
};