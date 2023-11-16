
#include "head_push_box.h"

extern char str[(15) * (15)];
extern int map[10][10];
extern int level;
extern int now_step;
extern int min_step[5];

void ClearConsole()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD home = { 0, 0 };
	DWORD written;
	FillConsoleOutputCharacter(hOut, ' ', 80 * 25, home, &written);
	FillConsoleOutputAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, 80 * 25, home, &written);
	SetConsoleCursorPosition(hOut, home);
}
void Print()
{
	int i = 0, j = 0, min_ = 0;
	//将str初始化为空
	str[0] = '\0';
	ClearConsole();
	//打印地图
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			//-1-空地""，0-墙"■"，1-路" "，2-箱子"✪"，3-人"⊙"，4-目标"☆"，5-达成目标"◇"
			if (map[i][j] == 0)
			{
				strcat(str, "■");
			}
			else if (map[i][j] == 1)
			{
				strcat(str, " ");
			}
			else if (map[i][j] == 2)
			{
				strcat(str, "✪");
			}
			else if (map[i][j] == 3)
			{
				strcat(str, "◇");
			}
			else if (map[i][j] == 4)
			{
				strcat(str, "☆");
			}
			else if (map[i][j] == 5)
			{
				strcat(str, "★");
			}
			else if (map[i][j] == 6)
			{
				strcat(str, "◈");
			}
			else if (map[i][j] == -1)
			{
				strcat(str, " ");
			}
			else
			{
				printf("地图出错\n");
				exit(-10086);
			}
			//每行末尾加上换行符
			if (9 == j)
			{
				strcat(str, "\n");
			}
		}

	}
	printf("按'r'重新开始本关卡\n");
	printf("按'n'跳过本关卡\n");
	printf("按'm'返回主菜单\n");
	printf("按'x'退出游戏\n");
	printf("按'z'返回上一个关卡\n");
	printf("当前步数：%d\n", now_step);
	printf("%s", str);
	//打印最小步数
	if (99999999 != min_step[level - 1])
	{
		printf("本关卡目前最小步数为：%d\n", min_step[level - 1]);
	}
	else
	{
		printf("本关卡暂时没有最佳成绩\n");
	}
}