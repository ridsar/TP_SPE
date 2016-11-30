#include <stdlib.h>
#include <stdio.h>

struct static_graph
{
  int **cost; //a two dimension array of int of size n*n, where cost[i][j] represent the price to go from i to j
  size_t n;
}

typedef struct static_graph s_stat_g;

struct dynamic_graph_node
{
  size_t node;
  int price;
  struct dynamic_graph_node *next;
}

typedef struct dynamic_graph_node s_dyn_g_n;

struct dynamic_graph
{
  s_dyn_g_n *node; //an array of size n, containing the list of node that you can acceed from the node n, with the relative price
  size_t n;
}

typedef struct dynamic_graph s_dyn_g;

// create a static graph of size n and fill with 0
s_stat_g *new_static(size_t n);

/*
 * create a static graph of size n
 * Fill the graph with the value in the file of path 'path'
 * It's a valid path, to a file fill of int between 0 and 9.
 * Exemple:
 * n = 3
 * file:
 * 014
 * 042
 * 666
 */
s_stat_g *from_file(char *path, size_t n);

/*
 * Convert a static graph to a dynamic one
 */
s_dyn_g *convert_to_dyn(s_stat_g *s);

/*
 * find the cheaper path to go to end from begin and return the price.
 * if the node or the path doesn't exist, return -1
 */
int shortest_stat(s_stat_g *s, int begin, int end);

int shortest_dyn(s_dyn_g *s, int begin, int end);

#ifdef DEBUG

int main(void)
{
    return 0;
}

#endif

