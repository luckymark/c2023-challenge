#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int SListType;
typedef struct SListNode
{
	SListType data;
	struct SListNode* next;
} SLTNode;
//尾部插入
void SListPushBack(SLTNode** pphead, SListType x);
//头部插入
void SListPushFront(SLTNode** pphead, SListType x);
//打印
void SListPrint(SLTNode* phead);
//双重指针 改变实参的地址
SLTNode* ReverseList(SLTNode** head);
//找到值相同当前第一个节点，返回他的地址
int SListFind(SLTNode* phead, SListType x);
//找到值相同当前节点的下一个节点，返回他的地址
int SListFindNext(SLTNode* phead, SListType x,int n);
//销毁
void SListDestroy(SLTNode** pphead);
