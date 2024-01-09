#include <stdio.h>
#include"Prime.h"
int main() {
    int n,k=1;
    scanf("%d",&n);
    k=Prime(n);
    if(k==0)
        printf("It is not prime!");
    else
        printf("It is prime!");
    return 0;
}
