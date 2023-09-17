#include <stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
int main() {
    char * letter="Hello";
    int m=0;
    int k=1;
    while(1){
        if(m==0)
            k=1;
        if(m==57)
            k=-1;
        for(int i=1;i<=m*2;i++)
            printf(" ");
        printf("%s",letter);
        Sleep(300);
        if(k==1)
            m++;
        else
            m--;
       system("cls");
       }
    return 0;
}