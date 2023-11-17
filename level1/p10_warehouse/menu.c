#include <windows.h>
#include "warehouse.h"

extern Goods goods[MAX_GOODS_NUM];
extern int goods_num;

//菜单
int menu()
{
	int choice;
	system("cls");
	printf("欢迎使用仓库管理系统！\n");
	while (1)
	{
		printf("请选择你要进行的操作：\n");
		printf("1.显示存货列表\n");
		printf("2.入库\n");
		printf("3.出库\n");
		printf("4.退出程序\n");
		printf("请输入你的选择：");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			show_goods_list();
			break;
		case 2:
			add_goods();
			break;
		case 3:
			remove_goods();
			break;
		case 4:
			save_goods_list();
			//弹出窗口确认是否退出
			int result = MessageBoxW(NULL, L"是否退出程序？", L"提示", MB_YESNO | MB_ICONQUESTION);
			if (result == IDYES)
			{
				exit(0);
			}
			break;
		default:
			printf("输入错误，请重新输入！\n");
		}
	}
}