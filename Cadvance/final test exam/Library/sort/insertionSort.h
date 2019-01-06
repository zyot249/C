// no need extra lib

/*------- Declaration BEGIN-------------------------------------------*/

typedef int sortDataType;

int insertionSortCmp(sortDataType a, sortDataType b) {

	/* a < b return 1 =>> inscreasing array */
	/* a > b return 1 =>> decreasing array */

	if (a > b) return(1);

	if (a == b) return(0);
	
	return(-1);
}

/*------- Declaration END ------------------------------------------- */

void insertionSwap(sortDataType *a, sortDataType *b) {

	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
	return;
}

void insertionSort(sortDataType arr[], int n) {

	int i, j;
	for (i = 1; i < n; i++) {
		j = i;
		while ( (j > 0) && insertionSortCmp(arr[j], arr[j-1]) == 1 ) {
			insertionSwap(&arr[j], &arr[j - 1]);
			j--;
		}
	}
	
	return;
}
