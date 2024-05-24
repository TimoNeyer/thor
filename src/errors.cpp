#include "errors.hpp"

BaseException::BaseException(Token backtracked, const char * message) {
  this->msg = ("{}\nlast seen Token in line {} column {}\n\
    type {} and value {}",
                    message, backtracked.line, backtracked.column,
                    backtracked.type, backtracked.value);
}

const char * BaseException::what() const noexcept {
  return this->msg.c_str();
}
