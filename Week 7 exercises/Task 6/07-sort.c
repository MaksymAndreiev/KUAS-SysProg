#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void bubbleSort(int array[], int left, int right){
    int i, j, temp;
    for(i = left; i < right; i++){
        for(j = left; j < right - i; j++){
            if(array[j] > array[j + 1]){
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int array[], int left, int right){
    int i, j, min, temp;
    for(i = left; i < right; i++){
        min = i;
        for(j = i + 1; j <= right; j++){
            if(array[j] < array[min]){
                min = j;
            }
        }
        temp = array[i];
        array[i] = array[min];
        array[min] = temp;
    }
}

void insertionSort(int array[], int left, int right){
    int i, j, temp;
    for(i = left + 1; i <= right; i++){
        temp = array[i];
        j = i - 1;
        while(j >= left && array[j] > temp){
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = temp;
    }
}

void quickSort(int array[], int left, int right){
    int i, j, pivot, temp;
    if(left < right){
        pivot = left;
        i = left;
        j = right;
        while(i < j){
            while(array[i] <= array[pivot] && i < right){
                i++;
            }
            while(array[j] > array[pivot]){
                j--;
            }
            if(i < j){
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
        temp = array[pivot];
        array[pivot] = array[j];
        array[j] = temp;
        quickSort(array, left, j - 1);
        quickSort(array, j + 1, right);
    }
}

#include <sys/time.h>

unsigned long millis(void)
{
    struct timeval tv;
    static unsigned long epoch = 0;
    gettimeofday(&tv, 0);
    if (!epoch) epoch = tv.tv_sec * 1000L + tv.tv_usec / 1000;
    return tv.tv_sec * 1000L + tv.tv_usec / 1000 - epoch;
}

void fill(int array[], int left, int right)
{
    for (int i = left;  i <= right;  ++i)
	array[i] = rand() & 4095; // random number in the range [0..4095]
}

#define NMAX 48000 // increase to maximum required number of elements in the array

int array[NMAX];

int main(int argc, char **argv){
    unsigned long start, end;
    FILE *file = fopen("times.csv", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    for (int n = 2000; n <= 40000; n += 2000) {
        // fill array with n random numbers
        fill(array, 0, n - 1);

        // sort the contents using bubbleSort
        start = millis();
        bubbleSort(array, 0, n - 1);
        end = millis();
        unsigned long bubbleSortTime = end - start;

        // refill array with n random numbers
        fill(array, 0, n - 1);

        // sort the contents using selectionSort
        start = millis();
        selectionSort(array, 0, n - 1);
        end = millis();
        unsigned long selectionSortTime = end - start;

        // refill array with n random numbers
        fill(array, 0, n - 1);

        // sort the contents using insertionSort
        start = millis();
        insertionSort(array, 0, n - 1);
        end = millis();
        unsigned long insertionSortTime = end - start;

        // sort the contents using quickSort
        start = millis();
        quickSort(array, 0, n - 1);
        end = millis();
        unsigned long quickSortTime = end - start;

        // print the results to the file
        fprintf(file, "%d,%lu,%lu,%lu,%lu\n", n, bubbleSortTime, selectionSortTime, insertionSortTime,
                quickSortTime);
    }

    fclose(file);

    return 0;
}
