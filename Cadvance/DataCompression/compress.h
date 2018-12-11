#include "Graph.h"

typedef struct huffmanTree
{
	Graph graph;
	JRB root;
}HuffmanTree;

HuffmanTree makeHuffmanTree(char* buffer,int size);