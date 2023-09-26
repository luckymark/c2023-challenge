#include<stdio.h>
#include<windows.h>
#include<time.h>
#include <conio.h>

#define N 2	//关卡数目
#define M (N*50)	//地图大小	M*M
int level = 0;//游戏等级
int map[M + 1][M + 1] = { 0 };
int large;//地图大小
int my_x, my_y;//我的位置
char str[2 * (M + 1)*(M + 1)] = { '\0' };//用来打印地图

void Menu();//菜单
void Initialize(int num);//初始化地图
void Creat_01(int X_index, int Y_index);//创建深度优先的随机地图
void Print();//根据随机结果打印地图
int HaveNeighbor(int X_index, int Y_index);//判断一个点是否有另一个为1的邻居点
int Move();//移动及判定
int FindMe();//找到当前所在位置
int Up();//上
int Down();//下
int Left();//左
int Right();//右




int main(){
    system("chcp 65001");
    int flag = 0;
    srand((unsigned ) time(NULL));
    system("color 0A");

    Menu();
    Initialize(large);
    while (1){
        flag = Move();
        if (flag == 1||flag == -1)
            return 0;
    }
}

int FindMe(){
    int i, j;
    for (i = 0;i < large;i++)
        for (j = 0;j < large;j++)
        {
            if (map[i][j] == 3)
            {
                my_x = i;
                my_y = j;
            }
        }
}

