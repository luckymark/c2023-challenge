//
// Created by Cz_13 on 2023/10/31.
//

#ifndef C2023_CHALLENGE_ALPHA_BETA_PRUNING_H
#define C2023_CHALLENGE_ALPHA_BETA_PRUNING_H

#include "gobang.h"
#include "string.h"

#define PATTERN_SIZE 11
#define PATTERN_NUM 18  // 模式
#define MAX_DEPTH 4 // 迭代层数， 只允许是偶数
#define INFINITY 2147283648 // 2 ^ 31

const int statements[PATTERN_NUM];
PIECE ai;
int best_pos[2];
const char patterns[PATTERN_NUM][PATTERN_SIZE];
int nodes[MAX_DEPTH + 1][BOARD_SIZE * BOARD_SIZE][3];   // 启发式搜索使用， 在get_score时对单个子进行打分, 之后再排序
int piece_score[BOARD_SIZE][BOARD_SIZE];    // 储存单个子的得分
int pred_chessboard[MAX_DEPTH + 1][BOARD_SIZE][BOARD_SIZE]; // 每层待探查棋子的粗略得分
int pos_num[MAX_DEPTH + 1];
int heu_locations[6][BOARD_SIZE * BOARD_SIZE][2];
int best_steps[MAX_DEPTH][2];

extern int search(Gobang *gobang, int depth, int alpha, int beta, PIECE cur_player);
extern int evaluate(Gobang *gobang);
extern void node_sort(Gobang *gobang);
extern void init_score(Gobang *gobang);
extern int first_search(Gobang *gobang, int depth, int alpha, int beta, PIECE cur_player);
extern void update_score(Gobang *gobang);
extern int init();

#endif //C2023_CHALLENGE_ALPHA_BETA_PRUNING_H
