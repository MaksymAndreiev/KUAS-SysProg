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

void Queue_grow(struct Queue *queue) {
    size_t new_capacity = queue->capacity * 2;
    ELT_T *new_elements = malloc(sizeof(ELT_T) * new_capacity);
    size_t first_fragment_size = queue->capacity - queue->outdex; // first fragment is from outdex to the end of the array
    size_t second_fragment_size = queue->index; // second fragment is from the index to the end of the new array

    for (size_t i = 0; i < first_fragment_size; ++i) {
        new_elements[i] = queue->elements[(queue->outdex + i) % queue->capacity];
    }

    for (size_t i = 0; i < second_fragment_size; ++i) {
        new_elements[first_fragment_size + i] = queue->elements[i];
    }

    free(queue->elements);
    queue->elements = new_elements;
    queue->capacity = new_capacity;
    queue->outdex = 0;
    queue->index = first_fragment_size + second_fragment_size;
}

void Queue_add(struct Queue *queue, ELT_T element) {
    if (Queue_isFull(queue)) {
        // grow the array
        Queue_grow(queue);
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

    printf("queue capacity: %zu\n", queue->capacity);
    Queue_add(queue, 32 * 32);
    printf("queue capacity: %zu\n", queue->capacity);

    for (int i = 1; i < 33; ++i) {
        Queue_remove(queue);
    }
    assert(Queue_isEmpty(queue));

    printf("all tests passed\n");

    return 0;
}

