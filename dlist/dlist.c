
#include "dlist.h"
#include <stdio.h>

static DNode *init_node(void *data, size_t size);

static void free_node(DNode* node);

int create_dlist(struct dlist *dlist)
{
	if ( dlist == NULL )
	{
		return -1;
	}

	dlist->size = 0;
	dlist->head = NULL;
	dlist->tail = NULL;

	return 0;
}

int insert_tail(struct dlist *dlist, void *data, size_t size)
{
	if( dlist == NULL || data == NULL )
	{
		return -1;
	}

	DNode *node = init_node(data, size);
	if ( node == NULL )
	{
		return -1;
	}

	if ( dlist->head == NULL )
	{
		node->next = node;
		node->prev = node;
		dlist->head = node;
		dlist->tail = node;
	}
	else
	{
		node->next = dlist->head;
		node->prev = dlist->tail;
		dlist->tail->next = node;
		dlist->head->prev = node;
		dlist->tail = node;
	}

	dlist->size += 1;

	return 0;
}

int insert_head(struct dlist *dlist, void *data, size_t size)
{
	if ( dlist == NULL || data == NULL )
	{
		return -1;
	}

	DNode *node = init_node(data, size);
	if ( node == NULL )
	{
		return -1;
	}

	if ( dlist->head == NULL )
	{
		node->next = node;
		node->prev = node;
		dlist->head = node;
		dlist->tail = node;
	}
	else
	{
		node->prev = dlist->tail;
		node->next = dlist->head;
		dlist->head->prev = node;
		dlist->tail->next = node;
		dlist->head = node;
	}
	dlist->size += 1;

	return 0;
}

int search_dlist(struct dlist *dlist, void *data, size_t size)
{
	if ( dlist == NULL || data == NULL )
	{
		return -1;
	}

	dlist->curr = dlist->head;
	
	do{
		if ( memcmp(dlist->curr->data, data, size) == 0 )
		{
			return 0;
		}
		dlist->curr = dlist->curr->next;

	}while( dlist->curr != dlist->head );
}

int delete_dlist(struct dlist *dlist, void *data, size_t size)
{
	if ( dlist == NULL || data == NULL )
	{
		return -1;
	}

	if ( search_dlist(dlist, data, size) == -1 )
	{
		return -1;
	}

	dlist->curr->prev->next = dlist->curr->next;
	dlist->curr->next->prev = dlist->curr->prev;

	if ( dlist->curr == dlist->head )
		dlist->head = dlist->curr->next;

	if ( dlist->curr == dlist->tail )
		dlist->tail = dlist->curr->next;

	free_node(dlist->curr);
	dlist->curr = NULL;
	dlist->size -= 1;

	return 0;
}

int delete_tail(struct dlist *dlist)
{
	if ( dlist == NULL || dlist->tail == NULL )
	{
		return -1;
	}
	if ( dlist->tail == dlist->head )
	{
		free_node(dlist->head);
		dlist->tail = NULL;
		dlist->head = NULL;
		dlist->size = 0;
	}
	else
	{
		dlist->curr = dlist->tail;

		dlist->tail->prev->next = dlist->tail->next;
		dlist->tail->next->prev = dlist->tail->prev;
		dlist->tail = dlist->tail->prev;
		free_node(dlist->curr);
		dlist->size -= 1;
	}
	return 0;
}

int delete_head(struct dlist *dlist)
{
	if ( dlist == NULL || dlist->tail == NULL )
	{
		return -1;
	}
	if ( dlist->tail == dlist->head )
	{
		free_node(dlist->head);
		dlist->head = NULL;
		dlist->tail = NULL;
		dlist->size = 0;
	}
	else
	{
		dlist->curr = dlist->head;

		dlist->head->prev->next = dlist->head->next;
		dlist->head->next->prev = dlist->head->prev;
		dlist->head = dlist->head->next;
		free_node(dlist->curr);
		dlist->size -= 1;
	}
}

void destroy_dlist(struct dlist *dlist)
{
	if ( dlist )
	{
		while( dlist->size )
		{
			delete_tail(dlist);
		}
	}
}

static DNode *init_node(void *data, size_t size)
{
	DNode *node = (DNode*)malloc(sizeof(DNode));
	if ( node == NULL )
	{
		return NULL;
	}
	node->data = malloc(size);
	if ( node->data == NULL )
	{
		return NULL;
	}

	memcpy(node->data, data, size);
	node->prev = NULL;
	node->next = NULL;

	return node;
}

static void free_node(DNode* node)
{
	if ( node )
	{
		if ( node->data )
			free(node->data);

		free(node);
	}

	return ;
}
