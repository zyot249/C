#ifndef __uGRAPH_H__
#define __uGRAPH_H__
#include "../libfdr/dllist.h"
#include "../libfdr/jrb.h"

typedef JRB Graph;

Graph createGraph();
void addEdge(Graph graph, int v1, int v2);
int adjacent(Graph graph, int v1, int v2);
int getAdjacentVertices (Graph graph, int v, int* output);
void dropGraph(Graph graph);
void BFS(Graph graph,int start,int stop,void(*func)(int));
void DFS(Graph graph,int start,int stop,void(*func)(int));

#endif
