#ifndef __wGRAPH_H__
#define __wGRAPH_H__

#include "./libfdr/jrb.h"
#include "./libfdr/dllist.h"

#define INFINITE_VALUE 1000000000000

typedef struct{
  JRB edges;
  JRB vertices;
}Graph;

//API
Graph create_graph();
void add_vertex(Graph graph,int id,char* name);
char* get_vertex(Graph graph,int id);
void add_edge(Graph graph,int v1,int v2,double weight); // edge from v1 --> v2 has weight
double get_edge_weight(Graph graph,int v1,int v2); // return weight of the edge from v1 --> v2 , return INFINITE_VALUE if no edge from v1 ---> v2
void drop_graph(Graph graph);

int indegree(Graph graph,int v,int* output); //find the vertices that points to v || return the number of output
int outdegree(Graph graph,int v,int*output); //find the vertices that v points to || return the number of output


//Shortest Path
double shortest_path(Graph graph,int s,int t,int* path,int* length);
//return total weight of path,return INFINITE_VALUE if no path found
#endif
