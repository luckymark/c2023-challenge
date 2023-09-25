#include <stdio.h>
#include <math.h>
#include "prime.h"
int main()
{

    int n;
    scanf("%d",&n);
    if(IsPrime(n)) printf("Yes");
    else printf("No");
    return 0;
}