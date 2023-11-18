#include "ChessTreeRobot.h"
#include "IPlayer.h"
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;
/*
 * Design:
 * 两个步骤：
 * Step1:检索几个常见的模型,预计我方和对手可能的下一步
 * Step2:搜索博弈树，预算分数
 * Step3:返回最高分数的点
*/
static vector<ChessModel> CheckModel(const ChessMap& map);
static vector<ChessModel> RankModel(const vector<ChessModel>& models);
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
    auto list= CheckModel(MapData);
    //region 没有匹配到模型，随便下
    if(list.empty()){
        cout<<"RANDOM  "<<list.size()<<endl;
        return (new RandomRobot())->NextStep();
    }
    //endregion
    //region 调试信息
    for(const auto& model:list){
        cout<<"-----------------"<<endl;
        cout<<"Whose: "<<(model.whose==PieceStatus::Black?"Black":"White")<<endl;
        cout<<"Model: "<<(model.type==ModelType::H4?"H4":(model.type==ModelType::H3?"H3":"M2"))<<endl;
        cout<<"Ava: ";
        for(auto p:model.ava)
            cout<<p.x<<" "<<p.y<<"   ";
        cout<<endl;
        cout<<"Points: ";
        for(auto p:model.points)
            cout<<p.x<<" "<<p.y<<"   ";
        cout<<endl;
    }
    //endregion
    //region 评估当前局面：
    int score=ChessTree::Evaluate(this->PlayerColor,MapData);
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

    if(this->EnableTreeSearch) {
        //region 搜索博弈树，预算分数
        auto tree = ChessTree::GenerateTree(6, this->PlayerColor);
        auto result = ChessTree::AlphaBetaSearch(tree);
        //endregion

        return result->point;
    }else return list[0].ava[0];
}

//按照优先等级排列Model
static vector<ChessModel> RankModel(const vector<ChessModel>& models){
    ModelType seniorType=ModelType::M2;
    for(const auto& model:models){
        if(model.type>seniorType){
            seniorType=model.type;
        }
    }
    vector<ChessModel> result;
    while(1) switch(seniorType){
        case ModelType::H4:
            for(const auto& item:models){
                if(item.type==ModelType::H4)
                    result.push_back(item);
                else if(item.type==ModelType::H3)
                    seniorType=ModelType::H3;
            }
                if(seniorType==ModelType::H4)
                    return result;
            break;
        case ModelType::H3:
            for(const auto& item:models){
                if(item.type==ModelType::H3)
                    result.push_back(item);
                else if(item.type==ModelType::M2)
                    seniorType=ModelType::M2;
            }
            if(seniorType==ModelType::H3)
                return result;
            break;
            default:
                for(const auto& item:models){
                    if(item.type==ModelType::M2)
                        result.push_back(item);
                }
                return result;
                break;
    }


}
//检索双方符合的模型，预判可能的步骤
static vector<ChessModel> CheckModel(const ChessMap& map){
    vector<ChessModel> result;
    for(int x=0;x<15;x++) {
        for (int y = 0; y < 15; y++) {
            //endregion
            //region 检索模型
            auto Check=[&](vector<Point>& p,ModelType type,int rules[][5],int rulesCount){

                //如果五个点为空则退出
                bool empty=true;
                for(int i=0;i<5;i++){
                    if(!p[i].EmptyInMap(map)){
                        empty= false;
                        break;
                    }
                }
                if(empty)return;

                ChessModel Model;
                Model.type=type;
                vector<Point> ava,points;

                //匹配模型类型
                //规则示例：01110，其中0表示空，1表示有子且相等
                //相等子是谁的
                PieceStatus owner=PieceStatus::None;
                auto detect=[&]() {
                    for (int i = 0; i < rulesCount; i++) {
                        bool match = true;
                        for (int j = 0; j < 5; j++) {
                            if (rules[i][j] == 1) {
                                if (p[j].EmptyInMap(map)) {
                                    match = false;
                                    break;
                                }
                                if (owner == PieceStatus::None) {
                                    owner = map[p[j].x][p[j].y];
                                } else {
                                    if (!p[j].EqualInMap(owner, map)) {
                                        match = false;
                                        break;
                                    }
                                }
                            }
                            else if (rules[i][j] == 0) {
                                if (!p[j].EmptyInMap(map)) {
                                    match = false;
                                    break;
                                }
                            }
                        }

                        if (match) {
                            //优先记录与rules中1靠近的空子坐标：
                            for (int j = 0; j < 5; j++) {
                                if (rules[i][j] == 0) {
                                    //如果已经存在则不重复添加
                                    bool found = false;
                                    for(const auto& point:ava)
                                        if(point.x==p[j].x&&point.y==p[j].y){
                                            found=true;
                                            break;
                                        }
                                    if(found)continue;

                                    if((j<4&&rules[i][j+1]==1)||(j>0&&rules[i][j-1]==1))
                                        ava.insert(ava.begin(),p[j]);
                                    else ava.push_back(p[j]);
                                }else if(type==ModelType::Win){
                                    ava.push_back(p[j]);
                                }
                            }
                        }
                    }
                };
                detect();
                if(ava.empty()) {
                    reverse(p.begin(), p.end());
                    detect();
                }


                if(!ava.empty()){
                    for(int i=0;i<5;i++)
                        points.push_back(p[i]);
                    Model.whose=owner;
                    Model.ava=ava;
                    Model.points=points;
                    result.push_back(Model);
                }

            };
            auto CheckWin=[&](vector<Point>& plist){
                //匹配五子连珠
                int ruleWin[1][5]={{1,1,1,1,1}};
                Check(plist,ModelType::H4,ruleWin,1);
            };
            auto CheckH4=[&](vector<Point>& plist){
                int ruleH4[4][5]={{1,1,1,1,0},
                                  {1,1,1,0,1},
                                  {1,1,0,1,1},
                                  {0,1,1,1,0}};
                Check(plist,ModelType::H4,ruleH4,4);
            };
            auto CheckH3=[&](vector<Point>& plist){
                //匹配活三和眠三
                int ruleH3[4][5]={{1,1,1,0,2},
                                  {1,0,1,1,0},
                                  {0,1,0,1,1},
                                  {1,0,1,0,1}};
                Check(plist,ModelType::H3,ruleH3,4);
            };
            auto CheckM2=[&](vector<Point>& plist){
                //匹配眠二
                int ruleM2[5][5]={{1,1,0,2,2},
                                  {0,1,0,1,0},
                                  {1,0,0,1,0},
                                  {1,1,0,2,2},
                                  {1,0,1,0,2}};
                Check(plist,ModelType::M2,ruleM2,5);
            };
           //endregion
           vector<vector<Point>> region;
            //region 遍历所有可能的五个点
            if(y<=10) {
                //取横向
                vector<Point> p = { {x, y}, {x, y + 1},  {x, y + 2}, {x, y + 3},  {x, y + 4}};
                region.push_back(p);
            }
            if(x<=10) {
                //取纵向
                vector<Point> p = { {x, y}, {x+1, y},  {x+2, y}, {x+3, y},  {x+4, y}};
                region.push_back(p);
            }
            if(x<=10&&y<=10) {
                //取左上到右下
                vector<Point> p = { {x, y}, {x+1, y + 1},  {x+2, y + 2}, {x+3, y + 3},  {x+4, y + 4}};
                region.push_back(p);
            }
            if(x>=4&&y<=10) {
                //取左下到右上
                vector<Point> p = { {x, y}, {x-1, y + 1},  {x-2, y + 2}, {x-3, y + 3},  {x-4, y + 4}};
                region.push_back(p);
            }
            //endregion
            for (auto &item: region) {
                CheckWin(item);
                CheckH4(item);
                CheckH3(item);
                CheckM2(item);
            }

        }
    }
    return RankModel(result);
}

