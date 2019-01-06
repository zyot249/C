#ifndef __GRAPH_DFS_H__
#define __GRAPH_DFS_H__

#include <stdio.h>
#include "./stack.h"
#include "./adj_list.h"

#ifndef __DECLARATION_DFS_BFS_H__
#define __DECLARATION_DFS_BFS_H__

bool processed[MAXV + 1];	// which vertex have been processed
bool discovered[MAXV + 1]; // which vertex have been discovered
int parent[MAXV + 1];

#endif

int visisted[MAXV + 1];
int entry_time[MAXV + 1];
int exit_time[MAXV + 1];

int time;
bool finished;

void initialize_dfs(Graph *g)
{
	for (int i = 0; i <= g->nvertices; i++)
	{
		processed[i] = discovered[i] = false;
		parent[i] = -1;
		entry_time[i] = exit_time[i] = 0;
	}

	time = 0;
	finished = false;
	return;
}

void find_path(Graph *g, int start, int end, int parent[])
{
	if ((start == end) || end == -1)
	{
		printf("\n %d", start);
	}
	else
	{
		find_path(g, start, parent[end], parent);
		printf(" %d", end);
	}

	return;
}

void process_vertex_ealy_dfs(Graph *g, int v)
{
	printf("process vertex : %d\n", v);
	return;
}

void process_edge_dfs(Graph *g, int x, int y)
{

	return;
}

void process_vertex_late_dfs(Graph *g, int v)
{
	return;
}

void dfs(Graph *g, int v)
{
	Edgenode *p; // temp node
	int y;			 // successor vertex

	if (finished)
		return;

	discovered[v] = true;
	time = time + 1;
	entry_time[v] = time;

	process_vertex_ealy_dfs(g, v);

	p = g->edges[v];

	while (p != NULL)
	{
		y = p->y;
		if (discovered[y] == false)
		{
			parent[y] = v;
			process_edge_dfs(g, v, y);
			dfs(g, y);
		}
		else if (!processed[y] || g->directed)
		{
			process_edge_dfs(g, v, y);
		}

		if (finished) return;

		p = p->next;
	}

	process_vertex_late_dfs(g, v);

	time = time + 1;
	exit_time[v] = time;

	processed[v] = true;
	return;
}

/* check if a graph contain a circle BEGIN */

void process_edge_is_cyclic(int x, int y)
{
	if (parent[y] != x && discovered[y] && !processed[y])
	{
		finished = true;
	}
	return;
}

int is_cyclic_dfs_helper(Graph *g, int v)
{
	Edgenode *p; // temp node
	int y;			 // successor vertex

	if (finished)
		return true;

	discovered[v] = true;
	time = time + 1;
	entry_time[v] = time;

	p = g->edges[v];
	while (p != NULL)
	{
		y = p->y;
		if (discovered[y] == false)
		{
			parent[y] = v;
			process_edge_is_cyclic(v, y);
			is_cyclic_dfs_helper(g, y);
		}
		else if (!processed[y] || g->directed)
		{
			process_edge_is_cyclic(v, y);
		}

		if (finished)
			return true;

		p = p->next;
	}

	time = time + 1;
	exit_time[v] = time;

	processed[v] = true;

	return false;
}

int is_cyclic(Graph *g)
{
	int i;
	for (int i = 0; i < g->nvertices; i++)
	{
		if (is_cyclic_dfs_helper(g, i))
		{
			return true;
		}
	}
	return false;
}

/* check if a graph contain a circle END */

/* Topological sort BEGIN */

stackNode *sorted;

void initialize_topo_sort(Graph *g)
{
	int i;
	for (int i = 0; i <= g->nvertices; i++)
	{
		processed[i] = discovered[i] = false;
		entry_time[i] = exit_time[i] = 0;
		parent[i] = -1;
	}

	sorted = NULL;
	time = 0;
	finished = false;
}

void dfs_topo_sort_helper(Graph *g, int v)
{
	Edgenode *p; // temp pointer
	int y;			 // successor vertex

	if (finished)
		return; // allow dfs to termilater

	discovered[v] = true;
	time = time + 1;
	entry_time[v] = time;

	p = g->edges[v];
	while (p != NULL)
	{
		y = p->y;

		if (discovered[y] == false)
		{
			parent[y] = v;
			dfs_topo_sort_helper(g, y);
		}

		if (finished)
			return;

		p = p->next;
	}

	push(&sorted, v);

	time = time + 1;
	exit_time[v] = time;

	processed[v] = true;
	return;
}

void topo_sort(Graph *g)
{
	int i;
	for (int i = 0; i < g->nvertices; i++)
	{
		if (discovered[i] == false)
		{
			dfs_topo_sort_helper(g, i);
		}
	}

	print_stack(&sorted);
	printf("\n");

	return;
}

/* Topological sort END */

/* count path BEGIN */

void initialize_count_path() {
	for (int i = 0; i <= MAXV; i++) {
		visisted[i] = false;
	}
	return;
}

void count_path(Graph *g, int start, int end, int *counter) {
	visisted[start] = true;
	
	if (start == end) {
		*counter = *counter + 1;
	} else {
		Edgenode *temp = g->edges[start];
		while (temp != NULL) {
			if (!visisted[temp->y]) {
				count_path(g, temp->y, end, counter);
			}
			temp = temp->next;
		}
	}

	visisted[start] = false;
}

/* count path END   */

#endif
