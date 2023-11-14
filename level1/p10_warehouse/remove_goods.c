#include "warehouse.h"

extern Goods goods[MAX_GOODS_NUM];
extern int goods_num;

// 3.出库
void remove_goods()
{
	//判断是否有存货
	if (goods_num == 0) {
		printf("当前没有存货！\n");
		return;
	}
	//询问用户需要全部出库还是部分出库
	printf("是否全部出库？(y/n)");
	char ch;
	scanf(" %c", &ch);

	//如果是全部出库，则直接出库
	if (ch == 'y') {
		goods_num = 0;
		printf("出库成功！\n");
		return;
	}
	if (ch != 'n') {
		printf("输入错误！\n");
		//清空输入缓冲区
		while (getchar() != '\n');
		//重新输入
		remove_goods();
	}
	//如果是部分出库，则询问用户出库型号和数量
	if(ch == 'n') {
		printf("请输入货物型号：");
		char name[20];
		int num;
		int i;
		printf("请输入货物型号：");
		scanf("%s", name);
		printf("请输入货物数量：");
		scanf("%d", &num);

		//如果出库数量大于库存数量，则提示库存不足
		//如果出库数量小于等于库存数量，则出库成功
		for (i = 0; i < goods_num; i++) {
			if (strcmp(goods[i].name, name) == 0) {
				goods[i].num -= num;
				if (goods[i].num < 0) {
					printf("库存不足！\n");
					goods[i].num += num;
					return;
				}
				printf("出库成功！\n");
				return;
			}
		}
		printf("没有找到该型号的货物！\n");
		return;
	}
}