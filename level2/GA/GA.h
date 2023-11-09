#ifndef C2023_CHALLENGE_GA_H
#define C2023_CHALLENGE_GA_H
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#define ELITE 10
#define GROUP_SIZE 310//减去10后可以除以4,为什么数字大了就不行了？
#define CIRCLE_TIME 1000
typedef struct{
    int data[700];
    int fitness;
    double start_percent;
    double end_percent;
    int now_x;
    int now_y;
    int ifsuccess;
    int now_bit;
    int vary_percent[700];
    int two_time;
}ind;
void init_maze(int (* )[26] ,int num);
void print_maze(int (* )[26],int num);
void init_group(ind *,const int);
void print_group(ind *,const int,int);
void count_fitness(ind *,int (* )[26],int ,const int);
void move(ind *,int(* )[26],const int,int);
void check(ind *,int (* )[26],int move_y,int move_x,int num);
void fitness(ind *,int);
void Select_Sort(ind *);
void all_percent_(ind *);
void roulette(ind *,const int);
void exchange(ind *,ind *,const int);
void vary(ind *,const int);
void print_result(ind *,int (* )[26],int,const int );
void check_result(ind *,int (* )[26],int move_y,int move_x,int num);
void move_again(ind *,int(* )[26],const int,int);
#endif //C2023_CHALLENGE_GA_H
