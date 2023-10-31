#include <stdio.h>
#include "stdlib.h"
#include "time.h"

#define MAX 1000000
#define N 1000 // 口算估出\sqrt{1000} 约等于32

void func1(){
    // int arr[MAX + 1] = {};
    int *arr = (int *)malloc(1000000 * sizeof(int) + 5);
    arr[1] = -1;    // -1 不是质数
    int j;
    int p;
    for(int i = 3; i < N;i += 2){
        if(arr[i] == -1)    // 如果不是素数, 跳过, 不需标记其倍数
            continue;
        // j = 2;   原方法
        j = i;  // 修改后不会标记 3 * 7后又标记7 * 3
        p = i * j;
        while(p <= MAX){
            arr[p] = -1;
            j ++;
            p = i * j;
        }
    }
    printf("2 ");
    for(int i = 3; i < MAX + 1; i += 2){
        if(arr[i] == 0){
            printf("%d ", i);
        }
    }
}

void func2(){
    int n = 0;
    scanf("%d", &n);
    if(n = 1){
        printf("abc");
    }
}


int main() {
    /*
     * 埃氏筛      func1
     * 欧拉筛      func2
     * */
    long start = clock();
    func1();
    long end = clock();
    printf("\ntime: %ld ms\n", end - start);
    return 0;
}