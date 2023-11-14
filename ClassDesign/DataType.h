//
// Created by cz241 on 11/3/2023.
//

#ifndef C2023_CHALLENGE_DATATYPE_H
#define C2023_CHALLENGE_DATATYPE_H

#include <string>
using namespace std;

enum class PieceStatus {
    None,
    Black,
    White
};
typedef PieceStatus ChessMap[15][15];
extern ChessMap MapData;
extern PieceStatus CurrentPlayer;

struct Point{
    int x,y;
    bool operator ==(const Point& p) const{
        return MapData[x][y]==MapData[p.x][p.y];
    }
    bool operator ==(const PieceStatus status) const{
        return MapData[x][y]==status;
    }
    bool operator !=(const Point& p) const{
        return MapData[x][y]!=MapData[p.x][p.y];
    }
    bool operator !=(const PieceStatus status) const{
        return MapData[x][y]!=status;
    }
};

#endif //C2023_CHALLENGE_DATATYPE_H
