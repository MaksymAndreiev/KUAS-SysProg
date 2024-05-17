#define ELEMENT_T const char *
#include "tree.c"
#include <string.h>

void printChar(const char *c){
    printf("%s ", c);
}

int main(){
    struct Tree *t = 0;
    Tree_insert(&t, "those", strcmp);
    Tree_insert(&t, "who", strcmp);
    Tree_insert(&t, "do", strcmp);
    Tree_insert(&t, "not", strcmp);
    Tree_insert(&t, "learn", strcmp);
    Tree_insert(&t, "from", strcmp);
    Tree_insert(&t, "history", strcmp);
    Tree_insert(&t, "are", strcmp);
    Tree_insert(&t, "doomed", strcmp);
    Tree_insert(&t, "to", strcmp);
    Tree_insert(&t, "repeat", strcmp);
    Tree_insert(&t, "it", strcmp);

    Tree_applyInOrder(t, printChar);
    return 0;
}
