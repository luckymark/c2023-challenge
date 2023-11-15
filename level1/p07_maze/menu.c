#include "head_maze.h"

extern int large;
extern int level;

void Menu()
{
	printf("使用wsad控制上下左右，esc退出，☆为终点⊙为玩家所在地\n");
	printf("请输入难度（1~2）\n");

	while (1)
	{
		scanf("%d", &level);
		if (level == 1)
		{
			break;
		}
		else if (level == 2)
		{
			printf("暂未开放，敬请期待\n");
			printf("请重新输入难度（1~2）\n");
		}
		else
		{
			//清空缓冲区
			while (getchar() != '\n')
				;
			printf("输入错误，请重新输入难度（1~2）\n");
		}
	}
	printf("请输入地图大小（3~100)（请输入奇数，输入偶数会自动+1）\n");
	while (1)
	{
		scanf("%d", &large);
		if (large >= 3 && large <= 100)
		{
			printf("正在生成地图，请稍后\n");
			Initialize(large);
			break;
		}
		else
		{
			//清空缓冲区
			while (getchar() != '\n')
				;
			printf("输入错误，请重新输入地图大小（3~100)（请输入奇数，输入偶数会自动+1）\n");
		}
	}
}
