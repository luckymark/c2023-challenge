
//
// Created by 81201 on 2023/9/14.
//打印一个九九表
#include <stdio.h>
int main(){
    system("chcp 65001");
    int s;
    for (int i = 1; i < 10; i++) {
        for (int j = 1; j < 10; j++) {
            s = i * j;
            if(i<=j)
                printf("%dx%d=%d    ",i,j,s);
            else
                printf("          ");
        }
        printf("\n");
    }
    return 0;
}
