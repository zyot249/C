#ifndef __STACK_INT_H__
#define __STACK_INT_H__

#include <stdlib.h>

typedef struct stackNode {
	int data;
	struct stackNode *next;
} stackNode;

stackNode *newStackNode(int data) {

	stackNode *node = (stackNode *)malloc(sizeof(stackNode));
	node->data = data;
	node->next = NULL;
	
	return node;
}

int isEmpty(stackNode *root) {

	return( !root );
}

void push(stackNode **root, int data) {

	stackNode *node = newStackNode(data);

	node->next = *root;
	*root = node;
	return;
}

int pop(stackNode **root) {

	if ( isEmpty(*root) ) {
		printf("Stack is empty!\n");
		return(-1);
	}
	
	stackNode *temp = *root;
	*root = (*root)->next;
	
	int popped = temp->data;
	free(temp);

	return(popped);
}

int peek(stackNode *root) {

	if ( isEmpty(root) ) {
		printf("Stack is empty!\n");
		return(-1);
	}

	return(root->data);
}

void print_stack(stackNode **root) {

	stackNode *temp = *root;
	
	while (temp != NULL) {
		printf(" %d", temp->data);
		temp = temp->next;
	}
	
	return;
}

#endif
