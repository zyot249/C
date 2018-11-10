#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./dGraph.h"


// Implementation APIs

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

void add_edge(Graph graph,int v1,int v2){
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
      tree = jval_v(node1->val);
    jrb_insert_int(tree,v2,new_jval_i(1));
  }
}

int has_edge(Graph graph,int v1,int v2){
  JRB node1 = jrb_find_int(graph.edges,v1);
  if(node1 == NULL)
    return 0;
  else{
    JRB node2 = jrb_find_int((JRB)jval_v(node1->val),v2);
    if(node2 == NULL) return 0;
    else return 1;
  }
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

void drop_graph(Graph graph){
  JRB node;
  jrb_traverse(node,graph.edges)
    jrb_free_tree((JRB)jval_v(node->val));
  
  jrb_free_tree(graph.edges);
  jrb_free_tree(graph.vertices);
}

void list_graph(Graph graph,int* output){
  JRB node,tree,name;
  tree = graph.vertices;
  for(node = jrb_first(tree);node != jrb_nil(tree);node = jrb_next(node)){
    int v = jval_i(node->key);
    name = jrb_find_int(graph.vertices,v);
    printf("Vertex %s : ",jval_s(name->val));
    int n = outdegree(graph,v,output);
    if(n != 0){
      for(int i = 0;i<n;i++){
	name = jrb_find_int(graph.vertices,output[i]);
	printf("--> %s ",jval_s(name->val));
      }
    }
    printf("\n");
  }
}

void BFS(Graph graph,int start,int stop,void(*func)(Graph,int)){
  JRB visited;
  Dllist queue,node;
  int u,v,i,n;
  int* output = (int*)malloc(100*sizeof(int));

  queue = new_dllist();
  dll_append(queue,new_jval_i(start));
  visited = make_jrb();

  while(!dll_empty(queue)){
    node = dll_first(queue);
    u = jval_i(node->val);
    dll_delete_node(node);

    if(jrb_find_int(visited,u) == NULL){
      func(graph,u);
      jrb_insert_int(visited,u,new_jval_i(1));
      if(u == stop)
	break;

      n = outdegree(graph,u,output);
      for(i = 0;i < n;i++){
	v = output[i];
	if(jrb_find_int(visited,v) == NULL)
	  dll_append(queue,new_jval_i(v));
      }
    }
  }
  jrb_free_tree(visited);
  free(output);
}

void DFS(Graph graph,int start,int stop,void(*func)(Graph,int)){
  JRB visited;
  Dllist stack,node;
  int u,n,i,v;
  int* output = (int*)malloc(100*sizeof(int));

  visited = make_jrb();
  stack = new_dllist();
  dll_prepend(stack,new_jval_i(start));

  while(!dll_empty(stack)){
    node = dll_first(stack);
    u = jval_i(node->val);
    dll_delete_node(node);

    if(jrb_find_int(visited,u) == NULL){
      func(graph,u);
      jrb_insert_int(visited,u,new_jval_i(1));
      if(u == stop)
	break;

      n = outdegree(graph,u,output);
      if(n != 0){
	for(i = n-1;i >= 0;i--){
	  v = output[i];
	  if(jrb_find_int(visited,v) == NULL)
	    dll_prepend(stack,new_jval_i(v));
	}
      }
    }
  }
  jrb_free_tree(visited);
  free(output);
}

int dag_Check,dag_Start;

void dag_visit(Graph graph,int v){
  if(has_edge(graph,v,dag_Start))
    dag_Check = 1;
}

int DAG(Graph graph){
  JRB node;
  jrb_traverse(node,graph.vertices){
    dag_Start = jval_i(node->key);
    dag_Check = 0;
    DFS(graph,dag_Start,-1,dag_visit);
    if(dag_Check == 1) return 0;
  }
  return 1;
}

