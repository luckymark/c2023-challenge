#include <stdio.h>
//一次移动
void move(char A,char B){
    printf("%c -> %c\n",A,B);
}
//把A通过B移动到C
void hano(int n,char A,char B,char C){
    if(n==1){
        move(A,C);
    }
    else{
        hano(n-1,A,C,B);
        move(A,C);
        hano(n-1,B,A,C);
    }
}
//这玩意自己写完都不知道他怎么能跑的

int main(){
    int n = 3;
    hano(n,'A','B','C');
    return  0;
}