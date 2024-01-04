#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char * judge(int i) {//一个返回T&F的函数，用于判断一个数是否为素数，判断思路同P02
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

int main(){
    system("chcp 65001");
    clock_t start_time, end_time;
    double  running_time;
    start_time = clock();//获取开始运行的时间
    printf("%s", "素数有:\n");
    for (int i = 2; i < 1001; i ++){//利用judge函数逐个打印1000以内的素数
        if (strcmp(judge(i), "true") == 0){
            printf("%d\n", i);
        }
        else
            continue;
    }
    end_time = clock();//获取结束运行的时间
    running_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;//将CPU时间转换为自然时间
    printf("程序运行时间是%.5f秒", running_time);
}
