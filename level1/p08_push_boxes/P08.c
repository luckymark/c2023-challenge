#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#define WIDTH 10
#define LENGTH 60

char map[WIDTH][LENGTH] = {
        "+------------------------------+",
        "|                              |",
        "|            * |    O          |",
        "|       |                      |",
        "|                 |            |",
        "|    O        *|               |",
        "|         ----     O           |",
        "|      *                       |",
        "|                              |",
        "+------------------------------+"

};

void printMap();
void initializeCharacter();
COORD* moveElement(COORD** element, short up, short down, short left, short right);
void moveCharacter(short up, short down, short left, short right);
void moveBox(COORD* coord, short up, short down, short left, short right);
COORD* getCursorPos();
void hideCursor();
void moveCursor(COORD* coord);
bool isSucceed();
bool judgeMapIsWall(COORD* coord);
bool judgeMapIsBox(COORD* coord);
bool judgeMapIsFinal(COORD* coord);
void clearElement(COORD** coord);
void printElement(COORD* coord, char element);

int main() {
    system("chcp 65001");
    hideCursor();

    //打印迷宫地图
    printMap();
    printf("%s", "P:角色\tO:箱子\t*:终点\t+、-、|:墙壁");

    //生成角色
    initializeCharacter();

    //读取光标并移动角色
    move:
    switch (getch()) {//switch-case语句每一个case后面都要加上break
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
    if (isSucceed()) {
        system("cls");
        printf("%s", "恭喜！！你已通过该游戏！！！");
        system("pause");//在外部控制台中运行的时候需要加上这一条指令避免控制台输出完毕自动关闭
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
    (*position).X = 20;
    (*position).Y = 2;//定义一个COORD类型的变量，并将其位置定在迷宫入口处

    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//获取控制台的标准输出句柄
    SetConsoleCursorPosition(hOutput, *position);//将光标移动到position指定的位置

    printf("%c", 'P');//将人物形象设置为大写字母P
}

COORD* moveElement(COORD** element, short up, short down, short left, short right){
    //清除当前人物
    clearElement(&(*element));

    //定义一个临时coord存储element的原始值
    COORD* temp_coord=(COORD*)malloc(sizeof(COORD));
    (*temp_coord).X=(*(*element)).X;
    (*temp_coord).Y=(*(*element)).Y;


    //根据输入修改element的值
    (*(*element)).X += right;
    (*(*element)).X -= left;
    (*(*element)).Y -= up;
    (*(*element)).Y += down;

    return temp_coord;
}


bool isSucceed(){
    if (map[2][13] == '6' && map[5][14] == '6' && map[7][7] == '6'){//如果检查到三个终点都已经到达，返回true
        return true;
    } else{
        return false;
    }
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
    if (t == '+' || t == '-' || t == '|'){//三个字符是墙壁的构成
        return true;
    } else{
        return false;
    }
}

bool judgeMapIsBox(COORD* coord){
    char t=map[coord->Y-1][coord->X];
    if (t == 'O'){ //’O‘代表箱子
        return true;
    } else{
        return false;
    }
}

bool judgeMapIsFinal(COORD* coord){
    char t=map[coord->Y-1][coord->X];
    if (t == '*' || t == '6'){  //到达前和到达后的终点
        return true;
    } else{
        return false;
    }
}

void moveCharacter(short up, short down, short left, short right){
    COORD* coord=getCursorPos();
    COORD* temp_coord= moveElement(&coord, up, down, left, right);

    if (judgeMapIsWall(coord) || judgeMapIsFinal(coord)){
        printElement(temp_coord, 'P');//如果前方是墙或终点，保持人物不动
    }
    else if (judgeMapIsBox(coord)){
        //定义一个temp2表示箱子当前的位置
        COORD* temp_coord2=(COORD*) malloc(sizeof(COORD));
        temp_coord2->X=coord->X;
        temp_coord2->Y=coord->Y;
        temp_coord2->X ++;

        moveBox(temp_coord2, up, down, left, right);

        //如果移动后箱子还在原地，那么保持人物不动；如果箱子已经移动，那么人物就可以移动。
        if (judgeMapIsBox(coord)){
            printElement(temp_coord, 'P');
        } else{
            printElement(coord, 'P');
        }
    } else {
        printElement(coord, 'P');
    }
}

void moveBox(COORD* coord, short up, short down, short left, short right){
    COORD* temp_coord=moveElement(&coord, up, down, left, right);

    if (judgeMapIsWall(coord)){
        printElement(temp_coord, 'O');//如果前方是墙，保持箱子不动
    }
    else if (judgeMapIsFinal(coord)){
        printElement(coord, '6');//如果前方是终点，将终点变为胜利指示符，并且清除掉地图上原本位置的箱子
        map[temp_coord->Y - 1][temp_coord->X]=' ';
        map[coord->Y - 1][coord->X]='6';
    }
    else{
        printElement(coord, 'O');//如果前方是空位，正常移动，并且清除掉地图上原本位置的箱子
        map[temp_coord->Y - 1][temp_coord->X]=' ';
        map[coord->Y - 1][coord->X]='O';
    }
}

void clearElement(COORD** coord){
    moveCursor(*coord);
    printf("\b\x20\b"); //打印空格清除掉原本的角色
    (*(*coord)).X -= 1;
}

void printElement(COORD* coord, char element){
    moveCursor(coord);
    printf("%c", element);//在移动后的指定位置打印人物
}

void moveCursor(COORD* coord) {
    HANDLE hOutput= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, *coord);//将光标移动到coord指定的位置
}