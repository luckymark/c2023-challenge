//
// Created by cz241 on 11/3/2023.
//

#ifndef C2023_CHALLENGE_DATATYPE_H
#define C2023_CHALLENGE_DATATYPE_H

#include <string>
#include <stack>
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
    [[nodiscard]]
    bool EmptyInMap(const ChessMap& map) const{
        return map[x][y]==PieceStatus::None;
    }
    [[nodiscard]]
    bool EqualInMap(const Point& p,const ChessMap& map) const{
        return map[x][y]==map[p.x][p.y];
    }
    [[nodiscard]]
    bool EqualInMap(PieceStatus status,const ChessMap& map)const {
        return map[x][y]==status;
    }
};
extern stack<Point> StepHistory;

#endif //C2023_CHALLENGE_DATATYPE_H
