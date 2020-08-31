#include <stdio.h>
#include <stdlib.h>
#include "arrutils.h"

int partition(int* arr, int left, int right) {
    int pivot = arr[right];
    int i = left;
    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[right]);
    return i;
}

void quicksort(int* arr, int left, int right) {
    if (left < right) {
        int pivot = partition(arr, left, right);
        quicksort(arr, left, pivot - 1);
        quicksort(arr, pivot + 1, right);
    }    
}

int main() {
    int n = 10;
    int* arr = generateRandomArray(n);
    display(arr, n);
    quicksort(arr, 0, n - 1);
    display(arr, n);
    return 0;
}