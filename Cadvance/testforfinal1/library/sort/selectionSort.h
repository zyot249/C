#ifndef __SELECTION_SORT_H
#define __SELECTION_SORT_H

#include <string.h>

/*------- Declaration BEGIN-------------------------------------------*/

typedef int dataTypeSort;

typedef int (*comparatorSelection)(void *a, void *b);

/* a > b return(1) => decresing order */
/* a < b return(1) => incresing order */

/*------- Declaration END ------------------------------------------- */

void swapSelection(dataTypeSort a, dataTypeSort b) {

	if (a > b) return(1);

	if (a == b) return(0);

	return(-1);
}


void selectionSort(
				   void *arr,
				   int n,
				   int elementSize,
				   comparatorSelection cmp
				   ) {

	int i, j;
	int extreIndex;
	
	for (i = 0; i < n; i++) {
		extreIndex = i;
		for (j = i + 1; j < n; j++) {
			if ( cmp(arr[j], &arr[extreIndex]) == 1) {
				extreIndex = j;
			}
		}

		selectionSwap(&arr[i], &arr[extreIndex]);
	}
	
	return;
}

#endif
