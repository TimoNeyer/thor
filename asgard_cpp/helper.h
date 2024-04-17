#pragma once
#define HELPER_H

#include <iostream>
#include <init.h>
#include <vector>


typedef enum {
    KEYWORD,
    ATTRIBUTE,
    OPERATOR,
    PUNCTUATOR,
    IDENTIFIER,
    NUMBER
} TokenTypes;

class TokenArray {
    public:
        std::vector <Line> container, ;
        TokenArray(int minsize){
            this->container.resize(minsize);
        };
        void addLine(Line& line){
            this->container.push_back(line);
            if (container.size() == container.capacity()) container.resize(container.capacity() * container.capacity());
        };
};

class Token {
    public:
        std::string value;
        TokenTypes type;
        int line;
        int column;
        Token(std::string str, int ln, int clmn) : value(str), line(ln), column(clmn), type(getType(str)){
            /*this->value = str;
            this->type = getType(value);
            this->line = line;
            this->column = column;*/
        };

};

class Line {
    public:
        std::vector <Token> values;
        int linenum;
        Line(std::string value, int line){
            this->linenum = line;
            this->values.resize(value.length());
            this->values = tokenize(value);
            this->values.shrink_to_fit();
        };
    std::vector <Token> tokenize(std::string& line){
        std::vector <Token> array;
        std::string current;
        int clmn = 0;
        for (char c : line){
            for (char delim : line_delim){
                if (c == delim) {
                    array.push_back(Token(current, this->linenum, clmn));
                    current = "";
                } else {
                    current.append(c);
                }
            }    
        }
    }
};

TokenTypes getType(std::string& value);
bool isPunctuator(char current);
bool isNumber(std::string& currrent);
bool isLinedelim(char current);
std::vector <Token> tokenize(std::string& line);