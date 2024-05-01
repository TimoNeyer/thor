#pragma once

#include <unordered_map>
#include <queue>

#include "lexer.hpp"

#define BLOCKBUFFER 4

enum BlockType {
    LEAF, PARAMETERS, STATEMENT, PREPROCESS
};

class Block {
    public:
    TokenType type;
    std::vector <Token> parameters;
    TokenArray body;
    Block(TokenType value);
    void push(Token value);
    void set(TokenArray value);
};

/*
possible contents of variable:
- reference
- int
- float
- bool
- array
- string -> f,n,r
- enum
- function
- bytes
- tuple
- objectptr -> function or class
*/

struct Variable {
    void * value;
    TokenType type;
};

class Parser{
        char delim;
        std::unordered_map <std::string, Variable> SymbolTable;
        TokenArray getPreprocess(TokenArray * lexerout);
        Block parseClass(TokenArray * values);
        Block parseDo(TokenArray * values);
        Block parseEnum(TokenArray * values);
        Block parseIf(TokenArray * values);
        Block parseImport(TokenArray * values);
        Block parseFn(TokenArray * values);
        Block parseFor(TokenArray * values);
        Block parseStruct(TokenArray * values);
        Block parseSwitch(TokenArray * values);
        Block parseThrow(TokenArray * values);
        Block parseWhile(TokenArray * values);
    public:
        std::queue <Block> main;
        Block blocking(TokenArray values, Block root);
        void parse(TokenArray lexerout);
        Parser();
};


