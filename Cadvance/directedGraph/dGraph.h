#ifndef __dGRAPH_H__
#define __dGRAPH_H__

#include "./libfdr/jrb.h"
#include "./libfdr/dllist.h"

typedef struct{
  JRB edges;
  JRB vertices;
}Graph;

// APIs
Graph create_graph();
void add_vertex(Graph graph,int id,char* name);
char* get_vertex(Graph graph,int id);
void add_edge(Graph graph,int v1,int v2); // from v1 to v2
int has_edge(Graph graph,int v1,int v2); // check whether the edge from v1 to v2 exists
int indegree(Graph graph,int v,int* output); // find the Vertices had a edge point to v
int outdegree(Graph graph,int v,int* output); // find the Vertices that vertex v points to
int DAG(Graph graph); // check if Graph is DAG( directed graph without directed cycles
void list_graph(Graph graph,int* output); // List adjacent of all vertex in graph
void drop_graph(Graph graph);
void list_graph(Graph graph,int* output); // List adjacent of all vertices of graph
//Traverse graph
void BFS(Graph graph,int start,int stop,void(*func)(Graph,int));
void DFS(Graph graph,int start,int stop,void(*func)(Graph,int));

#endif
