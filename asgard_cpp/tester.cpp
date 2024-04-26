#include <iostream>
#include <fstream>

#include "lexer.hpp"

int main(int argc, char * argv[]){
    if (argc != 2){
        perror("too few arguments given");
    }
    std::ifstream file(argv[1]);
    if (file.bad()) perror("failed to open file");
    Lexer parser(&file);
    parser.parse();
    //return 1;
    for (int i = 0; i < parser.container.values.size(); i++){
        if (parser.container.values.at(i).type == EMPTY) continue; 
        std::cout << "Token " << parser.container.values.at(i).value;
        std::cout << " is Type " << parser.container.values.at(i).type;
        std::cout << "\n";
    }
}