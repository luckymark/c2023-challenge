#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * judge(int i) {
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

int goldbach(int i, int * p){
    for (int j = 0; j < 25; j ++){
        for (int k = 0; k <25; k ++){
            for (int m = 0; m <25; m ++){
                if (i == (p[j] + p[k] + p[m])){
                    printf("%d 满足哥德巴赫猜想\n", i);
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
    int  sig_num[25];
    for (int i = 0; i < 25; ) {
        for (int j = 1; j < 100; j++) {
            if (strcmp((judge(j)), "true") == 0) {
                sig_num[i] = j;
                i++;
            }
            else
                continue;
        }
    }
    for (int i = 1; i < 100; i ++){
        goldbach(i, &sig_num[0]);
    }
    return 0;
}