int ChessTree::Evaluate(PieceStatus player,const ChessMap& map){
    auto mlist=CheckModel(map);
    int H4=0,H3=0,M2=0;
    int cH4=0,cH3=0,cM2=0;
    for(const auto& model:mlist){
        float p=1;
        if(model.whose!=player)
            p=-1.5;
        switch (model.type) {
            case ModelType::Win:
                return INT_MAX*p;
            case ModelType::H4:
                H4+=1000*p;
                cH4++;
                break;
            case ModelType::H3:
                H3+=100*p;
                cH3++;
                break;
            case ModelType::M2:
                M2+=p;
                cM2++;
                break;
            default:
                break;
        }
    }
    //求平均
    if(cH4!=0)
        H4/=cH4;
    if(cH3!=0)
        H3/=cH3;
    if(cM2!=0)
        M2/=cM2;
    int score=H4+H3+M2;
    return score;
}

PieceStatus Opponent(PieceStatus status){
    return status==PieceStatus::Black?PieceStatus::White:PieceStatus::Black;
}

ChessTree* ChessTree::GenerateTree(int depth, PieceStatus player) {
    auto* tree=new ChessTree();
    tree->maxDepth=depth;
    tree->root=new ChessNode();
    tree->root->map=&MapData;
    tree->root->score=Evaluate(player,MapData);
    tree->root->depth=0;
    tree->root->parent= nullptr;
    stack<ChessNode*> parents;
    parents.push(tree->root);
    //第一层节点由对手下产生
    PieceStatus nodePlayer=Opponent(player);
    tree->root->whose=nodePlayer;
    for(int i=1;i<depth;i++){
        //第i+1层节点，由CheckModel给出我方可走的点，预判对手可走点
        //对每个点，生成一个节点，计算分数
        nodePlayer=Opponent(nodePlayer);
        ChessNode* parent;
        while(!parents.empty()) {
            //上一层的节点作为父节点(多个)
            parent = parents.top();
            auto list = CheckModel(*parent->map);
            vector<Point> avaPoints;
            int count=0;
            for (const auto &item: list) {
                //该层对局玩家可能走的点
                for (const auto &p: item.ava) {
                    //如果该点已经存在，则不重复添加
                    bool found = false;
                    for (const auto &point: avaPoints)
                        if (point.x == p.x && point.y == p.y) {
                            found = true;
                            break;
                        }
                    if (found)continue;
                    avaPoints.push_back(p);
                    count++;
                }
                if(count>=5)
                    break;
            }
            if(count==0)avaPoints.push_back((new RandomRobot())->NextStep());
            //生成子节点
            for(auto p:avaPoints){
                auto node = new ChessNode();
                node->depth = i;
                node->parent = parent;
                node->point=p;
                ChessMap newMap;
                std::copy(&(*parent->map)[0][0], &(*parent->map)[0][0] + 15 * 15, &newMap[0][0]);
                newMap[p.x][p.y] = nodePlayer;
                //只生成节点，估分由alpha-beta剪枝算法计算
                //node->score = Evaluate(player, newMap);
                node->score=0;
                node->map = &newMap;
                //该层节点玩家
                node->whose = nodePlayer;
                //将节点加入父节点的子节点列表
                parent->children.push_back(node);
            }
            parents.pop();
        }
        //将第i+1层节点作为父节点，继续生成第i+2层节点
        for(const auto& node:parent->children)
            parents.push(node);
    }
    return tree;
}

