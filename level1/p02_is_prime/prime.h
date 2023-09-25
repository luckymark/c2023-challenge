#ifndef PRIME_H
#define PRIME_H

#include <stdbool.h>

bool IsPrime(int n)
{
    int end=sqrt(n)+1;;
    if(n==1) return false;
    else if(n==2) return true;
    else
    {
        for(int i=2;i<=end;++i)
        {
            if(n%i==0) {
                return false;
                break;
            }
        }
        return true;
    }
}

#endif