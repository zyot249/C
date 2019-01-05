#include <stdio.h>
#include <stdlib.h>
#include "compress.h"

void get_frequence_table(char* nameFile,int freTable[256]){
	FILE* fin = fopen(nameFile,"r");
	for (int i = 0; i < 256; ++i){
		freTable[i] = 0;
	}
	int c;
	while((c = fgetc(fin)) != EOF){
		freTable[c] += 1;
	}
}

int dll_size(Dllist dllist){
	int count = 0;
	Dllist node;
	dll_traverse(node, dllist){
		count++;
	}
	return count;
}

int dll_get_min(Dllist dllist){
	int min = DEFAULT;
	Dllist node;
	dll_traverse(node, dllist){
		int val = jval_i(node->val);
		min = (val < min) ? val : min ;	
	}
	dll_traverse(node, dllist){
		if(jval_i(node->val) == min){
			dll_delete_node(node);
			break;
		}
	}
	return min;
}

int graph_find_val(Graph graph,int val,int* output){
	JRB ptr;
	int key = DEFAULT;
	jrb_traverse(ptr,graph.vertices){
		if(jval_i(ptr->val) == val){
			int id = jval_i(ptr->key);
			if(indegree(graph,id,output) == 0){
				key = id;
				break;
			}
		}
	}
	return key;
}

void set_value_edge(Graph graph,int v1,int v2,int val){
	JRB node1 = jrb_find_int(graph.edges,v1);
  if(node1 == NULL)
    return;
  else{
    JRB node2 = jrb_find_int((JRB)jval_v(node1->val),v2);
    if(node2 == NULL) return;
    else {
    	node2->val = new_jval_i(val);
    }  
  }
}

int get_value_edge(Graph graph,int v1,int v2){
	JRB node1 = jrb_find_int(graph.edges,v1);
  if(node1 == NULL)
    return -1;
  else{
    JRB node2 = jrb_find_int((JRB)jval_v(node1->val),v2);
    if(node2 == NULL) return -1;
    else return jval_i(node2->val);
  }
}

HuffmanTree make_huffman_tree(char* buffer,int size){
	// Initialize a HuffmanTree
	int* output = (int*)malloc(100*sizeof(int));
	HuffmanTree huffTree;
	huffTree.graph = create_graph(1);
	Dllist pQueue = new_dllist();
	// Huffman Coding
	// make leaves from buffer
	// and make a priority queue with frequences of leaves
	for (int i = 0; i < size; ++i){
		if (buffer[i] != 0){
			add_vertex(huffTree.graph,i,buffer[i]);
			dll_append(pQueue, new_jval_i(buffer[i]));
		}
	}

	int genNewKey = 301;
	// make tree
	while(dll_size(pQueue) > 1){
		int min1 = dll_get_min(pQueue);
		int min2 = dll_get_min(pQueue);
		// add vertex
		add_vertex(huffTree.graph,genNewKey++,(min1 + min2));
		dll_append(pQueue,new_jval_i(min1 + min2));
		// add edge
		int id1 = graph_find_val(huffTree.graph,min1,output);
		add_edge(huffTree.graph,genNewKey-1,id1);
		int id2 = graph_find_val(huffTree.graph,min2,output);
		add_edge(huffTree.graph,genNewKey-1,id2);
		// set value 0 for the edge to node with smaller val
		if(min1 <= min2) set_value_edge(huffTree.graph,genNewKey-1,id1,0);
		else set_value_edge(huffTree.graph,genNewKey-1,id2,0);
	}

	huffTree.root = genNewKey -1;
	return huffTree;
}

JRB make_huffman_code_table(HuffmanTree huffTree){
	JRB codeTable = make_jrb();
	char code[20];
	int start = huffTree.root;
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
      
      n = outdegree(graph,u,output); // get list of adjacent 
      if(n != 0){
 				for(i = n-1;i >= 0;i--){
	  			v = output[i];
	  			if(jrb_find_int(visited,v) == NULL)
	    			dll_prepend(stack,new_jval_i(v)); // put if not visited
				}
      }else{

      }
    }
  }

  // free memory
  jrb_free_tree(visited);
  free_dllist(stack);
  free(output);
}