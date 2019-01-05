#ifndef __COMPRESS_H__
#define __COMPRESS_H__
#include "./unweightedGraph.h"

#define DEFAULT -1

typedef struct huffmanTree
{
	Graph graph;
	int root;
}HuffmanTree;

HuffmanTree make_huffman_tree(char* buffer,int size);
JRB make_huffman_code_table(HuffmanTree huffTree);
void get_frequence_table(char* nameFile,int freTable[256]);
#endif