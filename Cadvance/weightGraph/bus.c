#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./weightedGraph.h"

void print_menu(){
	printf("%s\n","1. Read Data" );
	printf("%s\n","2. Find shortest path" );
	printf("%s\n","3. Exit" );
}

void input_opt(int* opt){
	int a;
  printf("Your option :");
  scanf("%d",&a);
  *opt = a;
}

void read_data(Graph graph,char* nameFile){
	FILE* fin = fopen(nameFile,"r");
	if(fin == NULL){
		printf("Cannot open file %s! \n", nameFile);
		return;
	}else{

	}
}

int main()
{
	int opt;
	Graph map = create_graph();
	int* output = (int*)malloc(100*sizeof(int));
	do{
		print_menu();
		input_opt(&opt);
		switch(opt){
			case 1:
			{
				printf("%s\n","Enter the file name: " );
				char[50] name;
				scanf("%s",name);
				read_data(map,name);
				break;
			}
			case 2:
			{
				printf("%s\n", "Enter the start point:");
				char[20] start;
				scanf("%s",start);
				printf("%s\n", "Enter the end point:");
				char[20] end;
				scanf("%s",end);

			}
			case 3:
			{
				printf("%s\n", "Thanks For Using! GoodBye!");
				printf("%s\n", "---------------------------------------------------------------------");
			}
			default:
				printf("%s\n", "PLEASE choose the option from 1 to 3 !");
		}
	}while(opt != 3);
	return 0;
}