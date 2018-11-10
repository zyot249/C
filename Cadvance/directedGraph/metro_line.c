#include <stdio.h>
#include <stdlib.h>
#include "./dGraph.h"
#include <string.h>

void print_menu(){
  printf("\nWelcome to Metro Line Management!\n");
  printf("1.Read Data\n");
  printf("2.Test\n");
  printf("3.\n");
  printf("4.Exit Application\n");
}

void input_opt(int* opt){
  int a;
  printf("Your option :");
  scanf("%d",&a);
  *opt = a;
}

void read_data(Graph graph,char* name){
  FILE* fin = fopen(name,"r");
  if(fin == NULL){
    printf("Cannot open file %s !\n",name);
    return;
  }else{
    char line[100];
    int mode = 0; // mode = 1 (Station) || mode = 2 (Line)
    while( fgets(line,100,fin) != NULL){
      if(strcmp(line,"STATIONS\n") == 0) {
	mode = 1;
	continue;
      }
      if(strcmp(line,"LINES\n") == 0){
	mode = 2;
	continue;
      }
      switch(mode){
      case 1:
	{
	  char* key = strtok(line,"=");
	  char* name = strtok(NULL,"\n");
	  int v;
	  sscanf(key,"S%d",&v);
	  jrb_insert_int(graph.vertices,v,new_jval_s(strdup(name)));
	  break;
	}
      case 2:
	{
	  char* previous = NULL;
	  char* current = NULL;
	  strtok(line,"=");
	  current = strtok(NULL," ");
	  while(current != NULL){
	    if(previous != NULL){
	      int pre,cur;
	      sscanf(previous,"S%d",&pre);
	      sscanf(current,"S%d",&cur);
	      add_edge(graph,pre,cur);
	    }
	    previous = current;
	    current = strtok(NULL," ");
	  }
	  break;
	}
      }
    }
  }
}

int main()
{
  int opt;
  Graph graph = create_graph();
  int* output = (int*)malloc(100*sizeof(int));
  do{
    print_menu();
    input_opt(&opt);
    switch(opt){
    case 1:
      {
	char name[100];
	scanf("%s",name);
	read_data(graph,name);
	break;
      }
    case 2:
      {
	list_graph(graph,output);
	break;
      }
    case 3:
      {
	break;
      }  
    case 4:
      {
	printf("Thanks for using! Goodbye!\n");
	printf("____________________________________________________________\n\n");
	break;
      }
    default:
      printf("PLEASE choose the option from 1 to 4 !!\n");
    }
  }while(opt != 4);
  return 0;
}
