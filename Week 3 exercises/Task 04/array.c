#include <stdio.h>
#include <stdlib.h>

#ifndef ELEMENT_T
# define ELEMENT_T int
#endif

struct Array {
    size_t size;      // number of elements in array
    ELEMENT_T *elements;  // storage for size elements
};

/* Return a new, empty array.
 */
struct Array *newArray(void) {
    // size and elements are both initially 0
    return calloc(1, sizeof(struct Array));
}

struct Array *Array_clear(struct Array *a) {
    free(a->elements);
    a->elements = 0;
    a->size = 0;
    return a;
}

void Array_delete(struct Array *a) {
    free(a->elements);
    free(a);
}

/* Return the number of elements in the array.
 */
size_t Array_size(struct Array *array) {
    return array->size;
}

/* Append an element to the end of the array.
 */
void Array_addLast(struct Array *array, ELEMENT_T element) {
    size_t lastIndex = array->size;
    size_t newSize = lastIndex + 1;
    // if elements is 0, realloc will allocate the initial storage
    array->elements = realloc(array->elements, sizeof(ELEMENT_T) * newSize);
    array->elements[lastIndex] = element;
    array->size = newSize;
}

/* Store the element into the array at the given index.
 * Print an error message and exit if the index is out of bounds.
 */
void Array_set(struct Array *array, size_t index, ELEMENT_T element) {
    if (index >= array->size) {
        fprintf(stderr, "index %zi too large for array size %zi\n", index, array->size);
        exit(1);
    }
    array->elements[index] = element;
}

/* Return the element stored in array at the given index.
 * Print an error message and exit if the index is out of bounds.
 */
ELEMENT_T Array_get(struct Array *array, size_t index) {
    if (index >= array->size) {
        fprintf(stderr, "index %zi too large for array size %zi\n", index, array->size);
        exit(1);
    }
    return array->elements[index];
}

ELEMENT_T Array_first(struct Array *array) {
    if (Array_size(array) == 0) {
        fprintf(stderr, "Array is empty\n");
        exit(1);
    }
    return Array_get(array, 0);
}

ELEMENT_T Array_last(struct Array *array) {
    if (Array_size(array) == 0) {
        fprintf(stderr, "Array is empty\n");
        exit(1);
    }
    return Array_get(array, Array_size(array) - 1);
}

ELEMENT_T Array_removeLast(struct Array *array) {
    if (Array_size(array) == 0) {
        fprintf(stderr, "Array is empty\n");
        exit(1);
    }
    ELEMENT_T last = Array_last(array);
    array->size--;
    return last;
}

#ifdef UNIT_TEST

#include <assert.h>

int main(int argc, char **argv)
{
    struct Array *array = newArray();

    for (int i = 0;  i < 10;  ++i) {
    assert(Array_size(array) == i);
    Array_addLast(array, i*i);
    }

    for (int i = 0;  i < 10;  ++i) {
    printf("%d\n", Array_get(array, i));
    assert(Array_get(array, i) == i*i);
    }

    assert(Array_size(array) == 10);
    Array_clear(array);
    assert(Array_size(array) == 0);

    for (int i = 0;  i < 5;  ++i) {
    assert(Array_size(array) == i);
    Array_addLast(array, i*i);
    }
    assert(Array_size(array) == 5);

    assert(Array_first(array) == 0);
    assert(Array_last(array) == 16);

    while(Array_size(array) > 0) {
        int i = Array_size(array) - 1;
        assert(i*i==Array_removeLast(array));
        assert(Array_size(array) == i);
    }

    printf("all tests passed\n");

    return 0;
}

#endif
