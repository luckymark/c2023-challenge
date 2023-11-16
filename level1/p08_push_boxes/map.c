
#include "head_push_box.h"

extern int map[10][10];
extern Goal goal[5];
//根据关卡数读取地图
void Map(int level)
{
	if (level == 1)
	{
		FILE* maps1 =
			fopen("C:\\Users\\81201\\CLionProjects\\c2023-challenge\\level1\\p08_push_boxes\\map\\map1.txt", "r");
		if (maps1 == NULL)
		{
			perror("open failed:");
			return;
		}
		for (int i = 0; i < 10; i++)
		{
			fscanf(maps1,
				"%d %d %d %d %d %d %d %d %d %d",
				&map[i][0],
				&map[i][1],
				&map[i][2],
				&map[i][3],
				&map[i][4],
				&map[i][5],
				&map[i][6],
				&map[i][7],
				&map[i][8],
				&map[i][9]);
		}
		fclose(maps1);
		goal[0].x = 2;
		goal[0].y = 4;
		goal[1].x = 4;
		goal[1].y = 7;
		goal[2].x = 5;
		goal[2].y = 2;
		goal[3].x = 7;
		goal[3].y = 5;
	}
	else if (level == 2)
	{
		FILE* maps2 =
			fopen("C:\\Users\\81201\\CLionProjects\\c2023-challenge\\level1\\p08_push_boxes\\map\\map2.txt", "r");
		if (maps2 == NULL)
		{
			perror("open failed:");
			return;
		}
		for (int i = 0; i < 10; i++)
		{
			fscanf(maps2,
				"%d %d %d %d %d %d %d %d %d %d",
				&map[i][0],
				&map[i][1],
				&map[i][2],
				&map[i][3],
				&map[i][4],
				&map[i][5],
				&map[i][6],
				&map[i][7],
				&map[i][8],
				&map[i][9]);
		}
		fclose(maps2);
		goal[0].x = 4;
		goal[0].y = 7;
		goal[1].x = 5;
		goal[1].y = 7;
		goal[2].x = 6;
		goal[2].y = 7;
	}
	else if (level == 3)
	{
		FILE* maps3 =
			fopen("C:\\Users\\81201\\CLionProjects\\c2023-challenge\\level1\\p08_push_boxes\\map\\map3.txt", "r");
		if (maps3 == NULL)
		{
			perror("open failed:");
			return;
		}
		for (int i = 0; i < 10; i++)
		{
			fscanf(maps3,
				"%d %d %d %d %d %d %d %d %d %d",
				&map[i][0],
				&map[i][1],
				&map[i][2],
				&map[i][3],
				&map[i][4],
				&map[i][5],
				&map[i][6],
				&map[i][7],
				&map[i][8],
				&map[i][9]);
		}
		fclose(maps3);
		goal[0].x = 4;
		goal[0].y = 2;
		goal[1].x = 4;
		goal[1].y = 3;
		goal[2].x = 5;
		goal[2].y = 2;
		goal[3].x = 5;
		goal[3].y = 3;
	}
	else if (level == 4)
	{
		FILE* maps4 =
			fopen("C:\\Users\\81201\\CLionProjects\\c2023-challenge\\level1\\p08_push_boxes\\map\\map4.txt", "r");
		if (maps4 == NULL)
		{
			perror("open failed:");
			return;
		}
		for (int i = 0; i < 10; i++)
		{
			fscanf(maps4,
				"%d %d %d %d %d %d %d %d %d %d",
				&map[i][0],
				&map[i][1],
				&map[i][2],
				&map[i][3],
				&map[i][4],
				&map[i][5],
				&map[i][6],
				&map[i][7],
				&map[i][8],
				&map[i][9]);
		}
		fclose(maps4);
		goal[0].x = 5;
		goal[0].y = 1;
		goal[1].x = 6;
		goal[1].y = 1;
		goal[2].x = 6;
		goal[2].y = 2;
		goal[3].x = 6;
		goal[3].y = 3;
		goal[4].x = 6;
		goal[4].y = 4;
	}
	else if (level == 5)
	{
		FILE* maps5 =
			fopen("C:\\Users\\81201\\CLionProjects\\c2023-challenge\\level1\\p08_push_boxes\\map\\map5.txt", "r");
		if (maps5 == NULL)
		{
			perror("open failed:");
			return;
		}
		for (int i = 0; i < 10; i++)
		{
			fscanf(maps5,
				"%d %d %d %d %d %d %d %d %d %d",
				&map[i][0],
				&map[i][1],
				&map[i][2],
				&map[i][3],
				&map[i][4],
				&map[i][5],
				&map[i][6],
				&map[i][7],
				&map[i][8],
				&map[i][9]);
		}
		fclose(maps5);
		goal[0].x = 4;
		goal[0].y = 1;
		goal[1].x = 5;
		goal[1].y = 1;
		goal[2].x = 6;
		goal[2].y = 1;
	}
}