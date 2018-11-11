#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Graph.h"

void print_vertex(Graph graph,int u){
  JRB node = jrb_find_int(graph.vertices,u);
  printf("%6s",jval_s(node->val));
}

int main()
{
  Graph g = create_graph(1);
  int* output = (int*)malloc(100*sizeof(int));
  add_vertex(g, 0, "V0");
  add_vertex(g, 1, "V1");
  add_vertex(g, 2, "V2");
  add_vertex(g, 3, "V3");
  add_vertex(g, 4, "V4");
  add_vertex(g, 5, "V5");
  add_edge(g, 0, 1);
  add_edge(g, 1, 2);
  add_edge(g, 1, 3);
  add_edge(g, 2, 3);
  add_edge(g, 2, 4);
  add_edge(g, 4, 5);
  add_edge(g, 3, 5);
  /*
  if (DAG(g))
    printf("The graph is acycle\n");
  else printf("Have cycles in the graph\n");
  */
  printf("%s\n",get_vertex(g,1));
  printf("%d\n",has_edge(g,0,1));
  list_graph(g,output);
  
  printf("BFS from 0 to 4:");
  BFS(g,0,4,print_vertex);
  printf("\n");
  printf("DFS from 0 to 5:");
  DFS(g,0,5,print_vertex);
  printf("\n");
  
  //Dllist path;
  //path = shortest_path(g,1,5);
  //Dllist node;
  //dll_traverse(node,path){
  //printf("%d\t",jval_i(node->val));
  //}
  //printf("\n");
  printf("PATH:");
  shortest_path(g,0,4,print_vertex);
  printf("__________________________________\n");
  /*
  int n = topol_sort(g,output);
  for(int i = 0;i < n;i++)
    print_vertex(g,output[i]);
  printf("\n");
  */
  drop_graph(g);
  free(output);
  return 0;
}
