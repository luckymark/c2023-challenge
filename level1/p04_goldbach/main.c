#include <stdio.h>
const int N=100;
int NotPrime[N+2],primes[N+2],pNum;
void init_prime()
{
    for(int i=2;i<=N;++i)
    {
        if(!NotPrime[i]) primes[pNum++]=i;
        for(int j=0;j<pNum;++j)
        {
            int tem=primes[j]*i;
            if(tem<=N) NotPrime[tem]=1;
            if(i%primes[j]==0) break;
        }
    }
    return;
}
int main()
{
    int flag;
    init_prime();
    for(int i=8;i<=N;i+=2)
    {
        flag=1;
        for(int j=0;j<pNum&&primes[j]<i;++j)
        {
            if(!NotPrime[i-primes[j]])
            {
                flag=0;
                break;
            }
        }
        if(flag)
        {
            printf("wrong");
            return 0;
        }
    }
    printf("right");
    return 0;
}