#include <stdio.h>

int isPrimeNumber(int num){
    if(num == 1){
        return 0;
    }
    for(int i = 2; i * i <= num; i ++){
        if(!(num % i)){
            return 0;
        }
    }
    return 1;
}

void func(){
    /*
    任意输入一个正整数n
    判断n是否为素数
    */
    int num = 0;
    int flag = 1;
    while(flag){
        printf("pls input a positive number:");
        flag = scanf("%d", &num);
        if(num <= 0){
            printf("%d is not a positive number!\n", num);
            continue;
        }
        if(isPrimeNumber(num)){
            printf("%d is a prime number\n", num);
        }else{
            printf("%d is not a prime number\n", num);
        }
        // printf(" \n%u", num);
    }
}

int main() {
    // func();
    for(int i = 1; i <= 100; i ++){
        if(isPrimeNumber(i)){

            if((i - 2) > 0){
                printf(", ");
            }

            printf("%d, ", i);
        }
    }
    // printf("\b\b  ");

    return 0;
}

