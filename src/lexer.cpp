#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#include <stdlib.h>

#include "lexer.hpp"

Token::Token(){
    this->line = -1;
    this->column = -1;
    this->type = EMPTY;
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
    this->value = std::to_string(vl);
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
    this->values.resize(minsize);
};

TokenArray::TokenArray(){
    this->values.resize(CONTAINERBUFF);
}

TokenArray::TokenArray(TokenArray && other){
    values.swap(other.values);
}

TokenArray::TokenArray(TokenArray & other){
    values.swap(other.values);
}

bool TokenArray::push(Token token){
    if (values.capacity() == values.size()){
        values.resize(values.size() * 2);
    }
    values.push_back(token);
    return true;
}
 size_t TokenArray::size(){
    return values.size();
 }
 Token TokenArray::at(size_t index){
    return this->values.at(index);
 }

Lexer::Lexer(std::ifstream *file){
    this->stream.swap(*file);
    this->line = 0;
    this->column = 0;
}

void Lexer::parseNum(char value){
    double flt = 0;
    int iint = atoi(&value);
    int isFl = 0;
    if (stream.peek() == '0') {
        std::cout << "Number starting with 0 detected at line " << line;
        perror("ValueError");
    }
    while (stream.peek() != EOF){
        switch (stream.peek()){
            case '\r':
            case '\v':
            case '\t':
            case '\n':
            case ' ' :
                stream.get();
                continue;
            default:
            if (stream.peek() >= '0' && stream.peek() <= '9'){
                char current = stream.get();
                if (isFl){
                    flt = flt + atoi(&current) * std::pow(0.1, isFl++);
                    break;
                } else {
                    iint = iint * 10 + atoi(&current);
                    column++;
                    continue;
                }
            } else if (stream.peek() == '.'){
                if (isFl) {
                    std::cout << "error in line " << line;
                    perror("more than one decimal point");
                }
                isFl = true;
                flt = iint;
                stream.get();
                column++;
                continue;
            }
            else {
                goto exitNum;
            }
        }
    }
    exitNum:
    isFl ? container.push(Token(flt, FLOAT, line, column)):
    container.push(Token(iint, NUMBER, line, column));
    return;
}

bool Lexer::stdcheck(char next){
    return (next >= 'a' && next <= 'z') || 
           (next >= 'A' && next <= 'Z') ||
           next == '_'; 
}

void Lexer::parseIdent(char value){
    std::string name;
    name.push_back(value);
    while (stdcheck(stream.peek())) {
        column++;
        name.push_back(stream.get());
    }
    container.push(Token(name, isKeyword(name), line, column));
}

char Lexer::get_next(){
    char current = stream.peek();
    while ( stream.peek() == ' '  || 
            stream.peek() == '\n' || 
            stream.peek() == '\t') {
        if (stream.peek() == '\n') line++;
        current = stream.get();
        column++;
    }
    return current;
} 

bool Lexer::isComment(std::string current){
    if (current == "/*"){
        while (stream.peek() != EOF){
            if (stream.peek() == '*'){
                stream.get();
                if (stream.peek() == '/') return true;
            }
            stream.get();
        }
    }
    else if (current == "#"){
        while (stream.peek() != '\n') stream.get();
    } return true;
}

