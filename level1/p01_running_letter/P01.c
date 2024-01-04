#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>


void Running_letter(){
    int i, j, f, k;
    for (i = 1; i <= 140; i ++) {  //从左向右移动字母
        printf("%c", 'A');   //打印字母
        usleep(5000);  //等待一段时间
        system("cls");  //清屏
        for (j = 0; j < i; j ++){  //在字母前打印空格，制造出移动的效果
            printf(" ");
        }
        j --;
    }
    for (f = 1; f <= 140; f ++) {
        printf("%c", 'A');
        usleep(5000);
        system("cls");
        for (k = 72; k > f; k --){
            printf(" ");
        }
        k ++;
    }
}

int main(){
    Running_letter();
}
