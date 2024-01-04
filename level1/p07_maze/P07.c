#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#define WIDTH 13
#define LENGTH 42

char map[WIDTH][LENGTH] = {
        "+---+---+---+---+---+---+---+---+---+---+",
        "|           |               |           |",
        "+   +---+   +---+   +---+   +---+   +   +",
        "|   |       |       |           |   |   |",
        "+   +   +   +---+   +---+   +   +   +   +",
        "|       |               |   |   |   |   |",
        "+---+   +---+   +   +---+   +   +   +   +",
        "|       |       |   |       |   |   |   |",
        "+   +---+   +   +   +   +---+   +   +   +",
        "|   |       |   |   |   |               |",
        "+   +   +---+   +   +   +---+   +---+   +",
        "        |       |   |   |       |       |",
        "+---+---+---+---+---+---+---+---+---+   +"
};

void printMap();
void initializeCharacter();
void moveCharacter(short up, short down, short left, short right);
COORD* getCursorPos();
void hideCursor();
bool isExit();
bool judgeMapIsWall(COORD* coord);


int main() {
    system("chcp 65001");
    hideCursor();
    //打印迷宫地图
    printMap();

    //生成角色
    initializeCharacter();

    //读取光标并移动角色
    move:
    switch (getch()) {
        case 72://键盘输入的向上箭头ASCII码值为72
            moveCharacter(1, 0, 0, 0);
            break;
        case 80://键盘输入的向下箭头ASCII码值为80
            moveCharacter(0, 1, 0, 0);
            break;
        case 75://键盘输入的向左箭头ASCII码值为75
            moveCharacter(0, 0, 1, 0);
            break;
        case 77://键盘输入的向右箭头ASCII码值为77
            moveCharacter(0, 0, 0, 1);
            break;
    }

    //判断玩家是否到达出口，如果成功到达，则打印恭喜信息；如果未到达，则通过goto语句回到switch继续操作
    if (isExit()) {
        system("cls");
        printf("%s", "恭喜！！你已通过该迷宫！！！");
        system("pause");
    }
    else {
        goto move;
    }
}


void printMap() {//双层循环打印地图
    for (int i = 0; i < WIDTH; ++ i) {
        for (int j = 0; j < LENGTH; ++j) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

COORD* getCursorPos(){
    COORD* coord=(COORD*)malloc(sizeof(COORD));
    CONSOLE_SCREEN_BUFFER_INFO cursor_info;
    HANDLE hOutput= GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOutput == INVALID_HANDLE_VALUE || !GetConsoleScreenBufferInfo(hOutput, &cursor_info)){
        printf("%s", "获取光标当前位置失败，请重试！");
        exit(-1);
    }
    else {
        (*coord).X=cursor_info.dwCursorPosition.X;
        (*coord).Y=cursor_info.dwCursorPosition.Y;
    }//获取光标当前位置，存储到coord中

    return coord;
}

void initializeCharacter(){
    COORD *position=(COORD*)malloc(sizeof(COORD));
    (*position).X = 0;
    (*position).Y = 12;//定义一个COORD类型的变量，并将其位置定在迷宫入口处

    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//获取控制台的标准输出句柄
    SetConsoleCursorPosition(hOutput, *position);//将光标移动到position指定的位置

    printf("%c", 'O');//将人物形象设置为大写字母O
}

void moveCharacter(short up, short down, short left, short right){
    HANDLE hOutput= GetStdHandle(STD_OUTPUT_HANDLE);
    COORD* coord=getCursorPos();

    printf("\b\x20\b"); //打印空格清除掉原本的角色
    (*coord).X -= 1;
    COORD* temp_coord=(COORD*)malloc(sizeof(COORD));
    (*temp_coord).X=(*coord).X;
    (*temp_coord).Y=(*coord).Y;

    // 根据输入修改coord的值
    (*coord).X += right;
    (*coord).X -= left;
    (*coord).Y -= up;
    (*coord).Y += down;


    if (!judgeMapIsWall(coord)) {//如果移动方向上下一步并非墙壁，允许移动；如果是墙壁，保持人物原地不动
        SetConsoleCursorPosition(hOutput, *coord);//将光标移动到coord指定的位置
    } else{
        SetConsoleCursorPosition(hOutput, *temp_coord);//将光标移动到coord指定的位置

    }
    printf("%c", 'O');//在移动后的指定位置打印人物

}


bool isExit(){
    COORD* coord=getCursorPos();
    if ((*coord).X >= 38 && (*coord).Y == 13) {//如果到达了地图出口的坐标位置，返回true；如果没有，返回false
        return true;
    }
    else
        return false;
}

void hideCursor(){
    CONSOLE_CURSOR_INFO cursor_info;
    HANDLE hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hOutput, &cursor_info);
    cursor_info.bVisible=false;//设置光标为不可见
    SetConsoleCursorInfo(hOutput, &cursor_info);//应用设置
}

bool judgeMapIsWall(COORD* coord){
    char t=map[coord->Y-1][coord->X];
    if (t == ' '){
        return false;
    } else{
        return true;
    }
}

