#include <stdio.h>

int main() {
    //主要是为了无限测试
    for(;;) {
        printf("Enter a num:");
        int n;
        scanf("%d", &n);
        int count = 0;
        for (int i = 1; i < n; i++)
            count += n % i == 0;
        printf("%s", count==1 ? "is prime!\r\n" : "no\r\n");
    }
    return 0;
}