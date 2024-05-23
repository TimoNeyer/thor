#include "init.hpp"
/*
class keywords {
    std::vector <std::string> keywords = {
        "break",
        "case",
        "continue",
        "default",
        "do",
        "else",
        "for",
        "if",
        "return",
        "switch",
        "typedef",
        "while",
        "yield",

        "str"   // string
        "chr",  // char
        "flt",  // float
        "enm",  // enum
        "cls",  // class, maybe later
        "stc",  // struct
        "uni",  // union
        "vod",  // void
        "any",  // raw bytes
        "dbl",  // double

        "import",
        "var",
        "fn",
    };
    public:
        std::vector <std::string> getTypes(){
            std::vector <std::string> types;
            types.resize(10);
            for (int i=14;i<24;i++){
                types.push_back(keywords[i]);
            }
            return types;
        }
        std::vector <std::string> getKeywords(){
            std::vector <std::string> keywordls;
            keywordls.resize(14);
            for (int i = 0; i<14;i++){
                keywordls.push_back(keywords[i]);
            } 
            return keywordls;
        }
        std::vector <std::string> getDeclare(){
            std::vector <std::string> declares;
            declares.resize(3);
            for (int i=25;i<29;i++){
                declares.push_back(keywords[i]);
            }
            return declares;
        }
};

class attributes{
    std::vector <std::string> attributes = {
        "gc",
        "heimdall",
        "const",
        "long",
        "short",
        "unsigned",
        "signed",
    };
    public:
        std::vector <std::string> getAttr(){
            return attributes;
        };
};


class comments{
    std::vector <std::string> comments = {"", "# "};
    public:
        std::string getOpen(std::string chr){
            if (chr == comments.at(0)){
                return "";
            }
            else if (chr == comments.at(1)) {
                return "\n";
            }
            return "";
        }
};

int num_operatores = 35;

class operators {
    std::vector <std::string> operators = {
        "+",
        "-",
        "*",
        "/",
        "%",
        "++",
        "--",
        "=",
        "+=",
        "-=",
        "*=",
        "/=",
        "%=",
        "==",
        "!=",
        ">",
        "<",
        ">=",
        "<=",
        "&&",
        "||",
        "!",
        "&",
        "|",
        "^",
        "~",
        "<<",
        ">>",
        "&=",
        "|=",
        "^=",
        "<<=",
        ">>=",
        "->",
        ".",
        "**",   // square
        "//"    // divide with rest
    };
*/
    std::vector <std::string> getAfter(char current){
        std::vector <std::string> res;
        switch (current) {
        case '+':
            res.push_back("+");
            res.push_back("=");
            res.push_back("");
            return res;
        case '-':
            res.push_back("-");
            res.push_back("=");
            res.push_back("");
            return res;
        case '=':
            res.push_back("=");
            res.push_back("");
            return res;
        case '>':
            res.push_back("=");
            res.push_back(">");
            res.push_back(">=");
            res.push_back("");
            return res;
        case '<':
            res.push_back("=");
            res.push_back("<");
            res.push_back("<=");
            res.push_back("");
            return res;
        case '*':
            res.push_back("=");
            res.push_back("*");
            res.push_back("");
            return res;
        case '/':
            res.push_back("=");
            res.push_back("/");
            res.push_back("");
            return res;
        case '!':
            res.push_back("=");
            res.push_back("");
            return res;
        case '%':
            res.push_back("=");
            res.push_back("");
            return res;
        case '^':
            res.push_back("=");
            res.push_back("");
            return res;
        case '&':
            res.push_back("&");
            res.push_back("=");
            return res;
        case '|':
            res.push_back("|");
            res.push_back("=");
            return res;
        case '.':
            res.push_back("");
            return res;
        default:
            perror("failed to get follow up char");
        }
    }

/*
int num_punctuators = 28;
int ipunctuators[] = {32,48,58,65,91,97,123,126};
char punctuators[] = {
    ',',
    ';',
    ':',
    '\"',
    '\'',
    '!',
    '?',
    '(',
    ')',
    '[',
    ']',
    '{',
    '}',
    '#',
    '/',
    '*',
    '=',
    '+',
    '-',
    '%',
    '|',
    '&',
    '^',
    '`',
    '<',
    '>',
    '=',
    '~',
    '-',

    '@'
};

int num_line_delim = 3;
int idelim[] = {59,123,125};
char line_delim[3] = {
    ';',
    '{',
    '}'
};
*/