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
//记录每一步的历史
stack<Point> StepHistory;
//黑子先手
PieceStatus CurrentPlayer=PieceStatus::Black;
//玩家列表
IPlayer* Players[2];

int main(){
    InitWindow(Board_Size+60,Board_Size+90,"GobangCat");
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    //加载玩家：
    auto human=new HumanPlayer();
    human->PlayerColor=PieceStatus::Black;
    Players[0]=human;
    auto robot=new ChessTreeRobot();
   // robot->EnableTreeSearch=false;
    robot->PlayerColor=PieceStatus::White;
    Players[1]=robot;

    //是否有人胜出：
    bool wined=false;

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(SKYBLUE);
        //绘制棋盘背景：
        BoardDrawer::DrawBackground();
        //显示上一步
        BoardDrawer::HighlightLastPoint();
        //绘制棋子：
        BoardDrawer::DrawPieces();
        //进行一轮博弈
        if(!wined) {
            BoardDrawer::Round();
        }
        //判断有无胜出
        bool drew=false;
        auto winner=BoardDrawer::IfWined(drew);
        if(winner!=PieceStatus::None || drew){
            wined=true;
            string win=drew?"No one":(winner==PieceStatus::Black?"Black":"White");
            win.append(" Wined in "+to_string(BoardDrawer::GetSteps())+" steps!");
            DrawText(win.c_str(),20,Board_Size+40,20,BLACK);
            DrawText("Press ENTER to restart",20,Board_Size+60,20,BLACK);
            if(IsKeyPressed(KEY_ENTER)){
                wined=false;
                BoardDrawer::Restart();
            }
        }

        //悔棋
        if(IsKeyPressed(KEY_UP)){
            BoardDrawer::RegretAStep(2);
            if(wined)wined=false;
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}