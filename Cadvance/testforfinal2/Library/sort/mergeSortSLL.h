#ifndef __MERGER_SORT_SLL_H
#define __MERGER_SORT_SLL_H

#include "../ADT/SLL.h"
/*--------------Declaration BEGIN ---------------------------- */

typedef int (*mergeSLLCmp)(void *, void *);

/* example of int comparator function 

int cmpInt(void *a, void *b) {
	int valA = *(int *)a;
	int valB = *(int *)b;

	if (valA > valB) return(1);
	if (valA == valB) return(0);

	return(-1);
}

*/
/*--------------Declaration END  ----------------------------- */

void frontBackSplit(
					SLLNode *source,
					SLLNode **frontRef,
					SLLNode **backRef) {
	SLLNode *fast_p = source->next;
	SLLNode *slow_p = source;

	while (fast_p != NULL) {
		fast_p = fast_p->next;
		if (fast_p != NULL) {
			fast_p = fast_p->next;
			slow_p = slow_p->next;
		}
	}
	/* 'slow' is before the midpoint in the list, so split it in two
    at that point. */

	*frontRef = source;
	*backRef = slow_p->next;
	slow_p->next = NULL;
	return;
}

SLLNode *sortedMerge(SLLNode *a, SLLNode *b, mergeSLLCmp cmp) {

	if (a == NULL) return(b);
	if (b == NULL) return(a);

	SLLNode *result;
	
	if (cmp(a->data, b->data) == 1) {
		result = a;
		result->next = sortedMerge(a->next, b, cmp);
	}
	else {
		result = b;
		result->next = sortedMerge(a, b->next, cmp);
	}
	
	return(result);
}

void mergerSortSLLUtility(SLLNode **headRef, mergeSLLCmp cmp) {

	SLLNode *head = *headRef;

	SLLNode *a;
	SLLNode *b;

	if (head == NULL || head->next == NULL) {
		return;
	} 

	frontBackSplit(head, &a, &b);

	mergerSortSLLUtility(&a, cmp);
	mergerSortSLLUtility(&b, cmp);

	*headRef = sortedMerge(a, b, cmp); 
}

void mergerSortSLL(SLL *list, mergeSLLCmp cmp) {

	mergerSortSLLUtility(&(list->head), cmp);

	SLLNode *curr = list->head;

	while (curr->next == NULL) {
		curr = curr->next;
	}

	list->tail = curr;
	return;
}

#endif
