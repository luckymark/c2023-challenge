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
class SearchItem{
public:
    int index;
    Node<T> *last;
    Node<T> * ptr;
};

template<class T>
class NodeList {
public:
    Node<T> *FirstNode = nullptr;
    Node<T> *LastNode=nullptr;
    void PrintList(){
        Node<T>* now = FirstNode;
        while(now){
            cout<<now->Value<<"\t";
            now=now->NextNode;
        }
        cout<<endl;
    }
    void Append(T value){
        auto item=new Node<T>();
        item->Value=value;
        if(FirstNode== nullptr){
            LastNode=FirstNode=item;
        }else{
            LastNode->NextNode=item;
            LastNode=item;
        }
    }
    void Insert(T value){
        auto item=new Node<T>();
        item->Value=value;
        if(FirstNode== nullptr){
            LastNode=FirstNode=item;
        }else{
            item->NextNode=FirstNode;
            FirstNode=item;
        }
    }
    void Delete(T value){
        bool hasFound;
        auto result= FindNode(value,hasFound);
        while(hasFound){
            SearchItem<T> item=result[0];
            item.last->NextNode=item.ptr->NextNode;
            delete item.ptr;
            result= FindNode(value,hasFound);
        }
    }
    NodeList<T> Reverse(){
        NodeList<T> ReversedList;
        auto now=FirstNode;
        while(now){
            ReversedList.Insert(now->Value);
            now=now->NextNode;
        }
        return ReversedList;
    }
    vector<SearchItem<T>> FindNode(T& item,bool& hasFound){
        Node<T> *now=FirstNode;
        Node<T> *last;
        vector<SearchItem<T>> result;
        int index=0;
        hasFound=false;
        while (now){
            if(now->Value==item) {
                result.push_back(SearchItem<T>{index, last, now});
                hasFound=true;
            }
            last=now;
            now=now->NextNode;
            index++;
        }
        return result;
    }

};