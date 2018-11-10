#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./dGraph.h"

void printVertex(Graph graph,int u){
  JRB node = jrb_find_int(graph.vertices,u);
  printf("%6s",jval_s(node->val));
}

int main()
{
  Graph g = create_graph();
  int* output = (int*)malloc(100*sizeof(int));
  add_vertex(g, 0, "V0");
  add_vertex(g, 1, "V1");
  add_vertex(g, 2, "V2");
  add_vertex(g, 3, "V3");
  add_edge(g, 0, 1);
  add_edge(g, 1, 2);
  add_edge(g, 2, 0);
  add_edge(g, 1, 3);
  /*
  if (DAG(g))
    printf("The graph is acycle\n");
  else printf("Have cycles in the graph\n");
  */
  printf("%s\n",get_vertex(g,1));
  printf("%d\n",has_edge(g,0,1));
  list_graph(g,output);
  printf("BFS from 1 to all:");
  BFS(g,1,-1,printVertex);
  printf("\n");
  printf("DFS from 1 to all:");
  DFS(g,1,-1,printVertex);
  printf("\n");
  drop_graph(g);
  free(output);
  return 0;
}
