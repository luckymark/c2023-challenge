#include <stdio.h>
extern int level;
void Menu(){
    printf("使用wsad控制上下左右，esc退出，墙■,箱子✪,人⊙,目标☆,达成目标◇\n");
    printf("请输入关卡数(1~5)\n");

    while (1){
        scanf("%d",&level);
        if(1 != level &&2 != level && 3 != level && 4 != level && 5 != level)
        {
            printf("输入错误请重新输入！");
        }
        if(1 == level || 2 == level || 3 == level || 4 == level || 5 == level)
            break;
    }
}
