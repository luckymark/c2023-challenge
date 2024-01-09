//
// Created by 14212 on 2023/9/22.
//
#include"game.h"
#include<stdio.h>
void init_maze(char ch[][30]){//可以尝试指针表示法

    FILE * fp;
    char c;
    fp=fopen("D:/c2023-challenge/level1/c2023-challenge/level1/p07_maze/maze.txt","r+");
    while((c=getc(fp))<0)
        continue;
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<31;)
        {
            if(c=='\n')
            {
                c=getc(fp);
                break;
            }
            ch[i][j]=c;
            j++;
            c=getc(fp);

        }
    }
    fclose(fp);
}
int sum(int down,int up,int left,int right){
    int cnt=0;
    if(down<0)
        cnt++;
    if(up<0)
        cnt++;
    if(left<0)
        cnt++;
    if(right<0)
        cnt++;
    if(cnt>1||cnt==0)
        return 0;
    else
        return 1;
}
void change(char (*ch)[30],int mm,int * a,int * b,int m,int n){
    if(mm<0)
    {
        ch[*a][*b]=' ';
        *a=*a+m;
        *b+=n;
        ch[*a][*b]='@';
    }
    else
        return;
}
