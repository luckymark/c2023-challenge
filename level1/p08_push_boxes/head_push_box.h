#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>

//用结构体存五个关卡的终点坐标
typedef struct {
	int x;
	int y;
}Goal;
//用结构体存五个关卡的箱子坐标
typedef struct {
	int x;
	int y;
}Box;
//用结构体存五个关卡的人的坐标
typedef struct {
	int x;
	int y;
}Player;



void Map(int level);//读取文件中地图
void Print();//打印更改后的地图
void Menu();//菜单
int Push();//推动箱子或者移动
int Up();
int Down();
int Left();
int Right();
bool Finish();//判断是否结束
void Note();//记录得分
void Read();//读取文件中得分
