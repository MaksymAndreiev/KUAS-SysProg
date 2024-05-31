#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ELT_T int

#include "08-array.c"
#include "08-clock.c"

#define ARRAYSIZE  50000
#define FILENAME   "08-numbers-100000.txt"

int main(int argc, char **argv)
{
    struct Array *array = newArray(0);
    // create an array of random numbers
    array->elements = malloc(ARRAYSIZE * sizeof(int));
    for (int i = 0; i < ARRAYSIZE; i++) {
        array->elements[i] = rand() % 100000;
    }

    unsigned long start = microsecondClock();

    insertionSort(array);

    unsigned long stop = microsecondClock();

    printf("elapsed time: %f seconds\n", (stop - start) / 1000000.0);

    return 0;
}
