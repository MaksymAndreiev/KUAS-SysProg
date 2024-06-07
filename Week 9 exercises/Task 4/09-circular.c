#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ELT_T int

struct Queue {
    ELT_T *elements;
    size_t capacity;
    size_t index;
    size_t outdex;
};

struct Queue *newQueue(size_t size) {
    struct Queue *q = calloc(1, sizeof(struct Queue));
    q->elements = malloc(sizeof(ELT_T) * size);
    q->capacity = size;
    q->index = 0;
    q->outdex = 0;
    return q;
}

// implement the other required functions here

int Queue_isEmpty(struct Queue *queue) {
    return queue->index == queue->outdex; // if in index is the same as out index, the queue is empty
}

int Queue_isFull(struct Queue *queue) {
    return (queue->index + 1) % queue->capacity == queue->outdex;
}

void Queue_add(struct Queue *queue, ELT_T element) {
    if (Queue_isFull(queue)) {
        printf("Queue is full\n");
        exit(1);
    }
    queue->elements[queue->index] = element;
    queue->index = (queue->index + 1) % queue->capacity;
}

ELT_T Queue_remove(struct Queue *queue) {
    if (Queue_isEmpty(queue)) {
        printf("Queue is empty\n");
        exit(1);
    }
    ELT_T element = queue->elements[queue->outdex];
    queue->outdex = (queue->outdex + 1) % queue->capacity;
    return element;
}

ELT_T Queue_first(struct Queue *queue) {
    if (Queue_isEmpty(queue)) {
        printf("Queue is empty\n");
        exit(1);
    }
    return queue->elements[queue->outdex];
}

int main(int argc, char **argv) {
    struct Queue *queue = newQueue(32);

    assert(Queue_isEmpty(queue));

    for (int i = 1; i < 10; ++i) {
        Queue_add(queue, i * i);
        assert(!Queue_isEmpty(queue));
    }

    for (int i = 1; i < 10; ++i) {
        assert(!Queue_isEmpty(queue));
        assert(Queue_first(queue) == i * i);
        int j = Queue_remove(queue);
        assert(j == i * i);
    }

    assert(Queue_isEmpty(queue));

    for (int i = 1; i < 32; ++i) {
        assert(!Queue_isFull(queue));
        Queue_add(queue, i * i);
    }
    assert(Queue_isFull(queue));

    for (int i = 1; i < 32; ++i) {
        Queue_remove(queue);
    }
    assert(Queue_isEmpty(queue));

    printf("all tests passed\n");

    return 0;
}

