#ifndef __uwGRAPH_H__
#define __uwGRAPH_H__

#include "./libfdr/jrb.h"
#include "./libfdr/dllist.h"

typedef struct{
  JRB edges;
  JRB vertices;
  int kind; // kind = 0 --> undirected || kind != 0 -->1 --> directed
}Graph;

// APIs
Graph create_graph(int kind);
void add_vertex(Graph graph,int id,char* name); // each vertex (key(id) -- value(name))
char* get_vertex(Graph graph,int id); // return value(name) of vertex with key : id
void add_edge(Graph graph,int v1,int v2); // from v1 to v2
int has_edge(Graph graph,int v1,int v2); // check whether the edge from v1 to v2 exists
int indegree(Graph graph,int v,int* output); // find the Vertices had a edge point to v && return the indegree
int outdegree(Graph graph,int v,int* output); // find the Vertices that vertex v points to && return the outdegree

void drop_graph(Graph graph);
void list_graph(Graph graph,int* output); // List adjacent of all vertices of graph
//Traverse graph
void BFS(Graph graph,int start,int stop,void(*func)(Graph,int));
void DFS(Graph graph,int start,int stop,void(*func)(Graph,int));

Dllist shortest_path(Graph graph,int start,int stop);

//Function for Directed Graph
int DAG(Graph graph); // check if Graph is DAG( directed graph without directed cycles
int topol_sort(Graph graph, int *output); // print Topological sequence
#endif
