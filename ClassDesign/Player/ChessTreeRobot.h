//
// Created by cz241 on 11/14/2023.
//

#ifndef C2023_CHALLENGE_CHESSTREEROBOT_H
#define C2023_CHALLENGE_CHESSTREEROBOT_H
#include "../DataType.h"
#include <vector>
using namespace std;
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

enum class ModelType{
    H4,H3,M3,H2,M2
};

class ChessModel{
public:
    //模型类型
    ModelType type;
    //符合该模型的所有点坐标
    vector<Point> points;
    //空子坐标
    vector<Point> ava;
};

#endif //C2023_CHALLENGE_CHESSTREEROBOT_H
