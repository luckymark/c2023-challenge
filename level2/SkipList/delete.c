#include"标头.h"
#include<stdio.h>
int skip_list_delete(struct skip_list* list, int key)
{
	struct skip_list_node** update = NULL; /*用来更新每层索引指针，存放插入位置的前驱各层节点索引*/
	struct skip_list_node* cur = NULL;
	struct skip_list_node* prev = NULL;
	int i = 0;

	if (list == NULL && list->num == 0)
		return -1;

	/*申请update空间用于保存每层的节点索引指针*/
	update = (struct skip_list_node**)SKIP_LIST_MALLOC(sizeof(list->level * sizeof(struct skip_list_node*)));
	if (update == NULL)
		return -2;

	/*逐层查询,查找删除位置的前驱各层节点索引
	 *update[0] 存放第一层的删除位置前驱节点，update[0]->next[0]表示删除位置的前驱节点的下一节点(update[0]->next[0])的第一层索引值
	 *update[1] 存放第二层的删除位置前驱节点，update[1]->next[1]表示删除位置的前驱节点的下一节点(update[1]->next[0])的第二层索引值
	 *update[n] 存放第一层的删除位置前驱节点，update[n]->next[n]表示删除位置的前驱节点的下一节点(update[n]->next[0])的第n层索引值
	 */
	prev = list->head; /*从第一个节点开始的最上层开始找*/
	i = list->level - 1;
	for (; i >= 0; i--)
	{
		/* 各层每个节点的下一个节点不为空 && 下个节点的key小于要插入的key */
		while (((cur = prev->next[i]) != NULL) && (cur->key < key))
		{
			prev = cur; /* 向后移动 */
		}
		update[i] = prev; /* 各层要删除节点的前驱节点 */
	}

	/* 当前key存在 */
	if ((cur != NULL) && (cur->key == key))
	{
		/*逐层删除*/
		for (i = 0; i < list->level; i++)
		{
			if (update[i]->next[i] == cur)
			{
				update[i]->next[i] = cur->next[i];
			}
		}

		SKIP_LIST_FREE(cur);
		cur = NULL;

		/*更新索引的层数*/
		for (i = list->level - 1; i >= 0; i--)
		{
			/*如果删除节点后,某层的头结点后驱节点为空,则说明该层无索引指针,索引层数需要减1*/
			if (list->head->next[i] == NULL)
			{
				list->level--;
			}
			else
			{
				break;
			}
		}

		list->num--; /*节点数减1*/
	}
	else
	{
		return -3;
	}

	return 0;
}

	
