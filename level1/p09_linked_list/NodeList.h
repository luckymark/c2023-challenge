#pragma once
#include <vector>
#include <iostream>
using namespace std;

/*
 * 使用自定义模板类时，编译出现错误：
 * error C2955: 'XXXX' : use of class template requires template argumen
 * 如果是模板类，则该类的所有函数（不管有没用到模版参数）的实现都必须放在头文件中。
 */

template<class T>
class Node{
public:
    T Value;
    Node<T>* NextNode;
};

template<class T>
class NodeList {
public:
    Node<T> *FirstNode = nullptr;
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
            auto copyNext=new Node<T>();
            copyNext->Value=now->Value;
            copyNext->NextNode=temp;

            ReversedList.FirstNode=copyNext;
            now=now->NextNode;
        }
        return ReversedList;
    }
    std::vector<int> FindNode(T& item){
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