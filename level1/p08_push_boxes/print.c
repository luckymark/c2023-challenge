#include <stdio.h>
#include <windows.h>
#include "head_push_box.h"

extern char str[(15) * (15)];
extern int map[10][10];
extern int sure_step;
extern int level;
extern int now_step;


void Print()
{
    int i = 0,j = 0,min_ = 0;
    //将str初始化为空
    str[0] = '\0';
    system("cls");
    for(i = 0;i < 10;i++)
    {
        for (j = 0; j < 10; j++)
        {
            //-1-空地""，0-墙"■"，1-路" "，2-箱子"✪"，3-人"⊙"，4-目标"☆"，5-达成目标"◇"
            if(map[i][j] == 0)
            {
                strcat(str,"■");
            }
            if(map[i][j] == 1)
            {
                strcat(str," ");
            }
            if(map[i][j] == 2)
            {
                strcat(str,"✪");
            }
            if(map[i][j] == 3)
            {
                strcat(str,"◇");
            }
            if(map[i][j] == 4)
            {
                strcat(str,"☆");
            }
            if(map[i][j] == 5)
            {
                strcat(str,"★");
            }
            if(map[i][j] == 6)
            {
                strcat(str,"◈");
            }
            if(map[i][j] == -1)
                strcat(str," ");
            if(9 == j)
            {
                strcat(str,"\n");
            }
        }

    }

    min_ = Min_step(level);
    printf("按'r'重新开始本关卡\n");
    printf("当前步数：%d\n",now_step);
    printf("%s",str);
    if(99999999 != min_ && 0 != min_)
    {
        printf("本关卡目前最小步数为：%d\n",min_);
    }
    else
    {
        printf("本关卡暂时没有最佳成绩\n");
    }
}