#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "head_push_box.h"

int extern map[10][10];
int extern now_x,now_y;
extern int level;
extern int step[5];
extern int now_step;
extern int sure_step;

int FindMe(){
    int i,j;
    for(i = 0;i < 10;i++)
    {
        for(j = 0;j < 10;j++)
        {
            //找到自己的位置并记录所在坐标
            if(3 == map[i][j] || 6 == map[i][j])
            {
                now_x = i;
                now_y = j;
            }
        }
    }
}


int Push()
{
    now_step = 0;
    int flag = 0;
    Print();
    while (1)
    {
        FindMe();
        switch (getch())
        {
            case 'w':flag = Up();break;
            case 's':flag = Down();break;
            case 'a':flag = Left();break;
            case 'd':flag = Right();break;
            case 'r':return 3;//重新开始当前关卡
            case 27:return -1;
        }
        //返回值为1则移动成功记录并继续
        if(1 == flag)
        {
            now_step++;
            Print();
        }
            //返回为2则完成当前关卡
        else if(2 == flag)
        {
            now_step++;
            sure_step = now_step;
            step[level - 1] = now_step;
            Print();
            printf("挑战成功！\n");
            int result = MessageBoxW(NULL, L"恭喜通过本关！是否进行下一关卡", L"恭喜！", MB_YESNO);
            if(6 == result)
            {
                level++;
                return 2;
            }
            else if(7 == result)
            {
                system("pause");
                return 1;
            }
            else
            {
                printf("error");
            }
        }
    }
}

