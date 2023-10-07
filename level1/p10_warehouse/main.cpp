#include "StoreHelper.h"
/*
 * 幻想过在c++上直接上json/xml/ini的，但是得手搓一个解析器
 * 就不再本渣能力范围了(这要是C# 分分钟的事情...)
 * 于是直接粗暴地读写文件 能创一个是一个..
 *
 * */

const char spilt='|';
const string path="data.tw";

int main() {
    CreateDataFile();
    IndexList();

    for(;;) {
    string text = "1.显示存货列表\n"
                  "2.入库\n"
                  "3.出库\n"
                  "4.保存并退出程序\n";
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
            SaveDataToFile();
            exit(0);
    }
    system("pause");
    system("cls");
}
    return 0;
}