
#include "../include/dlist.h"
#include <stdio.h>

struct data{
	int a;
	char b;
	char c[10];
};

void display_head(struct dlist *dlist)
{
	struct data *data = NULL;
	dlist->curr = dlist->head;
	do {
		data =(struct data*)dlist->curr->data;
		printf("%d, %c %s\n", data->a, data->b, data->c);
		dlist->curr = dlist->curr->next;
	} while(dlist->curr != dlist->head);
}

void display_tail(struct dlist *dlist)
{
	struct data *data = NULL;
	dlist->curr = dlist->tail;
	do {
		data =(struct data*)dlist->curr->data;
		printf("%d, %c %s\n", data->a, data->b, data->c);
		dlist->curr = dlist->curr->prev;
	} while(dlist->curr != dlist->tail);
}

int main()
{
	int i = 0;
	struct dlist dlist = {}; 

	create_dlist(&dlist);

	struct data data[10] = { 
		{1, 'a', "aaa"},
	   	{2, 'b', "bbb"},
	   	{3, 'c', "ccc"},
	   	{4, 'd', "ddd"},
		{5, 'e', "eee"},
		{6, 'f', "fff"},
		{7, 'g', "ggg"},
		{8, 'h', "hhh"},
		{9, 'i', "iii"},
		{0, 'j', "jjj"}
	};

	for (i = 0; i < 10; i++)
	{
		//insert_head(&dlist, (void*)(&data[i]), sizeof(struct data));
		insert_tail(&dlist, (void*)(&data[i]), sizeof(struct data));
	}

	struct data temp = { 7, 'g', "ggg" };

	delete_dlist(&dlist, &temp, sizeof(temp));
	delete_tail(&dlist);
	delete_head(&dlist);

	display_head(&dlist);
	printf("\n\n");
	display_tail(&dlist);
	destroy_dlist(&dlist);
}
