#include <stdio.h>
#include <stdlib.h>
#include "../libfdr/jrb.h"

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
    tree = (JRB)jval_v(node->jval);
  }
  jrb_insert_int(tree,v1,new_jval_i(1));
}

/* return 1 if v1 and v2 are adjacent
 */
int adjacent(Graph graph,int v1,int v2){

}

/* output is array of adjacent vertices of vertice v
   return the number of adjacent vertices of v
 */
int getAdjacentVertices(Graph graph,int v,int* output){

}

/* Drop an undirected graph
 */
void dropGraph(Graph graph){

}
