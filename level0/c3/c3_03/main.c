//
// Created by 81201 on 2023/9/14.
//1. 编写一个斐波那契函数
#include <stdio.h>
void fb(int n){
    int a[n];
    for (int i = 0; i <= n; i++) {
        a[i]=1;
    }
    for (int i = 2; i <= n+1; i++) {
        a[i]=a[i-2]+a[i-1];
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ",a[i-1]);
    }
}
int main(){
    system("chcp 65001");
    int n=0;
    printf("输出几项:");
    scanf("%d",&n);
    fb(n);
    return 0;
}