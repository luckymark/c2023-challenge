#ifndef C2023_CHALLENGE_GOBANG_H
#define C2023_CHALLENGE_GOBANG_H

#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "stack.h"

#define DIR_NUM 4   // 有几个检验方向
#define BOARD_SIZE 15
#define PRED_COUNT 2    // 考虑附近的落点个数

enum PIECE{PLAYER_BLACK = -1, PLAYER_WHITE = 1};    // -1 为黑棋, 1 为白棋

const int direction[DIR_NUM][2];  // 遍历方向时使用的方向常量

typedef enum PIECE PIECE;      // -1 为黑棋, 1 为白棋
typedef struct Gobang{
    int chessboard[15][15];  // 棋盘 15 x 15, 0表示空, -1表示黑, 1表示白
    PIECE now_player;   // 当前应该下棋的玩家
    Stack *steps;
    int pos_steps[15][15];    // 可能的落子点, 采用一个棋盘表示, 0: 不建议搜索, 1: 建议搜索
    int pos_steps_num;
} Gobang;

extern void print_pos_steps_in_stdin(Gobang *gobang);
extern Gobang *create_gobang();
extern int fall(Gobang *gobang, int x, int y);
extern int is_win(Gobang *gobang);
extern void print_chessboard_in_stdin(Gobang *gobang);
extern int remove_piece(Gobang *gobang, int x, int y);
extern void print_debug_msg(Gobang *gobang);
extern void pred_init(Gobang *gobang);
extern int take_back(Gobang *gobang);
#endif //C2023_CHALLENGE_GOBANG_H
