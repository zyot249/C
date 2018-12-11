#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./busMap.h"

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

int read_data(Graph map,char* name){
	FILE* fin = fopen(name,"r");
	if(fin == NULL) {
		printf("Cannot open file %s\n", name);
		return 0;
	}else{
		char line[500];
		int mode = 0;
		int cnt = 1;
		char* bus;
		while(fgets(line,500,fin) != NULL){
			if(strcmp(line,"<BUS>\n") == 0){
				mode = 1;
				continue;
			}else if(strcmp(line,"<ARRIVE>\n") == 0){
				mode = 2;
				continue;
			}else if(strcmp(line,"<GOBACK>\n") == 0){
				mode = 2;
				continue;
			}


			//mode
			switch(mode){
				case 1:{
					bus = strdup(line);
					bus[strlen(bus) - 1] = '\0';
					break;
				}
				case 2:{
					char* previous = NULL;
					char* current = NULL;
					current = strtok(line,"-");
					while(current != NULL){
						if(get_vertex_id(map,current) == -1){
							add_vertex(map,cnt++,current);
						}
						if (previous != NULL){
							add_edge(map,get_vertex_id(map,previous),get_vertex_id(map,current),bus);
						}
						previous = current;
						current = strtok(NULL,"-\n");
					}
					break;
				}

			}
		}
		return cnt;
	}
}

int main()
{
	int opt;
	Graph map = create_graph();
	int cnt = 0;
	int* output = (int*)malloc(100*sizeof(int));
	do{
		print_menu();
		input_opt(&opt);
		switch(opt){
			case 1:
			{
				printf("%s\n","Enter the file name: " );
				char name[50];
				scanf("%s",name);
				cnt = read_data(map,name);
				break;
			}
			case 2:
			{
				
				printf("%s\n", "Enter the start point:");
				char start[20];
				scanf("%s",start);
				printf("%s\n", "Enter the end point:");
				char end[20];
				scanf("%s",end);

				Dllist path = shortest_path(map,get_vertex_id(map,start),get_vertex_id(map,end));
				if(path == NULL) printf("%s\n", "No Path\n");
				else{
					Dllist node;
					char* busName;
					for(node = path->flink;dll_next(node) != list;node = node->flink){
						Dllist nodeNext = node->flink;
						
					}
					printf("\n");
				}
				break;
			}
			case 3:
			{
				printf("%s\n", "Thanks For Using! GoodBye!");
				printf("%s\n", "---------------------------------------------------------------------");
				break;
			}
			default:
				printf("%s\n", "PLEASE choose the option from 1 to 3 !");
		}
	}while(opt != 3);
	return 0;
}