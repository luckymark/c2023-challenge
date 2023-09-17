#include <stdio.h>
#include<time.h>
int a[101]={0},k=0;
void Is_Prime(int try,int origin_n,int n){
    if(k==1)
        return;
    if(try==1)
    {
        if(a[n]==0) {
            k = 1;
            printf("%d Yes\n", origin_n);
            printf("%d\n",n);
            return;
        }
        else
            return;
    }
    for(int i=2;i<=origin_n/3+1;i++)
    {
        if(a[i]==0)
        {
            Is_Prime(try-1,origin_n,n-i);
        }
        if(k==1)
        {
            printf("%d\n",i);
            return;
        }
    }
}
int main() {
    for(int i=2;i*i<=100;i++)
    {
        if(a[i]==0)
        {
            int p=2;
            while(i*p<=100) {
                if(a[i*p]==0)
                    a[i*p]=1;
                p++;
            }
        }
    }
    for(int i=5;i<=100;i++)
    {
        Is_Prime(3,i,i);
        k=0;
    }
    return 0;
}