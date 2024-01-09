//
// Created by cz241 on 11/21/2023.
//

#ifndef C2023_CHALLENGE_MODELCHECKER_H
#define C2023_CHALLENGE_MODELCHECKER_H

#include <vector>
#include "DataType.h"

enum class ModelType{
    M2,H3,Cube2,Cube3,M4,Cube4,H4,Win
};

class ChessModel{
public:
    static string GetModelName(ModelType type);
    //模型类型
    ModelType type;
    //符合该模型的所有点坐标
    vector<Point> points;
    //是谁的模型
    PieceStatus whose;
    //空子坐标
    vector<Point> ava;
};

class ModelChecker {
public:
    static int Evaluate(PieceStatus player,const ChessMap& map);
    static vector<Point> GetAvaPoints(const ChessMap& map);
    static vector<ChessModel> CheckModel(const ChessMap& map);
    static vector<ChessModel> RankModel(const vector<ChessModel>& models);
};

#endif //C2023_CHALLENGE_MODELCHECKER_H
