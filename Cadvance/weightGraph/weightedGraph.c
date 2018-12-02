#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Implement API

Graph create_graph(){
  Graph g;
  g.edges = make_jrb();
  g.vertices = make_jrb();
  return g;
}

void add_vertex(Graph graph,int id,char* name){
  JRB node = jrb_find_int(graph.vertices,id);
  if(node == NULL){
    jrb_insert_int(graph.vertices,id,new_jval_s(strdup(name)));
  }
}

char* get_vertex(Graph graph,int id){
  JRB node = jrb_find_int(graph.vertices,id);
  if(node == NULL){
    printf("No vertex with id %d\n",id);
    return NULL;
  }else{
    char* name = strdup(jval_s(node->val));
    return name;
  }
}

void add_edge(Graph graph,int v1,int v2,double weight){
  JRB node1 = jrb_find_int(graph.vertices,v1);
  JRB node2 = jrb_find_int(graph.vertices,v2);
  if(node1 == NULL){
    printf("Vertex %d doesn't exist!\n",v1);
    return;
  }else if(node2 == NULL){
    printf("Vertex %d doesn't exist!\n",v1);
    return;
  }else if(node1 == NULL && node2 == NULL){
    printf("Vertex %d and %d don't exist!\n",v1,v2);
    return;
  }else{
    node1 = jrb_find_int(graph.edges,v1);
    JRB tree;
    if(node1 == NULL){
      tree = make_jrb();
      jrb_insert_int(graph.edges,v1,new_jval_v(tree));
    }else
      tree = (JRB)jval_v(node1->val);
    JRB check;
    check = jrb_find_int(tree,v2);
    if(check == NULL){
      jrb_insert_int(tree,v2,new_jval_d(weight));
    }
  }
}

double get_edge_weight(Graph graph,int v1,int v2){
  JRB node = jrb_find_int(graph.vertices,v1);
  if(node == NULL) return INFINITE_VALUE;
  else{
    if(v2 == v1) return 0;
  }
  JRB node1 = jrb_find_int(graph.edges,v1);
  if(node1 == NULL)
    return INFINITE_VALUE;
  else{
    JRB node2 = jrb_find_int((JRB)jval_v(node1->val),v2);
    if(node2 == NULL) return INFINITE_VALUE;
    else return jval_d(node2->val);
  }
}


}

void drop_graph(Graph graph){
  JRB node;
  jrb_traverse(node,graph.edges)
    jrb_free_tree((JRB)jval_v(node->val));
  
  jrb_free_tree(graph.edges);
  jrb_free_tree(graph.vertices);
}

int indegree(Graph graph,int v,int* output){
  JRB node = jrb_find_int(graph.vertices,v);
  if(node == NULL){
    printf("Vertex %d doesn't exist!\n",v);
    return -1;
  }else{
    int count = 0;
    jrb_traverse(node,graph.edges){
      JRB tmp = jval_v(node->val);
      if(jrb_find_int(tmp,v) != NULL)
	output[count++] = jval_i(node->key);
    }
    return count;
  }
}

int outdegree(Graph graph,int v,int* output){
  JRB node = jrb_find_int(graph.vertices,v);
  if(node == NULL){
    printf("Vertex %d doesn't exist!\n",v);
    return -1;
  }else{
    node = jrb_find_int(graph.edges,v);
    if(node == NULL) return 0;
    else{
      int count = 0;
      JRB tree = jval_v(node->val);
      jrb_traverse(node,tree)
	output[count++] = jval_i(node->key);
      return count;
    }
  }
}

Dllist find_min(Dllist dllist){
  Dllist min = dll_first(dllist);
  dll_traverse(Dllist ptr,dllist){
    if(jval_v(ptr->val)[1] < jval_v(min->val)[1])
      min = ptr;
  }
  return min;
}

double shortest_path(Graph graph,int s,int t,int* path,int* length){
  JRB visited,tNode;
  Dllist pQueue,qNode;
  int* output = (int*)malloc(100*sizeof(int));

  //Initialization
  pQueue = new_dllist();
  visited = make_jrb();

  jrb_traverse(tNode,graph.vertices){
    if(jval_i(tNode->key) == s){
      double table[2];
      table[0] = jval_i(tNode->key);
      table[1] = 0;
      dll_append(pQueue,new_jval_v(table));
    }else{
      double table[2];
      table[0] = jval_i(tNode->key);
      table[1] = INFINITE_VALUE;
      dll_append(pQueue,new_jval_v(table));
    }
  }

  
}
