#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./unweightedGraph.h"


// Implementation APIs

Graph create_graph(int kind){
  Graph g;
  g.edges = make_jrb();
  g.vertices = make_jrb();
  if(kind != 0) g.kind = 1;
  else g.kind = 0;
  return g;
}

void add_vertex(Graph graph,int id,int val){
  JRB node = jrb_find_int(graph.vertices,id);
  if(node == NULL){
    jrb_insert_int(graph.vertices,id,new_jval_i(val));
  }else{
    printf("The vertex with id : %d existed!\n", id);
  }
}

int get_vertex_val(Graph graph,int id){
  JRB node = jrb_find_int(graph.vertices,id);
  if(node == NULL){
    return -1;
  }else{
    int val = jval_i(node->val);
    return val;
  }
}

void add_edge(Graph graph,int v1,int v2){
  // check for existence of vertices v1 and v2
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
    node1 = jrb_find_int(graph.edges,v1); // find edge-tree of vertex v1
    JRB tree;
    if(node1 == NULL){ // edge-tree of vertex v1 doesn't exist(degree = 0)
      tree = make_jrb();
      jrb_insert_int(graph.edges,v1,new_jval_v(tree));
    }else tree = (JRB)jval_v(node1->val);
    // add edge v1 --> v2
    if(jrb_find_int(tree,v2) == NULL){ // check the existence of the edge btw v1 --> v2
      jrb_insert_int(tree,v2,new_jval_i(1)); // default value for edge is 1 - not used
    

      // For undirected if kind == 0
      if(graph.kind == 0){
        node2 = jrb_find_int(graph.edges,v2); // find edge-tree of vertex v2 
        if(node2 == NULL){ // edge-tree of vertex v2 doesn't exist(degree = 0)
          tree = make_jrb();
          jrb_insert_int(graph.edges,v2,new_jval_v(tree));
        }else tree = (JRB)jval_v(node2->val);
        // add adge v2 --> v1
        jrb_insert_int(tree,v1,new_jval_i(1));
      } 
    }
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
  JRB node = jrb_find_int(graph.vertices,v); // check the existence of vertex v
  if(node == NULL){
    printf("Vertex %d doesn't exist!\n",v);
    return -1;
  }else{
    int count = 0;
    jrb_traverse(node,graph.edges){
      JRB tmp = (JRB)jval_v(node->val);
      if(jrb_find_int(tmp,v) != NULL) 
        output[count++] = jval_i(node->key);
    }
    return count;
  }
}

int outdegree(Graph graph,int v,int* output){
  JRB node = jrb_find_int(graph.vertices,v); // check the existence of vertex v
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
  JRB node,name;
  jrb_traverse(node,graph.vertices){
    int v = jval_i(node->key);
    name = jrb_find_int(graph.vertices,v);
    printf("Vertex %d : ",jval_i(name->val));
    int n = outdegree(graph,v,output);
    if(n != 0){
      for(int i = 0;i<n;i++){
        name = jrb_find_int(graph.vertices,output[i]);
        printf("--> %d ",jval_i(name->val));
      }
    }
    printf("\n");
  }
}

void BFS(Graph graph,int start,int stop,void(*func)(Graph,int)){
  JRB visited; // save the visited vertices
  Dllist queue,node;
  int u,v,i,n;
  int* output = (int*)malloc(100*sizeof(int));

  // Initialization
  queue = new_dllist();
  dll_append(queue,new_jval_i(start)); // add start vertex into queue to visit first
  visited = make_jrb();

  while(!dll_empty(queue)){
    node = dll_first(queue); // dequeue
    u = jval_i(node->val); // get value - key of vertex
    dll_delete_node(node);

    if(jrb_find_int(visited,u) == NULL){ // didn't visit
      func(graph,u); // do sth on func
      jrb_insert_int(visited,u,new_jval_i(1)); // add into visited tree
      if(u == stop) break;

      n = outdegree(graph,u,output); // get list of adjacent 
      if(n != 0){
      	for(i = 0;i < n;i++){ 
        	v = output[i];
        	if(jrb_find_int(visited,v) == NULL)
          	dll_append(queue,new_jval_i(v)); // enqueue if not visited
      	}
      }
    }
  }

  // free memory
  jrb_free_tree(visited);
  free_dllist(queue);
  free(output);
}

