#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include "PushBox.h"

using namespace std;

char *path[2]={"PushBox1.txt","PushBox2.txt"};
char *Score[2]={"score1.txt","score2.txt"};
int   mp_sz[2][2]={{13,9},{13,19}};
HANDLE      HdOut;
bool        WIN;
FILE*       file;


int main()
{
    HdOut=GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i=0;i<2;++i)
    {
        InitMap(path[i],mp_sz[i][0],mp_sz[i][1]);
        if(!file) continue;
        while(1)
        {
            int input=getch();
            if(input==SP_SIGN)
            {
                input=getch();
                move(input);
                if(WIN)
                {
                    win(Score[i]);
                    break;
                }
            }
        }
    }
    over();
    return 0;
}