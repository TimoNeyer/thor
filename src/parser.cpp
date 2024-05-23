#include "parser.hpp"

Node::Node(Token &token)
{
    this->subtree = std::vector<Node *>();
    this->value = token;
}

Node::Node(Node &other)
{
    this->subtree = other.subtree;
    this->value = other.value;
}

void Node::push_node(Node &node)
{
    Node * stored_node = new Node(node);
    this->subtree.push_back(stored_node);
}

Node::~Node()
{
    for (Node * ptr : this->subtree)
    {
        delete ptr;
    }
}

Parser::Parser(){
    SymbolTable = std::unordered_map <std::string, Variable>();
    
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



void Parser::parse(TokenArray lexerout) {
    TokenArray bufferarray(16);
<<<<<<< Updated upstream
    for (unsigned long int i = 0; i< values.size(); i++){
        Token current = values.values.at(i);
=======
    for (int i = 0; i < lexerout.size(); i++){
        Token current = lexerout.at(i);
>>>>>>> Stashed changes
        switch (current.type) {
        case CLASS:
            
            break;
        case DO:
            
            break;
        case ENUM:
            
            break;
        case IF:
            
            break;
        case IMPORT:
            
            break;
        case FN:
            
            break;
        case FOR:
            
            break;
        case STRUCT:
            
            break;
        case SWITCH:
            
            break;
        case THROW:
            
            break;
        case WHILE:
            
            break;
        default:
            std::cout << "found unknown token " << current.value << std::endl;
            break;
        }
    }
}