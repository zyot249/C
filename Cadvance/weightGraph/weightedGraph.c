#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./weightedGraph.h"
//Implement API

Graph create_graph(){
  Graph g;
  g.edges = make_jrb();
  g.vertices = make_jrb();
  return g;
}

void add_vertex(Graph graph,int id,char* name){
  JRB node = jrb_find_int(graph.vertices,id);
  if(node == NULL){//if not exist the node with key id
    jrb_insert_int(graph.vertices,id,new_jval_s(strdup(name)));
  }
}

char* get_vertex(Graph graph,int id){
  JRB node = jrb_find_int(graph.vertices,id);
  if(node == NULL){
    return NULL; //if there doesnt exist the node with key id --> return NULL
  }else{
    char* name = strdup(jval_s(node->val));
    return name;
  }
}

void add_edge(Graph graph,int v1,int v2,double weight){
  JRB node1 = jrb_find_int(graph.vertices,v1);
  JRB node2 = jrb_find_int(graph.vertices,v2);
  //Check the existence of node v1 and v2
  if(node1 == NULL){
    printf("Vertex %d doesn't exist!\n",v1);
    return;
  }else if(node2 == NULL){
    printf("Vertex %d doesn't exist!\n",v1);
    return;
  }else if(node1 == NULL && node2 == NULL){
    printf("Vertex %d and %d don't exist!\n",v1,v2);
    return;
  }else{//if v1 and v2 exist
    node1 = jrb_find_int(graph.edges,v1);//find node 1 in edges tree
    JRB tree;//tree of outdegree of node v1
    if(node1 == NULL){
      tree = make_jrb();//if v1 doesnt exist in edges tree --> create a new tree for outdegree
      jrb_insert_int(graph.edges,v1,new_jval_v(tree));//insert node v1 to edges tree
    }else
      tree = (JRB)jval_v(node1->val);//if v1 existed 
    JRB check;
    check = jrb_find_int(tree,v2);//check the existence of the edge between v1 and v2
    if(check == NULL){
      jrb_insert_int(tree,v2,new_jval_d(weight));//insert the edge with weight
    }
  }
}

double get_edge_weight(Graph graph,int v1,int v2){
  JRB node = jrb_find_int(graph.vertices,v1);
  if(node == NULL) return INFINITE_VALUE;//if v1 doesnt exist
  else{
    if(v2 == v1) return 0;
  }
  JRB node1 = jrb_find_int(graph.edges,v1);
  if(node1 == NULL)
    return INFINITE_VALUE;//if v1 has no outdegree
  else{
    JRB node2 = jrb_find_int((JRB)jval_v(node1->val),v2);
    if(node2 == NULL) return INFINITE_VALUE;//if no edge between v1 and v2
    else return jval_d(node2->val);
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

//Shortest Path myself ( Dijkstra's Algorithm)

//Find the element with min distance to starting point in Priority Queue
Dllist find_min(Dllist pQueue){
  Dllist min = dll_first(pQueue);
  Dllist ptr;
  dll_traverse(ptr,pQueue){
    double* u = jval_v(ptr->val);
    double* v = jval_v(min->val);
    if(u[2] < v[2])
      min = ptr;
  }
  return min;
}

//Find the node u in Priority Queue
Dllist find_node(Dllist dllist,int u){
  Dllist find;
  dll_traverse(find,dllist){
    double* ptr = jval_v(find->val);
    if(ptr[0] == u)
      break;
  }
  return find;
}

//update new min distance to the starting point of the node v when go through node u(if not shorter --> not change)
void relax(Dllist pQueue,int u,int v,Graph graph){
  double weight = get_edge_weight(graph,u,v);//get weight of edge between u and v
  Dllist U = find_node(pQueue,u);
  Dllist V = find_node(pQueue,v);
  double* val_u = jval_v(U->val);
  double* val_v = jval_v(V->val);
  if(val_v[2] > (val_u[2] + weight)){//if exist new min distance
    val_v[2] = val_u[2] + weight;
    val_v[1] = u;//assign new parent of v is u
  }
}

double shortest_path(Graph graph,int s,int t,int* path,int* length){
  int n; 
  JRB visited,tNode;
  Dllist pQueue,qNode;
  int* output = (int*)malloc(100*sizeof(int));

  //Initialization
  pQueue = new_dllist();
  visited = make_jrb();

  //Add vertices to priority queue
  jrb_traverse(tNode,graph.vertices){
    if(jval_i(tNode->key) == s){
      double *table = (double*)malloc(3*sizeof(double));
      table[0] = jval_i(tNode->key);
      table[1] = -1;
      table[2] = 0;
      dll_append(pQueue,new_jval_v(table));
    }else{
      double *table = (double*)malloc(3*sizeof(double));
      table[0] = jval_i(tNode->key);
      table[1] = -1;
      table[2] = INFINITE_VALUE;
      dll_append(pQueue,new_jval_v(table));
    }
  }

  while(!dll_empty(pQueue)){
    qNode = find_min(pQueue);
    double* dou = jval_v(qNode->val);

    //relax
    n = outdegree(graph,dou[0],output);
    for (int i = 0; i < n; ++i){
      if(jrb_find_int(visited,output[i]) == NULL)
        relax(pQueue,dou[0],output[i],graph);
    }

    //add to visited tree
    double *table = (double*)malloc(2*sizeof(double));
    table[0] = dou[1];
    table[1] = dou[2];
    jrb_insert_int(visited,(int)dou[0],new_jval_v(table));

    dll_delete_node(qNode);
  }

  double distance = 0;
  tNode = jrb_find_int(visited,t);
  if(tNode != NULL){
    double* list = jval_v(tNode->val);
    distance = list[1];
    int cnt = 0;
    int parent = 0;
    int add = t;
  
    while(parent != -1){
      path[cnt++] = add;
      tNode = jrb_find_int(visited,add);
      double* fi = jval_v(tNode->val);
      parent = (int)fi[0];
      add = parent;
    }
    *length = cnt;
  }
  free(output);
  jrb_free_tree(visited);
  return distance;
}


//Shortest path teacher


