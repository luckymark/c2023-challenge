#include "NodeList.h"
#include <iostream>
using namespace std;

template<class T>
void SearchIndex(NodeList<T> list,T value){
    bool ref;
    vector<SearchItem<T>> result=list.FindNode(value,ref);
    if(ref) {
        cout << "Find " << value << " : ";
        for (SearchItem<T> item: result) {
            cout << " " << item.index;
        }
        cout << endl;
    }else{
        cout<<value<<" is not found."<<endl;
    }
}

int main(){
    NodeList<int> list;

    for(int i=1;i<=10;i++){
        list.Append(i);
        list.Append(i);
    }
    list.PrintList();

    list=list.Reverse();
    list.PrintList();

    SearchIndex(list,5);
    list.Delete(5);
    SearchIndex(list,5);

    list.PrintList();
    return 0;
}