#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;
/*
 * 幻想过在c++上直接上json/xml/ini的，但是得手搓一个解析器
 * 就不再本渣能力范围了(这要是C# 分分钟的事情...)
 * 于是直接粗暴地读写文件 能创一个是一个..
 *
 * */
vector<string> IdList;//index
vector<string> DataList;//data
const char spilt='|';
string DataBuilder(string id,string name,string count) {
    return id+spilt+name+spilt+count;
}
string ItemString(vector<string> result){
    return "货号:"+result[0]+" 名称:"+result[1]+" 数量:"+result[2]+"\r\n";
}
bool isIDExist(string id){
    for(int i=0;i<IdList.size();i++){
        if(IdList[i]==id)return true;
    }
    return false;
}

string path="data.tw";
vector<string> stringSplit(const std::string& strIn, char delim) {
    char* str = const_cast<char*>(strIn.c_str());
    string s;
    s.append(1, delim);
    vector<string> elems;
    char* splitted = strtok(str, s.c_str());
    while (splitted != NULL) {
        elems.push_back(std::string(splitted));
        splitted = strtok(NULL, s.c_str());
    }
    return elems;
}

void IndexList(){
    DataList.clear();
    IdList.clear();
    fstream fs;
    fs.open(path,ios::in);
    if(fs.is_open()){
        string str;
        while(getline(fs,str)){
            //执行strtok会将spilt->\0..
            DataList.push_back(str);
            vector data=stringSplit(str,spilt);
            IdList.push_back(data[0]);
        }
        fs.close();
    }
}
void ShowList(){
    for(int i=0;i<DataList.size();i++)
        cout<<ItemString(stringSplit(DataList[i],spilt))<<endl;
}
void WriteLine(){
    cout<<"输入货号:"<<endl;
    string id;
    cin>>id;
    if(isIDExist(id)){
        cout<<"This id has existed!"<<endl;
        return;
    }
    cout<<"输入名称:"<<endl;
    string name;
    cin>>name;
    cout<<"数量:"<<endl;
    string count;
    cin>>count;

    fstream fs;
    fs.open(path,ios::app);
    if(fs.is_open()){
        fs<<DataBuilder(id,name,count)<<"\r\n";
        fs.close();
    }
}
//使用复写的垃圾方法emmm..
void PopOut(){
    cout<<"输入货号:"<<endl;
    string id;
    cin>>id;

    string filedata;
    fstream fs;
    fs.open(path,ios::in);
    bool found=false;
    vector<string> result;
    if(fs.is_open()){
        string str;
        while(getline(fs,str)){
            vector data=stringSplit(str,'|');
            if(data[0]!=id)
                filedata+= DataBuilder(data[0],data[1],data[2])+"\r\n";
            else {
                found=true;
                result=data;
            }
        }
        fs.close();
    }
    if(found) {
        fstream writer;
        writer.open(path, ios::out);
        if (writer.is_open()) {
            writer << filedata;
            writer.close();
        }
        cout<<"已出库： "<<ItemString(result)<<endl;
    }else cout<<"??找不到此货号..\r\n"<<endl;
}

int main() {
    //create data file..
    ofstream fs;
    fs.open(path,ios::app);
    if(fs.is_open())fs.close();
    else cout<<"failed to access file."<<endl;

    for(;;) {
    IndexList();
    string text = "1.显示存货列表\r\n"
                  "2.入库\r\n"
                  "3.出库\r\n"
                  "4.退出程序\r\n";
    cout << text << endl;
    int ord;
    scanf("%d", &ord);

    switch (ord) {
        case 1:
            ShowList();
            break;
        case 2:
            WriteLine();
            break;
        case 3:
            PopOut();
            break;
        case 4:
            exit(0);
    }
    system("pause");
    system("cls");
}
    return 0;
}