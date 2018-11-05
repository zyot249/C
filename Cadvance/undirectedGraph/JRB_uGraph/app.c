#include <stdio.h>
#include <stdlib.h>
#include "./uGraph.h"

void printVertex(int v) { printf("%4d", v); }

int main()
{
  int i, n;
  int* output = (int*)malloc(100*sizeof(int));
  Graph g = createGraph();
  addEdge(g, 0, 1);
  addEdge(g, 1, 2);
  addEdge(g, 1, 3);
  addEdge(g, 2, 3);
  addEdge(g, 2, 4);
  addEdge(g, 4, 5);
  
  printf("\nBFS: start from node 1 to  4 : ");
  BFS(g, 1, 4,printVertex);
  printf("\nDFS: start from node 1 to all : ");
  DFS(g, 1, 4,printVertex);
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
