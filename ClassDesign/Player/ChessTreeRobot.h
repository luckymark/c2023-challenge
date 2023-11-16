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
public:
    //评估节点对局面的分数
    static int Evaluate(ChessNode* node);

};

enum class ModelType{
    M2=0,H3=1,H4=2
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
