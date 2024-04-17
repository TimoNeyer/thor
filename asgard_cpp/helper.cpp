#include "helper.h"
#include "init.h"
#include <vector>
#include <unordered_set>

bool isPunctuator(char current){
    for (int i = 0;i++<num_punctuators;){
        if (punctuators[i] == current) return true;
    }
    return false;
}

bool isNumber(const std::string& current) {
  for (char c : current) {
    if (!std::isdigit(c)) {
      return false;
    }
  }
  return true;
}

bool isLinedelim(char current){
    for (int i = 0;i++<num_line_delim;){
        if (current == line_delim[i]) return true;
    }
    return false;
}

TokenTypes getType(std::string& value){
    if (isNumber(value)) return NUMBER;
    for (int i = 0;i++< num_operators;){
        if (value == operators[i])return OPERATOR; 
    }
    for (int i = 0;i++<num_keywords;){
        if (value == keywords[i]) return KEYWORD;
    }

    return IDENTIFIER;
}




