#ifndef __BUBBLESORT
#define __BUBBLESORT

#ifndef __SWAP_FUNCTION
#define __SWAP_FUNCTION

void swap(void *a, void *b, size_t elementSize) {
    void *tmp = malloc(elementSize);
    memcpy(tmp, a, elementSize);
    memcpy(a, b, elementSize);
    memcpy(b, tmp, elementSize);
    free(tmp);
}

#endif

typedef int (*comparator)(void const*, void const*);

void bubbleSort(void *arr, size_t n, size_t size, comparator cmp) {

	size_t i, j;
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - i - 1; j++) {
			char *ptr_1 = (char *)arr + j * size;
			char *ptr_2 = (char *)arr + (j + 1) * size;
			if ( cmp(ptr_1, ptr_2) >= 0) {
				swap(ptr_1, ptr_2, size);
			}
		}
	}
	
	return;
}

#endif
