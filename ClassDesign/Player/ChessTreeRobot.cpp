#include "ChessTreeRobot.h"
#include "IPlayer.h"
#include <vector>
using namespace std;
/*
 * Design:
 * 采用多线程：
 * Thread 1: 检索几个常见的模型
 * Thread 2: 搜索博弈树，预算分数
*/
static vector<ChessModel> CheckModel();

Point ChessTreeRobot::NextStep() {
    //检索几个常见的模型
    auto list= CheckModel();
    //搜索博弈树，预算分数
    //返回最高分数的点
    if(list.empty()){
        return (new RandomRobot())->NextStep();
    }
    return list[0].ava[0];
}

static vector<ChessModel> CheckModel(){
    vector<ChessModel> result;
    for(int x=0;x<15;x++) {
        for (int y = 0; y < 15; y++) {
            ChessModel model;
            model.type=ModelType::H4;
            vector<Point> ava,points;
            auto CheckH4=[&](Point p1,Point p2,Point p3,Point p4,Point p5){
                //匹配活四和冲四
                //活四：若为己方则必胜
                //若为对方，能堵还是堵一下吧..
                //冲四：高威胁

                //如果五个点为空则退出
                if(p1==PieceStatus::None&&p2==PieceStatus::None&&p3==PieceStatus::None&&p4==PieceStatus::None&&p5==PieceStatus::None){
                    return;
                }
                //匹配两种活四类型
                //11110
                if(p1==p2&&p1==p3&&p1==p4&&p5==PieceStatus::None){
                    ava.push_back(p5);
                }
                //01111
                if(p2==p3&&p2==p4&&p2==p5&&p1==PieceStatus::None){
                    ava.push_back(p1);
                }

                //匹配四种冲四类型
                //11101
                if(p1==p2&&p1==p3&&p1==p5&&p4==PieceStatus::None){
                    ava.push_back(p4);
                }
                //11011
                if(p1==p2&&p1==p4&&p1==p5&&p3==PieceStatus::None){
                    ava.push_back(p3);
                }
                //10111
                if(p1==p3&&p1==p4&&p1==p5&&p2==PieceStatus::None){
                    ava.push_back(p2);
                }

                if(!ava.empty()){
                    points.push_back(p1);
                    points.push_back(p2);
                    points.push_back(p3);
                    points.push_back(p4);
                    points.push_back(p5);
                }
            };
            auto CheckH3=[&](Point p1,Point p2,Point p3,Point p4,Point p5){
                //匹配活三和眠三
                //如果五个点为空则退出
                if(p1==PieceStatus::None&&p2==PieceStatus::None&&p3==PieceStatus::None&&p4==PieceStatus::None&&p5==PieceStatus::None){
                    return;
                }
                //匹配两种活三类型
                //11100
                if(p1==p2&&p1==p3&&p4==PieceStatus::None&&p5==PieceStatus::None){
                    ava.push_back(p4);
                    ava.push_back(p5);
                }
                //10110
                if(p1==p3&&p1==p4&&p2==PieceStatus::None&&p5==PieceStatus::None){
                    ava.push_back(p2);
                    ava.push_back(p5);
                }

                //匹配眠三类型
                //01011
                if(p2==p4&&p2==p5&&p1==PieceStatus::None&&p3==PieceStatus::None){
                    ava.push_back(p1);
                    ava.push_back(p3);
                }
                //10011
                if(p1==p4&&p1==p5&&p2==PieceStatus::None&&p3==PieceStatus::None){
                    ava.push_back(p2);
                    ava.push_back(p3);
                }
                //10101
                if(p1==p3&&p1==p5&&p2==PieceStatus::None&&p4==PieceStatus::None){
                    ava.push_back(p2);
                    ava.push_back(p4);
                }

                if(!ava.empty()){
                    points.push_back(p1);
                    points.push_back(p2);
                    points.push_back(p3);
                    points.push_back(p4);
                    points.push_back(p5);
                }
            };
            auto CheckAll=[&](Point p1,Point p2,Point p3,Point p4,Point p5){
                CheckH3(p1,p2,p3,p4,p5);
                CheckH3(p5,p4,p3,p2,p1);
                CheckH4(p1,p2,p3,p4,p5);
                CheckH4(p5,p4,p3,p2,p1);
            };
            //取横向五个点：
            Point l1={x,y},l2={x,y+1},l3={x,y+2},l4={x,y+3},l5={x,y+4};
            CheckAll(l1,l2,l3,l4,l5);
            //取纵向五个点：
            Point u1={x,y},u2={x+1,y},u3={x+2,y},u4={x+3,y},u5={x+4,y};
            CheckAll(u1,u2,u3,u4,u5);
            //取左上到右下五个点：
            Point lu1={x,y},lu2={x+1,y+1},lu3={x+2,y+2},lu4={x+3,y+3},lu5={x+4,y+4};
            CheckAll(lu1,lu2,lu3,lu4,lu5);
            //取右上到左下五个点：
            Point ru1={x,y},ru2={x-1,y+1},ru3={x-2,y+2},ru4={x-3,y+3},ru5={x-4,y+4};
            CheckAll(ru1,ru2,ru3,ru4,ru5);

            if(!ava.empty()) {
                model.ava=ava;
                model.points=points;
                result.push_back(model);
            }
        }
    }
    return result;
}