int Move(){
    int flag = 0;
    Print();
    while (1){
        flag = 0;
        FindMe();
        switch (getch()) {
            case 'w':flag = Up();break;
            case 'a':flag = Left();break;
            case 's':flag = Down();break;
            case 'd':flag = Right();break;
            case 27:return -1;
        }
        //行走成功再重新打印一次地图
        if(flag == 2){
            Print();
        }
        else if(flag == 1){
            //通过了
            MessageBox(0, ("恭喜你赢了游戏，解锁了所有难度"), ("恭喜"), MB_OK);
            return 1;
        }
    }
}
int Up()
{
    if (my_x != 0)
    {
        if (map[my_x - 1][my_y] == 1)//可走
        {
            map[my_x - 1][my_y] = 3;
            map[my_x][my_y] = 1;
            return 2;//行走成功
        }
        else if (map[my_x - 1][my_y] == 4)
        {
            return 1;
        }
    }
    return 0;
}
int Down()
{
    if (my_x != large - 1)
    {
        if (map[my_x + 1][my_y] == 1)//可走
        {
            map[my_x + 1][my_y] = 3;
            map[my_x][my_y] = 1;
            return 2;//行走成功
        }
        else if (map[my_x + 1][my_y] == 4)
        {
            return 1;
        }
    }
    return 0;
}
int Right()
{
    if (my_y != large - 1)
    {
        if (map[my_x][my_y + 1] == 1)//可走
        {
            map[my_x][my_y + 1] = 3;
            map[my_x][my_y] = 1;
            return 2;//行走成功
        }
        else if (map[my_x][my_y + 1] == 4)
        {
            return 1;
        }
    }
    return 0;
}
int Left()
{
    if (my_y != 0)
    {
        if (map[my_x][my_y - 1] == 1)//可走
        {
            map[my_x][my_y - 1] = 3;
            map[my_x][my_y] = 1;
            return 2;//行走成功
        }
        else if (map[my_x][my_y - 1] == 4)
        {
            return 1;
        }
    }
    return 0;
}
int HaveNeighbor(int X_index, int Y_index){

    if(level == 0){
        if ((X_index >= 3 && map[X_index - 2][Y_index] == 1) || (X_index < large - 3 && map[X_index + 2][Y_index] == 1) || (Y_index >= 3 && map[X_index][Y_index - 2] == 1) || (Y_index < large - 3 && map[X_index][Y_index + 2] == 1))
            return  1;
        return  0;
    }
}
void Creat_01(int X_index, int Y_index)
{
    int rand_position, x, y, flag = 0;
    x = X_index;
    y = Y_index;
    //如果四个方向都没有了，返回上一步，否则，继续
    while (1)
    {
        flag = 0;
        flag = HaveNeighbor(X_index, Y_index);
        if (flag == 0)
        {
            return;
        }
        else
        {
            //当前位置记为5
            map[X_index][Y_index] = 5;
            x = X_index;
            y = Y_index;
            //随机方向产生地图，并把可通过路径记为5
            while (1)
            {
                rand_position = rand() % 4;
                if (rand_position == 0 && X_index >= 3 && map[X_index - 2][Y_index] == 1)//上
                {
                    X_index = X_index - 2;
                }
                else if (rand_position == 1 && X_index < large - 3 && map[X_index + 2][Y_index] == 1)//下
                {
                    X_index = X_index + 2;
                }
                else if (rand_position == 2 && Y_index >= 3 && map[X_index][Y_index - 2] == 1)//左
                {
                    Y_index -= 2;
                }
                else if (rand_position == 3 && Y_index < large - 3 && map[X_index][Y_index + 2] == 1)//右
                {
                    Y_index += 2;
                }
                map[(x + X_index) / 2][(y + Y_index) / 2] = 5;
                map[X_index][Y_index] = 5;
                Creat_01(X_index, Y_index);
                //递归结束break
                break;
            }
        }
    }
}
void Initialize(int num)
{
    int i,j;
    //地图只能是奇数
    if(num % 2 == 0)
        large++;
    //地图初始化为0
    for(i = 0;i < large;i++)
        for(j = 0;j < large;j++)
            map[i][j] = 0;
    //内部初始化间隔的1，外部初始化为-1
    for(i = 0;i < M;i++){
        for(j = 0;j < M;j++){
            if(i >= large || j>= large)
                map[i][j] = -1;
            else if(i != 0 && j != 0 && i != large -1 && j != large - 1 && i % 2 == 1 && j % 2 == 1)
                map[i][j] = 1;
        }
    }
    //开始创建地图
    if(level == 0)
        Creat_01(1, 1);
    //把随机的路径初始化为1
    for (i = 0; i < large; i++) {
        for (j = 0; j < large; j++) {
            if(map[i][j] == 5)
            {
                map[i][j] = 1;
            }
        }
    }
    //设置起点和终点
    map[1][1] = 3;
    map[large -2][large -2] = 4;
}
void Print()
{
    int i = 0, j = 0;
    str[0] = '\0';
    system("cls");
    for (i = 0;i < M;i++)
    {
        for (j = 0;j < M;j++)
        {
            if (map[i][j] == 0)
            {
                strcat(str, "■");
            }
                //printf("■");
            else if (map[i][j] == -1)
                break;
            else if (map[i][j] == 1)
            {
                strcat(str, " ");
            }
                //printf("  ");
            else if (map[i][j] == 3)
            {
                strcat(str, "⊙");
            }
                //	printf("⊙");
            else if (map[i][j] == 4)
            {
                strcat(str, "☆");
            }
                //	printf("☆");
            else if (map[i][j] == 5)
            {
                strcat(str, "◇");
            }
                //	printf("◇");
            else if (map[i][j] == 6)
            {
                strcat(str, "○");
            }
            //	printf("○");
        }
        if (map[i][0] != -1)
            strcat(str, "\n");
        //printf("\n");
    }
    printf("%s", str);
}
void Menu()
{
    char select[10];
    printf("分别用wasd控制人物移动，按Esc退出游戏，☆为终点⊙为玩家所在地\n");
    printf("请输入地图大小：");
    scanf("%d", &large);
    printf("请输入游戏难度(1、2):");
    while (1)
    {
        scanf("%s", select);
        if (strlen(select)>1)
        {
            printf("错误输入，请重新输入：");
        }
        else
        {
            if ('1' == select[0])
            {
                level = 0;
                break;
            }
            if ('2' == select[0])
            {
                printf("程序尚未实现！");
            }
            else
            {
                printf("错误输入，请重新输入：");
            }
        }
    }

}