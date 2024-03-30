#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "init.h"

#define DEFAULTSTARTINGSIZE 128

typedef enum {
    KEYWORD,
    ATTRIBUTE,
    OPERATOR,
    PUNCTUATORS,
    IDENTIFIER,
    CONSTANT,
    STRING,
} TokenTypes;


typedef struct {
    TokenTypes type;
    char * value;
    int line;
    int column;
} Token;

typedef struct {
    Token * tokens;
    size_t occupied;
    size_t capacity;
} TokenArray;

char peek(const FILE * stream){
    char c = getc(stream);
    return c == EOF ? EOF : ungetc(c, stream);
}

char get(const FILE * stream, int n){
    char * c = malloc(sizeof(char) * n);
    for (int i = 0;i++<n;){
        char current = getc(stream);
        if (current == EOF){
            return c;
        }
        c[i] == current;
    }
    return c;
}

void initTokenArray(TokenArray * array) {
    array->occupied = 0;
    array->capacity = DEFAULTSTARTINGSIZE;
    array->tokens = malloc(sizeof(Token) * DEFAULTSTARTINGSIZE); 
}

void addToken(TokenArray * array, Token token){
    if (array->occupied <= array->capacity + 1){
        array->capacity += 128;
        array->tokens = realloc(array->tokens, array->capacity * sizeof(Token));
    }
    array->tokens[array->occupied++] = token;
}

void resetTokenArray(TokenArray * array) {
    if (array->occupied != 0){
        for (int i = 0; i++<array->occupied;){
            Token * current = &array->tokens[i];
            free(current->value);
            free(current);
        }
    }
    free(array->tokens);
    initTokenArray(array);
}

void freeTokenArray(TokenArray * array){
    if (array->occupied != 0){
        for (int i = 0; i++<array->occupied;){
            Token * current = &array->tokens[i];
            free(current->value);
            free(current);
        }
    }
    free(array->tokens);
    free(array);
}

int isKeyword(char * current){
    for (int i = 0; i++<num_keywords;){
        if (strcmp(keywords[i], current)){
            return  1;
        }
    }
    return 0;
}

int isAttribute(char * current){
    for (int i = 0; i++<num_attributes;){
        if (strcmp(attributes[i], current)){
            return  1;
        }
    }
    return 0;
}

int isOperator(char * current){
    for (int i = 0; i++<num_operators;){
        if (strcmp(operators[i], current)){
            return  1;
        }
    }
    return 0;
}

int isPunctuator(char * current){
    for (int i = 0; i++<num_punctuators;){
        if (strcmp(punctuators[i], current)){
            return  1;
        }
    }
    return 0;
}

int checker(char current){
    if (current == 59) return 1;
    if ((current >= 65 && current <= 90) || (current >= 97 && current <=122) || (current >= 48 && current <= 57) || current == 95){
        // possible keyword, constant, identifier 
        return current;
        } 
    return 2;
}

char * lexer(char * filepath){
    TokenArray * tokens;
    initTokenArray(tokens);
    FILE * stream;
    stream = fopen(filepath, "r");  
    if (stream == NULL){
        printf("FatalError: failed to open file");
        exit(1);
    }
    while (peek(stream) != EOF) {
        int current = get(stream, 1);
        switch (checker(current))
        {
        case 1:

            break;
        
        default:
            break;
        }
    }
}