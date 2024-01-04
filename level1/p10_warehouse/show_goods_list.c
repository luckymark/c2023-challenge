#include "warehouse.h"

extern Goods goods[MAX_GOODS_NUM];
extern int goods_num;

// 1.显示存货列表
void show_goods_list()
{
	system("cls");
	if (goods_num == 0)
	{
		printf("当前没有存货！\n");
		return;
	}
	int i;
	printf("当前存货列表：\n");
	printf("型号\t数量\n");
	for (i = 0; i < goods_num; i++)
	{
		printf("%s\t%d\n", goods[i].name, goods[i].num);
	}
	system("pause");
}