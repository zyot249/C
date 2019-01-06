#include "./wGraph.h"

int main()
{
  Graph g = createGraph();
  // add the vertices and the edges of the graph here
  int s, t, length, path[1000];
  double weight = shortestPath(g, s, t, path, &length);
  if (weight == INFINITE_VALUE)
    printf(“No path between %d and %d\n”, s, t);
  else {
    printf(“Path between %d and %d:”, s, t);
    for (i=0; i<length; i++) printf(“%4d”, path[i]);
    printf(“Total weight: %f”, weight);
  }
  return 0;
}
