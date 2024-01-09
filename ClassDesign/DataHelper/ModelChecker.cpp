//
// Created by cz241 on 11/21/2023.
//

#include <iostream>
#include "ModelChecker.h"
#include "../Player/IPlayer.h"


vector<Point> ModelChecker::GetAvaPoints(const ChessMap& map){
    auto list = ModelChecker::CheckModel(map);
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
    if(count==0) {
        cout<<"Random ADD TO THE TREE!"<<endl;
        avaPoints.push_back((new RandomRobot())->NextStep());
    }
    return avaPoints;
}

//评估局面分数
int ModelChecker::Evaluate(PieceStatus player,const ChessMap& map){
    auto mlist=CheckModel(map);
    int H4=0,H3=0,M2=0;
    int cH4=0,cH3=0,cM2=0;
    vector<Point> Ava_Black,Ava_White;
    int Rep_Black=0,Rep_White=0;
    for(const auto& model:mlist){
        float p=1;
        if(model.whose!=player)
            p=-1.2;
        auto RepeatCheck=[](const Point& p,int& counter,vector<Point>& list,PieceStatus player){
            //如果该点已经存在，则不重复添加
            bool found = false;
            for (const auto &point: list)
                if (point.x == p.x && point.y == p.y) {
                    found = true;
                    break;
                }
            if (found) {
                counter++;
            }else list.push_back(p);
        };
        for(const auto& p:model.ava){
            if(model.whose==PieceStatus::Black){
                RepeatCheck(p,Rep_Black,Ava_Black,model.whose);
            }else RepeatCheck(p,Rep_White,Ava_White,model.whose);
        }
        switch (model.type) {
            case ModelType::Win:
                return 90000*p;
            case ModelType::H4:
                H4+=10000*p;
                cH4++;
                break;
            case ModelType::Cube4:
                H4+=1000*p;
                cH4++;
                break;
            case ModelType::M4:
                H4+=500*p;
                cH4++;
                break;
            case ModelType::Cube3:
                H4+=300*p;
                cH4++;
                break;
            case ModelType::H3:
                H3+=100*p;
                cH3++;
                break;
            case ModelType::Cube2:
                H4+=200*p;
                cH4++;
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
    if(player==PieceStatus::Black){
        score*=1.0+(float)Rep_Black/10.0;
    }else score*=1.0+(float)Rep_White/10.0;
    return score;
}

//按照优先等级排列Model
vector<ChessModel> ModelChecker::RankModel(const vector<ChessModel>& models){
    ModelType seniorType=ModelType::M2;
    for(const auto& model:models){
        if(model.type>seniorType){
            seniorType=model.type;
        }
    }
    vector<ChessModel> result;
    while(1) switch(seniorType){
            case ModelType::Win:
                for(const auto& item:models){
                    if(item.type==ModelType::Win)
                        result.push_back(item);
                }
                return result;
                break;
            case ModelType::H4:
                for(const auto& item:models){
                    if(item.type==ModelType::H4)
                        result.push_back(item);
                    else if(item.type==ModelType::Cube4)
                        seniorType=ModelType::Cube4;
                }
                if(seniorType==ModelType::H4)
                    return result;
                break;
            case ModelType::Cube4:
                for(const auto& item:models){
                    if(item.type==ModelType::Cube4)
                        result.push_back(item);
                    else if(item.type==ModelType::M4)
                        seniorType=ModelType::M4;
                }
                if(seniorType==ModelType::Cube4)
                    return result;
                break;
            case ModelType::M4:
                for(const auto& item:models){
                    if(item.type==ModelType::M4)
                        result.push_back(item);
                    else if(item.type==ModelType::Cube3)
                        seniorType=ModelType::Cube3;
                }
                if(seniorType==ModelType::M4)
                    return result;
                break;
            case ModelType::Cube3:
                for(const auto& item:models){
                    if(item.type==ModelType::Cube3)
                        result.push_back(item);
                    else if(item.type==ModelType::Cube2)
                        seniorType=ModelType::Cube2;
                }
                if(seniorType==ModelType::Cube3)
                    return result;
                break;
            case ModelType::Cube2:
                for(const auto& item:models){
                    if(item.type==ModelType::Cube2)
                        result.push_back(item);
                    else if(item.type==ModelType::H3)
                        seniorType=ModelType::H3;
                }
                if(seniorType==ModelType::Cube2)
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
vector<ChessModel> ModelChecker::CheckModel(const ChessMap& map){
    vector<ChessModel> result;
    for(int x=0;x<15;x++) {
        for (int y = 0; y < 15; y++) {
            //endregion
            //region 检索模型
            auto Check=[&](const vector<Point>& p,ModelType type,const vector<vector<int>>& rules){
                //如果五个点为空则退出
                bool empty=true;
                int pointCount=rules[0].size();
                for(int i=0;i<pointCount;i++){
                    if(!p[i].EmptyInMap(map)){
                        empty= false;
                        break;
                    }
                }
                if(empty)return;

                ChessModel Model;
                Model.type=type;
                vector<Point> ava,points;

                int rulesCount=rules.size();
                //匹配模型类型
                //规则示例：-101113，其中0表示空，1表示有子且相等，-1表示有子且不相等，2表示不匹配任何子，3表示优先落子
                //相等子是谁的
                PieceStatus owner=PieceStatus::None;
                auto detect=[&]() {
                    for (int i = 0; i < rulesCount; i++) {
                        bool match = true;
                        for (int j = 0; j < pointCount; j++) {
                            if (rules[i][j] == 1) {
                                if (p[j].EmptyInMap(map)) {
                                    match = false;
                                    break;
                                }
                                if (owner == PieceStatus::None) {
                                    owner = map[p[j].x][p[j].y];
                                }
                                if (!p[j].EqualInMap(owner, map)) {
                                    match = false;
                                    break;
                                }
                            }
                            else if(rules[i][j]==-1){
                                if (p[j].EmptyInMap(map)) {
                                    match = false;
                                    break;
                                }
                                if (owner == PieceStatus::None) {
                                    owner = Opponent(map[p[j].x][p[j].y]);
                                }
                                if (p[j].EqualInMap(owner, map)) {
                                    match = false;
                                    break;
                                }
                            }
                            else if (rules[i][j] == 0||rules[i][j]==3) {
                                if (!p[j].EmptyInMap(map)) {
                                    match = false;
                                    break;
                                }
                            }
                        }

                        if (match) {
                            for (int j = 0; j < pointCount; j++) {
                                if (rules[i][j] == 0||rules[i][j]==3) {
                                    //如果已经存在则不重复添加
                                    bool found = false;
                                    for(const auto& point:ava)
                                        if(point.x==p[j].x&&point.y==p[j].y){
                                            found=true;
                                            break;
                                        }
                                    if(found)continue;

                                    if(rules[i][j]==3/*||((j<4&&rules[i][j+1]==1)||(j>0&&rules[i][j-1]==1))*/)
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


                if(!ava.empty()){
                    for(int i=0;i<pointCount;i++)
                        points.push_back(p[i]);
                    Model.whose=owner;
                    Model.ava=ava;
                    Model.points=points;
                    result.push_back(Model);
                }

            };
            auto CheckCube=[&](const vector<vector<Point>>& p,ModelType type,const int rules[5]){
                //如果点全为空点则退出
                bool empty=true;
                for(const auto& points:p)
                    for(const auto& point:points){
                        if(!point.EmptyInMap(map)){
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
                bool match=true;
                for(int i=0;i<5;i++){
                    if(rules[i]==1){
                        if(p[0][i].EmptyInMap(map)||p[1][i].EmptyInMap(map)){
                            match=false;
                            break;
                        }
                        if(owner==PieceStatus::None){
                            owner=map[p[0][i].x][p[0][i].y];
                        }
                        if(!(p[0][i].EqualInMap(owner,map)&&p[1][i].EqualInMap(owner,map))){
                            match=false;
                            break;
                        }
                    }
                    else if(rules[i]==0){
                        if(!p[0][i].EmptyInMap(map)){
                            return;
                        }
                    }
                }
                if(match){
                    //只记录交点处的空子坐标(only)
                    for(int i=0;i<5;i++){
                        if(rules[i]==0){
                            ava.push_back(p[0][i]);
                            break;
                        }
                    }
                }

                if(!ava.empty()){
                    for(int px=0;px<2;px++) for(int i=0;i<5;i++)
                            points.push_back(p[px][i]);

                    Model.whose=owner;
                    Model.ava=ava;
                    Model.points=points;
                    result.push_back(Model);
                }
            };
            auto CheckWin=[&](vector<Point>& plist){
                //匹配五子连珠
                vector<vector<int>> ruleWin={{1,1,1,1,1}};
                Check(plist,ModelType::H4,ruleWin);
            };
            auto CheckCubeAll=[&](const vector<vector<Point>>& plist){
                //双向匹配
                //匹配双活四
                int ruleCube[5]={0,1,1,1,1};
                CheckCube(plist,ModelType::Cube4,ruleCube);
                //匹配双活三
                int ruleCubeH3[5]={0,1,1,1,2};
                CheckCube(plist,ModelType::Cube3,ruleCubeH3);
                //匹配双活二
                int ruleCubeM2[5]={0,1,1,2,2};
                CheckCube(plist,ModelType::Cube2,ruleCubeM2);
            };
            auto CheckH4=[&](vector<Point>& plist){
                vector<vector<int>> ruleH4={{1,1,1,1,0},
                                            {1,1,1,0,1},
                                            {1,1,0,1,1}};
                Check(plist,ModelType::H4,ruleH4);
            };
            auto CheckM4=[&](vector<Point>& plist){
                //匹配眠四
                vector<vector<int>> ruleM4={{0,1,1,1,0},
                                            {1,3,1,1,0}};
                Check(plist,ModelType::M4,ruleM4);
            };
            auto CheckH3=[&](vector<Point>& plist){
                //匹配活三和眠三
                vector<vector<int>> ruleH3={{0,3,1,1,1,-1},
                                            {0,1,3,1,1,-1},
                                            {0,1,1,3,1,-1},
                                            {1,0,0,1,1,2},
                                            {1,0,1,0,1,2},
                                            {-1,0,1,1,1,0,-1}};
                Check(plist,ModelType::H3,ruleH3);
            };
            auto CheckM2=[&](vector<Point>& plist){
                //匹配眠二
                vector<vector<int>> ruleM2={{0,3,1,1,0,0},
                                            {0,1,0,1,0,2},
                                            {2,1,0,0,1,2},
                                            {0,0,3,1,1,-1},
                                            {0,0,1,3,1,-1},
                                            {0,1,3,3,1,-1},
                                            {1,3,0,3,1,2}};
                Check(plist,ModelType::M2,ruleM2);
            };
            //endregion
            vector<vector<Point>> region;
            //region 遍历所有可能的五个点
            if(y<=10) {
                //取纵向+
                vector<Point> p = { {x, y}, {x, y + 1},  {x, y + 2}, {x, y + 3},  {x, y + 4}};
                if(y<=9)
                    p.push_back({x,y+5});
                else p.push_back({-1,-1});
                region.push_back(p);
            }
            if(y>=4){
                //取纵向-
                vector<Point> p = { {x, y}, {x, y - 1},  {x, y - 2}, {x, y - 3},  {x, y - 4}};
                if(y>=5)
                    p.push_back({x,y-5});
                else p.push_back({-1,-1});
                region.push_back(p);
            }
            if(x<=10) {
                //取横向+
                vector<Point> p = { {x, y}, {x+1, y},  {x+2, y}, {x+3, y},  {x+4, y}};
                if(x<=9)
                    p.push_back({x+5,y});
                else p.push_back({-1,-1});
                region.push_back(p);
            }
            if(x>=4) {
                //取横向-
                vector<Point> p = { {x, y}, {x-1, y},  {x-2, y}, {x-3, y},  {x-4, y}};
                if(x>=5)
                    p.push_back({x-5,y});
                else p.push_back({-1,-1});
                region.push_back(p);
            }
            if(x<=10&&y<=10) {
                //取左上到右下
                vector<Point> p = { {x, y}, {x+1, y + 1},  {x+2, y + 2}, {x+3, y + 3},  {x+4, y + 4}};
                if(x<=9&&y<=9)
                    p.push_back({x+5,y+5});
                else p.push_back({-1,-1});
                region.push_back(p);
            }
            if(x>=4&&y>=4) {
                //取左上到右下
                vector<Point> p = { {x, y}, {x-1, y - 1},  {x-2, y - 2}, {x-3, y - 3},  {x-4, y - 4}};
                if(x>=5&&y>=5)
                    p.push_back({x-5,y-5});
                else p.push_back({-1,-1});
                region.push_back(p);
            }
            if(x>=4&&y<=10) {
                //取右上到左下
                vector<Point> p = { {x, y}, {x-1, y + 1},  {x-2, y + 2}, {x-3, y + 3},  {x-4, y + 4}};
                if(x>=5&&y<=9)
                    p.push_back({x-5,y+5});
                else p.push_back({-1,-1});
                region.push_back(p);
            }
            if(x<=10&&y>=4) {
                //取右上到左下
                vector<Point> p = { {x, y}, {x+1, y - 1},  {x+2, y - 2}, {x+3, y - 3},  {x+4, y - 4}};
                if(x<=9&&y>=5)
                    p.push_back({x+5,y-5});
                else p.push_back({-1,-1});
                region.push_back(p);
            }
            //endregion
            for (auto &item: region) {
                CheckWin(item);
                CheckH4(item);
                CheckM4(item);
                CheckH3(item);
                CheckM2(item);
            }
            //从region中取两个点，检索双活四，双活三，双活二
            if(region.size()>=2){
                for(int i=0;i<region.size()-1;i++)
                    for(int j=i+1;j<region.size();j++){
                        CheckCubeAll({region[i],region[j]});
                    }
            }
        }
    }
    return RankModel(result);
}
string ChessModel::GetModelName(ModelType type){
    switch(type){
        case ModelType::Win:
            return "Win";
        case ModelType::H4:
            return "H4";
        case ModelType::Cube4:
            return "Cube4";
        case ModelType::Cube3:
            return "Cube3";
        case ModelType::Cube2:
            return "Cube2";
        case ModelType::M4:
            return "M4";
        case ModelType::H3:
            return "H3";
        case ModelType::M2:
            return "M2";
        default:
            return "Unknown";
    }
}
