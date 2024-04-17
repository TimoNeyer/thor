#pragma once
#define DYNSTRING_H

typedef struct {
    int size;
    int used;
    char * content
}str;

str * get_new_string(char * string);
str * get_new_string(char * string);
void str_free(str * string);
str * append(str * base, str * item, short int dofree);
str * append_char(str * base, char * item, short int dofree);
void insert(str * base, str * new, int index, short int dofree);
str ** str_split(str * base, char * delim);

