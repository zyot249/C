#ifndef __API_H__
#define __API_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./libfdr/jrb.h"
#include "./libfdr/dllist.h"
#include "./weightedGraph.h"


// API for App

int CheckMode(int argc,char const *argv[]);
void ErrorSyntaxNotify();
void ListProduct(char const *argv[]);
void DistanceDepot(char const *argv[]);
void CheckProductsInDepots(char const *argv[]);
void CheckAmountProduct(char const *argv[]);
JRB MakeProductTable(FILE *fsp,int* numProduct);
JRB MakeDepotTable(FILE *fkh,int* numDepot,Graph depotGraph,int numProduct);
void MakeConnectDepotGraph(FILE *fkh,Graph g);
int GetAmountProduct(JRB depotTable,int depotID,int productID);
void DoTransaction(char const *argv[]);
char* FormatTime(double time);


// Implement for API
int CheckMode(int argc,char const *argv[]){
	if(argc < 2) return -1;
	else{
		char modeChar;
		sscanf(argv[1],"-%c",&modeChar);
		switch(modeChar){
			case 't':{
				if(argc == 2) return 1;
				else return -1;
			}
			case 's':{
				if(argc == 3) return 2;
				else return -1;
			}
			case 'w':{
				if(argc == 5) return 3;
				return -1;
			}
			case 'a':{
				if(argc == 4) return 4;
				return -1;
			}
			case 'h':{
				if(argc == 6) return 5;
				return -1;
			}
			case 'g':{
				if(argc == 8) return 6;
				return -1;
			}
			default: printf("You need to use option -t -s -w -a -h -g to run app!\n");
		}
		return -1;
	}
}

void ErrorSyntaxNotify(){
	printf("Syntax Error!!\n");
	printf("Suggested Syntax: \n");
	printf("- ./app -t\n" );
	printf("- ./app -s sanpham.txt\n" );
	printf("- ./app -w khohang.txt 1 3\n" );
	printf("- ./app -a khohang.txt sanpham.txt\n" );
	printf("- ./app -h khohang.txt sanpham.txt 1 3\n" );
	printf("- ./app -g khohang.txt sanpham.txt 1 10 3 2\n" );
	printf("Try again!!\n");
}

void ListProduct(char const *argv[]){
	FILE *fin = fopen(argv[2],"r");
	if(fin == NULL) printf("Cannot Open File %s !\n",argv[2]);
	else{
		int n;
		fscanf(fin,"%d\n",&n);
		for (int i = 0; i < n; ++i){
			char buffer[50];
			fgets(buffer,50,fin);
			printf("%s", buffer);
		}
		printf("\n_____________________________________________________________________\n");
	}
}

void DistanceDepot(char const *argv[]){
	FILE *fin = fopen(argv[2],"r");
	if(fin == NULL) printf("Cannot Open File %s !\n",argv[2]);
	else{
		Graph g = create_graph(0);
		char firstLine[10];
		fgets(firstLine,10,fin);
		char buffer[50];
		do{
			fgets(buffer,50,fin);
		}while(strcmp(firstLine,buffer) != 0);

		// save to graph
		int n;
		sscanf(firstLine,"%d\n",&n);
		for (int i = 0; i < n; ++i){
			fgets(buffer,50,fin);
			int id1,id2,d;
			sscanf(buffer,"%d %d %d\n",&id1,&id2,&d);
			if(get_vertex(g,id1) == NULL)
				add_vertex(g,id1,"1");
			if(get_vertex(g,id2) == NULL)
				add_vertex(g,id2,"2");
			add_edge(g,id1,id2,(double)d);
		}

		// print distance
		int start = atoi(argv[3]);
		int end = atoi(argv[4]);
		double distance = get_edge_weight(g,start,end);
		if(distance == INFINITE_VALUE) printf("-1\n");
		else printf("%g km\n",distance );
		printf("_____________________________________________________________________\n");
	}
}

JRB MakeProductTable(FILE *fsp,int* numProduct){
	int num;
	fscanf(fsp,"%d\n",&num);
	*numProduct = num;
	JRB productTable = make_jrb();

	// make product table
	for (int i = 0; i < *numProduct; ++i){
		char nameBuff[30];
		char bufferProduct[50];
		char *nameProduct;
		int productID;
		fgets(bufferProduct,50,fsp);
		sscanf(bufferProduct,"%s %d\n",nameBuff,&productID);
		nameProduct = strdup(nameBuff);
		jrb_insert_int(productTable,productID,new_jval_s(nameProduct));
	}
	//
	return productTable;
}

JRB MakeDepotTable(FILE *fkh,int* numDepot,Graph depotGraph,int numProduct){
	char firstLine[10];
	fgets(firstLine,10,fkh);
	int num;
	sscanf(firstLine,"%d\n",&num);
	*numDepot = num;
	char bufferDepot[50];

	JRB depotTable;
	depotTable = make_jrb();

	for (int j = 0; j < *numDepot; ++j){
		fgets(bufferDepot,50,fkh);
		char nameDepot[30];
		int depotID;
		
		sscanf(bufferDepot,"%s %d\n",nameDepot,&depotID);
		JRB detail;
		detail = make_jrb();
		
		for (int i = 0; i < numProduct; ++i){
			fgets(bufferDepot,50,fkh);
			int id,amount;
			sscanf(bufferDepot,"%d %d\n",&id,&amount);
			jrb_insert_int(detail,id,new_jval_i(amount));
		}
		add_vertex(depotGraph,depotID,strdup(nameDepot));
		jrb_insert_int(depotTable,depotID,new_jval_v(detail));
	}

	return depotTable;
}

