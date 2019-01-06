/* -------declaration priority queue BEGIN----------------------- */

typedef int dataTypeHeap;

#define PQ_SIZE 200000

typedef struct {
	dataTypeHeap *q; // body of queue start from 1
	int n;                       // number of elements
} priorityQueue;

/* -------declaration priority queue END------------------------- */

int headCmp(dataTypeHeap a, dataTypeHeap b) {

	/* a < b return 1 =>> max heap */
	/* a > b return 1 =>> min heap */

	if (a < b) return(1);

	if (a == b) return(0);
	return(-1);
}

/* -------------------------------------------------------- */

void pq_init(priorityQueue *q) {

	q->n = 0;
	
	q->q = (dataTypeHeap *) malloc( (PQ_SIZE + 1) * sizeof(dataTypeHeap) );
	if (q->q == NULL) {
		printf("PQ_SIZE to too large ! \n");
		exit(1);
	}
	return;
}

int pqParent(int n) {
	if (n == 1) return(-1);
	else return( (int) n/2 );
}

int pqChild(int n) {
	return(2 * n);
}

void pqSwap(priorityQueue *q, int indexA, int indexB) {

	dataTypeHeap temp;
	temp = q->q[indexA];
	q->q[indexA] = q->q[indexB];
	q->q[indexB] = temp;
	return;
}

void bubbleUp(priorityQueue *q, int p) {

	if (pqParent(p) == -1) return; // at the root of heap, no parent

	if ( headCmp(q->q[pqParent(p)], q->q[p]) == 1 ) {
		pqSwap(q, p, pqParent(p));
		bubbleUp(q, pqParent(p));
	}
}

void pqInsert(priorityQueue *q, dataTypeHeap x) {

	if (q->n >= PQ_SIZE) {
		printf("Heap overflow! \n");
	}
	else {
		q->n += 1;
		q->q[ q->n ] = x;
		bubbleUp(q, q->n);
	}
	return;
}

void bubbleDown(priorityQueue *q, int p) {
	int c;            // child index
	int i;            // counter
	int extreIndex;   // index of min/max child

	c = pqChild(p);
	extreIndex = p;

	for (i = 0; i < 2; i++) {
		if ((c + i) <= q->n) {
			if ( headCmp(q->q[extreIndex], q->q[c + i]) == 1 ) {
				extreIndex = c + i;
			} 
		}
	}

	if (extreIndex != p) {
		pqSwap(q, p, extreIndex);
		bubbleDown(q, extreIndex);
	}
}

void makeHeap(priorityQueue *q, dataTypeHeap arr[], int n) {

	// O(n)

	int i;
	q->n = n;

	for (i = 0; i < n; i++) q->q[i + 1] = arr[i];

	for (i = q->n; i >= 1; i--) bubbleDown(q, i);

	return;
}

dataTypeHeap extractPeak(priorityQueue *q) {

	dataTypeHeap peakVal;  // modify here empty value of data type
	/* strcpy(peakVal.name, "NULL"); */
	/* strcpy(peakVal.reverseName, "NULL"); */

	if (q->n <= 0) {
		printf("Empty Heap!\n");
	}
	else {
		peakVal = q->q[1];

		q->q[1] = q->q[ q->n ];
		q->n -= 1;

		bubbleDown(q, 1);
	}

	return(peakVal);
}

/*  --------priority queue END ----------------------------------------*/

void heapSort(dataTypeHeap arr[], int n) {

	int i;
	
	priorityQueue q;
	pq_init(&q); // very important

	makeHeap(&q, arr, n);

	for (i = 0; i < n; i++) {
		arr[i] = extractPeak(&q);
	}
	
	return;
}
