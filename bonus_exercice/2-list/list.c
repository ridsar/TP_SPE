#include <stdlib.h>
#include <stdio.h>

/*doubly linked list without sentinel*/
struct list
{
  struct list *prev;
  struct list *next;
  int elm;
};

/*
 * list_len(list)
 * returns the length of the list
 */
size_t list_len(struct list *list)
{
    size_t res = 0;
    for (; list != NULL; list = list->next)
        res += 1;
    return res;
}

 
/*
 * list_print(list)
 * print the list.
 * expected output:
 * |0|1|2|3|4|...|42|666|\n (newline)
 */
void print_list(struct list *list)
{
    if (list)
    {
        for (; list; list = list->next)
       	 printf("|%d",list->elm);
	}
	printf("|\n");
}
/*
 * list_push_front(list, elm)
 * put elm in front of list and return the new head
 */
struct list *list_push_front(struct list *list, int elm)
{
    struct list *res = malloc( sizeof(struct list));
    res->prev = NULL;
    res->next = list;
    res->elm = elm;
	if (list)
   		 list->prev = res;
    return res;
}
 
/*
 * list_pop_front(list)
 * free the first node and return the new head or NULL if empty
 */
struct list *list_pop_front(struct list *list)
{
    if (!list)
        return list;
    if (!list->next)
    {
        free(list);
        return NULL;
    }
    struct list *res = list->next;
    res->prev = NULL;
    free(list);
    return res;
}
 
/*
 * list_find(list, value)
 * search for the first node containing value and returns (without detaching it)
 * the corresponding list node. The function returns NULL if the value is not
 * present in the list.
 */
struct list* list_find(struct list *list, int value)
{
    if (!list)
        return NULL;
    while (list && list->elm != value)
        list = list->next;
    return list;
}
 
/*
 * list_is_sorted(list)
 * check whether the list is sorted in increasing order(return 0 if it is, 0>
 * if not)
 */
int list_is_sorted(struct list *list)
 {
    if (!list || !list->next)
        return 1;
    int check = 1;
    while (list->next && check)
    {
			check = list->elm <= list->next->elm;
        list = list->next;
    }
    return check;
}

 
/*
 * list_insert(list, elm)
 * insert elm in the sorted list (keeping the list sorted)
 * Return the new head
 */
struct list *list_insert(struct list *list, int elm)
{
	struct list *tmp;
	struct list *result = list;
    struct list *res = malloc (sizeof(struct list));
    res->elm = elm;
	res->next = NULL;
	res->prev = NULL;
	if (!list)
		return res;
	while(list && elm > list->elm)
	{
		tmp = list;
		list = list->next;
	}
	if (!list)
	{
		tmp->next = res;
		res->prev = tmp;	
	}
	else if (!list->prev)
	{
		res->next = list;
		list->prev = res;
		return res;
	}
	else
	{
		res->next = list;
		res->prev = list->prev;
		list->prev->next = res;
		list->prev = res;
	} 
	return result;
}

/*
 * list_remove(list, elm)
 * Remove elm from the list and return the head
 * Do nothing if elm doesn't exist
 */
struct list *list_remove(struct list *list, int elm)
{
	struct list *res = list;
	struct list *tmp;
	while (list && list->elm != elm)
	{
		tmp = list;
		list = list->next;
	}
	if (list)
	{
		if (!list->prev)
		{
			tmp = list->next;
			free(list);
			return tmp;
		}
		if (!list->next)
		{
			list->prev->next = NULL;
			free(list);	
		}
		if (!list->prev && !list->next)
		{
			free(list);
			return NULL;
		}
		tmp->next = list->next;
		list->next->prev = tmp;
		free(list);
	
	}
	return res;
}
/*
 * list_free(list)
 * Free all node of list
 */
void free_list(struct list *list)
{
	while(list->next)
	{
		list = list-> next;
		free(list->prev);
		list->prev = NULL;
	}
	free(list);
}

//#ifdef DEBUG

int main(void)
{
	struct list *l = NULL;
	print_list(l);
	l = list_pop_front(l);
	print_list(l);
	printf("Should be : |\n");
	printf("%zu\n", list_len(l));
	printf("Should be : 0\n");
	print_list(list_find(l, 5));
	printf("Should be : NULL\n");
	l = list_push_front(l, 10);
	print_list(l);
	printf("Should be : |10|\n");
	l = list_push_front(l, 9);
	print_list(l);
	printf("Should be : |9|10|\n");
	l = list_push_front(l, 5);
	print_list(l);
	printf("Should be : |5|9|10|\n");
	l = list_push_front(l, 1);
	print_list(l);
	printf("Should be : |1|5|9|10|\n");
	print_list(list_find(l, 5));
	printf("Should be : |5|9|10|\n");
	printf("%d\n", list_is_sorted(l));
	printf("Should be : 1\n");
	l = list_pop_front(l);
	print_list(l);
	printf("Should be : |5|9|10|\n");
	l = list_pop_front(l);
	print_list(l);
	printf("Should be : |9|10|\n");
	l = list_pop_front(l);
	print_list(l);
	printf("Should be : |10|\n");
	l = list_pop_front(l);
	print_list(l);
	printf("Should be : |\n");
	l = list_insert(l, 1);
	print_list(l);
	printf("Should be : |1|\n");
	l = list_insert(l, 9);
	print_list(l);	
	printf("Should be : |1|9|\n");
	l = list_insert(l, 8);
	print_list(l);
	printf("Should be : |1|8|9|\n");
	l = list_insert(l, 2);
	print_list(l);
	printf("Should be : |1|2|8|9|\n");
	l = list_insert(l, 2);
	print_list(l);
	printf("Should be : |1|2|2|8|9|\n");
	printf("%d\n",list_is_sorted(l));
	l = list_remove(l, 8);
	print_list(l);
	printf("Should be : |1|2|2|9|\n");
	printf("%zu\n", list_len(l));
	printf("Should be :4\n");
	l = list_remove(l, 1);
	print_list(l);
	printf("Should be : |2|2|9|\n");
	l = list_remove(l, 2);
	print_list(l);
	printf("Should be : |2|9|\n");
	l = list_remove(l, 0);
	print_list(l);
	printf("Should be : |2|9|\n");
	printf("%d\n",list_is_sorted(l));
	
	free_list(l);
	print_list(l);
	printf("Should be : |\n");

    return 0;
}

//#endif

