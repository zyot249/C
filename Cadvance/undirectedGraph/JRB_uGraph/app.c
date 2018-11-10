#include <stdio.h>
#include <stdlib.h>
#include "./uGraph.h"

void printVertex(int v) { printf("%4d", v); }

int main()
{
  int i, n;
  int* output = (int*)malloc(100*sizeof(int));
  Graph g = createGraph();
  addEdge(g, 1, 2);
  addEdge(g, 2, 3);
  addEdge(g, 2, 4);
  addEdge(g, 3, 4);
  addEdge(g, 3, 5);
  addEdge(g, 5, 6);

  printf("The Graph:");
  listGraph(g,output);
  printf("\n");
  printf("\nBFS: start from node 1 to all : ");
  BFS(g, 1, -1,printVertex);
  printf("\nDFS: start from node 1 to all : ");
  DFS(g, 1, -1,printVertex);
  printf("\n");
  /*
  n = getAdjacentVertices(g,1,output);
  if(n != 0){
    printf("%d\n",n);
    for(i = 0;i<n;i++)
      printf("%4d",output[i]);
    printf("\n");
  }
  */
  return 0;
}
