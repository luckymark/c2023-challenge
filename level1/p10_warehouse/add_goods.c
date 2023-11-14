#include "warehouse.h"

extern Goods goods[MAX_GOODS_NUM];
extern int goods_num;

// 2.入库
void add_goods()
{
	char name[20];
	int num;
	printf("请输入货物型号：");
	scanf("%s", name);
	printf("请输入货物数量：");
	scanf("%d", &num);
	//判断是否已经存在该型号的货物
	int i;
	for (i = 0; i < goods_num; i++) {
		if (strcmp(goods[i].name, name) == 0) {
			goods[i].num += num;
			printf("入库成功！\n");
			return;
		}
	}
	//如果不存在，则添加新的货物
	strcpy(goods[goods_num].name, name);
	goods[goods_num].num = num;
	goods_num++;
	printf("入库成功！\n");
	//如果货物数量超过最大数量，则提示货物数量超过最大数量
	if (goods_num == MAX_GOODS_NUM) {
		printf("货物数量超过最大数量！\n");
	}
	//询问用户是否继续入库
	printf("是否继续入库？(y/n)");
	char ch;
	scanf(" %c", &ch);
	if (ch == 'y') {
		add_goods();
	}
}