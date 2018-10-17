#ifndef __uGRAPH_H__
#define __uGRAPH_H__


/* 
Define Structure
*/

typedef struct
{
  int* matrix;
  int size_max;
}Graph;

/////////////////////


/*
Define API function
*/

Graph createGraph(int size_max);
void addEdge(Graph graph,int v1,int v2);
int adjacent(Graph graph,int v1,int v2);
int getAdjacentVertices(Graph graph,int v,int* output);
void dropGraph(Graph graph);


////////////////////
#endif
