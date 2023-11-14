#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int SLDataType;

typedef struct SeqList
{
    SLDataType* a;
    int size;//表明数组中储存了多少个数据
    int capacity;//数组实际的空间容量
}SL;
void SeqListPrint(SL* ps);
void SeqListInit(SL* ps);
void SeqListDestroy(SL* ps);
void SeqListCheckCapacity(SL* sl);
void SeqListPushBack(SL* ps,SLDataType x);
void SeqListPopBack(SL* ps);
void SeqListPushFront(SL* ps,SLDataType x);
void SeqListPopFront(SL* ps);

int SeqListFind(SL* ps, SLDataType x);