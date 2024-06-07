#include <assert.h>

#define ELT_T int

#include "09-list.c"

#define Queue            List
#define newQueue()        newList()
#define Queue_add(Q, E)        List_addLast(Q, E) // First in
#define Queue_remove(Q)        List_removeFirst(Q) // First out
#define Queue_isEmpty(Q)    List_isEmpty(Q)
#define Queue_first(Q)        List_last(Q) // First == last in a list
// add more #defines here

int main(int argc, char **argv) {
    struct Queue *queue = newQueue();

    assert(Queue_isEmpty(queue));

    for (int i = 1; i < 10; ++i) {
        Queue_add(queue, i * i);
        assert(!Queue_isEmpty(queue));
        assert(Queue_first(queue) == i * i);
    }

    for (int i = 1; i < 10; ++i) {
        assert(!Queue_isEmpty(queue));
        int j = Queue_remove(queue);
        assert(j == i * i);
    }

    assert(Queue_isEmpty(queue));

    printf("all tests passed\n");

    return 0;
}
