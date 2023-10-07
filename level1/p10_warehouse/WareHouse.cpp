#include "WareHouse.h"
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>

using namespace std;

map<int,int> store;
HANDLE HdOut;
FILE *file;
bool ListOn=false;

void init()
{
    int WareNum;
    HdOut=GetStdHandle(STD_OUTPUT_HANDLE);
    file=fopen("WareHouse.txt","r");
    if(!file)
    {
        file=fopen("WareHouse.txt","w");
        fprintf(file,"0");
        fclose(file);
        file=fopen("WareHouose.txt","r");
    }
    fscanf(file,"%d",&WareNum);
    for(int i=1;i<=WareNum;++i)
    {
        int model,num;
        fscanf(file,"%d%d",&model,&num);
        store[model]=num;
    }
    fclose(file);
    printf("1-显示存货列表\n2-入库\n3-出库\n4-退出程序\n");
    return;
}
void clear()
{
    system("cls");
    printf("1-显示存货列表\n2-入库\n3-出库\n4-退出程序\n\n");
    return;
}
void move(int x,int y)
{
    COORD pos={x,y};
    SetConsoleCursorPosition(HdOut,pos);
    return;
}
void PrintList()
{
    clear();
    if(store.empty())
    {
        printf("库存为空");
    }
    for(map<int,int>::iterator it=store.begin();it!=store.end();++it)
    {
        printf("Model:%d,Rest:%d\n",it->first,it->second);
    }
    return;
}
void add(int model,int vary)
{
    map<int,int>::iterator it=store.find(model);
    clear();
    if(it==store.end())
    {
        if(vary<=0)
        {
            printf("出库失败,剩余货物不足.");
        }
        else
        {
            printf("出入库成功.");
            store[model]=vary;
        }
    }
    else
    {
        if((it->second+vary)<=0)
        {
            if((it->second+vary)<0)
            {
                printf("出库数量大于剩余数量,已将库存清空.");
            }
            else
            {
                printf("出入库成功.");
            }
            store.erase(it);
        }
        else
        {
            printf("出入库成功.");
            it->second+=vary;
        }
    }
    save();
    printf("\n按任意键继续...");
    getch();
    clear();
    if(ListOn) PrintList();
    return;
}
void save()
{
    file=fopen("WareHouse.txt","w");
    fprintf(file,"%d\n",store.size());
    for(map<int,int>::iterator it=store.begin();it!=store.end();++it)
    {
        fprintf(file,"%d ",it->first);
        fprintf(file,"%d\n",it->second);
    }
    fclose(file);
    return;
}
void TurnList()
{
    if(ListOn)
    {
        clear();
        ListOn=false;
    }
    else
    {
        PrintList();
        ListOn=true;
    }
    return;
}