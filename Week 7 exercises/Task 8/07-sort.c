#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef struct TreeNode {
    int value;
    int count;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->value = value;
    node->count = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Insert a value into the BST
TreeNode* insert(TreeNode* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value == root->value) {
        root->count++;
    } else if (value < root->value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

// In-order traversal to copy elements back to the array
void inOrderTraversal(TreeNode* root, int* array, int* index) {
    if (root != NULL) {
        inOrderTraversal(root->left, array, index);
        for (int i = 0; i < root->count; i++) {
            array[(*index)++] = root->value;
        }
        inOrderTraversal(root->right, array, index);
    }
}

// Delete the BST
void deleteTree(TreeNode* root) {
    if (root != NULL) {
        deleteTree(root->left);
        deleteTree(root->right);
        free(root);
    }
}

// TreeSort function
void treeSort(int array[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert(root, array[i]);
    }
    int index = 0;
    inOrderTraversal(root, array, &index);
    deleteTree(root);
}

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

#define NMAX 400000 // increase to maximum required number of elements in the array

int array[NMAX];

int main(int argc, char **argv){
    unsigned long start, end;
    // fill array with NMAX random numbers
    fill(array, 0, NMAX - 1);

    start = millis();
    // sort the contents
    quickSort(array, 0, NMAX - 1);
    end = millis();
    printf("Quick sort took %lu milliseconds\n", end - start);

    start = millis();
    // sort the contents
    treeSort(array, NMAX - 1);
    end = millis();
    printf("Tree sort took %lu milliseconds\n", end - start);
    return 0;
}
