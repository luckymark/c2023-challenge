#include "warehouse.h"

extern Goods goods[MAX_GOODS_NUM];
extern int goods_num;

// 5.加载存货列表
void load_goods_list()
{
	FILE* fp;
	int i;
	fp = fopen("goods_list.txt", "r");
	if (fp == NULL)
	{
		printf("文件打开失败！\n");
		exit(1);
	}
	for (i = 0; i < MAX_GOODS_NUM; i++)
	{
		if (fscanf(fp, "%s %d", goods[i].name, &goods[i].num) == EOF)
		{
			break;
		}
	}
	goods_num = i;
	fclose(fp);
}
