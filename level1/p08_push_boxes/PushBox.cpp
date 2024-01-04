#include "PushBox.h"
#include <windows.h>
#include <conio.h>

int mp[20][20];

static pos    player;
static int    BoxNum;
static int    score;

void MoveCursor(int x,int y)
{
    COORD pos={x,y};
    SetConsoleCursorPosition(HdOut,pos);
    return;
}
void InitMap(char *path,int width,int highth)
{
    score=500;
    file=fopen(path,"r");
    BoxNum=0;
    WIN=false;
    system("cls");
    if(!file){
        printf("Map file is not found.\nPress any key to start the next level...");
        getch();
        return;
    }
    for(int y=0;y<highth;++y) {
        for (int x = 0; x < width; ++x) {
            fscanf(file, "%d", &mp[x][y]);
            switch (mp[x][y]) {
                case PATH:
                    printf(" ");
                    break;
                case BARRIER:
                    printf("#");
                    break;
                case BOX:
                    BoxNum++;
                    printf("@");
                    break;
                case TARGET:
                    printf("*");
                    break;
                case PLAYER:
                    printf("+");
                    player.x=x;
                    player.y=y;
                    mp[x][y]=1;
                    break;
            }
        }
        printf("\n");
    }
    return;
}
void move(int op)
{
    pos tar=player,tem=player;
    switch(op)
    {
        case UP:
            tar.y--;
            tem.y-=2;
            break;
        case DOWN:
            tar.y++;
            tem.y+=2;
            break;
        case RIGHT:
            tar.x++;
            tem.x+=2;
            break;
        case LEFT:
            tar.x--;
            tem.x-=2;
            break;
    }
    switch(mp[tar.x][tar.y])
    {
        case TARGET:
        case PATH:
            MoveCursor(player.x,player.y);
            if(mp[player.x][player.y]==TARGET) printf("*");
            else printf(" ");
            MoveCursor(tar.x,tar.y);
            printf("+");
            player=tar;
            score--;
            break;
        case BARRIER:
            break;
        case FINISHED_TARGET:
        case BOX:
            if(mp[tem.x][tem.y]==PATH||mp[tem.x][tem.y]==TARGET)
            {
                score--;
                MoveCursor(player.x,player.y);
                if(mp[player.x][player.y]==TARGET) printf("*");
                else printf(" ");
                MoveCursor(tem.x,tem.y);
                if(mp[tem.x][tem.y]==PATH)
                {
                    printf("@");
                }
                else
                {
                    BoxNum--;
                    printf("!");
                }
                if(mp[tar.x][tar.y]==FINISHED_TARGET&&mp[tem.x][tem.y]==PATH) BoxNum++;
                MoveCursor(tar.x,tar.y);
                printf("+");
                if(mp[tar.x][tar.y]==FINISHED_TARGET) mp[tar.x][tar.y]=TARGET;
                else mp[tar.x][tar.y]=PATH;
                if(mp[tem.x][tem.y]==PATH) mp[tem.x][tem.y]=BOX;
                else mp[tem.x][tem.y]=FINISHED_TARGET;
                if(BoxNum==0) WIN=true;
                player=tar;
            }
            break;
    }
    return;
}
void win(char *FileName)
{
    fclose(file);
    file=fopen(FileName,"w");
    fprintf(file,"%d",score);
    fclose(file);
    file=NULL;
    system("cls");
    printf("You have passed this level.Your score is %d.\nPress any key to start the next level...",score);
    getch();
    return;
}
void over()
{
    system("cls");
    printf("You have win the game!!!");
}