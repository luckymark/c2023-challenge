#include <stdio.h>
#include <windows.h>
#include "head_push_box.h"


char str[(15) * (15)] = {'\0'};//输出地图用的数组
int now_x,now_y;//储存当前所在位置
int goal1_x,goal1_y,goal2_x,goal2_y,goal3_x,goal3_y,goal4_x,goal4_y,goal5_x,goal5_y;//储存目标点位置
int level = 0;//游戏等级
int step[5] = {0},now_step = 0;//记录步数即得分

//-1-空地，0-墙，1-路，2-箱子，3-人，4-目标，5-达成目标
int map[10][10] = {{1,1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1,1}};
int main() {
    int flag = 0;
    system("chcp 65001");
    Menu();
    while (1)
    {
        //等级5完成就通关
        if(6 == level)
        {
            MessageBoxW(NULL, L"恭喜您已经通关所有关卡", L"恭喜！", MB_OK);
            Note();
            return 0;
        }
        Map();
        Print();
        while (1){
            flag = Push();
            //1->成功一个关卡且不再进行  -1 ->本次运行结束
            if(1 == flag || -1 == flag){
                Note();
                return 0;
            }
            //2->成功一个关卡且继续进行  3->重玩关卡
            else if(2 == flag || 3 == flag)
            {
                break;
            }
        }
    }
}