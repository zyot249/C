#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "arrutils.h"

void swap(int* a, int* b) { 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 

void display(int* arr, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

int* generateRandomArray(int n) {
    srand(time(0)); 
    int* newArr = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        newArr[i] = rand() % 100;
    }
    return newArr;
}