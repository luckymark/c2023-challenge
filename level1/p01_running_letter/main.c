#include <stdio.h>
#include<windows.h>
#include<stdlib.h>
int main() {
    CONSOLE_CURSOR_INFO mice;
    mice.dwSize=1;
    mice.bVisible=FALSE;
    HANDLE handle= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle,&mice);
    char * letter="Hello";
    int m=0;
    int k=1;
    while(1){
        if(m==0)
            k=1;
        if(m==57) 
            k=-1;
        for(int i=1;i<=m*2;i++)
        {
            printf(" ");
            fflush(stdout);
        }
        printf("%s",letter);
        fflush(stdout);
        Sleep(300);
        if(k==1)
            m++;
        else
            m--;
       system("cls");
       }
    return 0;
}