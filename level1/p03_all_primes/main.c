#include <stdio.h>
#include<time.h>
#include"../p02_is_prime/Prime.h"
int main() {
   /* time_t start_time=0,end_time=0;
    static int a[10000001]={0};
    start_time=clock();
    for(int i=2;i*i<=10000000;i++)
    {
        if(a[i]==0)
        {
            int p=2;
            while(i*p<=10000000) {
                if(a[i*p]==0)
                    a[i*p]=1;
                p++;
            }
        }
    }*/
    /*for(int i=2;i<=100000;i++)
        if(a[i]==0)
            printf("%d ",i);*/
    /*end_time=clock();
    printf("\n%f\n",(double)(end_time-start_time)/CLOCKS_PER_SEC);*/

    int n,k=1;
    scanf("%d",&n);
    k=Prime(n);
    if(k==0)
        printf("It is not prime!");
    else
        printf("It is prime!");
    return 0;
}