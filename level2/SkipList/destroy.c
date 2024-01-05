#include"标头.h"
#include<stdio.h>
int skip_list_destroy(struct skip_list* list)
{
	struct skip_list_node* cur = NULL;

	if (list == NULL && list->head == NULL)
		return -1;

	while ((cur = list->head->next[0]) != NULL)
	{
		list->head->next[0] = cur->next[0];
		SKIP_LIST_FREE(cur);
		cur = NULL;
	}

	SKIP_LIST_FREE(list->head);
	SKIP_LIST_FREE(list);

	return 0;
}
