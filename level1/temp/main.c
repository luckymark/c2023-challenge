#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "head_temp.h"

#define M 100

int map[M + 1][M + 1] = { 0 };
int large = 0;
int level = 0;
int now_x;
int now_y;
char str[2 * (M + 1) * (M + 1)] = {'\0'};

void Menu();//菜单
void Initialize(int num);//初始化地图
void Creat_01(int x,int y);//开始创建地图
void Print();//打印地图
int HaveNeighbor(int x,int y);//判断是否有方向可以创建地图
int FindMe();//找到自己当前所在位置并赋值为3
int Move();//进行移动
int Up();
int Down();
int Left();
int Right();



int main(){
    system("chcp 65001");
    system("color 0A");
    srand((unsigned )time(NULL));
    int flag = 0;
    Menu();
    Initialize(large);
    while (1){
        flag = Move();
        if(1 == flag || -1 == flag){
            return 0;
        }
    }
}



void Initialize(int num){
    int i = 0,j = 0;
    //地图只能是奇数
    if(num % 2 == 0)
        large++;
    //地图初始化为0内部初始化间隔的1，外部初始化为-1
    for(i = 0;i < large;i++){
        for (j = 0; j < large; j++) {
            if(i < large && j < large){
                map[i][j] = 0;
            }
            if(i >= large || j >= large){
                map[i][j] = -1;
            }
            if(i % 2 == 1 && j % 2 == 1){
                map[i][j] = 1;
            }
        }
    }
    //开始创建地图
    if(level == 1){
        Creat_01(1,1);
    }
    //把随机的路径初始化为1
    for (i = 0; i < large; i++) {
        for(j = 0;j < large; j++){
            if(map[i][j] == 5){
                map[i][j] = 1;
            }
        }
    }
    map[1][1] = 3;
    map[large - 2][large - 2] = 4;
}

void Print(){
    int i = 0,j = 0;
    //将str初始化为空
    str[0] = '\0';
    system("cls");
    for(i = 0;i < large;i++){
        for (j = 0; j < large; j++) {
            if(map[i][j] == 0){
                strcat(str,"■");
            }
            if(map[i][j] == 1){
                strcat(str," ");
            }
            if(map[i][j] == 3){
                strcat(str,"⊙");
            }
            if(map[i][j] == 4){
                strcat(str,"☆");
            }
            //调试时测试用的值
            if(map[i][j] == 5){
                strcat(str,"◇");
            }
            if(map[i][j] == -1)
                break;
        }
        if(-1 != map[i][0]){
            strcat(str,"\n");
        }
    }
    printf("%s ",str);
}
int Move(){
    int flag = 0;
    Print();
    while (1){
        FindMe();
        switch (getch()) {
            case 'w':flag = Up();break;
            case 's':flag = Down();break;
            case 'a':flag = Left();break;
            case 'd':flag = Right();break;
            case 27:return -1;
        }
        //返回值为1则移动成功并继续
        if(1 == flag){
            Print();
        }
            //返回为2则成
        else if(2 == flag){
            printf("挑战成功！\n");
            MessageBoxW(NULL, L"恭喜通关！", L"恭喜！", MB_OK);
            system("pause");
            return 1;
        }
    }



}
int FindMe(){
    int i = 0,j = 0;
    for(i = 0;i < large;i++){
        for(j = 0;j < large;j++){
            //找到自己的位置并输出所在坐标
            if(3 == map[i][j]){
                now_x = i;
                now_y = j;
            }
        }
    }
}
int Up(){
    if(1 == map[now_x - 1][now_y]){
        map[now_x][now_y] = 1;
        map[now_x - 1][now_y] = 3;
        return 1;
    }
    else if(4 == map[now_x - 1][now_y])
        return 2;
    else
        return 0;

}
int Down(){
    if(1 == map[now_x + 1][now_y]){
        map[now_x][now_y] = 1;
        map[now_x + 1][now_y] = 3;
        return 1;
    }
    else if(4 == map[now_x + 1][now_y])
        return 2;
    else
        return 0;
}
int Left(){
    if(1 == map[now_x][now_y - 1]){
        map[now_x][now_y] = 1;
        map[now_x][now_y - 1] = 3;
        return 1;
    }
    else if(4 == map[now_x][now_y - 1])
        return 2;
    else
        return 0;
}
int Right(){
    if(1 == map[now_x][now_y + 1]){
        map[now_x][now_y] = 1;
        map[now_x][now_y + 1] = 3;
        return 1;
    }
    else if(4 == map[now_x][now_y + 1])
        return 2;
    else
        return 0;
}

void Creat_01(int x,int y){
    int old_x = x,old_y = y;
    int rand_direction = 0;
    while (1){
        if(HaveNeighbor(x,y)){
            while (1){
                old_x = x;
                old_y = y;
                map[x][y] = 5;
                rand_direction = rand() % 4;
                if(0 == rand_direction && map[x - 2][y] == 1 && x >= 3){
                    x -= 2;
                }
                else if(1 == rand_direction && map[x + 2][y] == 1 && x < large - 3){
                    x += 2;
                }
                else if(2 == rand_direction && map[x][y - 2] == 1 && y >= 3){
                    y -= 2;
                }
                else if(3 == rand_direction && map[x][y + 2] == 1 && y < large - 3){
                    y += 2;
                }
                map[(x + old_x) / 2][(y + old_y) / 2] = 5;
                map[x][y] = 5;
                Creat_01(x,y);
                break;
            }
        }
        else
            return;
    }
}

int HaveNeighbor(int x,int y){
    //有“邻居”则返回1
    if((x >= 3 && map[x - 2][y] == 1) || (x < large - 3 && map[x + 2][y] == 1) || (y >= 3 && map[x][y - 2] == 1) || (y <= large - 2 && map[x][y + 2] == 1))
        return 1;
    return 0;
}