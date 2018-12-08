#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./weightedGraph.h"

int main()
{
  Graph g = create_graph();
  //add vertices
  add_vertex(g,1,"1");
  add_vertex(g,2,"2");
  add_vertex(g,3,"3");
  add_vertex(g,4,"4");
  add_vertex(g,5,"5");
  add_vertex(g,6,"6");
  add_vertex(g,7,"7");
  add_vertex(g,8,"8");
  // add edges
  add_edge(g,1,2,9);
  add_edge(g,1,6,14);
  add_edge(g,1,7,15);
  add_edge(g,2,3,24);
  add_edge(g,6,3,18);
  add_edge(g,6,5,30);
  add_edge(g,6,7,5);
  add_edge(g,7,5,20);
  add_edge(g,7,8,44);
  add_edge(g,5,4,11);
  add_edge(g,5,8,16);
  add_edge(g,4,8,6);
  add_edge(g,4,3,6);
  add_edge(g,3,8,19);
  add_edge(g,3,5,2);
  int s, t, length, path[1000];
  s = 1;
  t = 8;
  length = 0;
  double weight = shortest_path(g, s, t, path, &length);
  if (weight == INFINITE_VALUE)
    printf("No path between %d and %d\n", s, t);
  else {
    printf("Path between %d and %d:\n", s, t);
    for (int i=length-1; i >= 0; i--) printf("%4d", path[i]);
    printf("\nTotal weight: %g\n", weight);
  }
  return 0;
}
