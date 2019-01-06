#ifndef __STACK_H
#define __STACK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*----------- declararation -----------------------------------*/

typedef struct _stackNode {
	void *data;
	struct _stackNode *next;
} stackNode;

typedef struct {
	int size;
	int elementSize;
	stackNode *top;
} stack;

stack *newStack(int elementSize) {

	stack *newStack = (stack *) malloc(sizeof(stack));
	newStack->size = 0;
	newStack->elementSize = elementSize;
	newStack->top = NULL;
	
	return(newStack);
}

void push(stack *stack, void *data) {

	stackNode *newNode = malloc(sizeof(stackNode));

	newNode->data = malloc(stack->elementSize);
	newNode->data = data;
	
	newNode->next = stack->top;
	stack->top = newNode;

	stack->size ++;
	return;
}

void *pop(stack *stack) {

	if (stack->top == NULL) {
		printf("Empty stack! Can not pop !\n");
		return(NULL);
	}
	
	void *data = malloc(sizeof(stack->elementSize));
	data = stack->top->data;

	stackNode *temp = stack->top;

	stack->top = stack->top->next;
	free(temp);
	
	stack->size --;
	return(data);
}

int emptyStack(stack *stack) {

	if (stack->top == NULL) {
		return(1);
	}
	
	return(0);
}


void *top(stack *stack) {

	void *data = malloc(stack->elementSize);

	data = stack->top->data;
	
	return(data);
}

void freeStack(stack *stack) {

	stackNode *curr = stack->top;
	stackNode *prev = NULL;
	
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}

	stack->elementSize = 0;
	stack->size = 0;
	return;
}

#endif

