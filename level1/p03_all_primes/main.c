#include <stdio.h>
#include <time.h>
#include <math.h>

int main() {
    system("chcp 65001");
    int n=3;
    int w=0;
    clock_t start,end;
    double times;
    printf("2 ");
    start = clock();
    for (n = 3; n < 1001; n++) {
        w=1;
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