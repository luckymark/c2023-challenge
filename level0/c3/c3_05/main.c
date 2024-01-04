
//
// Created by 81201 on 2023/9/14.
//1. 编写一个函数，判断2个矩形是否有重叠（即游戏中常用的碰撞检测函数）
#include <stdio.h>

typedef struct {
    int x;
    int y;
    int width;
    int height;
}recrangle;

int overlap(recrangle r1,recrangle r2){
    if(r1.x>=r2.x+r2.width||r2.x>=r1.x+r1.width)
        return 0;
    if(r1.y>=r2.y+r2.height||r2.y>=r1.y+r1.height)
        return 0;
    return 1;
}

int main(){
    int x;
    int y;
    int width;
    int height;
    system("chcp 65001");
    printf("请输入矩形1的坐标以及宽高：");
    scanf("%d %d %d %d",&x,&y,&width,&height);
    recrangle r1={x,y,width,height};
    printf("请输入矩形2的坐标以及宽高：");
    scanf("%d %d %d %d",&x,&y,&width,&height);
    recrangle r2={x,y,width,height};
    if(overlap(r1,r2))
        printf("两个矩形重叠了。\n");
    else
        printf("两个矩形没有重叠。\n");
    return 0;
}