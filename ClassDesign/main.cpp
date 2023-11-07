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

//defined at DataTypes.h
PieceStatus MapData[15][15]={PieceStatus::None};
PieceStatus CurrentPlayer=PieceStatus::Black;

int main(){
    InitWindow(Board_Size+60,Board_Size+90,"我不会写五子棋");
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(SKYBLUE);
        //绘制棋盘背景：
        BoardDrawer::DrawBackground();
        //绘制棋子：
        BoardDrawer::DrawPieces();
        //绘制当前玩家并响应鼠标事件：
        BoardDrawer::MouseEvent();

        PieceStatus winner=BoardDrawer::Win();
        BoardDrawer::OnWined(winner);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}