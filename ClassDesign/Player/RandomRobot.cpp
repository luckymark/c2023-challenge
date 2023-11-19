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
    else return {7,7};
    for(int range=1;range<=5;range++) {
        int count=0;
        do {
            x = lastPoint.x + rand() % (3*range) - 1;
            y = lastPoint.y + rand() % (3*range) - 1;
            if(count++>1000) break;
        } while (x < 0 || x >= 15 || y < 0 || y >= 15 || !Point{x, y}.EmptyInMap(MapData));
    }
    if(x < 0 || x >= 15 || y < 0 || y >= 15 || !Point{x, y}.EmptyInMap(MapData)){
        for(int i=0;i<15;i++)
            for(int j=0;j<15;j++)
                if(Point{i,j}.EmptyInMap(MapData))
                    return {i,j};
    }
    return {x,y};
}



