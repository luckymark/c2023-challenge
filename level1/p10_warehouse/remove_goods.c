#include "warehouse.h"

extern Goods goods[MAX_GOODS_NUM];
extern int goods_num;

// 3.出库
void remove_goods()
{
	//判断是否有存货
	if (goods_num == 0)
	{
		printf("当前没有存货！请重新选择\n");
		return;
	}
	while (!getchar());
	//询问用户需要全部出库还是部分出库
	printf("是否全部出库？(y/n)\n");
	//如果是全部出库，则直接出库
	switch (getchar())
	{
	case 'y':
		goods_num = 0;
		printf("出库成功！\n");
		break;
	case 'n':
	{
		char name[20];
		int num;
		printf("请输入货物型号：");
		while (1)
		{
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
		//判断是否存在该型号的货物
		if (is_exist(name))
		{
			for (int i = 0; i < goods_num; i++)
			{
				if (strcmp(goods[i].name, name) == 0)
				{
					//判断出库数量是否大于库存数量
					if (num > goods[i].num)
					{
						printf("出库数量大于库存数量！\n");
						return;
					}
					goods[i].num -= num;
					printf("出库成功！\n");
					return;
				}
			}
		}
		else
		{
			system("cls");
			printf("不存在该型号的货物！\n");
			return;
		}
	}
	break;
	default:
		printf("输入错误！请重新输入\n");
		return;
	}
}