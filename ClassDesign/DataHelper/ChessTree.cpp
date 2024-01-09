//
// Created by cz241 on 11/21/2023.
//

#include <iostream>
#include "ChessTree.h"
#include "../Player/IPlayer.h"
#include "ModelChecker.h"

void ChessTree::GenerateTree(int depth, PieceStatus player) {
    cout<<"Generating Tree..."<<endl;
    this->maxDepth=depth;
    this->root=new ChessNode();
    this->root->map=&MapData;
    this->root->score=this->Evaluator(player, MapData);
    this->root->depth=0;
    this->root->parent= nullptr;
    stack<ChessNode*> parents;
    parents.push(this->root);
    //第一层节点由对手下产生
    PieceStatus nodePlayer=Opponent(player);
    this->root->whose=nodePlayer;
    for(int i=1;i<depth;i++){
        //第i+1层节点，由CheckModel给出我方可走的点，预判对手可走点
        //对每个点，生成一个节点，计算分数
        nodePlayer=Opponent(nodePlayer);
        ChessNode* parent;
        while(!parents.empty()) {
            //上一层的节点作为父节点(多个)
            parent = parents.top();
            vector<Point> avaPoints= this->AvaPointGenerator(*parent->map);
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
    cout<<"Tree Generated!"<<endl;
}
void ChessTree::ShowTree()const {
    auto root=this->root;
    stack<ChessNode*> parents;
    parents.push(root);
    for(int i=0;i<this->maxDepth;i++) {
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
ChessNode* ChessTree::AlphaBetaSearch()const{
    cout<<"Searching Started."<<endl;
    ChessNode* result;
    auto root=this->root;
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
            int s = this->Evaluator(child->whose, *child->map);
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
      ShowTree();
    cout<<"Searching Finished."<<endl;
    return result;
}