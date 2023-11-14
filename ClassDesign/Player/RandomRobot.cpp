//
// Created by cz241 on 11/3/2023.
//
//
#include "IPlayer.h"

Point RandomRobot::NextStep() {
    int x=rand()%15;
    int y=rand()%15;
    while(MapData[x][y]!=PieceStatus::None){
        x=rand()%15;
        y=rand()%15;
    }
    return {x,y};
}



