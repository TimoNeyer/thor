#pragma once

#include "lexer.hpp"

#define BLOCKBUFFER 4

enum BlockType {
    LEAF, PARAMETERS, STATEMENT, PREPROCESS
};

class Block {
    public:
    BlockType type;
    std::vector <Block> blocks;
    std::vector <Token> tokens;
    Block(std::vector <Block> initvalues, BlockType current);
    Block(TokenArray initvalues);
    Block();
    void push(Block value);
    void push(Token value);
};





class Parser{
        void getPreprocess();
    public:
        Block main;
        void blocking(TokenArray values, Block root);
        Parser();
};


