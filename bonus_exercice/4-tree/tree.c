#include <stdlib.h>
#include <stdio.h>

/* 2-3-4 tree CHECK ON WIKIPEDIA*/
struct tree
{
  int n;           //number of key
  int key[3];      //key, in increaing order
  struct *tree[4]; //for a key K, tree[K] contain key < key[K], and tree[K] >key[K]
};

typedef struct tree s_tree;

/*
 * create an empty node
 */
s_tree *new_tree(void);

/*
 * insert i in t, return the head
 */
s_tree *insert_elt(s_tree *t, int i);

/*
 * remove i of t, return the head
 */
s_tree *remove_elt(s_tree *t, int i);

/*
 * print the key of the tree using a DFS algorithm
 */
void print_tree(s_tree *t);

#ifdef DEBUG

int main(void)
{
    return 0;
}

#endif

