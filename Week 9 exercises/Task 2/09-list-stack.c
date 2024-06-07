#include <assert.h>

#define ELT_T int

#include "09-list.c"

#define Stack            List
#define newStack()        newList()
#define Stack_push(S, E)  List_addFirst(S, E) // Last in
#define Stack_pop(S)      List_removeFirst(S) // Last out
#define Stack_isEmpty(S)    List_isEmpty(S)
#define Stack_top(S)      List_first(S) // Last == first in a list
// add more #defines here

int main(int argc, char **argv) {
    struct Stack *stack = newStack();

    assert(Stack_isEmpty(stack));

    for (int i = 1; i < 10; ++i) {
        Stack_push(stack, i * i);
        assert(!Stack_isEmpty(stack));
        assert(Stack_top(stack) == i * i);
    }

    for (int i = 9; i > 0; --i) {
        assert(!Stack_isEmpty(stack));
        int j = Stack_pop(stack);
        assert(j == i * i);
    }

    assert(Stack_isEmpty(stack));

    printf("all tests passed\n");

    return 0;
}
