#include <stdlib.h>
#include <stdio.h>

#define ELEMENT_T int

struct Array {
    size_t size;
    ELEMENT_T *elements;
};

typedef struct Array Array;

Array *new_array(size_t size) {
    Array *array = calloc(1, sizeof(*array));
    array->size = size;
    array->elements = calloc(size, sizeof(*array->elements));
    return array;
}

Array *Array_clear(Array *a) {
    free(a->elements);
    a->elements = NULL;
    a->size = 0;
    return a;
}

void Array_delete(Array *a) {
    free(a->elements);
    free(a);
}

void Array__boundsCheck(Array *a, size_t index) {
    if (index >= a->size) {
        printf("Index out of bounds\n");
        exit(1);
    }
}

void Array_print(Array *a) {
    printf("Array %p(%p [%zi])\n", a, a->elements, a->size);
}

void Array_addLast(Array *a, ELEMENT_T element) {
    ELEMENT_T *new_member = realloc(a->elements, sizeof(ELEMENT_T) * (a->size + 1));
    if (!new_member) {
        perror("realloc");
        exit(-1);
    }
    a->elements = new_member;
    a->elements[a->size] = element;
    a->size++;
}

size_t Array_size(Array *a) {
    return a->size;
}

ELEMENT_T Array_get(Array *a, size_t index) {
    Array__boundsCheck(a, index);
    return a->elements[index];
}

ELEMENT_T Array_set(Array *a, size_t index, ELEMENT_T element) {
    Array__boundsCheck(a, index);
    a->elements[index] = element;
    return a->elements[index];
}

int main() {
    Array *a = new_array(8);

    Array_print(a);

    for (int i = 0; i < Array_size(a); ++i) {
        printf("[%d] %d\n", i, Array_set(a, i, i * i));
    }

    for (int i = 8; i <= 10; ++i) {
        Array_addLast(a, i * i);
    }

    for (int i = 0; i < Array_size(a); ++i) {
        printf("[%d] %d\n", i, Array_get(a, i));
    }

    Array_clear(a);
    Array_print(a);
    Array_delete(a);
    Array_print(a);

    return 0;
}