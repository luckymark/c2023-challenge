#include"标头.h"
#include"create.cpp"
#include<stdio.h>
#include<stdlib.h>
/*以50%的概率产生插入元素的索引层数*/
static int skip_list_level(struct skip_list* list) {
	int i = 0, level = 1;
	for (i = 1; i < list->head->max_level; i++) 
	{
		if ((rand() % 2) == 1) 
		{
			level++;
		}
	}
	return level;
}

/*插入跳表节点*/
int skip_list_insert(struct skip_list* list, int key, int value) {
	struct skip_list_node** update = NULL; /*用来更新每层索引指针，存放插入位置的前驱各层节点索引*/
	struct skip_list_node* cur = NULL;
	struct skip_list_node* prev = NULL;
	struct skip_list_node* insert = NULL;
	int i = 0, level = 0;
	if (list == NULL)return -1;

	/*申请update空间用于保存每层的索引指针*/
	update = (struct skip_list_node**)SKIP_LIST_MALLOC(sizeof(list->head->max_level));
	if (update == NULL)return -2;

	/*逐层查询，查找插入位置的前驱各层节点索引
	 *update[0] 存放第一层的插入位置前驱节点，update[0]->next[0]表示插入位置的前驱节点的下一节点(update[0]->next[0])的第一层索引值
	 *update[1] 存放第二层的插入位置前驱节点，update[1]->next[1]表示插入位置的前驱节点的下一节点(update[1]->next[0])的第二层索引值
	 *update[n] 存放第一层的插入位置前驱节点，update[n]->next[n]表示插入位置的前驱节点的下一节点(update[n]->next[0])的第n层索引值
     */
	prev = list->head;/*从第一个节点开始的最上层开始找*/
	for (i = list->level - 1; i >= 0; i--) {
		while (((cur = prev->next[i]) != NULL) && (cur->key < key)) {
			prev = cur;/*向后移动*/
		}
		update[i] = prev;/*各层要插入的前驱节点*/
	}
	/*当前key已存在，返回错误*/
	if ((cur != NULL) && (cur->key == key))return -3;

	/*获取插入元素的随机层数，并更新跳表的最大层数*/
	level = skip_list_level(list);
	/*创建当前节点*/
	insert = skip_list_node_creat(level, key, value);
	if (level > list->level) {
		for (i = list->level; i < level; i++) {
			update[i] = list->head;
		}
		list->level = level;
	}

	for (i = 0; i < level; i++) {
		insert->next[i] = update[i]->next[i];
		update[i]->next[i] = insert;
	}
	list->num++;
}
