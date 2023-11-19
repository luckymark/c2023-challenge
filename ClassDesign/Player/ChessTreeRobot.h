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
    ChessMap* map; // 棋盘状态
    Point point;
    int score; // 评分
    int depth; // 深度
    PieceStatus whose; // 轮到谁下
    ChessNode* parent; // 父节点
    vector<ChessNode*> children; // 子节点
};

class ChessTree{
public:
    //评估对player一方的分数
    static int Evaluate(PieceStatus player,const ChessMap& map);
    //根据现有局面展开树
    static ChessTree* GenerateTree(int depth,PieceStatus player);
    //搜索最佳落子点
    static ChessNode* AlphaBetaSearch(ChessTree* tree);
    ChessNode* root;
    int maxDepth;
};

enum class ModelType{
    M2,H3,Cube2,Cube3,M4,Cube4,H4,Win
};

class ChessModel{
public:
    //模型类型
    ModelType type;
    //符合该模型的所有点坐标
    vector<Point> points;
    //是谁的模型
    PieceStatus whose;
    //空子坐标
    vector<Point> ava;
};

#endif //C2023_CHALLENGE_CHESSTREEROBOT_H
