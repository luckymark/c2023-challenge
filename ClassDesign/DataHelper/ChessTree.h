//
// Created by cz241 on 11/21/2023.
//

#ifndef C2023_CHALLENGE_CHESSTREE_H
#define C2023_CHALLENGE_CHESSTREE_H


#include <vector>
#include "DataType.h"

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
    //根据现有局面展开树
    void GenerateTree(int depth,PieceStatus player);
    //搜索最佳落子点
    [[nodiscard]] ChessNode* AlphaBetaSearch()const;
    void ShowTree()const;
    //评估对player一方的分数
    int (*Evaluator)(PieceStatus player, const ChessMap& map);
    //获取可走点
    vector<Point> (*AvaPointGenerator)(const ChessMap& map);
    ChessNode* root;
    int maxDepth;
};

#endif //C2023_CHALLENGE_CHESSTREE_H
