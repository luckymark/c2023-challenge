//
// Created by 14212 on 2023/9/24.
//
#include<stdio.h>
#include<windows.h>
#include"push_boxes.h"
extern int len;
extern int logo[];
void move(char (*maze)[100],struct box * all,int add_x,int add_y){
    maze[all->y][all->x]=' ';
    all->y+=add_y;
    all->x+=add_x;
    maze[all->y][all->x]=all->sign;
}
int check_object(char (*maze)[100],int add_x,int add_y,struct box * all,struct box * object_){
    for(int i=0;i<len;i++)
    {
        if(all->y+add_y==object_[i].y&&all->x+add_x==object_[i].x)
        {
            logo[i]=1;
            return 1;
        }
    }
    return -1;
}
void key_choose(int key,int * x,int * y){
    switch(key){
        case 1:
            *x=-1;
            *y=0;
            break;
        case 2:
            *x=1;
            *y=0;
            break;
        case 3:
            *x=0;
            *y=1;
            break;
        case 4:
            *x=0;
            *y=-1;
            break;
            //default:后续想一个default:
    }
}
int check_boxes(int add_x,int add_y,struct box * player,struct box box_[]){
    for(int i=0;i<len;i++)
    {
        if(player->x+add_x==box_[i].x&&player->y+add_y==box_[i].y)
        {
            return i;
        }
    }
    return -1;
}
int check_only_box(char (*maze)[100],int add_x,int add_y,struct box * boxes){
    if(maze[boxes->y+add_y][boxes->x+add_x]=='#')
        return 1;
    else
        return -1;
}
int check_wall(char (*maze)[100],int add_x,int add_y,struct box * all){
    if(maze[add_y+all->y][add_x+all->x]=='*'||add_x+all->x<0||add_y+all->y<0||add_x+all->x>=all->l_x||add_y+all->y>=all->l_y)
        return 1;
    else
        return -1;
}
int sum(int left,int right,int down,int up){
    int cnt=0;
    int key;
    if(left<0)
    {
        cnt++;
        key=1;
    }
    if(right<0)
    {
        cnt++;
        key=2;
    }
    if(down<0)
    {
        cnt++;
        key=3;
    }
    if(up<0)
    {
        cnt++;
        key=4;
    }
    if(cnt==0||cnt>1)
        return -1;
    else
        return key;
}
int key_check(){
    int escape= GetKeyState(VK_ESCAPE);
    if(escape<0)
        return -2;
    int left= GetKeyState(VK_LEFT);
    int right= GetKeyState(VK_RIGHT);
    int down= GetKeyState(VK_DOWN);
    int up= GetKeyState(VK_UP);
    return sum(left,right,down,up);
}
int check_win(void){
    int cnt=0;
    for(int i=0;i<len;i++)
        if(logo[i]==1)
            cnt++;
    if(cnt==len)
        return 1;
    else
        return -1;
}
int move_check(char (*maze)[100],int key,struct box * player,struct box * box_,struct box * object_){
    int box=0,wall=0,object=0,x=0,y=0;
    key_choose(key,&x,&y);
    box=check_boxes(x,y,player,box_);
    wall=check_wall(maze,x,y,player);
    if(wall==1)
        return -1;
    if(box>=0)
    {
        wall=check_wall(maze,x,y,&box_[box]);
        if(wall==1)
            return -1;
        if(check_only_box(maze,x,y,&box_[box])==1)
            return -1;
        object= check_object(maze,x,y,&box_[box],object_);//再次修改的时候注意把特殊情况加进去。
        move(maze,&box_[box],x,y);
        move(maze,player,x,y);
        if(check_win()==1)
            return 2;
        else
            return 1;
    }
    else
    {
        move(maze,player,x,y);
        return 1;
    }
}
int lose_check(double now_time,int step,int dif){
    if(dif==1) {
        if (now_time > 300)
            return -1;
        if(step>100)
            return -2;
        return 1;
    }
    else
    {
        if (now_time > 1200)
            return -1;
        if(step>1000)
            return -2;
        return 1;
    }
}