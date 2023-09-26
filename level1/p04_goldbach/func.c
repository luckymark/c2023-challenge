#include <stdio.h>
int isPrime(int n){
    int count = 0;
    for (int i = 1; i < n; i++)
        count += n % i == 0;
    return count==1;
}
void DivideNum(int n){
    for(int i=1;i<=n/2;i++){
        if(isPrime(i)&& isPrime(n-i))
            printf("\r\n%d = %d + %d",n,i,n-i);
    }
}