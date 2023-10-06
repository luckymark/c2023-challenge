#include <stdio.h>
int extern large;
int extern level;
void Menu(){
    printf("使用wsad控制上下左右，esc退出，☆为终点⊙为玩家所在地\n");
    printf("请输入地图大小（3~100)（请输入奇数，输入偶数会自动+1）\n");
    while (1){
        scanf("%d", &large);
        if(100 <= large || 3 >= large){
            printf("输入错误请重新输入！\n");
        }
        else if(3 < large && 100 > large)
            break;
    }
    printf("请输入游戏难度(1、2):\n");
    while (1){
        scanf("%d", &level);
        if(0 >= level || 3 <= level){
            printf("输入错误请重新输入！");
        }
        else if(2 == level){
            printf("功能尚未实现请重新输入");
        }
        if(1 == level)
            break;
    }

}
