
#include <stdbool.h>
#include "head_push_box.h"
extern int level;
extern int map[10][10];
extern Goal goal[5];
extern int goal_num[5];

//目标点全完成则关卡成功
bool Finish()
{
	int i;
	for(i = 0;i < goal_num[level - 1];i++)
	{
		if(5 == map[goal[i].x][goal[i].y])
		{
		}
		else
		{
			return false;
		}
	}
	return true;
}