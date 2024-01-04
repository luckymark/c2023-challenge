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

void SListPrint(SLTNode* phead);
void SListPushBack(SLTNode** pphead, SListType x);
void SListPushFront(SLTNode** pphead, SListType x);
void SListPopBack(SLTNode** pphead);
void SListPopFront(SLTNode** pphead);
//找到值相同当前第一个节点，返回他的地址
SLTNode* SListFind(SLTNode* phead, SListType x);
//默认在pos位置之后插入一个节点
void SListInsertAfter(SLTNode* pos, SListType x);
//默认在pos位置之前插入一个节点
void SListInsert(SLTNode** pphead, SLTNode* pos, SListType x);
//擦除某个节点
void SListErase(SLTNode** pphead, SLTNode* pos);
void SListEraseAfter(SLTNode* pos);
void SListDestroy(SLTNode** pphead);

//双重指针 改变实参的地址
SLTNode* ReverseList(SLTNode** head);
//单一指针，原本head地址不变，所以无法直接print
SLTNode* ReverseList_2(SLTNode* head);
//删除某一值
SLTNode* RemoveElement(SLTNode* phead, SListType value);
//找寻链表中间节点
SLTNode* MiddleNode(SLTNode* head);
//列表中倒数第k个节点
SLTNode* FindKthToTail(SLTNode* head, int k);
//合并两个链表
SLTNode * MergeTwoLists(SLTNode * l1,SLTNode* l2);