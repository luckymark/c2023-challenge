#include <windows.h>
#include <bits/stdc++.h>
#include <conio.h>

using namespace std;

#define MAZE_WIDTH  110
#define MAZE_HIGHTH 35
#define RAND_RANGE  8
#define UP          72
#define DOWN        80
#define LEFT        75
#define RIGHT       77
#define SP_SIGN     -32

typedef struct Pos
{
    int x;
    int y;
}pos;

HANDLE handle_out;
bool   mp[MAZE_WIDTH][MAZE_HIGHTH]={};
pos    start,end,usr;

void MoveCursor(int,int);
void InitMaze();
int  random(int,int);
void gPath(pos,pos);
void pave(int,int);
pos  Point(int,int);
bool move(int);
void win();

int main()
{
    handle_out=GetStdHandle(STD_OUTPUT_HANDLE);
    InitMaze();
    usr=start;
    usr.y--;
    MoveCursor(usr.x,usr.y);
    printf("!");
    while(1)
    {
        if(kbhit())
        {
            char input;
            input=getch();
            if(input==SP_SIGN)
            {
                int res=move(getch());
                if(res) break;
            }
        }
    }
    win();
    return 0;
}





void win()
{
    system("cls");
    printf("You win the game!!!");
    return;
}
bool move(int op)
{
    switch(op)
    {
        case UP:
            if(usr.y)
            {
                if(mp[usr.x][usr.y-1])
                {
                    MoveCursor(usr.x,usr.y);
                    printf(" ");
                    usr.y--;
                    MoveCursor(usr.x,usr.y);
                    printf("!");
                }
            }
            break;
        case LEFT:
            if(mp[usr.x-1][usr.y])
            {
                MoveCursor(usr.x,usr.y);
                printf(" ");
                usr.x--;
                MoveCursor(usr.x,usr.y);
                printf("!");
            }
            break;
        case RIGHT:
            if(mp[usr.x+1][usr.y])
            {
                MoveCursor(usr.x,usr.y);
                printf(" ");
                usr.x++;
                MoveCursor(usr.x,usr.y);
                printf("!");
            }
            break;
        case DOWN:
            if(usr.y==MAZE_HIGHTH-1) return true;
            if(mp[usr.x][usr.y+1])
            {
                MoveCursor(usr.x,usr.y);
                printf(" ");
                usr.y++;
                MoveCursor(usr.x,usr.y);
                printf("!");
            }
            break;
    }
    return false;
}
void pave(int x,int y)
{
    MoveCursor(x,y);
    printf(" ");
    mp[x][y]=true;
    return;
}
void MoveCursor(int x,int y)
{
    COORD position={x,y};
    SetConsoleCursorPosition(handle_out,position);
    return;
}
void InitMaze()
{
    for(int y=0;y<MAZE_HIGHTH;++y)
    {
        for(int x=0;x<MAZE_WIDTH;++x) printf("#");
        printf("\n");
    }

    start.x=0;
    start.y=1;
    end.x=0;
    end.y=MAZE_HIGHTH-2;

    while(abs(start.x-end.x)<3)
    {
        start.x=random(1,MAZE_WIDTH-2);
        end.x=random(1,MAZE_WIDTH-2);
    }
    pave(start.x,0);
    pave(end.x,MAZE_HIGHTH-1);

    gPath(start,Point(3,3));
    gPath(start,Point(3,2));
    gPath(start,Point(1,2));
    gPath(Point(1,2),Point(1,1));
    gPath(Point(3,3),end);
    gPath(Point(4,4),start);
    gPath(Point(1,4),start);
    gPath(Point(4,1),start);
    return;
}
pos Point(int x,int y)
{
    const int w=MAZE_WIDTH/5,h=MAZE_HIGHTH/5;
    pos P={w*x,h*y};
    return P;
}
void gPath(pos H,pos L)
{
    int now=H.y,left=min(H.x,L.x),right=max(H.x,L.x),_y,_x,m;

    if(H.y>L.y) swap(H,L);

    while(L.y-now>RAND_RANGE/2)
    {
        do
        {
            _y=random(1,RAND_RANGE/2);
            _x=random(-RAND_RANGE,RAND_RANGE);
        }while(H.x+_x<=0||H.x+_x>=MAZE_WIDTH-1||now+_y<=0||now+_y>=MAZE_HIGHTH-1);
        if(_x>0) m=1;
        else m=-1;
        for(int i=H.x;i!=H.x+_x;i+=m)
        {
            pave(i,now);
            pave(i,now+_y);
        }
        for(int i=now;i<=now+_y;++i) pave(H.x+_x,i);
        now=now+_y+1;
        pave(H.x,now);
        ++now;
    }
    for(;now<=L.y;++now) pave(H.x,now);

    now=left;
    while(right-now>RAND_RANGE/2)
    {
        do
        {
            _y=random(-(RAND_RANGE-2),RAND_RANGE-2);
            _x=random(1,RAND_RANGE/2);
        }while(now+_x<=0||now+_x>=MAZE_WIDTH-1||L.y+_y<=0||L.y+_y>=MAZE_HIGHTH-1);
        if(_y>0) m=1;
        else m=-1;
        for(int i=L.y;i!=L.y+_y&&i>0;i+=m)
        {
            pave(now,i);
            pave(now+_x,i);
        }
        for(int i=now;i<=now+_x;++i) pave(i,max(L.y+_y,0));
        now=now+_x+1;
        pave(now,L.y);
        ++now;
    }
    for(;now<=right;++now) pave(now,L.y);
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