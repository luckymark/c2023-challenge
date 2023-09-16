#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define MAZE_WIDTH  80
#define MAZE_HIGHTH 100
#define min(a,b) ((a<b)?a:b)
#define max(a,b) ((a>b)?a:b)

typedef struct Pos
{
    int x;
    int y;
}pos;

HANDLE handle_out;

void MoveCursor(int,int);
void InitMaze();
int  random(int,int);
void GenSide(pos,pos);
void gSide(pos,pos);

int main()
{
    pos A={2,2},B={100,20};
    handle_out=GetStdHandle(STD_OUTPUT_HANDLE);
    //InitMaze();
    GenSide(A,B);
    MoveCursor(2,2);
    printf("A");
    MoveCursor(100,20);
    printf("B");
    Sleep(5000);
    return 0;
}
void MoveCursor(int x,int y)
{
    COORD position={x,y};
    SetConsoleCursorPosition(handle_out,position);
    return;
}
void InitMaze()
{
    int in_pos=random(1,MAZE_WIDTH-2),out_pos;
    for(int i=0;i<MAZE_WIDTH;++i)
    {
        MoveCursor(i,0);
        printf("#");
        MoveCursor(i,MAZE_HIGHTH-1);
        printf("#");
    }
    for(int i=1;i<MAZE_HIGHTH-1;++i)
    {
        MoveCursor(0,i);
        printf("#");
        MoveCursor(MAZE_WIDTH-1,i);
        printf("#");
    }
    return;
}
void GenSide(pos A,pos B)
{
    pos M={(A.x+B.x)/2,(A.y+B.y)/2};
    if(B.y<A.y)
    {
        gSide(B,M);
        gSide(M,A);
    }
    else
    {
        gSide(A,M);
        gSide(M,B);
    }
    return;
}
void gSide(pos H,pos L)
{
    const int RAND_RANGE=5;
    int now=H.y,left=min(H.x,L.x),right=max(H.x,L.x);

    while(L.y-now>5)
    {
        int _y=random(1,RAND_RANGE),_x=random(-RAND_RANGE,RAND_RANGE),m;
        if(_x>0) m=1;
        else m=-1;
        for(int i=H.x;i!=H.x+_x&&i>0;i+=m)
        {
            MoveCursor(i,now);
            printf("#");
            MoveCursor(i,now+_y);
            printf("#");
        }
        for(int i=now;i<=now+_y;++i)
        {
            MoveCursor(max(H.x+_x,0),i);
            printf("#");
        }
        now=now+_y+1;
        MoveCursor(H.x,now);
        printf("#");
        ++now;
    }
    for(;now<=L.y;++now)
    {
        MoveCursor(H.x,now);
        printf("#");
    }


    now=left+1;
    while(right-now>5)
    {
        int _y=random(-3,3),_x=random(1,RAND_RANGE),m;
        if(_y>0) m=1;
        else m=-1;
        for(int i=L.y;i!=L.y+_y&&i>0;i+=m)
        {
            MoveCursor(now,i);
            printf("#");
            MoveCursor(now+_x,i);
            printf("#");
        }
        for(int i=now;i<=now+_x;++i)
        {
            MoveCursor(i,max(L.y+_y,0));
            printf("#");
        }
        now=now+_x+1;
        MoveCursor(now,L.y);
        printf("#");
        ++now;
    }
    for(;now<=right;++now)
    {
        MoveCursor(now,L.y);
        printf("#");
    }
    return;
}
int random(int Min,int Max)
{
    static int times=0;
    int ans;
    times++;
    srand(time(0)+times);
    times%=1000;
    ans=rand()%(Max-Min+1)+Min;
    return ans;
}