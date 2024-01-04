#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * judge(int i) {//一个判断是否为素数的函数，实现思路同P03
    int j;
    char * ret_value;
    for (j = 1; j <= i; j++) {
        if ((i % j == 0) && (j != i) && (j != 1))
            break;
        else
            continue;
    }
    if (j == (i + 1) && (j != 2)) {
        ret_value = strdup("true");
    }
    else
        ret_value = strdup("false");

    return ret_value;
}

int goldbach(int i, int * p){//此处p是素数数组
    for (int j = 0; j < 25; j ++){
        for (int k = 0; k <25; k ++){
            for (int m = 0; m <25; m ++){
                if (i == (p[j] + p[k] + p[m])){
                    printf("%d 满足哥德巴赫猜想\n", i);//三层循环遍历，确定素数数组中是否有三个素数相加等于输入的数，如果有，输出满足哥德巴赫猜想
                    return 0;
                }
                else
                    continue;
            }
        }
    }
}

int main(){
    system("chcp 65001");
    int sig_num[25]//定义一个素数数组
    for (int i = 0; i < 25; ) {//将1-100的素数填入数组中
        for (int j = 1; j < 100; j++) {
            if (strcmp((judge(j)), "true") == 0) {
                sig_num[i] = j;
                i++;
            }
            else
                continue;
        }
    }
    for (int i = 1; i < 100; i ++){//1-100内验证哥德巴赫猜想
        goldbach(i, &sig_num[0]);
    }
    return 0;
}