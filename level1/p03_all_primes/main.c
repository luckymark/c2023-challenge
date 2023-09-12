#include <stdio.h>
#include <windows.h>
const int N=1000;
int NotPrime[N+1]={},primes[N+1],num=0;
int main()
{

    WORD timer=0;
    SYSTEMTIME tm0,tm1;
    GetSystemTime(&tm0);
    for(int i=2;i<=N;++i)
    {
        if(!NotPrime[i]) primes[num++]=i;
        for(int j=0;j<num;++j)
        {
            int tem=primes[j]*i;
            if(tem<=N) NotPrime[tem]=1;
            if(i%primes[j]==0) break;
        }
    }
    GetSystemTime(&tm1);
    timer=(tm1.wSecond-tm0.wSecond)*1000+tm1.wMilliseconds-tm0.wMilliseconds;
    printf("Running Time:%dms\n",timer);
    for(int i=0;i<num;++i) printf("%d\n",primes[i]);
    return 0;
}