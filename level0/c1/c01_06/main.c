//从n个整数中，找出最大的那个数
// Created by 81201 on 2023/9/13.
//
#include <stdio.h>
/*void choose(int a,int b){
    int max;
    max=(a>b)?a:b;
    printf("最大的是：%d",max);
}*/
int main(){
    system("chcp 65001");
    printf("请确定您要输入几个整数：");
    int n,i,m;
    m=n-1;
    int a[m];
    scanf("%d",&n);
    printf("请输入n个整数：\n");
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    int max = a[0];
    for (int j = 0; j < n; j++) {
        if(a[j]>max)
            max = a[j];
    }
    printf("最大值是：%d",max);
    return 0;
}