void MakeConnectDepotGraph(FILE *fkh,Graph g){
	int n;
	fscanf(fkh,"%d\n",&n);
	char buffer[50];
	for (int i = 0; i < n; ++i){
			fgets(buffer,50,fkh);
			int id1,id2,d;
			sscanf(buffer,"%d %d %d\n",&id1,&id2,&d);
			add_edge(g,id1,id2,(double)d);
		}
}

void CheckProductsInDepots(char const *argv[]){
	FILE *fsp = fopen(argv[3],"r");
	FILE *fkh = fopen(argv[2],"r");
	if(fsp == NULL){
		printf("Cannot Open File %s !\n",argv[3]);
		return;
	}
	if(fkh == NULL){
		printf("Cannot Open File %s !\n",argv[2]);
		return;	
	}

	char firstLine[10];
	fgets(firstLine,10,fkh);
	char bufferDepot[50];
	int numDepot,numProduct;
	sscanf(firstLine,"%d\n",&numDepot);

	JRB productTable = MakeProductTable(fsp,&numProduct);

	for (int j = 0; j < numDepot; ++j){
		fgets(bufferDepot,50,fkh);
		char nameDepot[30];
		sscanf(bufferDepot,"%s",nameDepot);
		printf("%s\n",nameDepot );
		for (int i = 0; i < numProduct; ++i){
			fgets(bufferDepot,50,fkh);
			int id,amount;
			sscanf(bufferDepot,"%d %d\n",&id,&amount);
			JRB ptr;
			ptr = jrb_find_int(productTable,id);
			char *name = strdup(jval_s(ptr->val));
			printf("%s %d\n",name,amount );
		}
		printf("_____________________________________________________________________\n");
	}
}

int GetAmountProduct(JRB depotTable,int depotID,int productID){
	JRB ptr = jrb_find_int(depotTable,depotID);
	JRB detail = (JRB)jval_v(ptr->val);
	JRB product = jrb_find_int(detail,productID);
	int amount = jval_i(product->val);
	return amount;
}

void CheckAmountProduct(char const *argv[]){
	FILE *fsp = fopen(argv[3],"r");
	FILE *fkh = fopen(argv[2],"r");
	if(fsp == NULL){
		printf("Cannot Open File %s !\n",argv[3]);
		return;
	}
	if(fkh == NULL){
		printf("Cannot Open File %s !\n",argv[2]);
		return;	
	}
	int numProduct,numDepot;
	Graph depotGraph = create_graph(0);
	JRB productTable = MakeProductTable(fsp,&numProduct);
	JRB depotTable = MakeDepotTable(fkh,&numDepot,depotGraph,numProduct);
	MakeConnectDepotGraph(fkh,depotGraph);

	int productID = atoi(argv[4]);
	int depotID = atoi(argv[5]);

	// find name product
	JRB ptr = jrb_find_int(productTable,productID);
	char* productName = strdup(jval_s(ptr->val));

	char* depotName = strdup(get_vertex(depotGraph,depotID));
	printf("%s:\n",depotName);
	int amount = GetAmountProduct(depotTable,depotID,productID);
	printf("%s %d\n",productName,amount);
	printf("---In Other Adjacent Depot:\n");

	int* output = (int*)malloc(100*sizeof(int));
	int numAdjacentDepot = outdegree(depotGraph,depotID,output);
	for (int i = 0; i < numAdjacentDepot; ++i)
	{
		char* depotName1 = strdup(get_vertex(depotGraph,output[i]));
		printf("%s:\n",depotName1);
		amount = GetAmountProduct(depotTable,output[i],productID);
		printf("%s %d\n",productName,amount);
	}
}

char* FormatTime(double time){
	char* waitTime;
	int hour = (int)time;
	double minute = time - (double)hour;
	int minutes = (int)(60*minute);
	sprintf(waitTime,"%d hours %d minutes",hour,minutes);
	return waitTime;
}

void DoTransaction(char const *argv[]){
	FILE *fsp = fopen(argv[3],"r");
	FILE *fkh = fopen(argv[2],"r");
	if(fsp == NULL){
		printf("Cannot Open File %s !\n",argv[3]);
		return;
	}
	if(fkh == NULL){
		printf("Cannot Open File %s !\n",argv[2]);
		return;	
	}
	int numProduct,numDepot;
	Graph depotGraph = create_graph(0);
	JRB productTable = MakeProductTable(fsp,&numProduct);
	JRB depotTable = MakeDepotTable(fkh,&numDepot,depotGraph,numProduct);
	MakeConnectDepotGraph(fkh,depotGraph);

	int productID = atoi(argv[4]);
	int closestDepotID = atoi(argv[6]);
	int productAmount = atoi(argv[5]);
	int nextDepotID = atoi(argv[7]);

	int amountOfClosestDepot = GetAmountProduct(depotTable,closestDepotID,productID);
	if(amountOfClosestDepot >= productAmount){
		printf("Successful Transaction\n");
		printf("Waiting Time is: 30 minutes\n");
		return;
	}else{
		int amountOfNextDepot = GetAmountProduct(depotTable,nextDepotID,productID);
		if(amountOfNextDepot >= (productAmount - amountOfClosestDepot)){
			double distance = get_edge_weight(depotGraph,nextDepotID,closestDepotID);
			double time = 0.5 + (distance/30);
			char* waitTime = strdup(FormatTime(time));
			printf("Successful Transaction\n");
			printf("Waiting Time is: %s\n",waitTime);
		}else{
			printf("Failed Transaction\n");
			printf("Please Try Again!\n");
			return;
		}
	}
}

#endif