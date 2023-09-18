//
// Created by 81201 on 2023/9/14.
//1. 编写一个函数，计算数组的和
#include <stdio.h>

int sum(int b[],int n){
    int s = 0;
    for (int i = 0; i < n; ++i) {
        s = s + b[i];
    }
    return s;
}
int main(){
    system("chcp 65001");
    int n,i = 0;
    int a[n-1];
    printf("您要输入几个数：");
    scanf("%d",&n);
    printf("请输入您的数：");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    printf("数组的和是：%d",sum(a,n));
    return 0;
}
