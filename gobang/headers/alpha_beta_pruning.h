//
// Created by Cz_13 on 2023/10/31.
//

#ifndef C2023_CHALLENGE_ALPHA_BETA_PRUNING_H
#define C2023_CHALLENGE_ALPHA_BETA_PRUNING_H

#include "gobang.h"
#include "string.h"

#define PATTERN_SIZE 11
#define PATTERN_NUM 18  // 十六种模式
#define MAX_DEPTH 4 // 迭代层数， 只允许是偶数
#define INFINITY 2147283648 // 2 ^ 31

const int statements[PATTERN_NUM];
int best_pos[2];
int black_pos[2];
int white_pos[2];
const char patterns[PATTERN_NUM][PATTERN_SIZE];
int piece_state[BOARD_SIZE][BOARD_SIZE][DIR_NUM];   // 用来简化判分计算， 使同一种情况下不会对每一个棋子算分， 如冲四中， 一个棋子算了冲四的分， 其余三颗棋子便不会算该方向的分
int nodes[BOARD_SIZE * BOARD_SIZE][3];
int predict_piece[9][BOARD_SIZE * BOARD_SIZE][2];   // 所有能形成五的子
int predict_piece_index[9];
int piece_score[BOARD_SIZE][BOARD_SIZE];    // 储存单个子的得分
int is_init;
FILE *file;

extern long long search(Gobang *gobang, int depth, long long alpha, long long beta, PIECE cur_player);
extern long long evaluate(Gobang *gobang);
extern void node_sort(Gobang *gobang);
extern void init_score(Gobang *gobang);

#endif //C2023_CHALLENGE_ALPHA_BETA_PRUNING_H
