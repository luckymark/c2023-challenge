#include "IPlayer.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include "../DataHelper/ModelChecker.h"
#include "../DataHelper/ChessTree.h"

using namespace std;

/*
 * Design:
 * 两个步骤：
 * Step1:检索几个常见的模型,预计我方和对手可能的下一步
 * Step2:搜索博弈树，预算分数
 * Step3:返回最高分数的点
*/
vector<Point> AvaPointsOfOpponent;
int predictCount=0;

Point ChessTreeRobot::NextStep() {
    system("cls");
    //region 看一下模型能预判到对手多少点
    bool found = false;
    Point olast={-1,-1};
    if(!StepHistory.empty()) {
        olast = StepHistory.top();
        for (const auto &p: AvaPointsOfOpponent) {
            if (p.x == olast.x && p.y == olast.y) {
                predictCount++;
                found = true;
                break;
            }
        }
    }
    AvaPointsOfOpponent.clear();
    //endregion
    //检索几个常见的模型
    auto list= ModelChecker::CheckModel(MapData);
    //region 没有匹配到模型，随便下
    if(list.empty()){
        cout<<"RANDOM  "<<list.size()<<endl;
        return (new RandomRobot())->NextStep();
    }
    //endregion
    //region 调试信息
    cout<<"-------------Checked Model Count: "<<list.size()<<"-------------"<<endl;
    for(const auto& model:list){
        cout<<"Whose: "<<(model.whose==PieceStatus::Black?"Black":"White")<<endl;
        cout<<"Model: "<<ChessModel::GetModelName(model.type)<<endl;
        cout<<"Ava: ";
        for(auto p:model.ava) {
            cout << p.x << " " << p.y << "   ";
        }
        cout<<endl;
        cout<<"Points: ";
        for(auto p:model.points)
            cout<<p.x<<" "<<p.y<<"   ";
        cout<<endl;
    }
    //endregion
    //region 评估当前局面：
    int score=ModelChecker::Evaluate(this->PlayerColor,MapData);
    cout<<"Present Score: "<<score<<endl;
    //endregion
    //region 猜测对手
    if(found)
        cout<<"Predicted Opponent's Last Step: ("<<olast.x<<","<<olast.y<<") "<<predictCount<<" times!"<<endl;
    for(const auto &item:list)
        for(const auto& p:item.ava)
            AvaPointsOfOpponent.push_back(p);
    cout<<"Predicted Points Count: "<<AvaPointsOfOpponent.size()<<endl;
    //endregion
    if(this->EnableTreeSearch&&StepHistory.size()>=10) {
        //region 搜索博弈树，预算分数
        auto tree=new ChessTree();
        //装配估值器
        tree->Evaluator=ModelChecker::Evaluate;
        //装配可走点生成器
        tree->AvaPointGenerator=ModelChecker::GetAvaPoints;
        tree->GenerateTree(10, this->PlayerColor);
        auto result = tree->AlphaBetaSearch();
        delete tree;
        return result->point;
        //endregion
    }else return list[0].ava[0];
}