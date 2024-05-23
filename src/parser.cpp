#include "parser.hpp"

Node::Node()
{
    this->value = Token();
    this->subtree = std::vector<Node *>();
    this->parent = nullptr;
}

Node::Node(Token token, Node * parent)
{
    this->subtree = std::vector<Node *>();
    this->value = token;
    this->parent = parent;
}

Node::Node(Node &other, Node * parent)
{
    this->subtree = other.subtree;
    this->value = other.value;
}

void Node::push_node(Node * node)
{
    this->subtree.push_back(node);
}

Node::~Node()
{
    for (Node * ptr : this->subtree)
    {
        if (!ptr->subtree.empty()) delete &ptr ;
    }
}

Parser::Parser()
{
    this->SymbolTable = std::unordered_map <std::string, TokenType>();
    //this->current = std::queue <Node>();
    this->current = new Node();
    this->head = Node();
    this->preProc = TokenArray();
    this->backtrack = std::queue<Node *>();
}

void Parser::parseExpression(TokenArray * value, const size_t index)
{
    Node * exp = new Node(value->at(index), nullptr);
    switch (value->at(index).type)
    {
    case IDENTIFIER:

        break;
    
    default:
        break;
    }
}

void Parser::getPreprocess(TokenArray * lexerout)
{
    TokenArray PreProc(8);
    if (lexerout->values.front().type == HASHTAG)
    {
        int i = 1;
        for (i; 
            lexerout->values.at(i).type != HASHTAG
            && lexerout->values.at(i+1).type != BEGIN
            && i < MAXPREPROC;
            i++)
            {
                PreProc.push(lexerout->values.at(i));
            }
        lexerout->values = std::vector<Token>(lexerout->values.begin() + i, lexerout->values.end());
    } 
    if (PreProc.values.size() == 0) 
    {
        throw std::runtime_error("missing directives, add module name and start program with #begin;");
    }
    PreProc.values.shrink_to_fit();
    this->preProc = PreProc;
}

/*
Node Parser::parseClass(TokenArray * value, size_t index)
{
    if (value->at(index+1).type != LEFT_BRACE)
    Node * c = new Node(value, this->current);
    this->current = c;
    this->backtrack.push(c);
}
*/

void Parser::parseFn(TokenArray * value, size_t * index)
{
    if (value->at(++*index).type != LESS || 
        value->at(++*index).type < IDENTIFIER)
    
        {
            throw std::runtime_error("function signature has no type");
        }
    Node * fn = new Node(value->at(++*index), this->current);
    this->backtrack.push(fn);
    Node * type = new Node(value->at(++*index), fn);
    Node * name = new Node(value->at((++*index)), fn);
    this->SymbolTable.emplace(value->at(*index).value, 
                        value->at(*index).type);
    *index += 2; 
    Node * params = new Node(value->at(*index), fn);
// Place to implement const 
    for (int i = 0;
        i < MAXARGS
        && value->at(++*index).type != RIGHT_PAREN;
        i++)
        {
            Node * arg = new Node(value->at(*index), params);
            params->push_node(arg);
        }
    this->current = fn;
}

void Parser::parseIf(TokenArray * value, size_t * index)
{
//    if ()
}

void Parser::parse(TokenArray * lexerout) 
{
    this->getPreprocess(lexerout);
    for (size_t i = 0; i < lexerout->size(); i++){
        switch (lexerout->at(i).type) {
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
            this->parseFn(lexerout, &i);    
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
        case RIGHT_BRACE:
            this->current = this->backtrack.back();
            this->backtrack.pop();
            break;
        default:
            //std::cout << "found unknown token " << current.value << std::endl;
            break;
        }
    }
}