//
// Created by cz241 on 11/3/2023.
//
#include "BoardDrawer.h"

//defined at BoardDrawer.h
const float Board_Size=840;
const float Margin =20.0f;
const int LineThick=2;
const int PieceSize =20;
const int GridSize =  60;

//defined at DataType.h
ChessMap MapData={PieceStatus::None};
//黑子先手
PieceStatus CurrentPlayer=PieceStatus::Black;
//玩家列表
IPlayer *Player_Black,*Player_White;

int main(){
    InitWindow(Board_Size+60,Board_Size+90,"我不会写五子棋");
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    //加载玩家：
    Player_Black=new HumanPlayer();
    Player_White=new RandomRobot();

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(SKYBLUE);
        //绘制棋盘背景：
        BoardDrawer::DrawBackground();
        //绘制棋子：
        BoardDrawer::DrawPieces();
        //进行一轮博弈
        BoardDrawer::Round();
        //判断有无胜出
        BoardDrawer::IfWined();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}