#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include "WareHouse.h"
using namespace std;

int main()
{
    char input;
    int model,vary;
    init();
    while(1)
    {
        input=getch();
        switch(input)
        {
            case '1':
                TurnList();
                break;
            case '2':
                clear();
                printf("请先输入型号,后输入数量,以空格断开:\n");
                scanf("%d%d",&model,&vary);
                add(model,vary);
                break;
            case '3':
                clear();
                printf("请先输入型号,后输入数量,以空格断开:\n");
                scanf("%d%d",&model,&vary);
                add(model,-vary);
                break;
            case '4':
                return 0;
        }
    }
    return 0;
}