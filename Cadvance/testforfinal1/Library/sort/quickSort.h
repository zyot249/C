
#ifndef __QUICKSORT
#define __QUICKSORT

#include <string.h>

typedef int (*comparator)(void const *, void const *);

#ifndef __SWAP_FUNCTION
#define __SWAP_FUNCTION

void swap(void *a, void *b, size_t elementSize){
    void *tmp = malloc(elementSize);
    memcpy(tmp, a, elementSize);
    memcpy(a, b, elementSize);
    memcpy(b, tmp, elementSize);
    free(tmp);
	return;
}

#endif

int partition_two_way(void *arr, int low, int high, int size, comparator cmp) {
  
	int i;           // counter
	int p;           // pivot element index
	int firsthing;   // divider position for pivot

	char *ptr_i;
	char *ptr_p;
	char *ptr_firsthing;

	p = high;        // choose the pivot is the last element in array
	firsthing = low;
	
	ptr_p = (char *)arr + p * size;
  
	for (i = low; i < high; i++) {
		ptr_i = (char *)arr + i * size;
		ptr_firsthing = (char *)arr + firsthing * size;

		if ( cmp(ptr_i, ptr_p) < 0 ) {
			swap(ptr_i, ptr_firsthing, size);
			firsthing++;
		}
	}

	ptr_firsthing = (char *)arr + firsthing * size;
	swap(ptr_p, ptr_firsthing, size);

	return firsthing;
}

void quick_sort_two_way (void *arr, int low, int high, int size, comparator cmp) {
	
	int p; // index of partition

	if ( low < high ) {
		p = partition_two_way(arr, low, high, size, cmp);
		quick_sort_two_way(arr, low, p - 1, size, cmp);
		quick_sort_two_way(arr, p + 1, high, size, cmp);
	}
	
	return;
}

void partition_three_way(void *arr, int low, int high, int *i, int *j, int size, comparator cmp)
{
	char *ptr_mid;
	char *ptr_high;
	char *ptr_low;
    // To handle 2 elements
    if (high - low <= 1)
    {
		ptr_high = (char *)arr + high *size;
		ptr_low = (char *)arr + low * size;
        if (cmp(ptr_high, ptr_low) < 0) {
			swap(ptr_high, ptr_low, size);
		}
            
        *i = low;
        *j = high;
        return;
    }
 
    int mid = low;
    void *ptr_pivot = malloc(size);

	ptr_high = (char *)arr + high * size;
	memcpy(ptr_pivot, ptr_high, size);
 
    while (mid <= high)
    {
		ptr_mid = (char *)arr + mid * size;
		ptr_high = (char *)arr + high * size;
		ptr_low = (char *)arr + low * size;;
		
        if (cmp(ptr_mid, ptr_pivot) < 0) {
			ptr_low = (char *)arr + (low++) * size;
			ptr_mid = (char *)arr + (mid++) * size;
			swap(ptr_low, ptr_mid, size);
		}
        else if (cmp(ptr_mid, ptr_pivot) == 0) {
            mid++;
		}
		else if (cmp(ptr_mid, ptr_pivot) > 0) {
			ptr_mid = (char *)arr + mid * size;
			ptr_high = (char *)arr + (high--) * size;
			swap(ptr_mid, ptr_high, size);
		}
    }
 
    *i = low - 1;
    *j = mid;
}

void quick_sort_three_way(void *arr, int low, int high, int size, comparator cmp)
{
    if (low >= high) return;
 
    int i, j;

    partition_three_way(arr, low, high, &i, &j, size, cmp);
    quick_sort_three_way(arr, low, i, size, cmp);
    quick_sort_three_way(arr, j, high, size, cmp);
}

#endif

