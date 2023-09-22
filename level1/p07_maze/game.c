//
// Created by 14212 on 2023/9/22.
//
#include"game.h"
void init_maze(char ch[][30]){//可以尝试指针表示法
    for(int i=0;i<=10;i++)
        ch[i][3]=' ';
    for(int i=3;i<=17;i++)
        ch[10][i]=' ';
    for(int i=10;i>=4;i--)
        ch[i][17]=' ';
    for(int i=17;i>=14;i--)
        ch[4][i]=' ';
    for(int i=7;i<=22;i++)
        ch[6][i]=' ';
    for(int i=6;i>=1;i--)
        ch[i][7]=' ';
    for(int i=7;i<=26;i++)
        ch[1][i]=' ';
    for(int i=1;i<=16;i++)
        ch[i][26]=' ';
    ch[15][27]=ch[15][28]=' ';
    for(int i=6;i<=26;i++)
        ch[16][i]=' ';
    ch[17][16]=' ';
    for(int i=16;i<=22;i++)
        ch[18][i]=' ';
    ch[15][11]=ch[14][11]=' ';
    for(int i=1;i<=11;i++)
        ch[13][i]=' ';
    for(int i=13;i<=19;i++)
        ch[i][1]=' ';
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
