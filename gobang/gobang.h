#ifndef GOBANG_GOBANG_H
#define GOBANG_GOBANG_H
#include"raylib.h"
#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<stdlib.h>
#define WIDTH 1050
#define HEIGHT 1050
#define LATTICE_WIDTH 70
#define LATTICE_R 30
#define LAYER 4
typedef struct{
    Vector2 point_location[17][17];
    int lattice_extinct[17][17];//判断棋盘上该位置是黑棋还是白棋；
    int station_scores[5][17][17];
    int station_all_scores;
} Board;
void draw_background(void);//把背景搞上
void init_point_location(void);//给棋盘上的每个交点赋值
Vector2 check_hit(void);//检测鼠标的点击位置
void player_move(Image *);//但轮到玩家的时候玩家开始下棋
void computer_move(Image *);//轮到电脑开始下棋
#endif //GOBANG_GOBANG_H