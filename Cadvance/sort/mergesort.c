#include <stdio.h>
#include <stdlib.h>
#include "arrutils.h"

void merge (int* arr, int left, int mid, int right) {
    int i = left, j = mid + 1;
    while (i < j && j <= right) {
        if (arr[i] > arr[j]) {
            for (int k = j; k > i; k--) {
                swap(&arr[k], &arr[k - 1]);
            }
            i++;
            j++;
        } else {
            i++;
        }
    }
    
}

void mergeSort(int* arr, int left, int right) {
    int n = right - left + 1;
    if (n > 1) {
        int mid = (right + left)/2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int n = 10;
    int* arr = generateRandomArray(n);
    display(arr, n);
    mergeSort(arr, 0, n - 1);
    display(arr, n);
    return 0;
}