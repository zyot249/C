#ifndef __dGRAPH_H__
#define __dGRAPH_H__

#include "../libfdr/jrb.h"
#include "../libfdr/dllist.h"

typedef struct{
  JRB edges;
  JRB vertices;
}Graph;

// APIs
Graph createGraph();
void addVertex(Graph graph,int id,char* name);
char* getVertex(Graph graph,int id);
void addEdge(Graph graph,int v1,int v2); // from v1 to v2
int hasEdge(Graph graph,int v1,int v2); // check whether the edge from v1 to v2 exists
int indegree(Graph graph,int v,int* output); // find the Vertices had a edge point to v
int outdegree(Graph graph,int v,int* output); // find the Vertices that vertex v points to
int DAG(Graph graph); // check if Graph is DAG( directed graph without directed cycles
void dropGraph(Graph graph);

#endif
