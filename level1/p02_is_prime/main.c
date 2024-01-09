#include <stdio.h>
#include "../p04_goldbach/header.h"

int main() {
    //主要是为了无限测试
    for(;;) {
        printf("Enter a num:");
        int n;
        scanf("%d", &n);
        printf("%s", isPrime(n) ? "is prime!\r\n" : "no\r\n");
    }
    return 0;
}