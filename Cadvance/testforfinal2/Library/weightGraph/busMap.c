#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./busMap.h"

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

int get_vertex_id(Graph graph,char* name){
	JRB node;
	int check = 0;
	jrb_traverse(node,graph.vertices){
		char* getName = strdup(jval_s(node->val)); 
		if(strcmp(name,getName) == 0) {
			check = 1;
			break;
		}
	}
	if(check == 1)
		return jval_i(node->key);
	else return -1;
}

char* get_vertex_name(Graph graph,int id){
  JRB node = jrb_find_int(graph.vertices,id);
  if(node == NULL){
    return NULL; //if there doesnt exist the node with key id --> return NULL
  }else{
    char* name = strdup(jval_s(node->val));
    return name;
  }
}

void add_edge(Graph graph,int v1,int v2,char* bus){
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
    	Dllist list = new_dllist();//create a list of buses that go through this line
    	dll_append(list,new_jval_s(bus));
      jrb_insert_int(tree,v2,new_jval_v(list));//insert the edge with weight
    }else{
    	Dllist list = (Dllist)jval_v(check->val);//get the list of buses
    	dll_append(list,new_jval_s(bus));
    }
  }
}

Dllist get_list_bus(Graph graph,int v1,int v2){
	JRB node1 = jrb_find_int(graph.edges,v1);//find v1 in list edges
	if(node1 == NULL) return NULL;
	else{
		JRB node2 = jrb_find_int((JRB)jval_v(node1->val),v2);
		if(node2 == NULL) return NULL;
		else{
			Dllist list = (Dllist)jval_v(node2->val);//get the list of buses
			return list;
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
  Dllist path = new_dllist();
  tNode = jrb_find_int(pred,stop);
  if(tNode == NULL){
    printf("No Path!\n");
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
  // print result
  
  jrb_free_tree(pred);
  jrb_free_tree(visited);
  free(output);
  free_dllist(queue);
  return path;
}