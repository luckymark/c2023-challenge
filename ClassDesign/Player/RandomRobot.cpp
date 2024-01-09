//
// Created by cz241 on 11/3/2023.
//
//
#include "IPlayer.h"
#include <random>
#include <ctime>

Point RandomRobot::NextStep() {
    int x, y;
    //在上一点周围生成随机点
    Point lastPoint;
    if(!StepHistory.empty())
        lastPoint=StepHistory.top();
    else return {7,7};
    std::default_random_engine e;
    e.seed(time(0));
    for(int range=1;range<=14;range++) {
        int count=0;
        do {
            std::uniform_int_distribution<int> ux(lastPoint.x-range,lastPoint.x+range);
            std::uniform_int_distribution<int> uy(lastPoint.y-range,lastPoint.y+range);
            x = ux(e);
            y = uy(e);
            if(count++>10) break;
        } while (x < 0 || x >= 15 || y < 0 || y >= 15 || !Point{x, y}.EmptyInMap(MapData));
        if(x > 0 && x < 15 && y > 0 && y < 15 && Point{x, y}.EmptyInMap(MapData))
            break;
    }
    if(x < 0 || x >= 15 || y < 0 || y >= 15 || !Point{x, y}.EmptyInMap(MapData)){
        for(int i=0;i<15;i++)
            for(int j=0;j<15;j++)
                if(Point{i,j}.EmptyInMap(MapData))
                    return {i,j};
    }
    return {x,y};
}



