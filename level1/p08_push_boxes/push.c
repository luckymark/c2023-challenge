
#include "head_push_box.h"

int extern map[10][10];
int extern now_x, now_y;
extern int level;
extern int min_step[5];
extern int now_step;

int FindMe()
{
	int i, j;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			//找到自己的位置并记录所在坐标
			if (3 == map[i][j] || 6 == map[i][j])
			{
				now_x = i;
				now_y = j;
			}
		}
	}
}

int Push()
{
	TODO: //待实现撤回上一次移动功能
	//如何让人物移动一格后再撤回到原来位置？
	//如何记录每一步的移动？
	//如何实现撤回？
	//如何实现撤回后再移动？
	//如何实现撤回后再撤回？
	//如何实现撤回后再移动后再撤回？
	//如何实现撤回后再移动后再撤回后再移动？
	now_step = 0;
	int flag = 0;
	while (1)
	{
		FindMe();
		switch (getch())
		{
		case 'w':
			flag = Up();
			break;
		case 's':
			flag = Down();
			break;
		case 'a':
			flag = Left();
			break;
		case 'd':
			flag = Right();
			break;
		case 'r':
			return 3;//重新开始当前关卡
		case 'n':
			return 4;//跳过当前关卡
		case 'm':
			return 5;//返回主菜单
		case 'x':
			return 6;//退出游戏
		case 'z':
			return 7;//返回上一个关卡
		case 27:
			return -1;
		default:
			flag = 0;
		}
		//返回值为1则移动成功记录并继续
		if (1 == flag)
		{
			now_step++;
			Print();
		}
			//返回为2则完成当前关卡
		else if (2 == flag)
		{
			now_step++;
			//记录最小步数
			min_step[level - 1] = now_step < min_step[level - 1] ? now_step : min_step[level - 1];
			Print();
			printf("挑战成功！\n");
			int result = MessageBoxW(NULL, L"恭喜通过本关！是否进行下一关卡", L"恭喜！", MB_YESNO);
			if (6 == result)
			{
				level++;
				return 2;
			}
			else if (7 == result)
			{
				system("pause");
				return 1;
			}
			else
			{
				printf("error");
			}
		}
		else
		{
			Print();
		}
	}
}

