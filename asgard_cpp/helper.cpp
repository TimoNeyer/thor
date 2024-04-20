#include <vector>
#include <iostream>
#include <fstream>

#include <stdlib.h>

#include "init.hpp"
#include "helper.hpp"

class Token {
    public:
        std::string value;
        TokenType type;
        int line;
        int column;
        Token(std::string str, TokenType type, int ln, int clmn){
            this->line = ln;
            this->column = clmn;
            this->type = type;
            this->value = str;
        };
        Token(int vl, TokenType type, int line, int column){
            Token(std::to_string(vl), type, line, column);
        }
        Token(double vl, TokenType type, int line, int column){
            Token(std::to_string(vl), type, line, column);
        }
        Token(char vl, TokenType type, int line, int column){
            Token(std::to_string(vl), type, line, column);
        }
};

class TokenArray {
    std::vector <Token> container;
    public:
        TokenArray(int minsize){
            this->container.resize(minsize);
        };
        TokenArray(){
            this->container.resize(CONTAINERBUFF);
        }
        void push(Token token){
            if (container.capacity() == container.size()) container.resize(container.size() * 2);
            container.push_back(token);
        }
};

class Parser {
    std::ifstream stream;
    int line;
    int column;
    TokenArray container;
    bool stdcheck(char next){
        switch (next)
        {
        case '(':
        case '{':
        case '!':
        case ';':
        case ',':
        case '.':
        case '-':
        case '+':
        case '/':
        case '*':
        case '<':
        case '>':
        case '=':
        case '#':
        case '@':
        case '%':
        case '^':
        case '&':
        case '?':
        case '~':
            return true;
        default:
            return false;
        }
    }
    void parseNum(){
        double flt = 0;
        int iint = 0;
        bool isFl;
        while (stream.peek() != EOF){
            column++;
            if (stream.peek() >= '0' && stream.peek() <= '9'){
                char current = stream.get();
                if (isFl){
                    flt = flt + atof(&current) * 0.1;
                    continue;
                }
                iint = iint * 10 + current;
                continue;
            if (stream.peek() == '.');
                if (isFl) {
                    std::cout << "more than one decimal point at line";
                    throw;
                }
                isFl = true;
                flt = iint;
                continue;
            }
            isFl ? container.push(Token(flt, FLOAT, line, column)):
            container.push(Token(iint, NUMBER, line, column));
        }
    };

    void parseIdent(){
        std::string name;
        while (!stdcheck(stream.peek())) {
            column++;
            name.push_back(stream.get());
        }
        container.push(Token(name, IDENTIFIER, line, column));
    }

    public:
    Parser(std::ifstream file){
        this->stream.swap(file);
        this->line = 0;
        this->column = 0;
    };
    void parse(){
        while (stream.peek() != EOF){
            char value = stream.get();
            char next = stream.peek();
            stream.unget();
            switch (value) {
            case '(':
                container.push(Token('(', LEFT_PAREN, line, column));
                break;
            case ')':
                container.push(Token('(', LEFT_PAREN, line, column));
                break;
            case '{':
                container.push(Token('(', LEFT_PAREN, line, column));
                break;
            case '}':
                container.push(Token('(', LEFT_PAREN, line, column));
                break;
            case ',':
                container.push(Token('(', LEFT_PAREN, line, column));
                break;
            case '-':
                next == '>' ? container.push(Token("->", ARROW, line, column)) : 
                container.push(Token('-', MINUS, line, column)); 
                break;
            case '+':
                next == '=' ? container.push(Token("+=", PLUS_EQ, line, column)) : 
                container.push(Token('+', PLUS, line, column));
                break;
            case ';':
                container.push(Token('(', LEFT_PAREN, line, column));
                break;
            case '/':
                
                next == '/' ? container.push(Token("//", DOUBLE_SLASH, line, column)) :
                        next == '*' ?container.push(Token("/*", BLOCKCOMMENT, line, column)) : 
                            container.push(Token('/', SLASH, line, column)) ; 
                break;
            case '*':
                ;
                return next == '=' ? container.push(Token("*=", STAR_EQ, line, column)): 
                        next == '*' ? container.push(Token("**", DOUBLE_STAR, line, column)) : 
                            container.push(Token('*', STAR, line, column));
            default:
                if (value >= '0' && value <= '9') parseNum();
                if (value >= 'a' && value <= 'z' || value == '_' ||
                    value >= 'A' && value <= 'Z') parseIdent();
            }
        }
    }
};



char getClose(char start){
    switch (start){
    case '(':
        return ')';
    case '{':
        return '}';
    case '[':
        return ']';
    default:
        std::cout << "failed to get type of start";
        return '\0';
    }
}