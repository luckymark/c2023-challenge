
#include "head_maze.h"

//初始化地图
int map[101][101] = { 0 };
//初始化地图大小
int large = 0;
//初始化地图的级别
int level = 0;
//初始化当前所在位置
int now_x;
int now_y;
char str[(102) * (102)] = {'\0'};


int main(){
    system("chcp 65001");
	//设置颜色
    system("color 0A");
    srand((unsigned int)time(NULL));
	//标记是否退出
    int flag = 0;
    Menu();
	//开始走迷宫
    while (1){
        flag = Move();
        if(-1 == flag)
		{
			break;
		}
    }
	return 0;
}








