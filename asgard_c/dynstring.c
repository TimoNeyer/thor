#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MINSIZE 8

#include "dynstring.h"

str * get_new_string(char * string);


str* get_new_string(char * string){
    str* new;
    new->size = MINSIZE > strlen(string) ? MINSIZE : strlen(string);
    new = malloc(new->size * sizeof(char));
    new->used = new->size - strlen(string);
    return new;
}

void str_free(str * string){
    free(string->content);
    free(string);
}

str *  append(str * base, str * item, short int dofree){
    str * new = get_new_string(base->content);
    if (dofree) str_free(base);
    new->content = realloc(new->content, new->size + item->size);
    memcpy(new->content[new->size], item->content, item->size);
    new->size += item->size; 
    if (dofree) str_free(item);
    return new;
}

str * append_char(str * base, char * item, short int dofree){
    str * new = get_new_string(base->content);
    if (dofree) str_free(base);
    size_t sizeb = strlen(item);
    new->content = realloc(new->content, new->size + sizeb);
    memcpy(new->content[new->size], item, sizeb);
    new->size += sizeb; 
    if (dofree) free(item);
    return new;
}

void insert(str * base, str * new, int index, short int dofree){
    assert(base->size >= index);
    size_t tobemoved = base->size - index;
    base->content = realloc(base->content, base->size + new->size);
    memcpy(base->content[index], new->content, new->size);
    if (dofree) str_free(new);
}

str ** str_split(str * base, char * delim){
    str * current = get_new_string("");
    str ** list = malloc(MINSIZE * sizeof(str));
    for (int i = 0; i++<base->size;){
        if (base->content[i] == delim){
            
        } else {
            //append_char(current, base->content[i]);
        }

    }
}