#include <stdio.h>
#include <string.h>
#include "head_push_box.h"

extern int level;
extern int map[10][10];
int extern goal1_x,goal1_y,goal2_x,goal2_y,goal3_x,goal3_y,goal4_x,goal4_y,goal5_x,goal5_y;
void Map(){
    int maps[5][10][10];
    //打开5个文件并读取地图
    FILE *maps1 = fopen("C:\\Users\\81201\\CLionProjects\\c2023-challenge\\level1\\p08_push_boxes\\map\\map1.txt","r");
    if(maps1 == NULL)
    {
        perror("open failed:");
        return;
    }
    FILE *maps2 = fopen("C:\\Users\\81201\\CLionProjects\\c2023-challenge\\level1\\p08_push_boxes\\map\\map2.txt","r");
    if(maps1 == NULL)
    {
        perror("open failed:");
        return;
    }
    FILE *maps3 = fopen("C:\\Users\\81201\\CLionProjects\\c2023-challenge\\level1\\p08_push_boxes\\map\\map3.txt","r");
    if(maps1 == NULL)
    {
        perror("open failed:");
        return;
    }
    FILE *maps4 = fopen("C:\\Users\\81201\\CLionProjects\\c2023-challenge\\level1\\p08_push_boxes\\map\\map4.txt","r");
    if(maps1 == NULL)
    {
        perror("open failed:");
        return;
    }
    FILE *maps5 = fopen("C:\\Users\\81201\\CLionProjects\\c2023-challenge\\level1\\p08_push_boxes\\map\\map5.txt","r");
    if(maps1 == NULL)
    {
        perror("open failed:");
        return;
    }

    for(int i = 0;i < 10;i++)
    {
        fscanf(maps1,"%d %d %d %d %d %d %d %d %d %d",&maps[0][i][0],&maps[0][i][1],&maps[0][i][2],&maps[0][i][3],&maps[0][i][4],&maps[0][i][5],&maps[0][i][6],&maps[0][i][7],&maps[0][i][8],&maps[0][i][9]);
        fscanf(maps2,"%d %d %d %d %d %d %d %d %d %d",&maps[1][i][0],&maps[1][i][1],&maps[1][i][2],&maps[1][i][3],&maps[1][i][4],&maps[1][i][5],&maps[1][i][6],&maps[1][i][7],&maps[1][i][8],&maps[1][i][9]);
        fscanf(maps3,"%d %d %d %d %d %d %d %d %d %d",&maps[2][i][0],&maps[2][i][1],&maps[2][i][2],&maps[2][i][3],&maps[2][i][4],&maps[2][i][5],&maps[2][i][6],&maps[2][i][7],&maps[2][i][8],&maps[2][i][9]);
        fscanf(maps4,"%d %d %d %d %d %d %d %d %d %d",&maps[3][i][0],&maps[3][i][1],&maps[3][i][2],&maps[3][i][3],&maps[3][i][4],&maps[3][i][5],&maps[3][i][6],&maps[3][i][7],&maps[3][i][8],&maps[3][i][9]);
        fscanf(maps5,"%d %d %d %d %d %d %d %d %d %d",&maps[4][i][0],&maps[4][i][1],&maps[4][i][2],&maps[4][i][3],&maps[4][i][4],&maps[4][i][5],&maps[4][i][6],&maps[4][i][7],&maps[4][i][8],&maps[4][i][9]);
    }
    fclose(maps1);
    fclose(maps2);
    fclose(maps3);
    fclose(maps4);
    fclose(maps5);

    //记录各个关卡目标点位置
    for(int i = 0;i < 10;i++)
    {
        for(int j = 0;j < 10;j++)
        {
            if(1 == level)
            {
                map[i][j] = maps[0][i][j];
                goal1_x = 2;
                goal1_y = 4;
                goal2_x = 4;
                goal2_y = 7;
                goal3_x = 5;
                goal3_y = 2;
                goal4_x = 7;
                goal4_y = 5;
            }
            else if(2 == level)
            {
                map[i][j] = maps[1][i][j];
                goal1_x = 4;
                goal1_y = 7;
                goal2_x = 5;
                goal2_y = 7;
                goal3_x = 6;
                goal3_y = 7;
            }
            else if(3 == level)
            {
                map[i][j] = maps[2][i][j];
                goal1_x = 4;
                goal1_y = 2;
                goal2_x = 4;
                goal2_y = 3;
                goal3_x = 5;
                goal3_y = 2;
                goal4_x = 5;
                goal4_y = 3;
            }
            else if(4 == level)
            {
                map[i][j] = maps[3][i][j];
                goal1_x = 5;
                goal1_y = 1;
                goal2_x = 6;
                goal2_y = 1;
                goal3_x = 6;
                goal3_y = 2;
                goal4_x = 6;
                goal4_y = 3;
                goal5_x = 6;
                goal5_y = 4;
            }
            else if(5 == level)
            {
                map[i][j] = maps[4][i][j];
                goal1_x = 4;
                goal1_y = 1;
                goal2_x = 5;
                goal2_y = 1;
                goal3_x = 6;
                goal3_y = 1;
            }
        }
    }
}