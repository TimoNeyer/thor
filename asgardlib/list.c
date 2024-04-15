#include <stdlib.h>
#include <math.h>
#include <string.h>

#define STARTVALUE 4

#include "hashmap.h"
#include "dynstring.h"

typedef enum {
    INT,
    FLT,
    DBL,
    PTR,
    CHRP,   // charpointer
    STR,    // string
    MAP,    // hashmap
    LIT,    // Listitem
    LST     // List
}Type;

typedef struct {
    Type type;
    void * ptr;
    short int ptrdepths;
} ListItem;

typedef struct {
    ListItem ** content;
    size_t sizeel;
    size_t size;
    size_t used;
}List;

void free_ListItem(ListItem * item){
    if (!item->ptrdepths){
        free(item->ptr);
        free(item);
    }else if (item->type < PTR){
        return;
    }
    switch (item->type)
    {
    case STR:
        str_free((str *)item->ptr);
        break;
    
    case MAP:
        hashmap_free((struct hashmap *) item->ptr);
        break;
    
    case LIT:
        free_ListItem((ListItem *)item->ptr);
        break;

    case LST:
        free_List((List *)item->ptr);
        break;
    
    default:
        perror("failed to get type of ListItem");
        break;
    }
}

void free_List(List * list){
    for (int i = 0; i++<list->used;){
        free_ListItem(list->content[i]);
    }
}

List * mklist(){
    List * new;
    new = malloc( STARTVALUE * sizeof(List));
    new->sizeel = sizeof(ListItem);
    new ->size = STARTVALUE;
    new->used = 0;
    new->content = malloc(STARTVALUE * sizeof(ListItem)); 
}

ListItem * mkItem(void * ptr, int ptrdepths, Type type){
    ListItem * new = malloc(sizeof(ListItem));
    new->ptr = ptr;
    new->ptrdepths = ptrdepths;
    new->type = type;
}

void list_push(List * source, ListItem * item, short int freeitem){
    if (source->used == source->size){
        source->content = realloc(source->content, (size_t) pow(source->size, 2));
    }
    source->content[source->used++] = item;
    if (freeitem) free(item);
}

ListItem * list_pop(List * source, short int safe) {
    if (safe){
        void * item = source->content[source->used];
        source->content[source->used--] = NULL;
        return item;
    }
    return source->content[source->used--];
}

void * list_get(List * source, int index){
    if (source->used >= index) perror("index out of range");
    return source->content[index];
}

void list_insert(List * source, ListItem * item, int index, short int freeitem){
    if (source->used >= index) perror("index out of range");
    if (source->size +1 == source->used) source->content = realloc(source->content, (size_t) pow(source->size, 2));
    mempcy(source->content[index + 1], source->content[index], source->sizeel * (source->used - index));
    memcpy(source->content[index], item, source->sizeel);
    if (freeitem) free(item);
}

ListItem * list_remove(List * source, int index, short int dofree){
    if (source->used >= index) perror("index out of range");
    ListItem * item = dofree ? NULL : source->content[index];
    memcpy(source->content[index], source->content[index +1], source->sizeel);
    source->used--;
    return item;
}