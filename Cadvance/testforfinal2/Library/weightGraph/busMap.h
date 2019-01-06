#ifndef __busMAP_H__
#define __busMAP_H__

#include "./libfdr/jrb.h"
#include "./libfdr/dllist.h"

typedef struct{
  JRB edges;
  JRB vertices;
}Graph;

//API
Graph create_graph();
void add_vertex(Graph graph,int id,char* name);
int get_vertex_id(Graph graph,char* name);
char* get_vertex_name(Graph graph,int id);
void add_edge(Graph graph,int v1,int v2,char* bus); // edge from v1 --> v2 has list of buses that go through 
Dllist get_list_bus(Graph graph,int v1,int v2); // return list of buses going through of the edge from v1 --> v2 , return NULL if no edge from v1 ---> v2
void drop_graph(Graph graph);

int indegree(Graph graph,int v,int* output); //find the vertices that points to v || return the number of output
int outdegree(Graph graph,int v,int*output); //find the vertices that v points to || return the number of output
Dllist shortest_path(Graph graph,int start,int stop);

#endif