#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

HANDLE hd;

void SetConsoleSize(int w,int h)
{
    COORD sz={w,h};
    SMALL_RECT pos={0,0,w-1,h-1};
    SetConsoleScreenBufferSize(hd,sz);
    SetConsoleWindowInfo(hd,true,&pos);
    return;
}
void GetConsoleSize()
{
    int w,h;
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hd,&info);
    w=info.srWindow.Right-info.srWindow.Left+1;
    h=info.srWindow.Bottom-info.srWindow.Top+1;
    printf("width:%d,highth:%d\n",w,h);
    return;
}
void move(int x,int y)
{
    COORD pos={x,y};
    SetConsoleCursorPosition(hd,pos);
    return;
}
int random(int rMAX,int rMIN)
{
    int ans;
    srand(time(0));
    ans=rand()%(rMAX-rMIN+1)+rMIN;
    return ans;
}
void FormSide(COORD A,COORD B)
{
    if(A.Y>B.Y) swap(A,B);
    if(A.Y!=B.Y)
}
int main()
{
    hd=GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleSize(1000,1000);
    //GetConsoleSize();
    return 0;
}