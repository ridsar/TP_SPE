#include <stdio.h>
#include <stdlib.h>
#include <err.h>

struct heap
{
  int *data; 
  size_t n;
};

typedef struct heap s_heap;

/*
 * make_heap(int*, size_t)
 * make heap allocate an heap, using arr to store data and n as size. Arr have
 * to be already allocated. Arr is of size n and contain already n value, you
 * have to modify it to be sure that it respect the heap property(the first
 * value have to be the greatest). Left child of the cell i is 2i + 1, right
 * child 2i + 2.
 * Exemple:
 * int *arr = malloc(sizeof (int) * 10);
 * for (int i = 0; i < 10; i++)
 *   arr[i] = i;
 * s_heap *h = make_heap(arr, 10);
 * for (size_t i = 0; i <, h->n; i++)
 *   printf("|%i", h->data[i]);
 * printf("|\n");
 *
 * OUTPUT:
 * -> |9|8|6|7|4|5|2|0|3|1|
 * 
 * PSEUDOCODE
 * 
 * fct1(arr, current, size)
 *  max = position_max_child
 *  if max exist
 *    switch curent/max
 *    fct1(arr, max, size)
 *
 * fct0(arr, size)
 *   for (n = size / 2 - 1 to 0)
 *     fct1(arr, n, size)
 */

s_heap *make_heap(int *arr, size_t n)
{
	int swap;
    size_t i = 0, pos;
    while (i < n)
    {
		pos = 2*i+1;
        if (pos < n)
        {
			if (pos+1 && arr[pos] < arr[pos+1])
				pos += 1;
            if (arr[i] < arr[pos])
            {
				 swap = arr[i];
                 arr[i] = arr[pos];
                 arr[pos] = swap;
                 i = 0;
             }
             else
				++i;
        }
		else 
			++i;
	}
	s_heap *heap = malloc(sizeof(s_heap));
	heap->data = arr;
	heap->n = n;
	return heap;
}

void swap(s_heap *h, size_t p, size_t f)
{
	int c = h->data[p];
	h->data[p] = h->data[f];
	h->data[f] = c; 
}

/*
 * pop_heap(s_heap *h)
 * return the max value of the heap. 
 * the new head is now equal to the last value present in the heap, and you
 * have to switch the value with child to restore the heap property
 * You have to realloc the array at the right size every time
 */

// returns false if something goes wrong (realloc fails)
int realloc_func(s_heap *h, size_t size)
{
  int *tmp = realloc(h->data, size * sizeof (int));
  if (tmp == NULL) {
    // oups no more memory ?
    warn("realloc of data fails");
    return 0;
  }
  h->data = tmp;
  h->n = size;
  return 1;
}

int pop_heap(s_heap *h)
{
	int check = 1, top;
	int res = h->data[0];
	size_t pos;
	swap(h, 0, h->n-1);
	h->n -= 1;
	realloc_func(h, h->n); 
	pos = 1;
	while (pos < h->n && check)
	{
		top = pos / 2;
		if (pos+1 < h->n && h->data[pos+1] > h->data[pos])
			pos += 1;
		if (h->data[top] < h->data[pos])
			swap(h, top, pos);
		else 
			check = 0;
		pos = 2*pos+1;
	}
	return res;
}


/*
 * insert_heap(heap, elt)
 * insert a new elt in the heap. 
 * realloc the array to the correct size, put the new element at the last
 * position and swap with the parent until the heap property is restore
 */
void insert_heap(s_heap *h, int elt)
{
	int check = 1, top;
	h->n += 1;
	size_t pos = h->n;
	realloc_func(h, h->n);
	h->data[(h->n)-1] = elt;
	while (pos > 0 && check)
	{
		top = pos / 2;
		if (pos % 2 == 0)
			top -= 1;
		if (h->data[pos] > h->data[top])
			swap(h, pos, top);
		else 
			check = 0;
		pos = top;
	}
}

/*
 * heap_sort(arr, size)
 * sort the array arr of size n on decreasing order, using an heap.
 */
void heap_sort(int* arr, size_t n)
{
	s_heap *h = malloc(sizeof(s_heap));
	h->data = NULL;
	h->n = 0;
	for (size_t i = 0; i < n; ++i)
		insert_heap(h, arr[i]);
	for (size_t j = 0; j < n; ++j)
	{
		arr[j] = pop_heap(h);
	}
}

//#ifdef DEBUG

int main(void)
{
	int* arr = malloc(7 * sizeof(int));
	arr[0] = 1;
	arr[1] = 7;
	arr[2] = 3;
	arr[3] = 6;
	arr[4] = 8;
	arr[5] = 9;
	arr[6] = 10;
	for(size_t i = 0; i < 7; ++i)
		printf("%d ", arr[i]);
	printf("\n");
	heap_sort(arr, 7);
	for(size_t i = 0; i < 7; ++i)
		printf("%d ", arr[i]);
	printf("\n");


    return 0;
}

//#endif

