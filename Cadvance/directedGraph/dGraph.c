#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./dGraph.h"


// Implementation APIs

Graph createGraph(){
  Graph g;
  g.edges = make_jrb();
  g.vertices = make_jrb(); 
  return g;
}

void addVertex(Graph graph,int id,char* name){
  JRB node = jrb_find_int(graph.vertices,id);
  if(node == NULL){
    jrb_insert_int(graph.vertices,id,new_jval_s(strdup(name)));
  }
}

char* getVertex(Graph graph,int id){
  JRB node = jrb_find_int(graph.vertices,id);
  if(node == NULL){
    printf("No vertex with id %d\n",id);
    return NULL;
  }else{
    char* name = jval_s(node->val);
    return name;
  }
}
