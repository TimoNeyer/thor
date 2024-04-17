#include <iostream>
#include <fstream>

#include "helper.h"


TokenArray parse(std::string filename) {
    TokenArray container(128);
    std::ifstream file(filename);
    std::string currentchar;
    Line currentLine(16);
    int line = 0;
    int column = 0;
    bool seeking;
    while (file.peek() != EOF){
        char next = file.peek();
        if (isLinedelim(next)){
            
        }
        
    }
}

