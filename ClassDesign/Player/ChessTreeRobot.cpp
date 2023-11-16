#include "ChessTreeRobot.h"
#include "IPlayer.h"
#include <vector>
#include <iostream>
using namespace std;
/*
 * Design:
 * 两个步骤：
 * Step1:检索几个常见的模型
 * Step2:搜索博弈树，预算分数
*/
static vector<ChessModel> CheckModel();

Point ChessTreeRobot::NextStep() {
    //检索几个常见的模型
    auto list= CheckModel();
    //搜索博弈树，预算分数
    //返回最高分数的点
    system("cls");
    if(list.empty()){
        cout<<"RANDOM  "<<list.size()<<endl;
        return (new RandomRobot())->NextStep();
    }
    //调试信息
    for(auto model:list){
        cout<<"Model: "<<(model.type==ModelType::H4?"H4":model.type==ModelType::H3?"H3":"M2");
        cout<<"  Points: "<<model.points.size()<<endl;
        cout<<"Ava:  ";
        for(auto point:model.ava){
            cout<<"("<<point.x<<","<<point.y<<")  ";
        }
        cout<<"\n-----------------"<<endl;
    }
    //优先级：活四>眠四>活三>眠三>活二>眠二
    //优先级最高的模型
    ModelType seniorType=ModelType::M2;
    for(const auto& model:list){
        if(model.type>seniorType){
            seniorType=model.type;
        }
    }
    //输出SeniorType:
    cout<<"SeniorType: "<<(seniorType==ModelType::H4?"H4":seniorType==ModelType::H3?"H3":"M2")<<endl;
    for(const auto& model:list){
        if(model.type==seniorType){
            return model.ava[0];
        }
    }
}

