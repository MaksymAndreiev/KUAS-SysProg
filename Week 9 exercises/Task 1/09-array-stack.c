#include <assert.h>

#define ELT_T int

#include "09-array.c"

#define Stack            Array
#define newStack()        newArray(0)
#define Stack_push(S, E)  Array_append(S, E)
#define Stack_pop(S)      Array_removeLast(S)
#define Stack_isEmpty(S)    Array_isEmpty(S)
#define Stack_top(S)      Array_last(S)
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
