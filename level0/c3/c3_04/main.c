//
// Created by 81201 on 2023/9/14.
//1. 编写一个函数，判断三角形是否为直角三角形
#include <stdio.h>
int main(){
    system("chcp 65001");
    printf("请输入三角形的三边长:");
    float a,b,c;
    scanf("%f %f %f",&a,&b,&c);
    a=a*a;
    b=b*b;
    c=c*c;
    if(a==b+c||b==c+a||c==b+a)
        printf("该三角形是直角三角形。\n");
    else
        printf("该三角形不是直角三角形。\n");
    return 0;
}