#include <stdio.h>
#include <time.h>
#include <math.h>

int main() {
    system("chcp 65001");//输出中文
    int n=3;
    //判断是否是素数的变量
    int w=0;
    clock_t start,end;//定义时间计算的变量
    double times;
    printf("2 ");
    start = clock();            //计时开始
    //判断是否是素数
    for (n = 3; n < 1001; n++) {
        w=1;                       //定义中间变量减少运算次数
        float b= pow(n,0.5);
        for (int i = 2; i <= b; i++) {
            if(n%i==0)
            {
                w=0;
                break;
            }

        }
        if(w==1)
            printf("%d ",n);
    }
    end = clock();
    printf("\n");
    times = (double)(end - start)/CLOCKS_PER_SEC;
    printf("计算时间为：%f 秒\n",times);
    return 0;
}