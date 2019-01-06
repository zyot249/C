#ifndef __SLL_H
#define __SLL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*------------------------type declaration------------------------*/

typedef struct _SLLNode {
	void *data;
	struct _SLLNode *next;
} SLLNode;

typedef struct {
	SLLNode *head;
	SLLNode *tail;
	int size;
	int elementSize;
} SLL


/*-----------------------------------------------------------------*/

typedef void (*todo)(void *data);

/*-----------------------------------------------------------------*/

void iteratorSLL(SLL *list, todo toDo) {
	SLLNode *curr = list->head;
	while (curr != NULL) {
		toDo(curr->data);
		curr = curr->next;
	}
	return;
}

SLL *newSLL(int elementSize) {

	SLL *list = (SLL *)malloc(sizeof(SLL));

	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	list->elementSize = elementSize;
	
	return(list);
}

SLLNode *makeNewSLLNode(void *data) {

	SLLNode *newNode = (SLLNode *)malloc(sizeof(SLLNode));

	newNode->data = data;
	newNode->next = NULL;
	return(newNode);
}

void insertAtHead(SLL *list, void *data) {

	SLLNode *newNode = makeNewSLLNode(data);

	if (list->head == NULL) {
		list->head = list->tail = newNode;
		return;
	}

	newNode->next = list->head;
	list->head = newNode;

	list->size ++;
	return;
}

void insertAtTail(SLL *list, void *data) {

	SLLNode *newNode = makeNewSLLNode(data);

	if (list->tail == NULL) {
		list->head = list->tail = newNode;
		return;
	}

	list->tail->next = newNode;
	list->tail = newNode;

	list->size ++;
	return;
}

void insertAfter(SLL *list, SLLNode *targetNode, void *data) {

	if (targetNode == list->tail) {
		insertAtTail(list, data);
		return;
	}

	SLLNode *newNode = makeNewSLLNode(data);

	newNode->next = targetNode->next;
	targetNode->next = newNode;

	list->size ++;
	return;
}

void insertBefore(SLL *list, SLLNode *targetNode, void *data) {

	if (targetNode == list->head) {
		insertAtHead(list, data);
		return;
	}

	SLLNode *prev = NULL;
	SLLNode *curr = list->head;
	while (curr != targetNode && curr != NULL) {
		prev = curr;
		curr = curr->next;
	}

	if (curr == NULL) {
		printf("The target node not found! \n");
		return;
	}

	SLLNode *newNode = makeNewSLLNode(data);

	prev->next = newNode;
	newNode->next = curr;

	list->size ++;
	return;
}

void delete(SLL *list, SLLNode *targetNode) {

	if (targetNode == list->head) {
		list->head = list->head->next;
		free(targetNode);
		return;
	}

	SLLNode *prev = NULL;
	SLLNode *curr = list->head;
	while (curr != targetNode && curr != NULL) {
		prev = curr;
		curr = curr->next;
	}

	if (curr == NULL) {
		printf("The target node not found!\n");
		return;
	}

	if (curr == list->tail) {
		prev->next = NULL;
		list->tail = prev;
		return;
	}

	prev->next = curr->next;
	free(curr);

	list->size --;
	return;
}

void freeSLL(SLL *list) {

	SLLNode *curr = list->head;
	SLLNode *prev = NULL;
	
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}

	list->head = list->tail = NULL;
	list->size = 0;
	return;
}

#endif
