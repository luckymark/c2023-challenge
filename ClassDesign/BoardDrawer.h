//
// Created by cz241 on 11/6/2023.
//

#ifndef C2023_CHALLENGE_BOARDDRAWER_H
#define C2023_CHALLENGE_BOARDDRAWER_H
#include <raylib.h>
#include "DataType.h"
#include "Player/IPlayer.h"

extern const float Board_Size;
extern const float Margin;
extern const int LineThick;
extern const int PieceSize;
extern const int GridSize;
extern IPlayer* Players[2];

//负责绘制棋盘和棋子
class BoardDrawer {
private:
    static void ExchangePlayer();
public:
    static void Restart();
    static int GetSteps();
    static void ResetStep();
    static void RegretAStep(int stepCount);
    static void Round(int sleepTime=0);
    //绘制棋盘背景
    static void DrawBackground();
    //根据MapData绘制棋子
    static void DrawPieces();
    //到底是谁在赢这个游戏
    static PieceStatus  IfWined(bool& drew);
};


#endif //C2023_CHALLENGE_BOARDDRAWER_H
