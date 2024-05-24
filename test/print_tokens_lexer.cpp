#include <fstream>
#include <iostream>

#include "../src/lexer.hpp"
#include "../src/errors.hpp"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    throw BaseException(Token(), "Error, no file given");
  }
  std::ifstream file(argv[1]);
  if (file.bad())
    throw BaseException(Token(), "failed to open file");
  Lexer parser(&file);
  parser.parse();
  for (unsigned long int i = 0; i < parser.container.values.size(); i++) {
    if (parser.container.values.at(i).type == EMPTY)
      continue;
    std::cout << "Token " << parser.container.values.at(i).value;
    std::cout << " is Type " << parser.container.values.at(i).type;
    std::cout << "\n";
  }
  return 0;
}