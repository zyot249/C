
#include "queue.h" // require queue.h

/*--------------Declaration BEGIN ---------------------------- */

typedef int sortDataType;

int mergeCmp(sortDataType a, sortDataType b) {

	// a < b return(1) =>> increasing
	// a > b return(1) =>> decreasing

	if (a > b) return(1);

	if (a == b) return(0);

	return(-1);
}

/*--------------Declaration END  ----------------------------- */

void merge(sortDataType arr[], int low, int mid, int high) {

	int i;
	
	queue buffer1;
	queue buffer2;

	queue_init(&buffer1);
	queue_init(&buffer2);

	for (i = low; i <= mid; i++) enQueue(&buffer1, arr[i]);
	for (i = mid + 1; i <= high; i++) enQueue(&buffer2, arr[i]);

	i = low;

	while ( !isEmptyQueue(&buffer1) && !isEmptyQueue(&buffer2) ) {
		if ( mergeCmp(headQ(&buffer1), headQ(&buffer2)) == 1  )
			arr[i++] = deQueue(&buffer1);
		else
			arr[i++] = deQueue(&buffer2);
	}

	while ( !isEmptyQueue(&buffer1) ) arr[i++] = deQueue(&buffer1);
	while ( !isEmptyQueue(&buffer2) ) arr[i++] = deQueue(&buffer2); 
	
	return;
}

void mergeSort(sortDataType arr[], int low, int high) {

	int i;
	int mid;

	if (low < high) {
		mid = (low + high) / 2;
		mergeSort(arr, low, mid);
		mergeSort(arr, mid + 1, high);
		merge(arr, low, mid, high);
	}
	
	return;
}
