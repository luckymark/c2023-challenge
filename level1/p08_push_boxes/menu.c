#include "head_push_box.h"
extern int level;
void Menu()
{
	printf("使用wsad控制上下左右，esc退出，墙■,箱子✪,人⊙,目标☆,达成目标◇\n");
	printf("请输入关卡数(1~5)\n");

	while (1)
	{
		scanf_s("%d", &level);
		if (1 == level || 2 == level || 3 == level || 4 == level || 5 == level)
		{
			Map(level);
			break;
		}
		else
		{
			//清空缓冲区
			while (getchar() != '\n');
			printf("请输入正确的关卡数(1~5)\n");
		}
	}
}
