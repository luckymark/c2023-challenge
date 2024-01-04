//
// Created by Cz_13 on 2023/10/31.
//

#ifndef C2023_CHALLENGE_GUI_H
#define C2023_CHALLENGE_GUI_H

#include "raylib.h"
#include "time.h"
#include "gobang.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 1200
#define CHESSBOARD_START_X 32
#define CHESSBOARD_START_Y 32
#define MARGIN 24   // 页边空格 24, 上下左右均为24
#define PIECE_SIZE 45
#define BOUNDARY_LENGTH 3
#define GAP_LENGTH 54

extern void
gobang_gui(Gobang *gobang, int (*player_move)(Gobang *gobang, int x, int y), void (*ai_move)(Gobang *gobang), int *ai_piece);
#endif //C2023_CHALLENGE_GUI_H
