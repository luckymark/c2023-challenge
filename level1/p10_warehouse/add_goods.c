#include <stdbool.h>
#include "warehouse.h"

extern Goods goods[MAX_GOODS_NUM];
extern int goods_num;
//判断是否是有效的货物型号
_Bool is_valid_name(char *name)
{
	int i;
	for (i = 0; i < strlen(name); i++)
	{
		if (name[i] == ' ')
		{
			return false;
		}
	}
	return true;
}
//判断是否已经存在该型号的货物
bool is_exist(char *name)
{
	int i;
	for (i = 0; i < goods_num; i++)
	{
		if (strcmp(goods[i].name, name) == 0)
		{
			return true;
		}
	}
	return false;
}
// 2.入库
void add_goods()
{
	char name[20];
	int num;
	printf("请输入货物型号：");

	while (1){
		//清空缓冲区
		while (!getchar());
		scanf("%[^\n]", name);
		if (is_valid_name(name))
		{
			break;
		}
		printf("货物型号不能包含空格！\n");
		printf("请重新输入货物型号：");
	}

	printf("请输入货物数量：");
	scanf("%d", &num);
	//判断是否已经存在该型号的货物
	if(is_exist(name))
	{
		for (int i = 0; i < goods_num; i++)
		{
			if (strcmp(goods[i].name, name) == 0)
			{
				goods[i].num += num;
				system("cls");
				printf("入库成功！\n");
			}
		}
	}
	else
	{
		//如果不存在，则判断是否已经达到存货上限，如果没有，则入库成功，否则提示存货已满
		if (goods_num < MAX_GOODS_NUM)
		{
			strcpy(goods[goods_num].name, name);
			goods[goods_num].num = num;
			goods_num++;
			system("cls");
			printf("入库成功！\n");
		}
		else
		{
			system("cls");
			printf("存货已满！请重新选择您的操作\n");
			return;
		}
	}
	while (1){
		printf("是否继续入库？(y/n)\n");
		//清空缓冲区
		while (!getchar());
		switch (getchar())
		{
		case 'y':
			add_goods();
			break;
		case 'n':
			return;
		default:
			printf("输入错误！\n");
		}
	}
}