
//
// Created by 81201 on 2023/9/14.
//1. 编写一个函数，将美元换算为人民币

#define EXCHANGE_RATE 6.5
#include <stdio.h>

float utr(float u){
    float r = u * EXCHANGE_RATE;
    return r;
}
int main(){
    system("chcp 65001");
    float u;
    printf("请输入您的美元数量：");
    printf("转换成为了 %f 元", utr(u));
    return 0;
}