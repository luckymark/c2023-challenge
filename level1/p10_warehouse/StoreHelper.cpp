//
// Created by cz241 on 9/28/2023.
//

#include "StoreHelper.h"

vector<Item> DataList;

void CreateDataFile(){
    //create data file..
    ofstream fs;
    fs.open(path,ios::app);
    if(fs.is_open())fs.close();
    else cout<<"failed to access file."<<endl;
}

vector<string> stringSplit(const string& strIn, char delim) {
    char* str = const_cast<char*>(strIn.c_str());
    string s;
    s.append(1, delim);
    vector<string> elems;
    char* splitted = strtok(str, s.c_str());
    while (splitted != NULL) {
        elems.push_back(string(splitted));
        splitted = strtok(NULL, s.c_str());
    }
    return elems;
}

string DataBuilder(Item item) {
    return item.id+spilt+item.name+spilt+item.count;
}

string ItemString(Item item){
    return "货号:"+item.id+" 名称:"+item.name+" 数量:"+item.count+"\r\n";
}

bool isIDExist(string id,vector<Item>::iterator& ref){
    for(ref=DataList.begin();ref!=DataList.end();ref++)
        if(ref->id==id)
            return true;
    return false;
}

void IndexList(){
    fstream fs;
    fs.open(path,ios::in);
    if(fs.is_open()){
        string str;
        while(getline(fs,str)){
            vector data=stringSplit(str,spilt);
            DataList.push_back(Item{data[0],data[1],data[2]});
        }
        fs.close();
    }
}

void ShowList(){
    for(Item i:DataList)
        cout<<ItemString(i)<<endl;
}

void WriteLine(){
    cout<<"输入货号:"<<endl;
    string id;
    cin>>id;
    vector<Item>::iterator item;
    if(isIDExist(id,item)){
        cout<<"This id has existed!"<<endl;
        cout<<ItemString(*item)<<endl;
        return;
    }
    cout<<"输入名称:"<<endl;
    string name;
    cin>>name;
    cout<<"数量:"<<endl;
    string count;
    cin>>count;

    Item newItem{id,name,count};
    DataList.push_back(newItem);
}

void PopOut(){
    ShowList();
    cout<<"输入货号:"<<endl;
    string id;
    cin>>id;
    vector<Item>::iterator item;
    if(isIDExist(id,item)) {
        cout<<"已出库： "<<ItemString(*item)<<endl;
        DataList.erase(item);
    }
    else cout<<"??找不到此货号..\n"<<endl;
}

void SaveDataToFile(){
    string filedata;
    for(Item i : DataList)
        filedata+= DataBuilder(i)+"\n";

    fstream writer;
    writer.open(path, ios::out);
    if (writer.is_open()) {
        writer << filedata;
        writer.close();
    }
}