/*******************************************************
 * I have an idae make the garbage collection transparent
 * and scope based(to a large degree). The idea is to 
 * write a wrapper to malloc and then have the wrapper
 * modify return address of the stack frame beneath the
 * wrapper function. The new return address would point
 * to a garbage collection function. This garbage
 * collection function would then decide wheater or
 * not the memory that was allocated had left scope.
 * This task is not as easy as it would appear. If the 
 * function that is in question returns the memory
 * address directly or indirectly eg. member of a struct,
 * or appends it to a linked list, etc. then figuring
 * out scoping may still prove to be impossible.
 * 
 * Still this method has potential and if it can be fully
 * implemented then it could make memory managment easier.
 * 
 *******************************************************/

#include "auto_free.h"

struct free_node {
	struct free_node *next;
	void *data;
};

struct free_list {
	struct free_node *list;
	int count;
};

static struct free_list *auto_free_list;

void free_everything(void);
void init();

void auto_free_add(void *x)
{
	if(!auto_free_list)
		init();

	struct free_node *node = malloc(sizeof(struct free_node));
	if(!node){
		perror("malloc");
		exit(ENOMEM);
	}

	node->data = x;
	node->next = auto_free_list->list;
	auto_free_list->list = node;
	auto_free_list->count++;
}

int auto_free_count()
{
	return auto_free_list->count;
}

void init()
{
	auto_free_list = malloc(sizeof(struct free_list));
	if(!auto_free_list){
		perror("malloc");
		exit(ENOMEM);
	}

	auto_free_list->count = 0;
	auto_free_list->list = NULL;

	atexit(free_everything);
}

void recursive_free(struct free_node *node)
{
	if(!node)
		return;

	recursive_free(node->next);
	free(node->data);
	free(node);
}

void free_everything(void)
{
	recursive_free(auto_free_list->list);
	free(auto_free_list);
}
