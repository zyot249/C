#include <stdio.h>
#include <stdlib.h>
#include "arrutils.h"

void heapify(int* arr, int n, int root) {
    int left = 2*root + 1;
    if (left >= n) 
        return;
    int right = 2*root + 2, max = root;
    if (arr[left] > arr[root]) {
        max = left;
    }

    if (right < n && arr[right] > arr[max]) {
        max = right;
    }

    if (max != root) {
        swap(&arr[max], &arr[root]);
        heapify(arr, n, max);
    }
}

void heapSort(int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    int n = 10;
    int* arr = generateRandomArray(n);
    display(arr, n);
    heapSort(arr, n);
    display(arr, n);
    return 0;
}