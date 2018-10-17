#include <stdio.h>
#include <stdlib.h>
#include "./uGraph.h"

/* API Implementation
 */

Graph createGraph(int size_max){
  Graph graph;
  graph.size_max = size_max;
  int* matrix = (int*)malloc((size_max * size_max)*sizeof(int));
  for(int i = 0;i<(size_max*size_max);i++)
    matrix[i] = 0;
  graph.matrix = matrix;
  return graph;
}

void addEdge(Graph graph,int v1, int v2){
  if(graph.matrix[v1 + v2*graph.size_max] == 1){
    printf("This edge is existed!\n");
    return;
  }else{
    graph.matrix[v2*graph.size_max + v1] = 1;
    graph.matrix[v1*graph.size_max + v2] = 1;
  }
}

int adjacent(Graph graph,int v1,int v2){
  return graph.matrix[v1*graph.size_max + v2];
}

int getAdjacentVertices(Graph graph,int v,int* output){
  int num =0;
  for(int i = (v*graph.size_max);i<(v*graph.size_max + graph.size_max);i++){
    if(graph.matrix[i] == 1)
      output[num++] = i - v*graph.size_max;
  }
  return num;
}

void dropGraph(Graph graph){
  free(graph.matrix);
  graph.size_max = 0;
}
