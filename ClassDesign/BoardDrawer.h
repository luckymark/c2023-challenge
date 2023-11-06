//
// Created by cz241 on 11/6/2023.
//

#ifndef C2023_CHALLENGE_BOARDDRAWER_H
#define C2023_CHALLENGE_BOARDDRAWER_H
#include <raylib.h>
#include "DataTypes.h"

extern const float Board_Size;
extern const float Margin;
extern const int LineThick;
extern const int PieceSize;
extern const int GridSize;

class BoardDrawer {
public:
    //绘制当前玩家并响应鼠标事件：
    static void MouseEvent();
    //绘制棋盘背景
    static void DrawBackground();
    //根据MapData绘制棋子
    static void DrawPieces();
    //到底是谁在赢这个游戏
    static PieceStatus  Win();
    //有人赢了！！
    static void OnWined(PieceStatus winner);
};


#endif //C2023_CHALLENGE_BOARDDRAWER_H
