#pragma once

#include <unordered_map>
#include <queue>
#include <exception>

#include "lexer.hpp"

// define max lengths 
#define MAXFILESIZE 10000000
#define STDMAXS     128
#define MAXPREPROC  STDMAXS
#define MAXTYPELEN  STDMAXS
#define MAXARGS     STDMAXS

#define BLOCKBUFFER 4

enum BlockType {
    LEAF, PARAMETERS, STATEMENT, PREPROCESS
};

struct Node
{
    Token value;
    Node * parent;
    std::vector <Node *> subtree;
    Node();
    Node(Token token, Node * parent);
    Node(Node &other, Node * parent);
    void push_node(Node * node);
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

class Parser
{
        std::unordered_map <std::string, TokenType> SymbolTable;
        Node head;
        TokenArray preProc;

        // Helper
        void parseExpression(TokenArray * value, size_t index);

        void getPreprocess(TokenArray * lexerout);
        void parseClass(TokenArray * value, size_t index);
        void parseDo(TokenArray * value, size_t index);
        void parseEnum(TokenArray * value, size_t index);
        void parseIf(TokenArray * value, size_t * index);
        void parseImport(TokenArray * value);
        void parseFn(TokenArray * value, size_t * index);
        void parseFor(TokenArray * value);
        void parseStruct(TokenArray * value);
        void parseSwitch(TokenArray * value);
        void parseThrow(TokenArray * value);
        void parseWhile(TokenArray * value);
    public:
        //std::queue <Node> current;
        Node * current;
        std::queue<Node *> backtrack;

        void parse(TokenArray * lexerout);
        Parser();
};


