#include "stdio.h"
#include "time.h"

#define PI_NUM 10000
#define NUM (PI_NUM * 14 / 4)

// 无意间看到了ioccc的得奖作品，还附带解析的那种，故而逻辑有点相像

/*
 * 带余除法
 * spigot 算法
 * 公式对反正切级数进行欧拉变化得到
 * \frac{\pi}{2} = \sum_{k=0}^{\infty}{\frac{k!}{\left(2k+1\right)!!}}
 */

long long a[NUM + 1];
long long b = NUM;
long long c = NUM;
long long d = 0, e = 0;

int main(){
    long start = clock();
    for (long long i = 0; i < NUM + 1; i ++) {
        a[i] = 2000;
    }

    while (c != 0) {
        b = c;
        e = d % 10000;
        d = e;
        while (b != 0) {
            d = d * b + a[b] * 10000;
            a[b] = d % (2 * b - 1);
            d /= (2 * b - 1);
            b --;
        }
        c -= 14;
        printf("%04d", e + d / 10000);
    }
    long end = clock();
    printf("\ntime: %ld ms", end - start);  // 本机测试用时 260 ms，空间消耗显而易见
}