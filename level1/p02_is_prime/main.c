#include <stdio.h>
#include <math.h>

int main() {
    system("chcp 65001");
    int n;
    int a=0;
    printf("请输入一个数字n:\n");
    scanf("%d",&n);
    float b= pow(n,0.5);
    for (int i = 2; i < b; i++) {
        if(n%i==0)
        {
            a=1;
            printf("这个数不是素数。");
            break;
        }

    }
    if(a == 0)
        printf("这个数是素数。");
    return 0;
}