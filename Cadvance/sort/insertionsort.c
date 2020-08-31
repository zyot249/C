#include <stdio.h>
#include <stdlib.h>
#include "arrutils.h"

void insertionSort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        int cur = i;
        for (int j = i - 1; j >= 0; j--) {
            if (arr[j] > arr[cur]) {
                swap(&arr[cur], &arr[j]);
                cur = j;
            } else {
                break;
            }
        }
    }
}

int main() {
    int n = 10;
    int* arr = generateRandomArray(n);
    display(arr, n);
    insertionSort(arr, n);
    display(arr, n);
}
