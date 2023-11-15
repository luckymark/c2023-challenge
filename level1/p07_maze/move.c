
#include "head_maze.h"

extern  int large;
extern int now_x;
extern  int now_y;
extern int map[101][101];

int FindMe(){
    int i = 0,j = 0;
    for(i = 0;i < large;i++)
    {
        for(j = 0;j < large;j++)
        {
            //找到自己的位置并输出所在坐标
            if(3 == map[i][j])
            {
                now_x = i;
                now_y = j;
            }
        }
    }
}

int Move(){
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
            case 27:return -1;
        }
        //返回值为1则移动成功并继续
        if(1 == flag)
        {
            Print();
        }
		//返回为2则挑战成功
        else if(2 == flag)
        {
            printf("挑战成功！\n");
            MessageBoxW(NULL, L"恭喜通关！", L"恭喜！", MB_OK);
            system("pause");
            return 1;
        }
    }
}