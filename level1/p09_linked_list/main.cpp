#include <iostream>
#include <vector>
using namespace std;

template<class T>
class Node{
public:
    T Value;
    Node<T> *NextNode;
};

template<class T>
class NodeList{
public:
    Node<T>* FirstNode=nullptr;
    void PrintList(){
        Node<T>* now = FirstNode;
        while(now){
            cout<<now->Value<<"\t";
            now=now->NextNode;
        }
        cout<<endl;
    }

    NodeList<T> Reverse(){
        NodeList<T> ReversedList;
        ReversedList.FirstNode=new Node<T>();
        ReversedList.FirstNode->Value=FirstNode->Value;

        if(!FirstNode->NextNode)
            return ReversedList;

        Node<T>* now=FirstNode->NextNode;
        while(now){
            Node<T>* temp=ReversedList.FirstNode;
            Node<T>* copyNext=new Node<T>();
            copyNext->Value=now->Value;
            copyNext->NextNode=temp;

            ReversedList.FirstNode=copyNext;
            now=now->NextNode;
        }
        return ReversedList;
    }

    vector<int> FindNode(T& item){
        Node<T>* now=FirstNode;
        vector<int> result;
        int index=0;
        bool hasFound=false;
        while (now){
            if(now->Value==item) {
                result.push_back(index);
                hasFound=true;
            }
            now=now->NextNode;
            index++;
        }
        if(!hasFound)result.push_back(-1);
        return result;
    }
};

int main(){
    NodeList<int> list;
    Node<int>* now=list.FirstNode;
    for(int i=1;i<=10;i++){
        Node<int>* node=new Node<int>();
        node->Value=i;
        if(!now)
            list.FirstNode = node;
        else now->NextNode=node;
        now=node;
    }
    for(int i=1;i<=10;i++){
        Node<int>* node =new Node<int>();
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