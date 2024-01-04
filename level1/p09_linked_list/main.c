#include "list.h"
#include <stdio.h>

int main()
{
	system("chcp 65001");
	SLTNode* plist = NULL;
	SListPushFront(&plist, 5);
	SListPushFront(&plist, 3);
	SListPushFront(&plist, 5);
	SListPushFront(&plist, 1);
	SListPushFront(&plist, 5);
	SListPushFront(&plist, 3);
	SListPushFront(&plist, 2);
	SListPushFront(&plist, 1);
	SListPrint(plist);
	ReverseList(&plist);
	SListPrint(plist);
	int x = 5;
	int n = SListFind(plist,x);
	if(n != -1)
	{
		printf("第一个值为%d的节点序号是：%d\n",x,n);
	}
	else
	{
		printf("不存在值为%d的节点！",x);
	}
	n = SListFindNext(plist,5,SListFind(plist,5));
	if(n != -1)
	{
		printf("下一个值为%d的节点序号是：%d\n",x,n);
	}
	else
	{
		printf("不存在下一个节点！");
	}
	SListDestroy(&plist);
	return 0;
}