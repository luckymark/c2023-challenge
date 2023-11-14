#include "s_list.h"

void TestSList1()
{
	SLTNode* plist = NULL;
	SListPushBack(&plist, 1);
	SListPushBack(&plist, 2);
	SListPushBack(&plist, 3);
	SListPushBack(&plist, 4);
	SListPrint(plist);

	SListPushFront(&plist, 1);
	SListPushFront(&plist, 2);
	SListPushFront(&plist, 3);
	SListPushFront(&plist, 4);
	SListPrint(plist);
}

void TestSList2()
{
	SLTNode* plist = NULL;
	SListPushFront(&plist, 1);
	SListPushFront(&plist, 2);
	SListPushFront(&plist, 3);
	SListPushFront(&plist, 4);

	SListPopBack(&plist);
	SListPopBack(&plist);
	SListPopFront(&plist);
	SListPopBack(&plist);
	SListPrint(plist);
}

void TestSList3()
{
	SLTNode* plist = NULL;
	SListPushFront(&plist, 1);
	SListPushFront(&plist, 2);
	SListPushFront(&plist, 3);
	SListPushFront(&plist, 4);
	SListPushFront(&plist, 1);
	SListPushFront(&plist, 2);
	SListPushFront(&plist, 3);
	SListPushFront(&plist, 4);
	SListPrint(plist);
	SLTNode* pos = SListFind(plist, 2);
	int n = 1;
	while (pos)
	{
		printf("第%d个pos节点是: %p->%d\n", ++n, pos, pos->data);
		pos = SListFind(pos->next, 2);
	}
	//修改
	pos = SListFind(plist, 2);
	if (pos)
	{
		pos->data = 20;
	}
	SListPrint(plist);
}

void TestSList4()
{
	SLTNode* plist = NULL;
	SListPushFront(&plist, 1);
	SListPushFront(&plist, 2);
	SListPushFront(&plist, 3);
	SListPushFront(&plist, 4);
	SLTNode* pos = SListFind(plist, 4);
	SListInsert(&plist, pos, 20);
	SListPrint(plist);
	SLTNode* pos1 = SListFind(plist, 20);
	SListErase(&plist, pos1);
	SListPrint(plist);
}

void TestSList5()
{
	SLTNode* plist = NULL;
	SListPushFront(&plist, 1);
	SListPushFront(&plist, 2);
	SListPushFront(&plist, 3);
	SListPushFront(&plist, 4);
	SLTNode* pos = SListFind(plist, 1);
	SListInsertAfter(pos, 10);
	RemoveElement(plist, 1);
	SListPrint(plist);
	SListDestroy(&plist);
	SListPrint(plist);
}

void TestSList6()
{
	SLTNode* plist = NULL;
	SListPushFront(&plist, 1);
	SListPushFront(&plist, 2);
	SListPushFront(&plist, 3);
	SListPushFront(&plist, 4);
	SListPrint(plist);
	SListPrint(ReverseList(&plist));
	SListPrint(plist);
	SListDestroy(&plist);

	SListPushFront(&plist, 1);
	SListPushFront(&plist, 2);
	SListPushFront(&plist, 3);
	SListPushFront(&plist, 4);
	SListPrint(plist);

	SListPrint(ReverseList_2(plist));
	SListPrint(plist);

	SListDestroy(&plist);
}

void TestSList7()
{
	SLTNode* plist = NULL;
	SListPushFront(&plist, 4);
	SListPushFront(&plist, 3);
	SListPushFront(&plist, 2);
	SListPushFront(&plist, 1);

	SLTNode* pos = MiddleNode(plist);
	if (pos)
		printf("中间节点为:%p -> %d\n", pos, pos->data);
	else
		printf("中间节点为:NULL\n");

	int k = 1;
	SLTNode* pos2 = FindKthToTail(plist, k);
	if (pos2)
		printf("倒数第%d个节点为节点为:%p -> %d\n", k, pos2, pos2->data);
	else
		printf("倒数第%d个节点不存在\n", k);

	SLTNode* plist2 = NULL;
	SListPushFront(&plist2, 2);
	SListPushFront(&plist2, 2);
	SListPushFront(&plist2, 2);
	SListPushFront(&plist2, 1);


	SListPrint(MergeTwoLists(plist,plist2));
}
int main()
{
	system("chcp 65001");
	TestSList7();
	return 0;
}