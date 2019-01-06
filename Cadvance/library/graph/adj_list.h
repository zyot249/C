#ifndef __ADJ_LIST_H_
#define __ADJ_LIST_H_

#include <stdlib.h>

#define MAXV 1000 // max vertex

typedef int bool;
enum { false, true };

typedef struct Edgenode {
  int y; // adjacency info
  int weight;
  struct Edgenode *next; // the next adge in list
} Edgenode;

typedef struct
{
  Edgenode *edges[MAXV + 1];
  int degree[MAXV + 1]; // outter degree of each vertex
  char *vertex_names[MAXV + 1];
  int nvertices; // number of vertex in graph
  int nedges;    // number of edge in graph;
  bool directed; // is graph directed
} Graph;

void init_graph(Graph *g, bool directed)
{
  int i;

  g->nvertices = 0;
  g->nedges = 0;
  g->directed = directed;

  for (int i = 0; i <= MAXV; i++)
    g->degree[i] = 0;
  for (int i = 0; i <= MAXV; i++)
  {
    g->edges[i] = NULL;
    g->vertex_names[i] = NULL;
  }

  return;
}

void add_vertex_name(Graph *g, int vertex_index, char *name)
{
  g->vertex_names[vertex_index] = name;
  return;
}

char *get_vertex_name(Graph *g, int vertex_index)
{
  return g->vertex_names[vertex_index];
}

void insert_edge(Graph *g, int x, int y, bool directed)
{
  Edgenode *p = (Edgenode *)malloc(sizeof(Edgenode)); // temp pointer

  p->weight = 0;
  p->y = y;
  p->next = g->edges[x];

  g->edges[x] = p;
  g->degree[x]++;

  if (directed == false)
  {
    insert_edge(g, y, x, true);
  }
  else
  {
    g->nedges++;
  }

  return;
}

void insert_weighted_edge(Graph *g, int x, int y, int weight, bool directed) {
  Edgenode *p = (Edgenode *)malloc(sizeof(Edgenode)); // temp pointer

  p->weight = weight;
  p->y = y;
  p->next = g->edges[x];

  g->edges[x] = p;
  g->degree[x]++;

  if (directed == false) {
    insert_weighted_edge(g, y, x, weight, true);
  } else {
    g->nedges++;
  }

  return;
}


void read_graph_from_file(Graph *g, char *fn, bool directed)
{

  FILE *fp = fopen(fn, "r");

  if (fp == NULL)
  {
    printf("Can not open file !\n");
  }
  else
  {
    init_graph(g, directed);

    int x, y; // vertex in edge (x, y)
    int nedges;
    fscanf(fp, "%d %d", &(g->nvertices), &nedges);

    for (int i = 0; i < nedges; i++)
    {
      fscanf(fp, "%d %d", &x, &y);
      insert_edge(g, x, y, directed);
    }
  }

  fclose(fp);
  return;
}

void read_weighted_graph(Graph *g, char *fn, bool directed)
{

  FILE *fp = fopen(fn, "r");

  if (fp == NULL) {
    printf("Can not open file !\n");
  } else {
    init_graph(g, directed);

    int x, y, weight; // vertex in edge (x, y)
    int nedges;
    fscanf(fp, "%d %d", &(g->nvertices), &nedges);

    for (int i = 1; i <= nedges; i++) {
      fscanf(fp, "%d %d %d ", &x, &y, &weight);
      insert_weighted_edge(g, x, y, weight, directed);
    }
  }

  fclose(fp);
  return;
}

void print_graph_by_vertex_index(Graph *g)
{
  Edgenode *p; // temp pointer

  for (int i = 1; i <= g->nvertices; i++)
  {
    printf("degree : %d ||  %d ", g->degree[i], i);

    p = g->edges[i];
    while (p != NULL)
    {
      printf("--> %d", p->y);
      p = p->next;
    }
    printf("\n");
  }
  return;
}

void print_graph_by_vertex_name(Graph *g)
{
  Edgenode *p; // temp pointer

  for (int i = 0; i < g->nvertices; i++)
  {
    printf("degree : %d ||  %s ", g->degree[i], get_vertex_name(g, i));

    p = g->edges[i];
    while (p != NULL)
    {
      printf("--> %s", get_vertex_name(g, p->y));
      p = p->next;
    }
    printf("\n");
  }
  return;
}

#ifndef __BUBBLE_SORT_LINKED_LIST_H__
#define __BUBBLE_SORT_LINKED_LIST_H__

void swap_y(Edgenode *a, Edgenode *b)
{
  int temp;
  temp = a->y;
  a->y = b->y;
  b->y = temp;

  temp = a->weight;
  a->weight = b->weight;
  b->weight = temp;
  return;
}

void bubble_sort_linked_list(Edgenode *start)
{
  int swapped, i;
  Edgenode *ptr1;
  Edgenode *lptr = NULL;

  if (start == NULL)
    return;

  do
  {
    swapped = 0;
    ptr1 = start;

    while (ptr1->next != lptr)
    {
      if (ptr1->y > ptr1->next->y)
      {
        swap_y(ptr1, ptr1->next);
        swapped = 1;
      }
      ptr1 = ptr1->next;
    }
    lptr = ptr1;
  } while (swapped);
}

#endif

void sort_vertex_graph(Graph *g)
{
  for (int i = 0; i < g->nvertices; i++)
  {
    bubble_sort_linked_list(g->edges[i]);
  }
  return;
}

#ifndef __DECLARATION_DFS_BFS_H__
#define __DECLARATION_DFS_BFS_H__

bool processed[MAXV + 1];  // which vertex have been processed
bool discovered[MAXV + 1]; // which vertex have been discoverded
int parent[MAXV + 1];

#endif

#endif
