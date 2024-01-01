#include<stdlib.h>
#define SKIP_LIST_MALLOC(size) malloc(size);
#define SKIP_LIST_CALLOC(n,size) calloc(n,size);
#define SKIP_LIST_FREE(p) free(p);

struct skip_list_node
{
	int key;//
	int value;//存储的内容
	int max_level;//当前节点最大层数
	struct skip_list_node* next[];//柔性数组
	//根据该节点层数的不同指向大小不同的数组
};
struct skip_list {
	int level;//跳表的索引层数
	int num;//节点数目
	struct skip_list_node* head;
};
extern struct  skip_list* skip_list_creat(int max_level);
extern int skip_list_insert(struct skip_list* list, int key, int value);
extern int skip_list_delete(struct skip_list* list, int key);
extern int skip_list_modify(struct skip_list* list, int key, int value);
extern int skip_list_search(struct skip_list* list, int key, int* value);
extern int skip_list_destroy(struct skip_list* list);
