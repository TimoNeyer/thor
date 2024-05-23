#pragma once

#include <unordered_map>
#include <queue>

#include "lexer.hpp"

#define BLOCKBUFFER 4

enum BlockType {
    LEAF, PARAMETERS, STATEMENT, PREPROCESS
};

struct Node
{
    Token value;
    std::vector <Node *> subtree;
    Node(Token &token);
    Node(Node &other);
    void push_node(Node &node);
    ~Node();
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

struct Variable 
{
    void * value;
    TokenType type;
};

class Parser
{
        std::unordered_map <std::string, Variable> SymbolTable;
        Node head;
        TokenArray getPreprocess(TokenArray * lexerout);
<<<<<<< Updated upstream
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

=======
        Node parseClass(TokenArray * values);
        Node parseDo(TokenArray * values);
        Node parseEnum(TokenArray * values);
        Node parseIf(TokenArray * values);
        Node parseImport(TokenArray * values);
        Node parseFn(TokenArray * values);
        Node parseFor(TokenArray * values);
        Node parseStruct(TokenArray * values);
        Node parseSwitch(TokenArray * values);
        Node parseThrow(TokenArray * values);
        Node parseWhile(TokenArray * values);
>>>>>>> Stashed changes
    public:
        std::queue <Node> current;
        void parse(TokenArray lexerout);
        Parser();
};


