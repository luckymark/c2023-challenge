#include "list.h"

SLTNode* CreatListNode(SListType x)
{
	SLTNode* newNode = (SLTNode*)malloc(sizeof(SLTNode));
	if (newNode == NULL)
	{
		printf("melloc failed!");
		exit(-1);
	}
	newNode->data = x;
	newNode->next = NULL;

	return newNode;
}

void SListPushBack(SLTNode** pphead, SListType x)
{
	assert(pphead);
	SLTNode* newNode = CreatListNode(x);

	if (*pphead == NULL)
	{
		*pphead = newNode;
	}
	else
	{
		//找到尾节点
		SLTNode* tail = *pphead;
		while (tail->next != NULL)
		{
			tail = tail->next;
		}

		tail->next = newNode;
	}
}

void SListPushFront(SLTNode** pphead, SListType x)
{
	assert(pphead);
	SLTNode* newnode = CreatListNode(x);

	newnode->next = *pphead;
	*pphead = newnode;
}

void SListPrint(SLTNode* phead)
{
	SLTNode* cur = phead;
	while (cur != NULL)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}

SLTNode* ReverseList(SLTNode** head)
{

	if (head == NULL)
		return NULL;
	SLTNode* n1, * n2, * n3;
	n1 = NULL;
	n2 = *head;
	n3 = (*head)->next;
	while (n2)
	{
		n2->next = n1;
		n1 = n2;
		n2 = n3;
		if (n3)
			n3 = n3->next;
	}
	*head = n1;
	return *head;
}

int SListFind(SLTNode* phead, SListType x)
{
	assert(phead);
	SLTNode* cur = phead;
	int i = 0;
	while (cur)
	{
		i++;
		if (x == cur->data)
		{
			return i;
		}
		else
		{
			cur = cur->next;
		}
	}
	return -1;
}

int SListFindNext(SLTNode* phead, SListType x,int n)
{
	assert(phead);
	SLTNode* cur = phead;
	int i = n;
	while (i--)
	{
		cur =cur->next;
	}
	while (cur)
	{
		n++;
		if (x == cur->data)
		{
			return n;
		}
		else
		{
			cur = cur->next;
		}
	}
	return -1;
}

void SListDestroy(SLTNode** pphead)
{
	assert(pphead);
	while (*pphead)
	{
		SLTNode* next = (*pphead)->next;
		free(*pphead);
		*pphead = next;
	}
	*pphead = NULL;
}