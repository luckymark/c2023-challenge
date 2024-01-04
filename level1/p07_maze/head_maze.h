#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

void Menu();//菜单
void Initialize(int num);//初始化地图
void Create_01(int x,int y);//开始创建地图
bool HaveNeighbor(int x,int y);//判断是否有方向可以创建地图
void Print();//打印地图
int Move();//进行移动
int FindMe();//找到自己当前所在位置并赋值为3
int Up();
int Down();
int Left();
int Right();

