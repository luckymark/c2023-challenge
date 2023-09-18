//
// Created by 81201 on 2023/9/14.
//1. 编写一个阶乘函数
#include <stdio.h>

void factorial(int n){
    int s=1;
    for (int i = 1; i <= n; i++) {
        s = s * i;
    }
    printf("该阶乘等于：%d",s);
}
int main(){
    int n;
    system("chcp 65001");
    printf("您要计算几的阶乘：");
    scanf("%d",&n);
    factorial(n);
    return 0;
}