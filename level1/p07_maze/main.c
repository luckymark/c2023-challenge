#include <stdio.h>
#include"game.h"
#include<windows.h>
int main() {
    char maze[20][30];
    init_maze(maze);
    int x=3,y=0;
    while(1){
        for(int i=0;i<20;i++)
        {
            for(int j=0;j<30;j++)
                printf("%2c",maze[i][j]);
            printf("\n");
        }
        if(y==19&&x==1)
        {
            printf("You win!\n");
            break;
        }
        Sleep(200);
        int down=0,up=0,left=0,right=0;
        while((((down=GetKeyState(VK_DOWN))>=0||maze[y+1][x]=='*')&&
            ((up= GetKeyState(VK_UP))>=0||maze[y-1][x]=='*'||y-1<0)&&
            ((left= GetKeyState(VK_LEFT))>=0||maze[y][x-1]=='*')&&
            ((right= GetKeyState(VK_RIGHT))>=0||maze[y][x+1]=='*'))||
            sum(down,up,left,right)==0)
            continue;
        change(maze,down,&y,&x,1,0);
        change(maze,up,&y,&x,-1,0);
        change(maze,left,&y,&x,0,-1);
        change(maze,right,&y,&x,0,1);
        system("cls");
    }
    system("pause");
    return 0;
}