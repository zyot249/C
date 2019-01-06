#ifndef __QUEUE_H
#define __QUEUE_H

/* ----------Declarartion -------------------------------- */

typedef struct queueNode_ {
	void *data;
	struct queueNode_ *next;
} queueNode;

typedef struct {
	int size;
	int elementSize;
	queueNode *head;
	queueNode *tail;
} queue;

/*-------------------------------------------------------- */

queue *newQueue(int elementSize) {

	queue *newQ = (queue *) malloc(sizeof(queue));
	
	newQ->size = 0;
	newQ->elementSize = elementSize;
	newQ->head = NULL;
	newQ->tail = NULL;

	return(newQ);
}

int emptyQ(queue *Q) {

	if (Q->head == NULL) {
		return(1);
	}
	
	return(0);
}

void enQueue(queue *Q, void *data) {

	queueNode *newNode = (queueNode *) malloc(sizeof(queueNode));
	newNode->next = NULL;
	newNode->data = data;
	
	if (Q->head == NULL) {
		Q->head = Q->tail = newNode;
		Q->size ++;
		return;
	}

	Q->tail->next = newNode;
	Q->tail = newNode;
	Q->size ++;
	
	return;
}

void *deQueue(queue *Q) {

	if (Q->head == NULL) {
		printf("Empty Queue! Can not deQueue!\n");
		return(NULL);
	}

	if (Q->head == Q->tail) {
		
		void *data = Q->head->data;
		free(Q->head);
		Q->head = Q->tail = NULL;
		
		return(data);
	}

	void *data = Q->head->data;
	queueNode *temp = Q->head;
	
	Q->head = Q->head->next;
	free(temp);
	Q->size --;
	
	return(data);
}

void *headQ(queue *Q) {
	return(Q->head->data);
}

#endif 
