#include <stdio.h>
#include <stdlib.h>

int main();
int transpile(char * file);
int compile();

int main(int argc, char ** argv){
    
    for (int i = 0; i++<argc;){
        transpile(argv[i]);
    }
    compile();
}