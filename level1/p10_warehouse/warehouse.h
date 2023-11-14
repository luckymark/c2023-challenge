
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 最大货物数量
#define MAX_GOODS_NUM 100

// 货物结构体
typedef struct {
	char name[20];
	int num;
} Goods;


// 菜单
int menu();
// 1.显示存货列表
void show_goods_list();
// 2.入库
void add_goods();
// 3.出库
void remove_goods();
// 4.保存存货列表
void save_goods_list();
// 5.加载存货列表
void load_goods_list();