static vector<ChessModel> CheckModel(){
    vector<ChessModel> result;
    for(int x=0;x<15;x++) {
        for (int y = 0; y < 15; y++) {
            ChessModel H4Model;
            H4Model.type=ModelType::H4;
            vector<Point> ava,points;

            ChessModel H3Model;
            H3Model.type=ModelType::H3;
            vector<Point> avaH3,pointsH3;

            ChessModel M2Model;
            M2Model.type=ModelType::M2;
            vector<Point> avaM2,pointsM2;

            auto CheckH4=[&](Point p1,Point p2,Point p3,Point p4,Point p5){
                //匹配活四和冲四
                //活四：若为己方则必胜
                //若为对方，能堵还是堵一下吧..
                //冲四：高威胁

                //如果五个点为空则退出
                if(p1==PieceStatus::None&&p2==PieceStatus::None&&p3==PieceStatus::None&&p4==PieceStatus::None&&p5==PieceStatus::None){
                    return;
                }
                //匹配活四类型
                //11110
                if(p1!=PieceStatus::None&&p1==p2&&p1==p3&&p1==p4&&p5==PieceStatus::None){
                    ava.push_back(p5);
                }
                //匹配四种冲四类型
                //11101
                if(p1!=PieceStatus::None&&p1==p2&&p1==p3&&p1==p5&&p4==PieceStatus::None){
                    ava.push_back(p4);
                }
                //11011
                if(p1!=PieceStatus::None&&p1==p2&&p1==p4&&p1==p5&&p3==PieceStatus::None){
                    ava.push_back(p3);
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
                //01110
                if(p2!=PieceStatus::None&&p2==p3&&p2==p4&&p1==PieceStatus::None&&p5==PieceStatus::None){
                    avaH3.push_back(p1);
                    avaH3.push_back(p5);
                }
                //1011
                if(p1!=PieceStatus::None&&p1==p3&&p1==p4&&p2==PieceStatus::None){
                    avaH3.push_back(p2);
                }

                //匹配眠三类型
                //01011
                if(p2!=PieceStatus::None&&p2==p4&&p2==p5&&p1==PieceStatus::None&&p3==PieceStatus::None){
                    avaH3.push_back(p3);
                    avaH3.push_back(p1);
                }
                //10011
                if(p1!=PieceStatus::None&&p1==p4&&p1==p5&&p2==PieceStatus::None&&p3==PieceStatus::None){
                    avaH3.push_back(p3);
                    avaH3.push_back(p2);
                }
                //10101
                if(p1!=PieceStatus::None&&p1==p3&&p1==p5&&p2==PieceStatus::None&&p4==PieceStatus::None){
                    avaH3.push_back(p2);
                    avaH3.push_back(p4);
                }

                if(!avaH3.empty()){
                    pointsH3.push_back(p1);
                    pointsH3.push_back(p2);
                    pointsH3.push_back(p3);
                    pointsH3.push_back(p4);
                    pointsH3.push_back(p5);
                }
            };
            auto CheckM2=[&](Point p1,Point p2,Point p3,Point p4,Point p5){
                //如果五个点为空则退出
                if(p1==PieceStatus::None&&p2==PieceStatus::None&&p3==PieceStatus::None&&p4==PieceStatus::None&&p5==PieceStatus::None){
                    return;
                }

                //001100
                if(p3!=PieceStatus::None&&p3==p4&&p1==PieceStatus::None&&p2==PieceStatus::None&&p5==PieceStatus::None){
                    avaM2.push_back(p1);
                    avaM2.push_back(p2);
                    avaM2.push_back(p5);
                }
                //01010
                if(p2!=PieceStatus::None&&p2==p4&&p1==PieceStatus::None&&p3==PieceStatus::None&&p5==PieceStatus::None){
                    avaM2.push_back(p1);
                    avaM2.push_back(p3);
                    avaM2.push_back(p5);
                }
                //10010
                if(p1!=PieceStatus::None&&p1==p4&&p2==PieceStatus::None&&p3==PieceStatus::None&&p5==PieceStatus::None){
                    avaM2.push_back(p2);
                    avaM2.push_back(p3);
                    avaM2.push_back(p5);
                }
                //00011
                if(p4!=PieceStatus::None&&p4==p5&&p1==PieceStatus::None&&p2==PieceStatus::None&&p3==PieceStatus::None){
                    avaM2.push_back(p3);
                    avaM2.push_back(p1);
                    avaM2.push_back(p2);
                }
                //00101
                if(p3!=PieceStatus::None&&p3==p5&&p1==PieceStatus::None&&p2==PieceStatus::None&&p4==PieceStatus::None){
                    avaM2.push_back(p2);
                    avaM2.push_back(p1);
                    avaM2.push_back(p4);
                }

                if(!avaM2.empty()){
                    pointsM2.push_back(p1);
                    pointsM2.push_back(p2);
                    pointsM2.push_back(p3);
                    pointsM2.push_back(p4);
                    pointsM2.push_back(p5);
                }
            };
            auto CheckAll=[&](Point p1,Point p2,Point p3,Point p4,Point p5){
                CheckH4(p1,p2,p3,p4,p5);
                CheckH4(p5,p4,p3,p2,p1);
                CheckH3(p1,p2,p3,p4,p5);
                CheckH3(p5,p4,p3,p2,p1);
                CheckM2(p1,p2,p3,p4,p5);
                CheckM2(p5,p4,p3,p2,p1);
            };
            if(y<=10) {
                //取横向五个点：
                Point l1 = {x, y}, l2 = {x, y + 1}, l3 = {x, y + 2}, l4 = {x, y + 3}, l5 = {x, y + 4};
                CheckAll(l1, l2, l3, l4, l5);
            }
            if(x<=10) {
                //取纵向五个点：
                Point u1 = {x, y}, u2 = {x + 1, y}, u3 = {x + 2, y}, u4 = {x + 3, y}, u5 = {x + 4, y};
                CheckAll(u1, u2, u3, u4, u5);
            }
            if(x<=10&&y<=10) {
                //取左上到右下五个点：
                Point lu1 = {x, y}, lu2 = {x + 1, y + 1}, lu3 = {x + 2, y + 2}, lu4 = {x + 3, y + 3}, lu5 = {x + 4,y + 4};
                CheckAll(lu1, lu2, lu3, lu4, lu5);
            }
            if(x>=4&&y<=10) {
                //取右上到左下五个点：
                Point ru1 = {x, y}, ru2 = {x - 1, y + 1}, ru3 = {x - 2, y + 2}, ru4 = {x - 3, y + 3}, ru5 = {x - 4,y + 4};
                CheckAll(ru1, ru2, ru3, ru4, ru5);
            }

            if(!ava.empty()) {
                H4Model.ava=ava;
                H4Model.points=points;
                result.push_back(H4Model);
            }
            else if(!avaH3.empty()) {
                H3Model.ava=avaH3;
                H3Model.points=pointsH3;
                result.push_back(H3Model);
            }
            else if(!avaM2.empty()) {
                M2Model.ava=avaM2;
                M2Model.points=pointsM2;
                result.push_back(M2Model);
            }

        }
    }
    return result;
}

int ChessTree::Evaluate(ChessNode *node) {

}