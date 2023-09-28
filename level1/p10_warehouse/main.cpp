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