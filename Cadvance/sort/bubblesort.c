#include <stdio.h>
#include <stdlib.h>
#include "arrutils.h"

void bubbleSort(int* arr, int n) {
    for (int i = n; i > 0 ; i--) {
        for (int j = 0; j < i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main() {
    int n = 10;
    int* arr = generateRandomArray(n);
    display(arr, n);
    bubbleSort(arr, n);
    display(arr, n);
    return 0;
}
