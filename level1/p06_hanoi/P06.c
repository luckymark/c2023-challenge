#include "stdio.h"

void hanoi_step(int num, char A, char B, char C){//利用递归实现汉诺塔
    if (num == 1){
        printf("%c -> %c\n", A, C);
    }
    else {
        hanoi_step(num - 1, A, C, B);
        printf("%c -> %c\n", A, C);
        hanoi_step(num - 1, B ,A, C);
    }
}

int main(){
    hanoi_step(64, 'A', 'B', 'C');
    return 0;
}