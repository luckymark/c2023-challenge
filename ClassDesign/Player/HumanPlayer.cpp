#include "IPlayer.h"
#include <raylib.h>
#include "../BoardDrawer.h"

Point HumanPlayer::NextStep()
{
    Vector2 mousePos=GetMousePosition();
    int x=(mousePos.x)/GridSize;
    int y=(mousePos.y)/GridSize;
    DrawCircle(Margin+x*GridSize,Margin+y*GridSize,PieceSize-5,CurrentPlayer==PieceStatus::Black?BLACK:WHITE);
    //绘制当前玩家：
    string current= "CurrentPlayer: ";
    current.append(CurrentPlayer==PieceStatus::Black?"Black":"White");
    DrawText(current.c_str(),20,Board_Size+40,20,BLACK);
    //响应鼠标点击：
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        if(x>=0&&x<15&&y>=0&&y<15) {
            if (MapData[x][y] == PieceStatus::None) {
                return {x, y};
            }
        }
    }
    return {-1,-1};
}