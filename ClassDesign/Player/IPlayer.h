#ifndef C2023_CHALLENGE_IPLAYER_H
#define C2023_CHALLENGE_IPLAYER_H
//Player的抽象接口
#include "../DataType.h"

class IPlayer
{
public:
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
#endif