void ShowTree(ChessTree *tree) {
    auto root=tree->root;
    stack<ChessNode*> parents;
    parents.push(root);
    for(int i=0;i<tree->maxDepth;i++) {
        ChessNode* parent;
        while (!parents.empty()) {
            parent = parents.top();
            for (const auto &node: parent->children) {
                cout << "Depth: " << node->depth << "  Whose: " <<(node->whose==PieceStatus::Black?"Black":"White")<<" Point:"<<node->point.x<<","<<node->point.y << endl;
            }
            parents.pop();
        }
        cout<<"-----------------"<<endl;
        for (const auto &node: parent->children)
            parents.push(node);
    }
}

ChessNode* ChessTree::AlphaBetaSearch(ChessTree *tree){
    ChessNode* result;
    ShowTree(tree);
    auto root=tree->root;
    ChessNode* parent=root;
    //root节点是由对手下的，以下搜索应该利于我方：
    //深度优先搜索，直到最底层节点
    PieceStatus benefitWhom= Opponent(root->whose);
    while(true) {
        int tempDepth=parent->depth;
        while (!parent->children.empty()) {
            for(int k=0;k<parent->children.size();k++) {
                auto node = parent->children[k];
                //如果该节点已经计算过分数
                if (node->score != 0){
                    //如果该节点局面为我方所下，则找出最小分数节点
                    if(node->whose==benefitWhom){
                        if(k>0){
                            //如果上一个节点分数小于此节点，则剪去该节点
                            if(parent->children[k-1]->score<node->score) {
                                parent->children.erase(parent->children.begin() + k);
                            }else{
                                //否则剪去上一个节点
                                parent->children.erase(parent->children.begin() + k-1);
                            }
                            k--;
                            continue;
                        }
                    }
                    else{
                        //如果该节点局面为对手所下，则找出最大分数节点
                        if(k>0){
                            //如果上一个节点分数大于此节点，则剪去该节点
                            if(parent->children[k-1]->score>node->score) {
                                parent->children.erase(parent->children.begin() + k);
                            }else{
                                //否则剪去上一个节点
                                parent->children.erase(parent->children.begin() + k-1);
                            }
                            k--;
                            continue;
                        }
                    }
                }
                else { parent = node; break; }
            }
            if(tempDepth==parent->depth)
                break;
        }

        if(tempDepth==parent->depth){
            //该层节点估分完毕
            //更新父节点分数
            parent->score=parent->children[0]->score*(-1);
            //如果到达根节点，则退出while循环
            if(parent->depth==0){
                result=parent->children[0];
                break;
            }
            parent=parent->parent;
            //不是根节点，则继续向上一层
            continue;
        }

        //到达最底层节点，取同父节点下的所有子节点
        ChessNode *TopScored = parent;
        for (auto &child: parent->parent->children) {
            //计算所有子节点分数，根据利于该局玩家的规则估分
            int s = ChessTree::Evaluate(child->whose, *child->map);
            child->score = s;
            //该局为我方所下产生，则父节点为对手，我方的最小分数方向是对方的最大分数方向
            if (child->whose == benefitWhom) {
                if (TopScored->score > child->score)
                    TopScored = child;
            } else {
                //该局为对手所下产生，则父节点为我方，对方的最大分数方向是我方的最小分数方向
                if (TopScored->score < child->score)
                    TopScored = child;
            }
        }
        //更新父节点分数
        parent->parent->score = TopScored->score * (-1);

        //走向上一层
        parent = parent->parent->parent;
    }
    ShowTree(tree);
    delete tree;
    return result;
}
