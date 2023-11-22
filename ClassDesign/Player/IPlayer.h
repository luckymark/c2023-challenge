#ifndef C2023_CHALLENGE_IPLAYER_H
#define C2023_CHALLENGE_IPLAYER_H
//Player的抽象接口
//定义了玩家的基本行为
//所有玩家于此定义
#include "../DataHelper/DataType.h"

class IPlayer
{
public:
    PieceStatus PlayerColor;
    virtual Point NextStep() = 0;
};

class RandomRobot : public IPlayer
{
public:
    Point NextStep() override;
};
class HumanPlayer : public IPlayer
{
public:
    Point NextStep() override;
};
class ChessTreeRobot : public IPlayer
{
    public:
    Point NextStep() override;
    bool EnableTreeSearch=true;
};

#endif