#include"标头.h"
#include<stdio.h>
#include<string.h>
/*动态申请跳表节点*/
static skip_list_node* skip_list_node_creat(int level, int key, int value) {
	struct skip_list_node* node = NULL;
	/*节点空间大小为节点数据大小+level层索引所占用的大小*/
	node = (skip_list_node*)SKIP_LIST_MALLOC(sizeof(*node) + level * sizeof(node));
	if (node == NULL) {
		printf("fail to malloc node");
		return NULL;
	}

	/*把申请空间初始化为0*/
	memset(node, 0, sizeof(*node) + level * sizeof(node));
	node->key = key;
	node->value = value;
	node->max_level = level;

	return node;
}
/*创建跳表头节点*/
struct skip_list* skip_list_creat(int max_level) {
	struct skip_list* list = NULL;
	list = (skip_list*)SKIP_LIST_MALLOC(sizeof(*list));
	if (list == NULL) {
		printf("fail to malloc list");
		return NULL;
	}
	
	list->level = 1;
	list->num = 0;
	list->head = skip_list_node_creat(max_level, 0, 0);
	if (list->head = NULL) {
		SKIP_LIST_FREE(list);
		printf("fail to malloc list");
		return NULL;
	}
	return list;
}

	 

	 
