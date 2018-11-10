#include <stdio.h>
#include <stdlib.h>
#include "./uGraph.h"
#include "../libfdr/jrb.h"
#include "../libfdr/dllist.h"

/* Implement Function
 */

/* Create an undirected graph
 */
Graph createGraph(){
  Graph g = make_jrb();
  return g;
}

/* Add the edge between 2 vertices v1 and v2
 */
void addEdge(Graph graph,int v1,int v2){
  JRB node = jrb_find_int(graph,v1);
  JRB tree;

  if(node == NULL){
    tree = make_jrb();
    jrb_insert_int(graph,v1,new_jval_v(tree));
  }else{
    tree = (JRB)jval_v(node->val);
  }
  jrb_insert_int(tree,v2,new_jval_i(1));

  node = jrb_find_int(graph,v2);
  if(node == NULL){
    tree = make_jrb();
    jrb_insert_int(graph,v2,new_jval_v(tree));
  }else{
    tree = (JRB)jval_v(node->val);
  }
  jrb_insert_int(tree,v1,new_jval_i(1));
}

/* return 1 if v1 and v2 are adjacent
 */
int adjacent(Graph graph,int v1,int v2){
  JRB node = jrb_find_int(graph,v1);
  if(node == NULL) return 0;
  else{
    if(jrb_find_int((JRB)jval_v(node->val),v2) == NULL)
      return 0;
    else return 1;
  }
}

/* output is array of adjacent vertices of vertice v
   return the number of adjacent vertices of v
 */
int getAdjacentVertices(Graph graph,int v,int* output){
  JRB node = jrb_find_int(graph,v);
  JRB tree;
  int count = 0;

  if(node != NULL){
    tree = (JRB)jval_v(node->val);
    count = 0;
    jrb_traverse(node,tree)
      output[count++] = jval_i(node->key);
  }
  return count;
}
/* List adjacent of all Vertices
 */
void listGraph(Graph graph,int* output){
  JRB node;
  for(node = jrb_first(graph);node != jrb_nil(graph);node = jrb_next(node)){
    int n = getAdjacentVertices(graph,jval_i(node->key),output);
    printf("\nVertex %d ",jval_i(node->key));
    if(n != 0)
      for(int i = 0;i<n;i++)
	printf("--> %d ",output[i]);
  }
}

/* Drop an undirected graph
 */
void dropGraph(Graph graph){
  JRB node;
  jrb_traverse(node,graph)
    jrb_free_tree((JRB)jval_v(node->val));

  jrb_free_tree(graph);
}

/* BFS
 */

void BFS(Graph graph,int start,int stop,void(*func)(int)){
  JRB visited;
  Dllist queue,node;
  int n,i,u,v;
  int* output = (int*)malloc(100*sizeof(int));
  
  queue = new_dllist();
  dll_append(queue,new_jval_i(start));
  visited = make_jrb();

  while(!dll_empty(queue)){
    node = dll_first(queue);
    u = jval_i(node->val);
    dll_delete_node(node);

    if( jrb_find_int(visited,u) == NULL){ // not yet visited
      //visit u
      func(u);
      jrb_insert_int(visited,u,new_jval_i(1));
      if( u == stop)
	break;

      //add adjacent of u to queue
      n = getAdjacentVertices(graph,u,output);
      for(i = 0;i<n;i++){
	v = output[i];
	if(jrb_find_int(visited,v) == NULL)
	  dll_append(queue,new_jval_i(v));
      }
    }
  }
  jrb_free_tree(visited);
  free(output);
}

void DFS(Graph graph,int start,int stop,void(*func)(int)){
  JRB visited;
  Dllist stack,node;
  int n,i,u,v;
  int* output = (int*)malloc(100*sizeof(int));
  
  stack = new_dllist();
  dll_prepend(stack,new_jval_i(start));
  visited = make_jrb();

  while(!dll_empty(stack)){
    node = dll_first(stack);
    u = jval_i(node->val);
    dll_delete_node(node);

    if( jrb_find_int(visited,u) == NULL){ // not yet visited
      //visit u
      func(u);
      jrb_insert_int(visited,u,new_jval_i(1));
      if( u == stop)
	break;

      //add adjacent of u to queue
      n = getAdjacentVertices(graph,u,output);
      for(i = 0;i<n;i++){
	v = output[i];
	if(jrb_find_int(visited,v) == NULL)
	  dll_prepend(stack,new_jval_i(v));
      }
    }
  }
  jrb_free_tree(visited);
  free(output);
}
