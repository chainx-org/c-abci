
#ifndef __DLIST_H__
#define __DLIST_H__

#include <string.h>
#include <stdlib.h>

typedef struct DNode{
	struct DNode *next;
	struct DNode *prev;
	void *data;
}DNode;

struct dlist{
	size_t size;
	DNode *head;
	DNode *tail;
	DNode *curr;
};


int create_dlist(struct dlist *dlist);

int insert_tail(struct dlist *dlist, void *data, size_t size);

int insert_head(struct dlist *dlist, void *data, size_t size);

int search_dlist(struct dlist *dlist, void *data, size_t size);

int delete_dlist(struct dlist *dlist, void *data, size_t size);

int delete_tail(struct dlist *dlist);

int delete_head(struct dlist *dlist);

void destroy_dlist(struct dlist *dlist);

#endif
