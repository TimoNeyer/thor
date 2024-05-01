#include "parser.hpp"

Block::Block(TokenType value){
    type = value;
}

void Block::push(Token value){
    parameters.push_back(value);
}

void Block::set(TokenArray value){
    body.values.swap(value.values);
}

Parser::Parser(){
}

TokenArray Parser::getPreprocess(TokenArray * lexerout){
    TokenArray PreProc(8);
    if (lexerout->values.front().type == HASHTAG){
        for (int i = 0; lexerout->values.at(++i).type != HASHTAG && 
            lexerout->values.at(i+1).type != BEGIN;){
                PreProc.push(lexerout->values.at(i));
            }
    } else if (PreProc.values.size() == 0) {
        std::cout << "missing directives, add module name and start program with #begin;";
        throw;
    }
    PreProc.values.shrink_to_fit();
    return PreProc; 
}

Block Parser::blocking(TokenArray values, Block root) {
    TokenArray bufferarray(16);
    for (int i = 0; i< values.size(); i++){
        Token current = values.values.at(i);
        switch (current.type) {
        case CLASS:
            main.push(parseClass(&values));
            break;
        case DO:
            main.push(parseDo(&values));
            break;
        case ENUM:
            main.push(parseEnum(&values));
            break;
        case IF:
            main.push(parseIf(&values));
            break;
        case IMPORT:
            main.push(parseImport(&values));
            break;
        case FN:
            main.push(parseFn(&values));
            break;
        case FOR:
            main.push(parseFor(&values));
            break;
        case STRUCT:
            main.push(parseStruct(&values));
            break;
        case SWITCH:
            main.push(parseSwitch(&values));
            break;
        case THROW:
            main.push(parseThrow(&values));
            break;
        case WHILE:
            main.push(parseWhile(&values));
            break;
        default:
            std::cout << "found unknown token " << current.value << std::endl;
            break;
        }
    }
}


void Parser::parse(TokenArray lexerout){
}