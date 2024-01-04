//从3个整数中，找出最大的那个数
// Created by 81201 on 2023/9/13.
//
#include <stdio.h>
/*void choose(int a,int b,int c){
    int max1,max;
    max1=(a>b)?a:b;
    max=(max1>c)?max1:c;
    printf("最大的是：%d\n",max);
}*/
int main(){
    system("chcp 65001");
    int a,b,c;
    printf("请输入三个整数：\n");
    scanf("%d""%d""%d",&a,&b,&c);
    int max1,max;
    max1=(a>b)?a:b;
    max=(max1>c)?max1:c;
    printf("最大的是：%d\n",max);
    //choose(a,b);
    return 0;
}