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
void ShowList(){
    fstream fs;
    fs.open(path,ios::in);
    if(fs.is_open()){
        string str;
        while(getline(fs,str)){
            vector data=stringSplit(str,'|');
            cout<<"货号:"+data[0]+" 名称:"+data[1]+" 数量:"+data[2]+"\r\n"<<endl;
        }
        fs.close();
    }
}
void WriteLine(){
    cout<<"输入货号:"<<endl;
    string id;
    cin>>id;
    cout<<"输入名称:"<<endl;
    string name;
    cin>>name;
    cout<<"数量:"<<endl;
    string count;
    cin>>count;

    fstream fs;
    fs.open(path,ios::app);
    if(fs.is_open()){
        fs<<id+"|"+name+"|"+count<<"\r\n";
        fs.close();
    }
}
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
                filedata+=data[0]+"|"+data[1]+"|"+data[2]+"\r\n";
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
        cout<<"已出库： 货号:"+result[0]+" 名称:"+result[1]+" 数量:"+result[2]+"\r\n"<<endl;
    }else cout<<"??找不到此货号..\r\n"<<endl;
}

int main() {
    //先创建库存文件 如果不存在
    ofstream fs;
    fs.open(path, ios::app);
    if (!fs)  //true则说明文件打开出错
    cout << "failed to create file.." << endl;
    else fs.close();
for(;;) {
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