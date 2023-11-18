//
// Created by cz241 on 11/3/2023.
//
//
#include "IPlayer.h"

Point RandomRobot::NextStep() {
    int x, y;
    //在上一点周围生成随机点
    Point lastPoint;
    if(!StepHistory.empty())
        lastPoint=StepHistory.top();
    else lastPoint={7,7};
    do {
        x = lastPoint.x + rand() % 3 - 1;
        y = lastPoint.y + rand() % 3 - 1;
    }while(x<0||x>=15||y<0||y>=15||!Point{x,y}.EmptyInMap(MapData));

    return {x,y};
}



