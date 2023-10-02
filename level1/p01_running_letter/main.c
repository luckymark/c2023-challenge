#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>


void Running_letter(){
    int i, j, f, k;
    for (i = 1; i <= 140; i ++) {
        printf("%c", 'A');
        usleep(4800);
        system("cls");
        for (j = 0; j < i; j ++){
            printf(" ");
        }
        j --;
    }
    for (f = 1; f <= 140; f ++) {
        printf("%c", 'A');
        usleep(4800);
        system("cls");
        for (k = 79; k > f; k --){
            printf(" ");
        }
        k ++;
    }
}

int main(){
    Running_letter();
}