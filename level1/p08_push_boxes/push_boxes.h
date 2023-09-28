//
// Created by 14212 on 2023/9/23.
//

#ifndef C2023_CHALLENGE_PUSH_BOXES_H
#define C2023_CHALLENGE_PUSH_BOXES_H
struct box {
    int y;
    int x;
    char sign;
    int l_x;
    int l_y;
};
struct box init_maze(char (*maze)[100],int num,int * len,struct box * object,struct box * boxes);
void init_0(char (*maze)[100]);
void print_maze(char (*maze)[100],int max_x,int max_y);
int key_check();
int sum(int left,int right,int down,int up);
int move_check(char (*maze)[100],int key,struct box * player,struct box * box_,struct box * object_);
int check_boxes(int add_x,int add_y,struct box * player,struct box * box_);
int check_wall(char (*maze)[100],int add_x,int add_y,struct box * all);
void move(char (*maze)[100],struct box * all,int add_x,int add_y);
int check_object(char (*maze)[100],int add_x,int add_y,struct box * all,struct box * object);
int init_topic(void);
void init_player(struct box * player,int num);
void init_object(char (*maze)[100],struct box * object);
int check_only_box(char (*maze)[100],int add_x,int add_y,struct box * boxes);
double score(double all_time,int step_number,int dif);
int lose_check(double now_time,int step,int dif);
#endif //C2023_CHALLENGE_PUSH_BOXES_H
