#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<math.h>

//地图边长L，包括迷宫主体20，外侧的包围的墙体2，最外侧包围路径2（之后会解释）
//可根据需要修改，有上限
#define L 24

#define WALL  0 //墙
#define ROUTE 1 //路径
#define PLAYER 2//玩家

//控制迷宫的复杂度，数值越大复杂度越低，最小值为0
//默认为简单难度，可根据需要在degree函数里调整不同难度的复杂度
int Rank = 6;

void menu();   //主菜单界面
void start();  //开始游戏
void degree(); //游戏难度
void explain();//游戏说明
int init(int** Maze);  //初始化迷宫
void print(int** Maze);//画迷宫
void CreateMaze(int **maze, int x, int y);    //创建迷宫
void move(int** Maze, char t, int *x, int *y);//移动角色

int main() {
    system("chcp 65001");
    menu();
    return 0;
}

void menu() { //主菜单
    while(1) {
        system("cls"); //清屏
        char t;
        printf("*******(走迷宫)*******");
        printf("\n======================\n");
        printf("\n||   1. 开始 游戏   ||\n");
        printf("\n||   2. 游戏 说明   ||\n");
        printf("\n||   3. 游戏 难度   ||\n");
        printf("\n||   4. 关闭 游戏   ||\n");
        printf("======================\n");
        t=getch();    //不回显函数
        switch(t) {
            case '1':
                start();
                break;  //开始一局游戏
            case '2':
                explain();
                break;  //进入游戏说明界面
            case '3':
                degree();
                break;  //调整游戏难度
            case '4':
                printf("\n欢迎下次再玩，再见（￣︶￣）↗");
                Sleep(1500);
                exit(0);
                break;  //结束程序
            default :
            {
                printf("输入错误，请重新输入。");
                break;
            }
        }
    }
}

void CreateMaze(int **maze, int x, int y) {//构建迷宫
    maze[x][y] = ROUTE;
    //确保四个方向随机，而不再是固定的上下左右这种排列
    int direction[4][2] = { { 1,0 },{ -1,0 },{ 0,-1 },{ 0,1 } };
    int i, j;
    for (i = 0; i < 4; i++) {
        int r = rand() % 4;
        int temp = direction[0][0];
        direction[0][0] = direction[r][0];
        direction[r][0] = temp;
        temp = direction[0][1];
        direction[0][1] = direction[r][1];
        direction[r][1] = temp;
    }
    //向四个方向开挖
    for (i = 0; i < 4; i++) {
        int dx = x;
        int dy = y;
        //控制挖的距离，由Rank来调整大小
        int range = 1 + (Rank == 0 ? 0 : rand() % Rank);
        while (range > 0) {
            //计算出将要访问到的坐标
            dx += direction[i][0];
            dy += direction[i][1];
            //排除掉回头路
            if (maze[dx][dy] == ROUTE) {
                break;
            }
            //判断是否挖穿路径
            int count = 0, k;
            for (j = dx - 1; j < dx + 2; j++) {
                for (k = dy - 1; k < dy + 2; k++) {
                    //abs(j - dx) + abs(k - dy) == 1 确保只判断九宫格的四个特定位置
                    if (abs(j - dx) + abs(k - dy) == 1 && maze[j][k] == ROUTE) {
                        count++;
                    }
                }
            }
            //count大于1表明墙体会被挖穿，停止
            if (count > 1)
                break;
            //确保不会挖穿时，前进
            range -= 1;
            maze[dx][dy] = ROUTE;
        }
        //没有挖穿危险，以此为节点递归
        if (range <= 0) {
            CreateMaze(maze, dx, dy);
        }
    }
}

int init(int** Maze) {//初始化迷宫
    int i;
    //最外围层设为路径的原因，为了防止挖路时挖出边界，同时为了保护迷宫主体外的一圈墙体被挖穿
    for (i = 0; i < L; i++) {
        Maze[i][0] = ROUTE;
        Maze[0][i] = ROUTE;
        Maze[i][L - 1] = ROUTE;
        Maze[L - 1][i] = ROUTE;
    }
    //创造迷宫，（2，2）为起点
    CreateMaze(Maze, 2, 2);
    //画迷宫的入口和出口，给出玩家初始位置
    Maze[2][1] = PLAYER;
    //由于算法随机性，出口有一定概率不在（L-3,L-2）处，此时需要寻找出口
    for (i = L - 3; i >= 0; i--) {
        if (Maze[i][L - 3] == ROUTE) {
            Maze[i][L - 2] = ROUTE;
            //返回出口所在的纵坐标
            return i;
        }
    }
}

