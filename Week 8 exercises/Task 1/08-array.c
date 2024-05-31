#include <stdlib.h>
#include <stdio.h>

#ifndef  ELT_T
# define ELT_T int
#endif

struct Array {
    ELT_T *elements;    // memory containing
    size_t size;    // this many elements
};

/* make a new Array and pre-allocate enough space for size elements
 */
struct Array *newArray(size_t size) {
    struct Array *array = malloc(sizeof(struct Array));
    array->elements = calloc(size, sizeof(ELT_T));
    array->size = size;
    return array;
}

size_t Array_size(struct Array *array) {
    return array->size;
}

/* print a message and exit if index is not within the bounds of the array
 */
void Array__boundsCheck(struct Array *array, size_t index) {
    if (index >= array->size) {
        fprintf(stderr, "index %zi is out of bounds for array of size %zi\n", index, array->size);
        exit(1);
    }
}

/* return the element of the array at the given index
 */
ELT_T Array_get(struct Array *array, size_t index) {
    Array__boundsCheck(array, index);
    return array->elements[index];
}

/* store the element into the array at the given index
 */
void Array_put(struct Array *array, size_t index, ELT_T element) {
    Array__boundsCheck(array, index);
    array->elements[index] = element;
}

/* store the element into the array at the given index
 */
void Array_append(struct Array *array, ELT_T element) {
    array->size += 1;
    array->elements = realloc(array->elements, sizeof(ELT_T) * array->size);
    array->elements[array->size - 1] = element;
}

ssize_t Array_linSearch(struct Array *array, ELT_T element) {
    for (size_t i = 0; i < array->size; i++) {
        if (array->elements[i] == element) {
            return i;
        }
    }
    return -1;
}