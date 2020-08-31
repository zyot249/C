#include <stdio.h>
#include <stdlib.h>
#include "arrutils.h"

void selectionSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int max = arr[i];
        int maxIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] > max) {
                max = arr[j];
                maxIndex = j;
            }
        }
        if (maxIndex != i)
            swap(&arr[maxIndex], &arr[i]);
    }
}

int main() {
    int n = 10;
    int* arr = generateRandomArray(n);
    display(arr, n);
    selectionSort(arr, n);
    display(arr, n);
    return 0;
}