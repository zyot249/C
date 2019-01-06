#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./weightedGraph.h"

void PrintMenu(){
	printf("\n--------------Your Option--------------\n");
	printf("1. List of Product\n");
	printf("2. List of Transaction History\n");
	printf("3. Relative Level\n");
	printf("4. List of Relative Product\n");
	printf("5. Undirected Relative\n");
	printf("6. Exit\n");
	printf("Your choice: \n");
}

void UpdateRelativeLevel(Graph productTable,int id1,int id2){
	if(has_edge(productTable,id1,id2)){
				JRB ptr,val,tree;
				ptr = jrb_find_int(productTable.edges,id1);
				tree = (JRB)jval_v(ptr->val);
				val = jrb_find_int(tree,id2);
				double level = jval_d(val->val);
				val->val = new_jval_d(++level);
			}else{
				add_edge(productTable,id1,id2,1);
			}
}

int ReadProduct(char* fileName,Graph productTable){
	FILE *fin = fopen(fileName,"r");
	if(fin == NULL){
		printf("Cannot Open File %s !\n",fileName);
		return -1;
	}
	int numProduct = 0;
	char buffer[110];
	while(fgets(buffer,110,fin) != NULL){
		char productName[100];
		int productId;
		sscanf(buffer,"%d %s\n",&productId,productName);
		add_vertex(productTable,productId,strdup(productName));
		numProduct++;
	}
	return numProduct;
}

int ReadOrderHistory(char* fileName,Graph productTable){
	FILE *fin = fopen(fileName,"r");
	if(fin == NULL){
		printf("Cannot Open File %s !\n",fileName);
		return -1;
	}
	int numOrder = 0;
	char buffer[100];
	printf("List Transaction: \n");
	while(fgets(buffer,100,fin) != NULL){
		char* id;
		id = strtok(buffer," ");
		int numOrder = 0;
		int listOrder[50];
		listOrder[numOrder++] = atoi(id);
		while((id = strtok(NULL," ")) != NULL){
			listOrder[numOrder++] = atoi(id);
		}
		for (int i = 0; i < numOrder-1; ++i){
			for (int j = i+1; j < numOrder; ++j){
				UpdateRelativeLevel(productTable,listOrder[i],listOrder[j]);
			}
		}
		for (int i = 0; i < numOrder; ++i){
			char* name = strdup(get_vertex(productTable,listOrder[i]));
			printf("%s ",name );
		}
		printf("\n");

	}
}

int GetMaxId(Dllist pQueue){
	Dllist ptr,maxNode;
	double max = 0;
	int id;
	dll_traverse(ptr,pQueue){
		double* table = jval_v(ptr->val);
		if(table[1] > max){
			id = (int)table[0];
			max = table[1];
			maxNode = ptr;
		}
	}
	dll_delete_node(maxNode);
	return id;
}

int main()
{
	Graph productTable = create_graph(0);
	int* output = (int*)malloc(100*sizeof(int));
	char input[100];
	int opt, numProduct, numOrder;
	printf("Welcome to The Strongest Application!!\n");
	do{
		PrintMenu();
		scanf("%s",input);
		if(strlen(input) > 1){
			printf("Wrong Input\n");
			printf("PLEASE choose from 1-6 Option!!\n");
			continue;
		}
		opt = atoi(input);
		switch(opt){
			case 1:{
				numProduct = ReadProduct("products.txt",productTable);
				printf("List Products:\n");
				JRB ptr;
				jrb_traverse(ptr,productTable.vertices){
					int id = jval_i(ptr->key);
					char* name = strdup(jval_s(ptr->val));
					printf("Ma san pham : %d\n",id );
					printf("Ten san pham : %s\n\n",name );
				}
				break;
			}
			case 2:{
				numOrder = ReadOrderHistory("orderhistory.txt",productTable);
				break;
			}
			case 3:{
				int id1,id2;
				printf("Enter 2 Product Codes(form [id1 id2]): \n");
				scanf("%d %d",&id1,&id2);
				double relativeLevel = get_edge_weight(productTable,id1,id2);
				if(relativeLevel == INFINITE_VALUE)
					printf("Relative Level is: -1\n");
				else{
					printf("Relative Level is: %g\n", relativeLevel);
				}
				break;
			}
			case 4:{
				int id;
				printf("Enter  Product Code: \n");
				scanf("%d",&id);
				int numAdjacent = outdegree(productTable,id,output);
				Dllist pQueue = new_dllist();
				for (int i = 0; i < numAdjacent; ++i){
					double* table = (double*)malloc(2*sizeof(double));
					table[0] = (double)output[i];
					table[1] = get_edge_weight(productTable,id,output[i]);
					dll_prepend(pQueue,new_jval_v(table));
				}
				printf("List of Relative Products: ");
				while(!dll_empty(pQueue)){
					int id = GetMaxId(pQueue);
					char* name = get_vertex(productTable,id);
					printf("%s ,",name);
				}
				break;
			}
			case 5:{
				int id1,id2;
				printf("Enter 2 Product Codes(form [id1 id2]): \n");
				scanf("%d %d",&id1,&id2);
				int* path = (int*)malloc(50*sizeof(int));
				int length = 0;
				double distance = shortest_path(productTable,id1,id2,path,&length);
				if(distance == INFINITE_VALUE){
					printf("No Relation\n");
				}else{
					printf("This is the relation:\n");
					for (int i = length-1; i >= 1; --i)
					{
						char* name = strdup(get_vertex(productTable,path[i]));
						printf("%s -- ",name );
					}
					char* name = strdup(get_vertex(productTable,path[0]));
					printf("%s\n", name);
				}
				break;
			}
			case 6:{
				printf("Thank You For Using!!\nGoodbye!\n");
				break;
			}
			default: printf("PLEASE choose from 1-6 Option!!\n");
		}
	}while(opt != 6);
	free(output);
	drop_graph(productTable);
	return 0;
}