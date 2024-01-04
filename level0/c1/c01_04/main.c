//从2个整数中，找出最大的那个数
// Created by 81201 on 2023/9/13.
//
#include <stdio.h>
/*void choose(int a,int b){
    int max;
    max=(a>b)?a:b;
    printf("最大的是：%d\n",max);
}*/
int main(){
    system("chcp 65001");
    int a,b;
    printf("请输入两个整数：\n");
    scanf("%d""%d",&a,&b);
    int max;
    max=(a>b)?a:b;
    printf("最大的是：%d\n",max);
    //choose(a,b);
    return 0;
}