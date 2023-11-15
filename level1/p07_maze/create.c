#include "head_maze.h"

extern int map[101][101];
extern int large;

//创建迷宫
void Create_01(int x, int y)
{
	//记录上一次的位置
	int old_x = x, old_y = y;
	//记录随机的方向
	int rand_direction = 0;
	while (1)
	{
		// 判断是否有邻居
		if (HaveNeighbor(x, y))
		{
			while (1)
			{
				old_x = x;
				old_y = y;
				map[x][y] = 5;
				rand_direction = rand() % 4;
				if (0 == rand_direction && map[x - 2][y] == 1 && x >= 3)
				{
					x -= 2;
				}
				else if (1 == rand_direction && map[x + 2][y] == 1 && x < large - 3)
				{
					x += 2;
				}
				else if (2 == rand_direction && map[x][y - 2] == 1 && y >= 3)
				{
					y -= 2;
				}
				else if (3 == rand_direction && map[x][y + 2] == 1 && y < large - 3)
				{
					y += 2;
				}
				map[(x + old_x) / 2][(y + old_y) / 2] = 5;
				map[x][y] = 5;
				Create_01(x, y);
				break;
			}
		}
		else
			return;
	}
}