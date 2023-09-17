#include <stdio.h>

int main() {
    int n,k=1;
    scanf("%d",&n);
    if(n==1)
        k=0;
    else
    {
        for(int i=2;i*i<=n;i++)
            if(n%i==0)
                k=0;
    }
    if(k==0)
        printf("It is not prime!");
    else
        printf("It is prime!");
    return 0;
}
