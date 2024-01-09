#include <stdio.h>
#include <time.h>
#include "../p04_goldbach/header.h"

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