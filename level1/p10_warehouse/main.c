
#include"warehouse.h"

// 货物列表
Goods goods[MAX_GOODS_NUM];
int goods_num = 0;

int main()
{
	system("chcp 65001");
	load_goods_list();
	menu();
	return 0;
}


