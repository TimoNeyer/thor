#include "parser.hpp"

Block::Block(std::vector <Block> initvalues, BlockType current){
    type = current;
    blocks.swap(initvalues);
}

Block::Block(TokenArray initvalues){
    type = LEAF;
    tokens.swap(initvalues.values);
}

Block::Block(){
    type = STATEMENT;
    blocks.resize(BLOCKBUFFER);
    blocks.clear();
}

void Block::push(Token value){
    if (type != LEAF){
        std::cout << "recieved Tokens into non Leaf Block";
        throw;
    }
    if (tokens.size() == tokens.capacity()) {
        tokens.resize(tokens.size() * 2);
    }
    tokens.push_back(value);
}

void Block::push(Block value){
    if (type  == LEAF) {
        std::cout << "recieved Block into Leaf Block";
        throw;
    }
    if (blocks.size() == blocks.capacity()) {
        blocks.resize(blocks.size() * 2);
    }
    blocks.push_back(value);
}

Parser::Parser(){
    main = Block();
}

void Parser::getPreprocess(){

}

void Parser::blocking(TokenArray values, Block root){
    TokenArray buffertokens(16);
    Block bufferblock = Block();
    for (int i = 0; i< values.values.size(); i++){
        switch (values.values.at(i).type) {
            case LEFT_BRACE:
                while (i < values.values.size() - 1 && 
                        values.values.at(i++).type != RIGHT_BRACE){
                    buffertokens.push(values.values.at(i));
                };
                bufferblock.push(Block(buffertokens));
                break;
            case LEFT_PAREN:
                while (i < values.values.size() - 1 && 
                        values.values.at(i++).type != RIGHT_PAREN) {
                    buffertokens.push(values.values.at(i));
                };
                bufferblock.push(Block(buffertokens));
                break;
        }
    }
}