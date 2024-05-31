#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

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

void quickSort(char *array[], int left, int right){
    int i, j;
    char *pivot, *temp;
    if(left < right){
        i = left;
        j = right + 1;
        pivot = array[left];
        do{
            do{
                i++;
            }while(strcmp(array[i], pivot) < 0);
            do{
                j--;
            }while(strcmp(array[j], pivot) > 0);
            if(i < j){
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }while(i < j);
        temp = array[left];
        array[left] = array[j];
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
    char *strings[] = {"the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
    quickSort(strings, 0, sizeof(strings) / sizeof(*strings) - 1);
    for(int i = 0; i < sizeof(strings) / sizeof(*strings); i++){
        printf("%s ", strings[i]);
    }

    return 0;
}
