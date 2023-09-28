//
// Created by 14212 on 2023/9/23.
//
#include<stdio.h>
#include"push_boxes.h"
extern int len;
extern int logo[6];
struct box init_maze(char (*maze)[100],int num,int * len_,struct box * object,struct box * boxes){
    struct box exam;
    FILE * fp;
    switch(num){
        case 1:
            fp=fopen("D:/c2023-challenge/level1/c2023-challenge/level1/p08_push_boxes/low_challenge.txt","r");
            break;
        case 2:
            fp=fopen("D:/c2023-challenge/level1/c2023-challenge/level1/p08_push_boxes/high_challenge.txt","r");
            break;
    }
    int i=0,j=0;
    int box_number=0,object_number=0;
    char s;
    while((s=getc(fp))<0)
        continue;
    while(s!=EOF)
    {
        j=0;
        while(s!='\n'&&s!=EOF)
        {
            if(s=='#'){
                boxes[box_number].y=i;
                boxes[box_number].x=j;
                box_number++;
            }
            if(s=='&'){
                object[object_number].y=i;
                object[object_number].x=j;
                object_number++;
            }
            maze[i][j++]=s;
            s=getc(fp);
        }
        i++;
        if(s=='\n')
            s=getc(fp);
    }
    exam.y=i;
    exam.x=j;
    * len_=object_number;
    fclose(fp);
    return exam;
}
void init_0(char (*maze)[100]){
    for(int i=0;i<100;i++)
        for(int j=0;j<100;j++)
            maze[i][j]=0;
}
void print_maze(char (*maze)[100],int max_x,int max_y){
    for(int i=0;i<max_y;i++)
    {
        for(int j=0;j<max_x;j++)
            printf("%2c",maze[i][j]);
        printf("\n");
    }
}
int init_topic(void){
    int num,p;
    printf("This is the game PUSH_BOXES!\n");
    printf("If you succeed,you will get a score according to your time and steps.\n");
    printf("If the time in low_challenge > 5min or in high_challenge > 20min,you will lose!\n");
    printf("If your steps in low_challenge > 100 or in high_challenge > 1000,you will lose,too\n");
    printf("The signs are: '@':player  '#':boxes  '&':objects\n");
    printf("After the game begins,you can press \"Esc\" to escape the game.\n");
    printf("You can input the number to choose the difficulty:\n");
    printf("1:low_challenge          2:high_challenge\n");
    p=scanf("%d",&num);
    while(p==0||num>2||num<1){
        printf("Please input the right number!!!\n");
        getchar();
        p=scanf("%d",&num);
    }
    return num;
}
void init_player(struct box * player,int num){
    switch(num){
        case 1:
            player->x=1;
            player->y=1;
            break;
        case 2:
            player->x=13;
            player->y=12;
            break;
    }
}
void init_object(char (*maze)[100],struct box * object){
    for(int i=0;i<len;i++){
        if(maze[object[i].y][object[i].x]==' ')
        {
            maze[object[i].y][object[i].x]='&';
            logo[i]=0;
        }
    }
}