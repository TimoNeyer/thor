#include <vector>
#include <iostream>
#include <fstream>

#include <stdlib.h>

#include "lexer.hpp"

Token::Token(){
    this->line = -1;
    this->column = -1;
    this->type = IEOF;
    this->value = std::string("");
}

Token::Token(std::string str, TokenType type, int ln, int clmn){
    this->line = ln;
    this->column = clmn;
    this->type = type;
    this->value = str;
}

Token::Token(int vl, TokenType type, int ln, int clmn){
    this->line = ln;
    this->column = clmn;
    this->type = type;
}

Token::Token(double vl, TokenType type, int ln, int clmn){
    this->line = ln;
    this->column = clmn;
    this->type = type;
    this->value = std::to_string(vl);
}

Token::Token(char vl, TokenType type, int ln, int clmn){
    this->line = ln;
    this->column = clmn;
    this->type = type;
    this->value = std::to_string(vl);
}

TokenArray::TokenArray(int minsize){
    this->container.resize(minsize);
};

TokenArray::TokenArray(){
    this->container.resize(CONTAINERBUFF);
}

void TokenArray::push(Token token){
    if (container.capacity() == container.size()) container.resize(container.size() * 2);
    container.push_back(token);
}

TokenArray::~TokenArray(){
    delete &container;
}

void Parser::parseNum(){
    double flt = 0;
    int iint = 0;
    bool isFl = false;
    while (stream.peek() != EOF){
        column++;
        switch (stream.peek()){
            case '\r':
            case '\v':
            case '\t':
            case '\n':
            case ' ' :
                continue;
            default:
            if (stream.peek() >= '0' && stream.peek() <= '9'){
                char current = stream.get();
                if (isFl){
                    flt = flt + atof(&current) * 0.1;
                    continue;
                }
                iint = iint * 10 + current;
                continue;
            }
            if (stream.peek() == '.'){
                if (isFl) {
                    std::cout << "more than one decimal point at line";
                    throw;
                }
                isFl = true;
                flt = iint;
                continue;
            }
            else {
                break;
            }
        }
    }
    isFl ? container.push(Token(flt, FLOAT, line, column)):
    container.push(Token(iint, NUMBER, line, column));

};

bool Parser::stdcheck(char next){
    return next >= 'a' && next <= 'z' || 
           next >= 'A' && next <= 'Z' ||
           next == '_'; 
}

void Parser::parseIdent(){
    std::string name;
    while (stdcheck(stream.peek())) {
        column++;
        name.push_back(stream.get());
    }
    container.push(Token(name, IDENTIFIER, line, column));
}

char Parser::get_next(std::streampos return_addr){
    char current;
    while ( stream.peek() == ' '  || 
            stream.peek() == '\n' || 
            stream.peek() == '\r' ||
            stream.peek() == '\t' ||
            stream.peek() == '\v') {
        current = stream.get();
    }
    stream.seekg(return_addr);
    return current;
} 

void Parser::isComment(std::string current){
    if (current == "/*"){
        while (stream.peek() != EOF){
            if (stream.peek() == '*'){
                stream.get();
                if (stream.peek() == '/') return;
            }
            stream.get();
        }
    }
    else if (current == "#"){
        while (stream.peek() != '\n') stream.get();
    } return;
}

char Parser::getClose(char start){
    switch (start){
    case '(':
        return ')';
    case '{':
        return '}';
    case '<':
        return '>';
    default:
        std::cout << "failed to get type of start";
        return EOF;
    }
}

Parser::Parser(std::ifstream file){
    this->stream.swap(file);
    this->line = 0;
    this->column = 0;
};

void Parser::parse(){
    while (stream.peek() != EOF){
        std::streampos retaddr = stream.tellg();
        char value = stream.get();
        char next = get_next(retaddr);
        switch (value) {
            case '\r':
            case '\v':
            case '\t':
            case '\n':
            case ' ':
                continue;
                break;
            case '(':
                container.push(Token('(', LEFT_PAREN, line, column));
                break;
            case ')':
                container.push(Token(')', RIGHT_PAREN, line, column));
                break;
            case '{':
                container.push(Token('{', LEFT_BRACE, line, column));
                break;
            case '}':
                container.push(Token('}', LEFT_PAREN, line, column));
                break;
            case '<':
                next == '=' ? container.push(Token("<=", GREATER_EQ, line, column)) :
                container.push(Token('<', GREATER, line, column));
                break;
            case '>':
                next == '=' ? container.push(Token(">=", GREATER_EQ, line, column)) :
                    container.push(Token('>', LESS, line, column));
                break;
            case ',':
                container.push(Token(',', COMMA, line, column));
                break;
            case '-':
                next == '>' ? container.push(Token("->", ARROW, line, column)) : 
                    container.push(Token('-', MINUS, line, column)); 
                break;
            case '+':
                next == '=' ? container.push(Token("+=", PLUS_EQ, line, column)) : 
                    next == '+' ? container.push(Token("++", DOUBLE_PLUS, line, column)) :
                    container.push(Token('+', PLUS, line, column));
                break;
            case ';':
                container.push(Token(';', SEMICOLON, line, column));
                break;
            case '/':
                next == '/' ? container.push(Token("//", DOUBLE_SLASH, line, column)) :
                    next == '*' ? isComment("/*") : 
                    container.push(Token('/', SLASH, line, column)) ; 
                break;
            case '*':
                next == '=' ? container.push(Token("*=", STAR_EQ, line, column)): 
                    next == '*' ? container.push(Token("**", DOUBLE_STAR, line, column)) : 
                    container.push(Token('*', STAR, line, column));
                break;
            case '#':
                isComment("#");
                break;
            default:
                if (value >= '0' && value <= '9') parseNum();
                if (value >= 'a' && value <= 'z' || 
                    value >= 'A' && value <= 'Z' ||
                    value == '_' ) parseIdent();
        }
    }
}

Parser::~Parser(){
    delete[] &container;
    stream.close();
}