char Lexer::getClose(char start){
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

TokenType Lexer::isKeyword(std::string value){
    TokenType previous = container.values.at(container.values.size() - 1).type;
    if (previous == HASHTAG && value == "begin") return BEGIN;
    else if (value == "break") return BREAK;
    else if (value == "case") return CASE;
    else if (value == "class") return CLASS;
    else if (value == "continue") return CONTINUE;
    else if (value == "default") return DEFAULT;
    else if (value == "do") return DO;
    else if (value == "else") return ELSE;
    else if (value == "enum") return ENUM;
    else if (value == "false") return FALSE;
    else if (value == "fn") return FN;
    else if (value == "for") return FOR;
    else if (value == "if") return IF;
    else if (value == "import") return IMPORT;
    else if (previous == HASHTAG && value == "module") return MODULE;
    else if (value == "null") return INULL;
    else if (value == "return") return RETURN;
    else if (value == "str") return STR;
    else if (value == "struct") return STRUCT;
    else if (value == "switch") return SWITCH;
    else if (value == "throw") return THROW;
    else if (value == "true") return TRUE;
    else if (value == "var") return VAR;
    else if (value == "while") return WHILE;
    else if (value == "yield") return YIELD;
    return IDENTIFIER;
}

void Lexer::parseString(char start){
    std::string value;
    while (stream.peek() != EOF) {
        if (stream.peek() == start){
            stream.get();
            switch (start) {
                case '`':
                    container.push(Token(value, RSTRING , line, column));
                    return;
                case '"':
                    container.push(Token(value, FSTRING , line, column));
                    return;
                default:
                    container.push(Token(value, NSTRING , line, column));
                    return;
            }
        }
        value.push_back(stream.get());
    }
}
void Lexer::parse(){
    while (stream.peek() != EOF){
        char value = stream.get();
        char next = get_next();
        switch (value) {
            //case '\r':
            //case '\v':
            case '\t':
            case '\n':
            case ' ':
                break;
            case '(':
                container.push(Token("(", LEFT_PAREN, line, column));
                break;
            case ')':
                container.push(Token(")", RIGHT_PAREN, line, column));
                break;
            case '{':
                container.push(Token("{", LEFT_BRACE, line, column));
                break;
            case '}':
                container.push(Token("}", RIGHT_BRACE, line, column));
                break;
            case '<':
                next == '=' ? container.push(Token("<=", GREATER_EQ, line, column)) || stream.get() :
                container.push(Token("<", GREATER, line, column)); 
                break;
            case '>':
                next == '=' ? container.push(Token(">=", GREATER_EQ, line, column)) || stream.get():
                    container.push(Token(">", LESS, line, column));
                break;
            case ',':
                container.push(Token(",", COMMA, line, column));
                break;
            case '-':
                next == '>' ? container.push(Token("->", ARROW, line, column)) || stream.get() : 
                    next == '=' ? container.push(Token("-=", MINUS_EQ, line, column)) || stream.get() :
                    next == '-' ? container.push(Token("--", DOUBLE_MINUS, line, column)) || stream.get() :
                    container.push(Token("-", MINUS, line, column)); 
                break;
            case '+':
                next == '=' ? container.push(Token("+=", PLUS_EQ, line, column)) || stream.get(): 
                    next == '+' ? container.push(Token("++", DOUBLE_PLUS, line, column)) || stream.get():
                    container.push(Token("+", PLUS, line, column));
                break;
            case ';':
                container.push(Token(";", SEMICOLON, line, column));
                break;
            case '/':
                next == '*' ? isComment("/*") : 
                next == '/' ? container.push(Token("//", DOUBLE_SLASH, line, column)) || stream.get() :
                container.push(Token("/", SLASH, line, column)) ; 
                break;
            case '*':
                next == '=' ? container.push(Token("*=", STAR_EQ, line, column)) || stream.get() : 
                    next == '*' ? container.push(Token("**", DOUBLE_STAR, line, column)) || stream.get(): 
                    container.push(Token("*", STAR, line, column));
                break;
            case '=':
                next == '=' ? container.push(Token("==", EQUAL_EQ, line, column)) || stream.get() : 
                    container.push(Token("=", EQUAL, line, column));
            case '#':
                container.push(Token("#", HASHTAG, line, column));
                break;
            case '.':
                next == '.' ? container.push(Token("..", DOUBLE_DOT, line, column)) || stream.get() :
                    container.push(Token(".", DOT, line, column));
                break;
            case ':':
                next == '=' ? container.push(Token(":=", ASSIGN, line, column)) :
                    next == ':' ? container.push(Token("::", DOUBLE_COLON, line, column)) :
                    container.push(Token(":", COLON, line, column));
            default:
                if (value >= '0' && value <= '9') parseNum(value);
                if (value == '`' || value == '"' || value == '\'') parseString(value);
                if ((value >= 'a' && value <= 'z') || 
                    (value >= 'A' && value <= 'Z') ||
                    value == '_' ) parseIdent(value);
        }
    }
    container.values.shrink_to_fit();
}
/*
Parser::~Parser(){
    delete[] &container;
    stream.close();
}
*/
