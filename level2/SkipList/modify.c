#include"标头.h"
#include<stdio.h>
int skip_list_modify(struct skip_list* list, int key, int value)
{
	struct skip_list_node* cur = NULL;
	struct skip_list_node* prev = NULL;
	int i = 0;

	if (list == NULL && list->num == 0)
		return -1;

	/*逐层查找,查找查询位置原始链表的节点*/
	prev = list->head; /*从第一个节点开始的最上层开始找*/
	i = list->level - 1;
	for (; i >= 0; i--)
	{
		/* 各层每个节点的下一个节点不为空 && 下个节点的key小于要插入的key */
		while (((cur = prev->next[i]) != NULL) && (cur->key < key))
		{
			prev = cur; /* 向后移动 */
		}
	}

	/* 当前key存在 */
	if ((cur != NULL) && (cur->key == key))
	{
		cur->value = value;
	}
	else
	{
		return -3;
	}

	return 0;
}
