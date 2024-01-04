
#include "warehouse.h"

extern Goods goods[MAX_GOODS_NUM];
extern int goods_num;

// 4.保存存货列表
void save_goods_list()
{
	FILE* fp;
	int i;
	//打开文件的路径是相对于可执行文件的路径
	fp = fopen("goods_list.txt", "w");
	if (fp == NULL)
	{
		printf("文件打开失败！\n");
		exit(1);
	}
	for (i = 0; i < goods_num; i++)
	{
		fprintf(fp, "%s %d\n", goods[i].name, goods[i].num);
	}
	fclose(fp);
}