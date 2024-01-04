
//
// Created by 81201 on 2023/9/14.
//打印所有1-100，能被3整除，但不能被5整除的数
#include <stdio.h>
int main(){
    for (int i = 1; i < 101; i++) {
        if (i%3==0&&i%5!=0)
            printf("%d\n",i);
    }
    return 0;
}

