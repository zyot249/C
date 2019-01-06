#ifndef __QUEUE_INT_H__
#define __QUEUE_INT_H__

// A linked list node to store a queue entry
struct QNode
{
    int data;
    struct QNode *next;
};

// The queue, front stores current node, rear stores the last node
typedef struct
{
    struct QNode *front, *rear;
} Queue;

// create a new linked list node.
struct QNode *newNode(int k)
{
    struct QNode *temp = (struct QNode*) malloc( sizeof(struct QNode) );
    temp->data = k;
    temp->next = NULL;
    return temp;
}

// create an empty queue
Queue *createQueue()
{
    Queue *q = (Queue*) malloc( sizeof(Queue) );
    q->front = q->rear = NULL;
    return q;
}

// add an item in queue
void enQueue(Queue *q, int data)
{
    struct QNode *temp = newNode(data);
    // if queue is empty the new node is front and rear both
    if (q->rear == NULL){
        q->front = q->rear = temp;
        return;
    }

    // add the new node at the end of queue and change rear
    q->rear->next = temp;
    q->rear = temp;
    return;
}

// remove an item from given queue
int deQueue(Queue *q)
{
    // if queue is empty, return NULL
    if (q->front == NULL) {
        printf("The Queue is empty!");
        return(-111);
    }

    // store previous front data and move front one node ahead
    int data = q->front->data;
    q->front = q->front->next;

    //if front become NULL, change rear also as NULL
    if (q->front == NULL){
        q->rear = NULL;
    }
    return data;
}

int empty_queue(Queue *q) {
	if (q->front == NULL)
		return(1);
	else
	   	return(0);
}

#endif
