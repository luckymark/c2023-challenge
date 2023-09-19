#include <stdio.h>
#include <math.h>

int main() {
    system("chcp 65001");           //输出中文
    int n;
    int a=0;                        //定义一个变量用来判断是否是素数
    printf("请输入一个数字n:\n");
    scanf("%d",&n);
    float b= pow(n,0.5);      //定义中间变量减少运算次数
    //判断素数
    for (int i = 2; i < b; i++) {
        if(n%i==0)
        {
            a=0;
            printf("这个数不是素数。");
            break;
        }

    }
    if(a == 1)
        printf("这个数是素数。");
    return 0;
}