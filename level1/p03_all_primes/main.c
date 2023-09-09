#include <stdio.h>
#include <time.h>

int isPrime(int n){
    int count = 0;
    for (int i = 1; i < n; i++)
        count += n % i == 0;
    return count==1;
}
int main() {
    time_t start,done;
    start=clock();
    for(int i=2;i<=1000;i++){
        if(isPrime(i))
            printf("%d ",i);
    }
    done=clock();
    printf("\r\nFinished in %f ms",(double)(done-start));
    return 0;
}