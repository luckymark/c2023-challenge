#include <stdio.h>
#include <stdlib.h>

int main(){
    system("chcp 65001");
    int i, j;
    printf("%s", "请输入一个正整数，我会为您判断它是否为素数\n");
    scanf("%d", &i);
    for (j = 1; j <= i; j ++){
        if ((i % j == 0) && (j != i) && (j != 1))
            break;
        else
            continue;
    }
    if (j == (i + 1) && (j != 2)) {
        printf("%s", "您输入的数字是素数！");

    }
    else
        printf("%s", "您输入的数字不是素数！");
    return 0;
}