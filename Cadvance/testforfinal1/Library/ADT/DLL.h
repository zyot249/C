/*---------Type declaration------------------------------------*/

typedef int dataTypeDLL;

typedef struct DLLNode {
	dataTypeDLL data;
	struct DLLNode *next;
	struct DLLNode *prev;
} DLLNode;

typedef struct {
	DLLNode *head;
	DLLNode *tail;
} DLL;

/*---------------------------------------------------------------*/

void displayDLLNode(DLLNode *node) {

	printf("%d - ",  node->data);
	return;
} 

/*-------------------------------------------------------------- */

void DLL_init(DLL *list) {

	list->head = NULL;
	list->tail = NULL;
	return;
}

DLLNode *makeNewDLLNode(dataTypeDLL data) {

	DLLNode *newNode = (DLLNode *) malloc(sizeof(DLLNode));

	newNode->data = data;
	newNode->prev = NULL;
	newNode->next = NULL;

	return(newNode);
}

void insertAtHead(DLL *list, dataTypeDLL data) {

	DLLNode *newNode = makeNewDLLNode(data);
	if (list->head == NULL) {
		list->head = list->tail = newNode;
		return;
	}

	newNode->next = list->head;
	list->head->prev = newNode;
	list->head = newNode;
	return;
}

void insertAtTail(DLL *list, dataTypeDLL data) {

	DLLNode *newNode = makeNewDLLNode(data);
	if (list->tail == NULL) {
		list->head = list->tail = newNode;
		return;
	}

	list->tail->next = newNode;
	newNode->prev = list->tail;
	list->tail = newNode;
	return;
}

void insertAfter(DLL *list, DLLNode *targetNode, dataTypeDLL data) {

	if (targetNode == list->tail) {
		insertAtTail(list, data);
		return;
	}

	DLLNode *newNode = makeNewDLLNode(data);

	newNode->next = targetNode->next;
	newNode->prev = targetNode;
	targetNode->next = newNode;
	newNode->next->prev = newNode;
	return;
}

void insertBefore(DLL *list, DLLNode *targetNode, dataTypeDLL data) {

	if (targetNode == list->head) {
		insertAtHead(list, data);
		return;
	}

	DLLNode *newNode = makeNewDLLNode(data);

	newNode->next = targetNode;
	newNode->prev = targetNode->prev;
	targetNode->prev = newNode;
	newNode->prev->next = newNode;
	return;
}

void delete(DLL *list, DLLNode *targetNode) {

	if (targetNode == list->head) {
		targetNode->next->prev = NULL;
		list->head = targetNode->next;
		free(targetNode);
		return;
	}

	if (targetNode == list->tail) {
		targetNode->prev->next = NULL;
		list->tail = targetNode->prev;
		free(targetNode);
		return;
	}

	targetNode->next->prev = targetNode->prev;
	targetNode->prev->next = targetNode->next;
	free(targetNode);
	return;
}

void printDLLFromHead(DLL *list) {

	DLLNode *curr = list->head;

	while (curr != NULL) {
		displayDLLNode(curr);
		curr = curr->next;
	}
	
	printf("\n");
	return;
}

void printDLLFromTail(DLL *list) {

	DLLNode *curr = list->tail;

	while (curr != NULL) {
		displayDLLNode(curr);
		curr = curr->prev;
	}

	printf("\n");
	return;
}


