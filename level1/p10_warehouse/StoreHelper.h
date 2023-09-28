//
// Created by cz241 on 9/28/2023.
//

#ifndef C2023_CHALLENGE_STOREHELPER_H
#define C2023_CHALLENGE_STOREHELPER_H
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

struct Item{
public:
    string id,name,count;
};

extern const char spilt;
extern const string path;
//启动时创建库文件 若不存在
void CreateDataFile();
vector<string> stringSplit(const string& strIn, char delim);
string DataBuilder(Item item);
string ItemString(Item item);
bool isIDExist(string id);

void IndexList();
void ShowList();
void WriteLine();
void PopOut();

#endif //C2023_CHALLENGE_STOREHELPER_H
