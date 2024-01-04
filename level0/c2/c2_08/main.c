//
// Created by 81201 on 2023/9/14.
//输入n个数，并将它们逆序输出
#include <stdio.h>
int main(){
    system("chcp 65001");
    printf("请决定您要输入几个数：");
    int n = 0,i ,j;
    float a[i];
    scanf("%d", &n);
    j = n - 1;
    printf("请输入您的数：");
    for (i = 0; i < n; i++) {
        scanf("%f",&a[i]);
    }
    for (j; j >= 0; j--) {
        printf("%f ",a[j]);
    }
    return 0;
}
