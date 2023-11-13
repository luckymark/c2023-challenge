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
};
//博弈树的节点
class ChessNode{
public:
    Point lastPoint;
    int score;
    int depth;
    ChessNode* last;
    ChessNode* next;
    ChessMap map;
};

class ChessTree{

};

#endif //C2023_CHALLENGE_DATATYPE_H
