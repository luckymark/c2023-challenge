//
// Created by 81201 on 2023/9/14.
//打印1-100，是7的倍数，或者尾数为7的所有数，并打印这些数的总和
#include <stdio.h>
int main(){
    system("chcp 65001");
    int j = 0;
    for (int i = 2; i < 101; i++) {
        if (i%7==0||i%10==7){
            j = j + i;
            printf("%d\n",i);
        }
    }
    printf("这些数的总和是：%d",j);
    return 0;
}