void print(int** Maze) {//画迷宫
    int i, j;
    for (i = 0; i < L; i++) {
        for (j = 0; j < L; j++) {
            if (Maze[i][j] == ROUTE)
                printf("  ");//表示道路
            else if(Maze[i][j] == WALL)
                printf("回");//表示墙体
            else
                printf("十");//表示玩家
        }
        printf("\n");
    }
}
//将原先的引用int &x，更改为现在的指针指向int *x
void move(int** Maze, char t, int *x, int *y) {//移动角色
    int i = *x, j = *y;//记录原始位置
    switch(t) {
        case 'w':    //向上移动
            *x -= 1;
            break;
        case 's':    //向下移动
            *x += 1;
            break;
        case 'a':    //向左移动
            *y -= 1;
            break;
        case 'd':    //向右移动
            *y += 1;
            break;
        default:
            break;
    }
    if(*x>=0 && *x<L-1 && *y>=0 && *y<L-1 && Maze[*x][*y]!=WALL) {//符合条件，移动
        Maze[i][j] = 1;
        Maze[*x][*y] = 2;
    } else {//保持位置不变
        *x = i;
        *y = j;
    }
}

void start() { //开始一局游戏
    char t;
    //y,x表示角色横纵坐标, out表示出口的纵坐标
    int *p, *q;
    int x = 2, y = 1, out = 0, i = 0;
    p = &x;
    q = &y;
    //随机数发生器初始化函数
    srand((unsigned)time(NULL));
    //申请数组空间
    int **Maze = (int**)malloc(L * sizeof(int *));
    for (i = 0; i < L; i++) {
        Maze[i] = (int*)calloc(L, sizeof(int));
    }
    //得到出口纵坐标
    out = init(Maze);
    //游戏开始
    system("cls");
    print(Maze);
    while(t = getch()) {
        if(t == 27)   //如果输入为ESC键，结束游戏回到主菜单
            break;
        system("cls");//清屏
        move(Maze, t, p, q);//根据输入t进行移动
        print(Maze);//重新绘制迷宫
        if(x == out && y == L-2) {//已经到出口，游戏结束
            system("cls");
            printf("=============\n");
            printf("游 戏 胜 利！\n");
            printf("=============\n");
            printf("即将后返回主菜单……");
            Sleep(1500);//执行挂起一段时间，暂停1.5秒后打印
            break;
        }
    }
    //一局游戏结束，释放内存
    for (i = 0; i < L; i++) free(Maze[i]);
    free(Maze);
}

void explain() { //操作说明
    while(1) {
        char t;
        system("cls");
        printf("=================================================\n");
        printf("感谢您体验本游戏，游戏的操作如下：\n");
        printf("\n1.将输入法调整为英文（小写）\n");
        printf("\n2.通过w,s,a,d四个键控制角色上下左右移动\n");
        printf("\n3.在任意界面均可按“ESC”键返回到主菜单\n");
        printf("\n胜利条件：移动角色到出口处，加油各位(￣▽￣)\"!\n");
        printf("=================================================\n");
        t=getch();  //不回显函数
        switch(t) {
            //ESC键的ASCII码值
            case 27:
                //返回主菜单
                menu();
                break;
            default :
                break;
        }
    }
}

void degree() { //调整游戏难度
    while(1) {
        char t;
        system("cls");
        printf("=======================\n");
        printf("输入1,2,3进行难度调整：\n");
        printf("\n||    1.简  单    ||\n");
        printf("\n||    2.中  等    ||\n");
        printf("\n||    3.困  难    ||\n");
        printf("=======================\n");
        t=getch();  //不回显函数
        switch(t) {
            case '1':
                Rank = 6;
                printf("\n当前难度：简单，即将返回主菜单……");
                Sleep(1500);
                menu();//返回主菜单
                break;
            case '2':
                Rank = 3;
                printf("\n当前难度：中等，即将返回主菜单……");
                Sleep(1500);
                menu();//返回主菜单
                break;
            case '3':
                Rank = 0;
                printf("\n当前难度：困难，即将返回主菜单……");
                Sleep(1500);
                menu();//返回主菜单
                break;
            case 27:
                menu();
                break;
            default :
                break;
        }
    }
}