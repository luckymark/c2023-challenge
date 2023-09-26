#include "NodeList.h"
#include <iostream>
using namespace std;

int main(){
    auto* p=new Node<int>();
    NodeList<int> t;
    cout<<p->NextNode<<endl;
    cout<<t.FirstNode<<endl;

    NodeList<int> list;
    Node<int>* now=list.FirstNode;
    for(int i=1;i<=10;i++){
        auto* node=new Node<int>();
        node->Value=i;
        if(!now)
            list.FirstNode = node;
        else now->NextNode=node;
        now=node;
    }
    for(int i=1;i<=10;i++){
        auto* node =new Node<int>();
        node->Value=i;
        now->NextNode=node;
        now=node;
    }
    list.PrintList();
    list=list.Reverse();
    list.PrintList();

    int i=5;
    vector result=list.FindNode(i);
    for(int d:result)
        cout<<d<<"\t";
    cout<<endl;
    i=0;
    vector result1=list.FindNode(i);
    for(int d:result1)
        cout<<d<<"\t";
    cout<<endl;
    return 0;
}