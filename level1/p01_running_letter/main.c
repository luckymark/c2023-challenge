#include <stdio.h>
#include <windows.h>

#define RIGHT 00
#define LEFT  1


HANDLE hd;
int width,dir=RIGHT;
void move(int x,int y)
{
    COORD pos={x,y};
    SetConsoleCursorPosition(hd,pos);
    return;
}
void GetSize()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hd,&info);
    width=info.srWindow.Right;
    return;
}
int ne(int now)
{
    if(dir==RIGHT)
    {
        if(now!=width) return now+1;
        else
        {
            dir=LEFT;
            return now-1;
        }
    }
    else
    {
        if(now) return now-1;
        else
        {
            dir=RIGHT;
            return now+1;
        }
    }
}

int main() {
    int now;
    hd= GetStdHandle(STD_OUTPUT_HANDLE);
    GetSize();
    printf("a");
    while(1)
    {
        move(now,0);
        printf(" ");
        now=ne(now);
        move(now,0);
        printf("a");
        Sleep(25);
    }
    return 0;
}