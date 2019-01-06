#ifndef __GRAPH_BFS_H__
#define __GRAPH_BFS_H__

#include <stdio.h>
#include "./adj_list.h"
#include "./queue.h"

#ifndef __DECLARATION_DFS_BFS_H__
#define __DECLARATION_DFS_BFS_H__

bool processed[MAXV + 1];	// which vertex have been processed
bool discovered[MAXV + 1]; // which vertex have been discoverded
int parent[MAXV + 1];

#endif

void initialize_bfs(Graph *g)
{
	for (int i = 0; i < g->nvertices; i++)
	{
		processed[i] = discovered[i] = false;
		parent[i] = -1;
	}
	return;
}

void process_vertex_ealy_bfs(Graph *g, int v)
{
	printf("process vertex : %d\n", v);
	return;
}

void process_edge_bfs(Graph *g, int x, int y)
{
	//printf("process edge (%d, %d) \n", x, y);
	return;
}

void process_vertex_late_bfs(Graph *g, int v)
{
	//printf("process vertex late : %d \n", v);
	return;
}

void bfs(Graph *g, int start)
{
	Queue *q;		 // queue of vertices to visit
	int v;			 // current vertex
	int y;			 // successor vertex
	Edgenode *p; // temp node

	initialize_bfs(g);

	q = createQueue();
	enQueue(q, start);
	discovered[start] = true;

	while (empty_queue(q) == false)
	{
		v = deQueue(q);
		process_vertex_ealy_bfs(g, v);
		processed[v] = true;
		p = g->edges[v];

		while (p != NULL)
		{
			y = p->y;

			if (processed[y] == false || g->directed)
			{
				process_edge_bfs(g, v, y);
			}

			if (discovered[y] == false)
			{
				enQueue(q, y);
				discovered[y] = true;
				parent[y] = v;
			}

			p = p->next;
		}
		process_vertex_late_bfs(g, v);
	}
	return;
}

void find_shortes_path(Graph *g, int start, int end, int parent[])
{
	if (start == end || end == -1)
	{
		printf("\n%d", start);
	}
	else
	{
		find_shortes_path(g, start, parent[end], parent);
		printf(" %d", end);
	}
	return;
}

#endif
