//
// Created by 81201 on 2023/9/14.
//打印2-100的所有偶数

#include <stdio.h>
int main(){
    for (int i = 2; i < 101; i++) {
        if (i%2==0)
            printf("%d\n",i);
    }
    return 0;
}