void DFS(Graph graph,int start,int stop,void(*func)(Graph,int)){
  JRB visited; // save the visited vertices
  Dllist stack,node;
  int u,n,i,v;
  int* output = (int*)malloc(100*sizeof(int));

  // Initialization
  visited = make_jrb();
  stack = new_dllist();
  dll_prepend(stack,new_jval_i(start)); // add start vertex into stack to visit first

  while(!dll_empty(stack)){
    node = dll_first(stack); // pop
    u = jval_i(node->val);	// get value - key of vertex
    dll_delete_node(node);

    if(jrb_find_int(visited,u) == NULL){ // didn't visit
      func(graph,u); // do sth
      jrb_insert_int(visited,u,new_jval_i(1)); // add into visited tree
      if(u == stop)
				break;

      n = outdegree(graph,u,output); // get list of adjacent 
      if(n != 0){
 				for(i = n-1;i >= 0;i--){
	  			v = output[i];
	  			if(jrb_find_int(visited,v) == NULL)
	    			dll_prepend(stack,new_jval_i(v)); // put if not visited
				}
      }
    }
  }

  // free memory
  jrb_free_tree(visited);
  free_dllist(stack);
  free(output);
}



// For Directed Graph
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

// Find Shortest Path
Dllist shortest_path(Graph graph,int start,int stop){
  JRB visited,pred,tNode; // in pred: node has : key is keyofNode and value is predecessor of this node when BFS
  Dllist queue,qNode;
  int* output = (int*)malloc(100*sizeof(int));
  int u,v,n,k;
  
  visited = make_jrb();
  pred = make_jrb();
  queue = new_dllist();
  dll_append(queue,new_jval_i(start));
  jrb_insert_int(pred,start,new_jval_i(-1));

  // Start BFS from start to stop
  while(!dll_empty(queue)){
    qNode = dll_first(queue);
    u = jval_i(qNode->val);
    dll_delete_node(qNode);

    if(jrb_find_int(visited,u) == NULL){
      jrb_insert_int(visited,u,new_jval_i(1));
    }
    
    if(u == stop) break;
    
    n = outdegree(graph,u,output);
    if(n != 0){
      for(int i = 0;i < n;i++){
				v = output[i];
				if(jrb_find_int(visited,v) == NULL)
	  			//add outdegree of u to pred,value of node v in pred is u
	  			if(jrb_find_int(pred,v) == NULL){
	    			jrb_insert_int(pred,v,new_jval_i(u));
	    			dll_append(queue,new_jval_i(v));
	  			}
      }
    }
  }
  
  // Finish BFS
  // Get path
  Dllist path = new_dllist();
  tNode = jrb_find_int(pred,stop);
  if(tNode == NULL){
    return NULL;
  }else{
    //find path in pred by finding predecessor
    dll_prepend(path,new_jval_i(stop));
    k = jval_i(tNode->val);
    while(k != start){
      dll_prepend(path,new_jval_i(k));
      tNode = jrb_find_int(pred,k);
      k = jval_i(tNode->val);
    }
    dll_prepend(path,new_jval_i(k));
  }
 
  jrb_free_tree(pred);
  jrb_free_tree(visited);
  free(output);
  free_dllist(queue);

  return path;
}

// Topological Sort
int topol_sort(Graph graph, int *output){
  JRB node;
  JRB indegreeTable = make_jrb();
  int cont, count, v;

  // add all vertices with their indegree to indegreeTable
  jrb_traverse(node, graph.vertices){
    v = jval_i(node->key);
    jrb_insert_int(indegreeTable, v, new_jval_i(indegree(graph, v, output)));
  }

  //loop
  count = 0;
  cont = 1;
  while(cont){
    cont = 0;
    //Find the vertex has indegree = 0
    jrb_traverse(node, indegreeTable){
      if(jval_i(node->val) == 0){
				cont = 1;
				break;
      }
    }
    
    if(cont){
      output[count++] = jval_i(node->key); // add found vertex Node to result
      jrb_delete_node(node);
      
      // find outdegree of vertex Node and decrease the indegree of them by 1
      jrb_traverse(node, indegreeTable){
				if(has_edge(graph, output[count-1], jval_i(node->key))){
	  			node->val = new_jval_i(jval_i(node->val) - 1);
				}
      }	
    }
  }

  jrb_free_tree(indegreeTable);
  return count;
}
